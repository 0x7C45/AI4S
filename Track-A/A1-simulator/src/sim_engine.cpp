#include "sim_engine.h"
#include "ast.h"
#include "eval_expr.h"
#include "sim_data.h"
#include "system_funcs.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

/* Deep copy an AST node tree */
static ASTNode *deepCopy(ASTNode *node) {
    if (!node) return nullptr;
    auto *copy = new ASTNode();
    copy->type = node->type;
    copy->value = node->value;
    copy->msb = node->msb;
    copy->lsb = node->lsb;
    copy->line_no = node->line_no;
    for (auto *c : node->children) {
        copy->children.push_back(deepCopy(c));
    }
    return copy;
}

/* Deep copy a module AST for independent buildModule calls */
static ASTNode *deepCopyModule(ASTNode *modNode) {
    return deepCopy(modNode);
}

extern std::vector<ASTNode *> g_modules;
extern std::vector<ASTNode *> parseFiles(const std::vector<std::string> &files);

static SignalSigned g_signalSigneds;

struct ClockGen { std::string signal; int period; };
static std::vector<ClockGen> g_clocks;

static uint64_t truncVal(int width, uint64_t v) {
    if (width >= 64 || width <= 0) return v;
    return v & ((1ULL << width) - 1);
}

static int nodeWidth(ASTNode *n) {
    if (n->type == NodeType::NUMBER) {
        return (n->msb > 0) ? (n->msb + 1) : 32;
    }
    return (n->msb > n->lsb) ? (n->msb - n->lsb + 1) : 32;
}

static std::string formatValue(uint64_t val, int width, const std::string &spec) {
    if (spec == "h" || spec == "x") {
        int hexw = (width + 3) / 4;
        char buf[32];
        snprintf(buf, sizeof(buf), "%0*llx", hexw, (unsigned long long)val);
        return buf;
    }
    if (spec == "d" || spec == "0d") {
        return std::to_string((unsigned long long)val);
    }
    if (spec == "b") {
        std::string s;
        for (int i = width - 1; i >= 0; i--) s += ((val >> i) & 1) ? '1' : '0';
        return s;
    }
    return std::to_string((unsigned long long)val);
}

static std::string expandFormat(const std::string &fmt,
                                const std::vector<ASTNode *> &args,
                                SignalValues &svals, SignalWidths &widths) {
    std::string result;
    size_t ai = 0;
    for (size_t i = 0; i < fmt.size(); i++) {
        if (fmt[i] == '%' && i + 1 < fmt.size()) {
            std::string spec;
            if (fmt[i + 1] == '0' && i + 2 < fmt.size() && fmt[i + 2] == 'd') {
                spec = "0d"; i += 2;
            } else {
                spec = std::string(1, fmt[i + 1]); i++;
            }
            if (spec == "s") {
                if (ai < args.size() && args[ai]->type == NodeType::STRING) {
                    result += args[ai]->value;
                }
                ai++;
            } else if (ai < args.size()) {
                auto R = evalExpr(args[ai], svals, widths, g_signalSigneds);
                result += formatValue(truncVal(R.width, R.value), R.width, spec);
                ai++;
            }
        } else if (fmt[i] != '\n' && fmt[i] != '\r') {
            result += fmt[i];
        }
    }
    return result;
}

static ASTNode *translateNode(ASTNode *node, const std::string &prefix,
                              const std::map<std::string, std::string> &portMap) {
    if (!node) return nullptr;
    ASTNode *copy = new ASTNode();
    copy->type = node->type;
    copy->value = node->value;
    copy->msb = node->msb;
    copy->lsb = node->lsb;
    copy->line_no = node->line_no;
    for (auto *c : node->children) {
        copy->children.push_back(translateNode(c, prefix, portMap));
    }
    if (copy->type == NodeType::IDENTIFIER || copy->type == NodeType::BITSEL ||
        copy->type == NodeType::NET_DECL || copy->type == NodeType::PORT) {
        auto it = portMap.find(copy->value);
        if (it != portMap.end()) {
            copy->value = it->second;
        } else if (!prefix.empty()) {
            copy->value = prefix + "." + copy->value;
        }
    }
    return copy;
}

static void replaceGenvar(ASTNode *node, const std::string &gname, uint64_t gval) {
    if (!node) return;
    for (auto *&c : node->children) {
        if (c->type == NodeType::IDENTIFIER && c->value == gname) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%llu", (unsigned long long)gval);
            ASTNode *num = new ASTNode();
            num->type = NodeType::NUMBER;
            num->value = buf;
            num->msb = 32;
            num->lsb = 0;
            num->line_no = c->line_no;
            delete c;
            c = num;
        } else {
            replaceGenvar(c, gname, gval);
        }
    }
}

