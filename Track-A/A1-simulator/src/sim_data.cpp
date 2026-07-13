#include "sim_data.h"
#include <algorithm>
#include <fstream>

static void writeU32(std::ofstream &f, uint32_t v) { f.write(reinterpret_cast<char *>(&v), 4); }
static void writeU64(std::ofstream &f, uint64_t v) { f.write(reinterpret_cast<char *>(&v), 8); }
static void writeStr(std::ofstream &f, const std::string &s) {
    uint32_t len = (uint32_t)s.size();
    writeU32(f, len);
    f.write(s.data(), len);
}
static uint32_t readU32(std::ifstream &f) { uint32_t v; f.read(reinterpret_cast<char *>(&v), 4); return v; }
static uint64_t readU64(std::ifstream &f) { uint64_t v; f.read(reinterpret_cast<char *>(&v), 8); return v; }
static std::string readStr(std::ifstream &f) {
    uint32_t len = readU32(f);
    std::string s(len, '\0');
    f.read(&s[0], len);
    return s;
}

static void writeAST(std::ofstream &f, ASTNode *node, std::vector<ASTNode *> &flat) {
    if (!node) return;
    flat.push_back(node);
    for (auto *c : node->children) writeAST(f, c, flat);
}

bool writeModuleDefs(const std::string &path, const std::vector<ModuleDef *> &modules) {
    std::ofstream f(path, std::ios::binary);
    if (!f) return false;
    writeU32(f, (uint32_t)modules.size());
    for (auto *m : modules) {
        writeStr(f, m->name);
        writeU32(f, (uint32_t)m->params.size());
        for (auto &p : m->params) { writeStr(f, p.first); writeU64(f, p.second); }
        writeU32(f, (uint32_t)m->signals.size());
        for (auto &s : m->signals) {
            writeStr(f, s.name);
            writeU32(f, (uint32_t)s.width);
            writeU64(f, s.init_value);
            writeU32(f, s.is_reg ? 1 : 0);
            writeU32(f, s.is_signed ? 1 : 0);
        }
        std::vector<ASTNode *> flat;
        for (auto *item : m->items) writeAST(f, item, flat);
        writeU32(f, (uint32_t)flat.size());
        for (auto *n : flat) {
            writeU32(f, (uint32_t)n->type);
            writeStr(f, n->value);
            writeU32(f, (uint32_t)n->msb);
            writeU32(f, (uint32_t)n->lsb);
            writeU32(f, (uint32_t)n->children.size());
            for (auto *c : n->children) {
                auto it = std::find(flat.begin(), flat.end(), c);
                uint32_t idx = (it != flat.end()) ? (uint32_t)(it - flat.begin()) : 0;
                writeU32(f, idx);
            }
        }
        writeU32(f, (uint32_t)m->items.size());
        for (auto *item : m->items) {
            auto it = std::find(flat.begin(), flat.end(), item);
            writeU32(f, (uint32_t)(it - flat.begin()));
        }
    }
    return true;
}

bool readModuleDefs(const std::string &path, std::vector<ModuleDef *> &modules) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    uint32_t nmod = readU32(f);
    for (uint32_t mi = 0; mi < nmod; mi++) {
        auto *m = new ModuleDef();
        m->name = readStr(f);
        uint32_t npar = readU32(f);
        for (uint32_t i = 0; i < npar; i++) { auto k = readStr(f); m->params[k] = readU64(f); }
        uint32_t nsig = readU32(f);
        for (uint32_t i = 0; i < nsig; i++) {
            SignalDef s;
            s.name = readStr(f);
            s.width = (int)readU32(f);
            s.init_value = readU64(f);
            s.is_reg = readU32(f) != 0;
            s.is_signed = readU32(f) != 0;
            m->signals.push_back(s);
        }
        uint32_t nflat = readU32(f);
        std::vector<ASTNode *> flat(nflat, nullptr);
        for (uint32_t i = 0; i < nflat; i++) {
            flat[i] = new ASTNode();
            flat[i]->type = (NodeType)readU32(f);
            flat[i]->value = readStr(f);
            flat[i]->msb = (int)readU32(f);
            flat[i]->lsb = (int)readU32(f);
            uint32_t nch = readU32(f);
            flat[i]->children.resize(nch);
            for (uint32_t j = 0; j < nch; j++) {
                uint32_t ci = readU32(f);
                flat[i]->children[j] = (ci < nflat) ? flat[ci] : nullptr;
            }
        }
        uint32_t nitems = readU32(f);
        for (uint32_t i = 0; i < nitems; i++) {
            uint32_t idx = readU32(f);
            if (idx < nflat) m->items.push_back(flat[idx]);
        }
        modules.push_back(m);
    }
    return true;
}