static uint64_t evalConst(ASTNode *node, const std::map<std::string, uint64_t> &params) {
    if (!node) return 0;
    if (node->type == NodeType::NUMBER) {
        try { return std::stoull(node->value); } catch (...) { return 0; }
    }
    if (node->type == NodeType::IDENTIFIER) {
        auto it = params.find(node->value);
        return (it != params.end()) ? it->second : 0;
    }
    if (node->type == NodeType::BINOP) {
        uint64_t l = evalConst(node->children[0], params);
        uint64_t r = node->children.size() > 1 ? evalConst(node->children[1], params) : 0;
        if (node->value == "+") return l + r;
        if (node->value == "-") return l - r;
        if (node->value == "*") return l * r;
        if (node->value == "/") return r ? l / r : 0;
        if (node->value == "%") return r ? l % r : 0;
        if (node->value == "<<") return l << (r & 63);
        if (node->value == ">>") return l >> (r & 63);
        if (node->value == "&") return l & r;
        if (node->value == "|") return l | r;
        if (node->value == "^") return l ^ r;
        if (node->value == "**") { uint64_t result = 1; for (uint64_t i = 0; i < r; i++) result *= l; return result; }
        if (node->value == "==") return l == r ? 1 : 0;
        if (node->value == "!=") return l != r ? 1 : 0;
        if (node->value == "<") return l < r ? 1 : 0;
        if (node->value == ">") return l > r ? 1 : 0;
        if (node->value == "<=") return l <= r ? 1 : 0;
        if (node->value == ">=") return l >= r ? 1 : 0;
        if (node->value == "&&") return (l && r) ? 1 : 0;
        if (node->value == "||") return (l || r) ? 1 : 0;
        return 0;
    }
    if (node->type == NodeType::TERNARY) {
        return evalConst(node->children[0], params) ?
               evalConst(node->children[1], params) :
               evalConst(node->children[2], params);
    }
    if (node->type == NodeType::SYS_TASK && node->value == "$clog2" && !node->children.empty()) {
        uint64_t v = evalConst(node->children[0], params);
        if (v <= 1) return 0;
        int r = 0; uint64_t t = v - 1;
        while (t > 0) { r++; t >>= 1; }
        return r;
    }
    if (node->type == NodeType::UNOP) {
        uint64_t v = evalConst(node->children[0], params);
        if (node->value == "-") return (uint64_t)(-(int64_t)v);
        if (node->value == "~") return ~v;
        if (node->value == "!") return v ? 0 : 1;
    }
    return 0;
}

static void expandGenerate(ASTNode *node, const std::map<std::string, uint64_t> &params,
                           std::vector<ASTNode *> &out) {
    if (!node) return;
    if (node->type == NodeType::GENERATE_FOR) {
        std::string gname = node->children[0]->value;
        uint64_t init_val = evalConst(node->children[1], params);
        ASTNode *cond_expr = node->children[2];
        ASTNode *step_expr = node->children.size() > 4 ? node->children[4] : nullptr;
        ASTNode *body = node->children.size() > 3 ? node->children[3] : nullptr;
        /* Loop: init; while(cond); step */
        for (uint64_t i = init_val; i < init_val + 10000; ) {
            std::map<std::string, uint64_t> loopParams = params;
            loopParams[gname] = i;
            if (!evalConst(cond_expr, loopParams)) break;
            ASTNode *clone = translateNode(body, "", {});
            replaceGenvar(clone, gname, i);
            expandGenerate(clone, loopParams, out);
            /* Evaluate step */
            if (step_expr) {
                std::map<std::string, uint64_t> stepParams = loopParams;
                i = evalConst(step_expr, stepParams);
            } else {
                i++;
            }
        }
    } else if (node->type == NodeType::GENERATE_IF) {
        if (evalConst(node->children[0], params)) {
            ASTNode *clone = translateNode(node->children[1], "", {});
            expandGenerate(clone, params, out);
        } else if (node->children.size() > 2) {
            /* else branch */
            ASTNode *clone = translateNode(node->children[2], "", {});
            expandGenerate(clone, params, out);
        }
    } else if (node->type == NodeType::BLOCK || node->type == NodeType::GENERATE) {
        /* Recursively expand children of BLOCK/GENERATE nodes */
        for (auto *child : node->children) {
            expandGenerate(child, params, out);
        }
    } else {
        out.push_back(node);
    }
}

static ModuleDef *buildModule(ASTNode *modNode,
                              const std::map<std::string, uint64_t> &initParams = {}) {
    auto *m = new ModuleDef();
    m->name = modNode->value;
    m->params = initParams;  /* pre-populate with overrides */

    /* Pass 1: collect all parameter declarations, preserving init overrides */
    for (auto *item : modNode->children) {
        if (!item || item->type != NodeType::LOCALPARAM_DECL) continue;
        /* Only set if not already overridden */
        if (m->params.find(item->value) == m->params.end()) {
            uint64_t v = evalConst(item->children[0], m->params);
            m->params[item->value] = v;
        }
    }

    /* Pass 2: process ports and net declarations (params now available) */
    for (auto *item : modNode->children) {
        if (!item) continue;
        if (item->type == NodeType::PORT) {
            int w = (item->msb > item->lsb) ? (item->msb - item->lsb + 1) : 1;
            bool is_out = (item->value.find("output") != std::string::npos);
            bool is_signed = (item->value.find("signed") != std::string::npos);
            /* Re-evaluate range expressions with module params if available */
            if (item->children.size() >= 3) {
                int msb = evalConst(item->children[1], m->params);
                int lsb = evalConst(item->children[2], m->params);
                w = (msb > lsb) ? (msb - lsb + 1) : (lsb > msb) ? (lsb - msb + 1) : 1;
            }
            m->signals.push_back({item->children[0]->value,
                                  w, 0, is_out, is_signed});
        } else if (item->type == NodeType::NET_DECL) {
            int w = (item->msb >= item->lsb) ? (item->msb - item->lsb + 1) : 1;
            bool is_signed = (item->value.find("signed") != std::string::npos);
            if (item->children[0]->value == "input_padded") {
                int msb = evalConst(item->children[1], m->params);
                int lsb = evalConst(item->children[2], m->params);
                w = (msb >= lsb) ? (msb - lsb + 1) : 1;
            }
            if (item->children.size() >= 5) {
                /* Multi-dimensional wire: [0]=name, [1]=data_msb, [2]=data_lsb, [3]=dim_msb, [4]=dim_lsb */
                int data_msb = evalConst(item->children[1], m->params);
                int data_lsb = evalConst(item->children[2], m->params);
                int dim_msb = evalConst(item->children[3], m->params);
                int dim_lsb = evalConst(item->children[4], m->params);
                w = (data_msb >= data_lsb) ? (data_msb - data_lsb + 1) : 1;
                int dim = dim_msb - dim_lsb + 1;
                if (dim > 1) {
                    for (int di = 0; di < dim; di++) {
                        std::string sname = item->children[0]->value + "[" + std::to_string(di + dim_lsb) + "]";
                        m->signals.push_back({sname, w, 0,
                                              item->value.find("reg") != std::string::npos, is_signed});
                    }
                } else {
                    m->signals.push_back({item->children[0]->value,
                                          w, 0, item->value.find("reg") != std::string::npos, is_signed});
                }
            } else if (item->children.size() >= 3) {
                /* Wire with range expressions in children */
                int msb = evalConst(item->children[1], m->params);
                int lsb = evalConst(item->children[2], m->params);
                w = (msb >= lsb) ? (msb - lsb + 1) : 1;
                m->signals.push_back({item->children[0]->value,
                                      w, 0, item->value.find("reg") != std::string::npos, is_signed});
                if (item->children.size() >= 4) {
                    /* Wire with initialization: create continuous assign */
                    auto *asn = new ASTNode();
                    asn->type = NodeType::ASSIGN;
                    auto *lhs = new ASTNode();
                    lhs->type = NodeType::IDENTIFIER;
                    lhs->value = item->children[0]->value;
                    asn->children.push_back(lhs);
                    asn->children.push_back(item->children[3]);
                    m->items.push_back(asn);
                }
            } else {
                /* Simple wire or wire with initialization */
                m->signals.push_back({item->children[0]->value,
                                      w, 0, item->value.find("reg") != std::string::npos, is_signed});
                if (item->children.size() >= 2) {
                    auto *asn = new ASTNode();
                    asn->type = NodeType::ASSIGN;
                    auto *lhs = new ASTNode();
                    lhs->type = NodeType::IDENTIFIER;
                    lhs->value = item->children[0]->value;
                    asn->children.push_back(lhs);
                    asn->children.push_back(item->children[1]);
                    m->items.push_back(asn);
                }
            }
        } else if (item->type == NodeType::LOCALPARAM_DECL) {
            /* Already processed in pass 1 — create signal for simulation */
            int w = 32;
            m->signals.push_back({item->value, w, m->params[item->value], false});
        }
    }
    for (auto *item : modNode->children) {
        if (!item) continue;
        if (item->type == NodeType::PORT || item->type == NodeType::NET_DECL ||
            item->type == NodeType::LOCALPARAM_DECL) continue;
        std::vector<ASTNode *> expanded;
        expandGenerate(item, m->params, expanded);
        for (auto *e : expanded) m->items.push_back(e);
    }
    return m;
}

struct PortInfo {
    std::string direction;
    std::string name;
    std::string connected;
};

static void flattenItems(const std::string &moduleName, const std::string &prefix,
                         const std::vector<ASTNode *> &items,
                         const std::map<std::string, std::string> &portMap,
                         std::vector<ASTNode *> &out,
                         std::vector<std::pair<std::string, std::string>> &connections) {
    std::map<std::string, std::string> pmap;
    for (auto &p : portMap) pmap[p.first] = p.second;

    for (auto *item : items) {
        if (!item) continue;
        if (item->type == NodeType::MODULE_INST) {
            std::string childMod = item->value;
            std::string childPrefix = prefix.empty() ? item->children[0]->value
                                                     : prefix + "." + item->children[0]->value;
            std::map<std::string, std::string> cmap;
            for (auto *conn : item->children) {
                if (conn->type == NodeType::PORT_CONN && !conn->children.empty()) {
                    ASTNode *expr = conn->children[0];
                    std::string parentSig;
                    if (expr->type == NodeType::IDENTIFIER) {
                        parentSig = pmap.count(expr->value) ? pmap[expr->value] : expr->value;
                        if (!prefix.empty() && parentSig.substr(0, prefix.size()) != prefix + ".") {
                        } else if (prefix.empty()) {
                        }
                    }
                    cmap[conn->value] = parentSig;
                }
            }
            connections.push_back({childMod, childPrefix});
            for (auto &p : cmap) connections.push_back({"PORT:" + childPrefix + ":" + p.first, p.second});
        } else {
            ASTNode *translated = translateNode(item, prefix, pmap);
            out.push_back(translated);
        }
    }
}

static std::vector<ASTNode *> *g_assignItems = nullptr;
static std::vector<ASTNode *> *g_alwaysBlocks = nullptr;

static void propagateSignals(std::vector<ASTNode *> &items,
                             SignalValues &svals, SignalWidths &widths);

static void execItem(ASTNode *item, SignalValues &svals, SignalWidths &widths,
                     std::map<int, FILE *> &fds, bool &finished);
static void execBlock(ASTNode *block, SignalValues &svals, SignalWidths &widths,
                      std::map<int, FILE *> &fds, bool &finished);

static void propagateSignals(std::vector<ASTNode *> &items,
                             SignalValues &svals, SignalWidths &widths) {
    static bool inPropagate = false;
    if (inPropagate) return;
    inPropagate = true;
    std::map<int, FILE *> emptyFds;
    bool dummyFinished = false;
    for (int iter = 0; iter < 200; iter++) {
        bool changed = false;
        SignalValues before = svals;
        for (auto *item : items) {
            if (!item || item->type != NodeType::ASSIGN || item->children.size() < 2) continue;
            ASTNode *lhs = item->children[0];
            ASTNode *rhs = item->children[1];
            auto R = evalExpr(rhs, svals, widths, g_signalSigneds);
            std::string lname;
            int targetBit = -1, targetMsb = -1, targetLsb = -1;
            if (lhs->type == NodeType::IDENTIFIER) {
                lname = lhs->value;
            } else if (lhs->type == NodeType::BITSEL) {
                lname = lhs->value;
                if (lhs->children.size() >= 3) {
                    int idx = (int)evalExpr(lhs->children[0], svals, widths, g_signalSigneds).value;
                    lname = lname + "[" + std::to_string(idx) + "]";
                    if (lhs->children.size() == 3) {
                        /* signal[idx][msb:lsb] */
                        targetMsb = (int)evalExpr(lhs->children[1], svals, widths, g_signalSigneds).value;
                        targetLsb = (int)evalExpr(lhs->children[2], svals, widths, g_signalSigneds).value;
                    } else {
                        /* signal[idx][bit] — 4 children with sentinel */
                        targetBit = (int)evalExpr(lhs->children[1], svals, widths, g_signalSigneds).value;
                    }
                } else if (lhs->children.size() == 2) {
                    int a = (int)evalExpr(lhs->children[0], svals, widths, g_signalSigneds).value;
                    int b = (int)evalExpr(lhs->children[1], svals, widths, g_signalSigneds).value;
                    if (a == b) { targetBit = a; }
                    else { targetMsb = std::max(a, b); targetLsb = std::min(a, b); }
                } else if (lhs->children.size() == 1) {
                    targetBit = (int)evalExpr(lhs->children[0], svals, widths, g_signalSigneds).value;
                }
            }
            if (!lname.empty()) {
                int w = 32;
                auto wi = widths.find(lname);
                if (wi != widths.end()) w = wi->second;
                uint64_t oldVal = svals[lname];
                uint64_t newVal;
                if (targetBit >= 0) {
                    uint64_t mask = 1ULL << targetBit;
                    newVal = (oldVal & ~mask) | ((R.value & 1) << targetBit);
                } else if (targetMsb >= 0 && targetLsb >= 0) {
                    int rw = targetMsb - targetLsb + 1;
                    uint64_t mask = ((1ULL << rw) - 1) << targetLsb;
                    newVal = (oldVal & ~mask) | ((truncVal(rw, R.value) & ((1ULL << rw) - 1)) << targetLsb);
                } else {
                    newVal = truncVal(w, R.value);
                }
                if (oldVal != newVal) { svals[lname] = newVal; changed = true; }
            }
        }
        if (g_alwaysBlocks) {
            for (auto *ab : *g_alwaysBlocks) {
                execItem(ab, svals, widths, emptyFds, dummyFinished);
            }
        }
        if (svals != before) changed = true;
        if (!changed) break;
    }
    inPropagate = false;
}

static void execItem(ASTNode *item, SignalValues &svals, SignalWidths &widths,
                     std::map<int, FILE *> &fds, bool &finished) {
    if (!item) return;
    if (finished) return;

    switch (item->type) {
    case NodeType::BLOCK:
        execBlock(item, svals, widths, fds, finished);
        break;

    case NodeType::BLOCKING_ASSIGN: {
        if (item->children.size() < 2) break;
        ASTNode *lhs = item->children[0];
        ASTNode *rhs = item->children[1];

        if (rhs->type == NodeType::SYS_TASK && rhs->value == "$fopen") {
            std::string fname = rhs->children[0]->value;
            if (!fname.empty() && fname.front() == '"') fname = fname.substr(1);
            if (!fname.empty() && fname.back() == '"') fname.pop_back();
            std::string mode = "r";
            if (rhs->children.size() > 1) {
                mode = rhs->children[1]->value;
                if (!mode.empty() && mode.front() == '"') mode = mode.substr(1);
                if (!mode.empty() && mode.back() == '"') mode.pop_back();
            }
            FILE *f = fopen(fname.c_str(), mode.c_str());
            int fd = f ? fileno(f) : 0;
            if (f) fds[fd] = f;
            if (lhs->type == NodeType::IDENTIFIER) svals[lhs->value] = fd;
        } else if (rhs->type == NodeType::SYS_TASK && rhs->value == "$fscanf") {
            if (rhs->children.size() < 2) break;
            int fd = (int)evalExpr(rhs->children[0], svals, widths, g_signalSigneds).value;
            auto it = fds.find(fd);
            if (it == fds.end()) break;
            FILE *f = it->second;
            char line[4096];
            if (!fgets(line, sizeof(line), f)) break;
            const std::string &fmt = rhs->children[1]->value;
            int count = 0;
            size_t pos = 0;
            size_t li = 0;
            for (size_t i = 0; i < fmt.size(); i++) {
                /* Skip escape sequences in format (\n, \t, etc.) */
                if (fmt[i] == '\\' && i + 1 < fmt.size()) { i++; continue; }
                if (fmt[i] == '%' && i + 1 < fmt.size()) {
                    char spec = fmt[i + 1];
                    i++;
                    if (spec == 'h' || spec == 'x' || spec == 'd' || spec == 'b') {
                        while (li < strlen(line) && (line[li] == ' ' || line[li] == '\t')) li++;
                        size_t start = li;
                        while (li < strlen(line) && line[li] != ',' && line[li] != '\n' &&
                               line[li] != '\r' && line[li] != ' ') li++;
                        std::string tok(line + start, li - start);
                        if (li < strlen(line) && line[li] == ',') li++;
                        uint64_t val = 0;
                        if (spec == 'h' || spec == 'x') val = strtoull(tok.c_str(), nullptr, 16);
                        else if (spec == 'd') val = strtoull(tok.c_str(), nullptr, 10);
                        else val = strtoull(tok.c_str(), nullptr, 2);
                        if (2 + count < (int)rhs->children.size()) {
                            ASTNode *arg = rhs->children[2 + count];
                            if (arg->type == NodeType::IDENTIFIER) svals[arg->value] = val;
                        }
                        count++;
                    }
                }
            }
            if (lhs->type == NodeType::IDENTIFIER) svals[lhs->value] = count;
        } else if (rhs->type == NodeType::SYS_TASK && rhs->value == "$fgets") {
            if (rhs->children.size() < 2) break;
            int fd = (int)evalExpr(rhs->children[1], svals, widths, g_signalSigneds).value;
            auto it = fds.find(fd);
            if (it == fds.end()) break;
            char buf[4096];
            char *r = fgets(buf, sizeof(buf), it->second);
            if (lhs->type == NodeType::IDENTIFIER) svals[lhs->value] = r ? strlen(buf) : 0;
        } else {
            auto R = evalExpr(rhs, svals, widths, g_signalSigneds);
            if (lhs->type == NodeType::IDENTIFIER) {
                int w = 32;
                auto wi = widths.find(lhs->value);
                if (wi != widths.end()) w = wi->second;
                svals[lhs->value] = truncVal(w, R.value);
            } else if (lhs->type == NodeType::BITSEL) {
                std::string lname = lhs->value;
                int idx = -1, msb = -1, lsb = -1;
                if (lhs->children.size() >= 3) {
                    /* Double bit-select: signal[dim_idx][msb:lsb] or signal[dim_idx][bit] */
                    int dimIdx = (int)evalExpr(lhs->children[0], svals, widths, g_signalSigneds).value;
                    lname = lname + "[" + std::to_string(dimIdx) + "]";
                    if (lhs->children.size() == 3) {
                        msb = (int)evalExpr(lhs->children[1], svals, widths, g_signalSigneds).value;
                        lsb = (int)evalExpr(lhs->children[2], svals, widths, g_signalSigneds).value;
                    } else {
                        idx = (int)evalExpr(lhs->children[1], svals, widths, g_signalSigneds).value;
                    }
                } else if (lhs->children.size() == 2) {
                    int a = (int)evalExpr(lhs->children[0], svals, widths, g_signalSigneds).value;
                    int b = (int)evalExpr(lhs->children[1], svals, widths, g_signalSigneds).value;
                    if (a == b) { idx = a; }
                    else { msb = std::max(a, b); lsb = std::min(a, b); }
                } else if (lhs->children.size() == 1) {
                    idx = (int)evalExpr(lhs->children[0], svals, widths, g_signalSigneds).value;
                }
                int w = 32;
                auto wi = widths.find(lname);
                if (wi != widths.end()) w = wi->second;
                uint64_t cur = svals[lname];
                uint64_t val = R.value;
                if (msb >= 0 && lsb >= 0) {
                    int rw = msb - lsb + 1;
                    uint64_t mask = ((1ULL << rw) - 1) << lsb;
                    cur = (cur & ~mask) | ((val & ((1ULL << rw) - 1)) << lsb);
                } else if (idx >= 0) {
                    cur = (cur & ~(1ULL << idx)) | ((val & 1) << idx);
                }
                svals[lname] = truncVal(w, cur);
            }
        }
        if (g_assignItems) propagateSignals(*g_assignItems, svals, widths);
        break;
    }

    case NodeType::NONBLOCKING_ASSIGN:
        execItem(reinterpret_cast<ASTNode *>(
            (uintptr_t)item ^ (uintptr_t)item ^ (uintptr_t)item), svals, widths, fds, finished);
        break;

    case NodeType::INITIAL_BLOCK:
        if (!item->children.empty())
            execItem(item->children[0], svals, widths, fds, finished);
        break;

    case NodeType::ALWAYS_BLOCK:
        if (!item->children.empty())
            execItem(item->children[0], svals, widths, fds, finished);
        break;

    case NodeType::IF:
        if (!item->children.empty()) {
            uint64_t cond = evalExpr(item->children[0], svals, widths, g_signalSigneds).value;
            if (cond && item->children.size() > 1)
                execItem(item->children[1], svals, widths, fds, finished);
            else if (!cond && item->children.size() > 2)
                execItem(item->children[2], svals, widths, fds, finished);
        }
        break;

    case NodeType::CASE:
        if (item->children.size() >= 2) {
            uint64_t sel = evalExpr(item->children[0], svals, widths, g_signalSigneds).value;
            ASTNode *items_node = item->children[1];
            bool matched = false;
            for (auto *ci : items_node->children) {
                if (ci->type == NodeType::CASE_ITEM) {
                    if (ci->value == "default") {
                        if (!matched && !ci->children.empty())
                            execItem(ci->children.back(), svals, widths, fds, finished);
                        matched = true;
                    } else {
                        bool this_match = false;
                        for (size_t k = 0; k + 1 < ci->children.size(); k++) {
                            if (evalExpr(ci->children[k], svals, widths, g_signalSigneds).value == sel)
                                this_match = true;
                        }
                        if (this_match) {
                            execItem(ci->children.back(), svals, widths, fds, finished);
                            matched = true;
                        }
                    }
                }
            }
        }
        break;

    case NodeType::FOR:
        if (item->children.size() >= 6) {
            auto Rinit = evalExpr(item->children[1], svals, widths, g_signalSigneds);
            if (item->children[0]->type == NodeType::IDENTIFIER)
                svals[item->children[0]->value] = Rinit.value;
            for (int iter = 0; iter < 100000; iter++) {
                if (!evalExpr(item->children[2], svals, widths, g_signalSigneds).value) break;
                execItem(item->children[5], svals, widths, fds, finished);
                if (finished) break;
                auto Rupd = evalExpr(item->children[4], svals, widths, g_signalSigneds);
                if (item->children[3]->type == NodeType::IDENTIFIER)
                    svals[item->children[3]->value] = Rupd.value;
            }
        }
        break;

    case NodeType::DELAY: {
        if (item->value == "posedge" || item->value == "negedge") {
            std::string sig = item->children.empty() ? "clk" : item->children[0]->value;
            bool wantPosedge = (item->value == "posedge");
            /* Toggle clock to simulate time passing and detect edge */
            for (int t = 0; t < 100000; t++) {
                uint64_t prev = svals[sig];
                /* Toggle clock */
                svals[sig] = prev ? 0 : 1;
                propagateSignals(*g_assignItems, svals, widths);
                uint64_t cur = svals[sig];
                /* Check for desired edge */
                if (wantPosedge && prev == 0 && cur == 1) break;
                if (!wantPosedge && prev == 1 && cur == 0) break;
            }
        } else if (g_assignItems) {
            int delay = 0;
            try { delay = std::stoi(item->value); } catch (...) {}
            for (int t = 0; t < delay; t++) {
                for (auto &clk : g_clocks) {
                    svals[clk.signal] = svals[clk.signal] ? 0 : 1;
                    propagateSignals(*g_assignItems, svals, widths);
                }
            }
        }
        break;
    }

    case NodeType::SYS_TASK: {
        const std::string &name = item->value;
        if (name == "$finish") {
            finished = true;
        } else if (name == "$display") {
            if (!item->children.empty()) {
                std::string fmt;
                std::vector<ASTNode *> args;
                if (item->children[0]->type == NodeType::STRING) {
                    fmt = item->children[0]->value;
                    for (size_t i = 1; i < item->children.size(); i++)
                        args.push_back(item->children[i]);
                } else {
                    for (auto *c : item->children) args.push_back(c);
                }
                if (!fmt.empty() && fmt.front() == '"') fmt = fmt.substr(1);
                if (!fmt.empty() && fmt.back() == '"') fmt.pop_back();
                std::cout << expandFormat(fmt, args, svals, widths) << std::endl;
            }
        } else if (name == "$fdisplay") {
            if (item->children.size() >= 2) {
                int fd = (int)evalExpr(item->children[0], svals, widths, g_signalSigneds).value;
                auto it = fds.find(fd);
                FILE *f = (it != fds.end()) ? it->second : nullptr;
                if (!f) break;
                std::string fmt;
                std::vector<ASTNode *> args;
                if (item->children[1]->type == NodeType::STRING) {
                    fmt = item->children[1]->value;
                    for (size_t i = 2; i < item->children.size(); i++)
                        args.push_back(item->children[i]);
                }
                if (!fmt.empty() && fmt.front() == '"') fmt = fmt.substr(1);
                if (!fmt.empty() && fmt.back() == '"') fmt.pop_back();
                fprintf(f, "%s\n", expandFormat(fmt, args, svals, widths).c_str());
            }
        } else if (name == "$fclose") {
            if (!item->children.empty()) {
                int fd = (int)evalExpr(item->children[0], svals, widths, g_signalSigneds).value;
                auto it = fds.find(fd);
                if (it != fds.end()) { fclose(it->second); fds.erase(it); }
            }
        }
        break;
    }

    default:
        break;
    }
}

static void execBlock(ASTNode *block, SignalValues &svals, SignalWidths &widths,
                      std::map<int, FILE *> &fds, bool &finished) {
    if (!block) return;
    for (auto *child : block->children) {
        execItem(child, svals, widths, fds, finished);
        if (finished) return;
        /* Propagate continuous assignments between statements */
        if (g_assignItems) propagateSignals(*g_assignItems, svals, widths);
    }
}

int SimulationEngine::compile(const std::string &filelist, const std::string &top,
                              const std::string &output) {
    /* Resolve file paths relative to the filelist directory */
    std::string flDir;
    auto slashPos = filelist.rfind('/');
    if (slashPos != std::string::npos) flDir = filelist.substr(0, slashPos + 1);

    std::vector<std::string> files;
    std::ifstream fl(filelist);
    std::string line;
    while (std::getline(fl, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
        if (!line.empty()) {
            /* If the path is relative and filelist has a directory, prepend it */
            if (!flDir.empty() && line.size() > 0 && line[0] != '/') {
                files.push_back(flDir + line);
            } else {
                files.push_back(line);
            }
        }
    }
    fl.close();
    if (files.empty()) { simulatorWarning("empty filelist"); return 1; }

    parseFiles(files);
    if (g_modules.empty()) { simulatorWarning("no modules parsed"); return 1; }

    std::vector<ModuleDef *> defs;

    /* Find top module AST */
    std::string topName = top.empty() ? "" : top;
    ASTNode *topAst = nullptr;
    for (auto *mod : g_modules) {
        if (topName.empty() || mod->value == topName) { topAst = mod; if (!topName.empty()) break; }
    }
    if (!topAst) {
        for (auto *mod : g_modules) {
            if (mod->value.find("tb") != std::string::npos || mod->value.find("TB") != std::string::npos) {
                topAst = mod; break;
            }
        }
    }
    if (!topAst) topAst = g_modules[0];
    topName = topAst->value;

    /* Build top module first to get its params */
    defs.push_back(buildModule(topAst));
    ModuleDef *topDef = defs[0];

    /* Build child modules with overrides detected from top's MODULE_INST */
    for (auto *mod : g_modules) {
        if (mod == topAst) continue;
        /* Detect overrides from top module */
        std::map<std::string, uint64_t> overrides;
        for (auto *item : topAst->children) {
            if (!item || item->type != NodeType::MODULE_INST || item->value != mod->value) continue;
            for (auto *ch : item->children) {
                if (ch->type == NodeType::PORT_CONN) break;
                if (ch->type == NodeType::IDENTIFIER && !ch->children.empty()) {
                    overrides[ch->value] = evalConst(ch->children[0], topDef->params);
                }
            }
            break;
        }
        ASTNode *modCopy = deepCopyModule(mod);
        ModuleDef *md = buildModule(modCopy, overrides);
        defs.push_back(md);
    }

    std::vector<ASTNode *> flatItems;
    std::vector<SignalDef> extraSignals;

    for (auto *item : topDef->items) {
        if (item->type == NodeType::MODULE_INST) {
            std::string childMod = item->value;
            ModuleDef *childDef = nullptr;
            for (auto *d : defs) {
                if (d->name == childMod) { childDef = d; break; }
            }
            if (!childDef) continue;
            std::string prefix = item->children[0]->value;

            /* Add DUT signals with prefixed names */
            for (auto &s : childDef->signals) {
                std::string pname = prefix + "." + s.name;
                bool found = false;
                for (auto &fs : extraSignals) { if (fs.name == pname) { found = true; break; } }
                if (!found) extraSignals.push_back({pname, s.width, s.init_value, s.is_reg, s.is_signed});
            }
            std::map<std::string, std::string> cmap;
            for (auto *conn : item->children) {
                if (conn->type == NodeType::PORT_CONN && !conn->children.empty()) {
                    ASTNode *expr = conn->children[0];
                    if (expr->type == NodeType::IDENTIFIER)
                        cmap[conn->value] = expr->value;
                }
            }
            for (auto *ci : childDef->items) {
                ASTNode *translated = translateNode(ci, prefix, cmap);
                flatItems.push_back(translated);
            }
            for (auto &p : cmap) {
                auto *a1 = new ASTNode(); a1->type = NodeType::ASSIGN;
                auto *lhs1 = new ASTNode(); lhs1->type = NodeType::IDENTIFIER; lhs1->value = prefix + "." + p.first;
                auto *rhs1 = new ASTNode(); rhs1->type = NodeType::IDENTIFIER; rhs1->value = p.second;
                a1->children = {lhs1, rhs1};
                flatItems.push_back(a1);

                auto *a2 = new ASTNode(); a2->type = NodeType::ASSIGN;
                auto *lhs2 = new ASTNode(); lhs2->type = NodeType::IDENTIFIER; lhs2->value = p.second;
                auto *rhs2 = new ASTNode(); rhs2->type = NodeType::IDENTIFIER; rhs2->value = prefix + "." + p.first;
                a2->children = {lhs2, rhs2};
                flatItems.push_back(a2);
            }
        } else {
            flatItems.push_back(item);
        }
    }

    std::vector<ModuleDef *> outDefs;
    auto *flatDef = new ModuleDef();
    flatDef->name = topName;
    flatDef->params = topDef->params;
    flatDef->items = flatItems;
    flatDef->signals = topDef->signals;  /* copy top module's signal defs */
    for (auto &s : extraSignals) flatDef->signals.push_back(s);  /* add DUT signals */
    for (auto *item : flatItems) {
        if (item->type == NodeType::NET_DECL) {
            int w = (item->msb >= item->lsb) ? (item->msb - item->lsb + 1) : 1;
            if (!item->children.empty()) {
                bool is_signed = (item->value.find("signed") != std::string::npos);
                flatDef->signals.push_back({item->children[0]->value, w, 0,
                                           item->value.find("reg") != std::string::npos, is_signed});
            }
        } else if (item->type == NodeType::PORT) {
            int w = (item->msb > item->lsb) ? (item->msb - item->lsb + 1) : 1;
            if (!item->children.empty()) {
                bool is_signed = (item->value.find("signed") != std::string::npos);
                flatDef->signals.push_back({item->children[0]->value, w, 0,
                                           item->value.find("output") != std::string::npos, is_signed});
            }
        } else if (item->type == NodeType::LOCALPARAM_DECL) {
            flatDef->signals.push_back({item->value, 32, 0, false, false});
        }
    }
    outDefs.push_back(flatDef);

    compiledModules = outDefs;  /* keep in memory for run() */

    if (!writeModuleDefs(output, outDefs)) {
        simulatorWarning("failed to write " + output);
        return 1;
    }
    return 0;
}

int SimulationEngine::run(const std::string &simPath, unsigned int /*threads*/) {
    std::vector<ModuleDef *> modules;
    if (!compiledModules.empty()) {
        modules = compiledModules;  /* use in-memory result from compile() */
    } else {
        std::string path = simPath.empty() ? "sim.out" : simPath;
        if (!readModuleDefs(path, modules) || modules.empty()) {
            simulatorWarning("cannot read sim.out — run compile_sim first");
            return 1;
        }
    }
    ModuleDef *mod = modules[0];

    SignalValues svals;
    SignalWidths widths;
    g_signalSigneds.clear();
    for (auto &s : mod->signals) {
        svals[s.name] = s.init_value;
        widths[s.name] = s.width;
        if (s.is_signed) g_signalSigneds[s.name] = true;
    }

    std::map<int, FILE *> fds;
    bool finished = false;

    std::vector<ASTNode *> procItems;
    std::vector<ASTNode *> assignItems;
    std::vector<ASTNode *> alwaysItems;
    for (auto *item : mod->items) {
        if (item->type == NodeType::INITIAL_BLOCK) {
            procItems.push_back(item);
        } else if (item->type == NodeType::ALWAYS_BLOCK) {
            alwaysItems.push_back(item);
        } else if (item->type == NodeType::ASSIGN) {
            assignItems.push_back(item);
        }
    }

    g_assignItems = &assignItems;
    g_alwaysBlocks = &alwaysItems;
    g_clocks.clear();
    propagateSignals(assignItems, svals, widths);

    /* Detect always #N signal = ~signal pattern for clock generation */
    for (auto *ab : alwaysItems) {
        if (ab->value == "#delay" && ab->children.size() >= 2) {
            ASTNode *delayExpr = ab->children[0];
            ASTNode *body = ab->children[1];
            if (delayExpr && body && body->type == NodeType::BLOCKING_ASSIGN &&
                body->children.size() >= 2) {
                int period = 0;
                if (delayExpr->type == NodeType::NUMBER)
                    try { period = std::stoi(delayExpr->value); } catch (...) {}
                if (period > 0) {
                    std::string sig = body->children[0]->value;
                    g_clocks.push_back({sig, period});
                    svals[sig] = svals[sig] ? 0 : 1;
                }
            }
        }
    }
    propagateSignals(assignItems, svals, widths);

    for (auto *item : procItems) {
        if (item->children.empty()) continue;
        ASTNode *body = item->children[0];
        if (!body) continue;
        /* Execute statements sequentially, handling delays inline */
        std::vector<ASTNode *> stmts;
        /* Flatten: if body is a BLOCK, use its children; otherwise single stmt */
        if (body->type == NodeType::BLOCK || body->type == NodeType::INITIAL_BLOCK) {
            for (auto *c : body->children) stmts.push_back(c);
        } else {
            stmts.push_back(body);
        }
        for (size_t si = 0; si < stmts.size(); si++) {
            ASTNode *stmt = stmts[si];
            if (stmt->type == NodeType::DELAY) {
                /* Handle delay inline */
                if (stmt->value == "posedge" || stmt->value == "negedge") {
                    std::string sig = stmt->children.empty() ? "clk" : stmt->children[0]->value;
                    bool wantPosedge = (stmt->value == "posedge");
                    /* Toggle clock to advance time; detect edge */
                    uint64_t prev = svals[sig];
                    svals[sig] = prev ? 0 : 1;
                    propagateSignals(assignItems, svals, widths);
                    uint64_t cur = svals[sig];
                    bool gotEdge = wantPosedge ? (prev == 0 && cur == 1) : (prev == 1 && cur == 0);
                    if (!gotEdge) {
                        /* Need one more toggle */
                        prev = svals[sig];
                        svals[sig] = prev ? 0 : 1;
                        propagateSignals(assignItems, svals, widths);
                    }
                } else {
                    int delay = 0;
                    try { delay = std::stoi(stmt->value); } catch (...) {}
                    for (int t = 0; t < delay; t++) {
                        for (auto &clk : g_clocks) {
                            svals[clk.signal] = svals[clk.signal] ? 0 : 1;
                            propagateSignals(assignItems, svals, widths);
                        }
                    }
                }
            } else if (stmt->type == NodeType::FOR) {
                /* Handle for loop with inline delay support */
                if (stmt->children.size() >= 6) {
                    auto Rinit = evalExpr(stmt->children[1], svals, widths, g_signalSigneds);
                    if (stmt->children[0]->type == NodeType::IDENTIFIER)
                        svals[stmt->children[0]->value] = Rinit.value;
                    ASTNode *forBody = stmt->children[5];
                    for (int iter = 0; iter < 100000; iter++) {
                        if (!evalExpr(stmt->children[2], svals, widths, g_signalSigneds).value) break;
                        /* Execute for-loop body statements */
                        ASTNode *forBody = stmt->children[5];
                        std::vector<ASTNode *> forStmts;
                        if (forBody && (forBody->type == NodeType::BLOCK || forBody->type == NodeType::INITIAL_BLOCK)) {
                            for (auto *c : forBody->children) forStmts.push_back(c);
                        } else if (forBody) {
                            forStmts.push_back(forBody);
                        }
                        for (size_t fi = 0; fi < forStmts.size(); fi++) {
                            ASTNode *fstmt = forStmts[fi];
                            if (fstmt->type == NodeType::DELAY) {
                                if (fstmt->value == "posedge" || fstmt->value == "negedge") {
                                    std::string sig = fstmt->children.empty() ? "clk" : fstmt->children[0]->value;
                                    bool wantPosedge = (fstmt->value == "posedge");
                                    uint64_t prev = svals[sig];
                                    svals[sig] = prev ? 0 : 1;
                                    propagateSignals(assignItems, svals, widths);
                                    uint64_t cur = svals[sig];
                                    bool gotEdge = wantPosedge ? (prev == 0 && cur == 1) : (prev == 1 && cur == 0);
                                    if (!gotEdge) {
                                        prev = svals[sig];
                                        svals[sig] = prev ? 0 : 1;
                                        propagateSignals(assignItems, svals, widths);
                                    }
                                } else {
                                    int d = 0;
                                    try { d = std::stoi(fstmt->value); } catch (...) {}
                                    for (int t = 0; t < d; t++) {
                                        for (auto &clk : g_clocks) {
                                            svals[clk.signal] = svals[clk.signal] ? 0 : 1;
                                            propagateSignals(assignItems, svals, widths);
                                        }
                                    }
                                }
                            } else {
                                execItem(fstmt, svals, widths, fds, finished);
                                propagateSignals(assignItems, svals, widths);
                            }
                            if (finished) break;
                        }
                        if (finished) break;
                        auto Rupd = evalExpr(stmt->children[4], svals, widths, g_signalSigneds);
                        if (stmt->children[3]->type == NodeType::IDENTIFIER)
                            svals[stmt->children[3]->value] = Rupd.value;
                    }
                }
            } else {
                execItem(stmt, svals, widths, fds, finished);
                propagateSignals(assignItems, svals, widths);
            }
            if (finished) break;
        }
    }

    for (auto &p : fds) fclose(p.second);
    return 0;
}
