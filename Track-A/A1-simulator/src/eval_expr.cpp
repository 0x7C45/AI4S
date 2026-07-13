#include "eval_expr.h"
#include "ast.h"

static uint64_t trunc(int width, uint64_t val) {
    if (width >= 64 || width <= 0) return val;
    return val & ((1ULL << width) - 1);
}

static EvalResult evalImpl(const ASTNode *node, const SignalValues &signals,
                           const SignalWidths &widths, const SignalSigned &signeds) {
    if (!node) return {0, 32};

    switch (node->type) {
    case NodeType::NUMBER: {
        int w = (node->msb > 0) ? (node->msb + 1) : 32;
        uint64_t v = 0;
        try { v = std::stoull(node->value); } catch (...) { v = 0; }
        return {v, w};
    }

    case NodeType::IDENTIFIER: {
        int w = 32;
        auto wi = widths.find(node->value);
        if (wi != widths.end()) w = wi->second;
        auto it = signals.find(node->value);
        return {it == signals.end() ? 0 : it->second, w};
    }

    case NodeType::BINOP: {
        auto L = evalImpl(node->children[0], signals, widths, signeds);
        auto R = evalImpl(node->children[1], signals, widths, signeds);
        uint64_t l = trunc(L.width, L.value);
        uint64_t r = trunc(R.width, R.value);
        int lw = L.width, rw = R.width;
        const std::string &op = node->value;

        if (op == "+")  return {l + r, std::max(lw, rw)};
        if (op == "-")  return {l - r, std::max(lw, rw)};
        if (op == "*")  return {l * r, std::max(lw, rw)};
        if (op == "**") {
            uint64_t result = 1;
            for (uint64_t i = 0; i < r; i++) result *= l;
            return {result, std::max(lw, rw)};
        }
        if (op == "&")  return {l & r, std::max(lw, rw)};
        if (op == "|")  return {l | r, std::max(lw, rw)};
        if (op == "^")  return {l ^ r, std::max(lw, rw)};
        if (op == "~^") return {~(l ^ r), std::max(lw, rw)};
        if (op == "~&") return {~(l & r), std::max(lw, rw)};
        if (op == "~|") return {~(l | r), std::max(lw, rw)};
        if (op == "<<") return {l << (r & 63), lw};
        if (op == ">>") return {l >> (r & 63), lw};
        if (op == ">>>") {
            /* Determine signedness: check if left operand is a signed identifier */
            bool isSigned = false;
            if (node->children[0]->type == NodeType::IDENTIFIER) {
                auto si = signeds.find(node->children[0]->value);
                if (si != signeds.end()) isSigned = si->second;
            }
            if (isSigned && (l & (1ULL << (lw - 1)))) {
                /* Sign-extend and arithmetic right shift */
                int64_t sv;
                if (lw <= 32)      sv = (int64_t)(int32_t)(uint32_t)l;
                else if (lw <= 64) sv = (int64_t)(l | ~((1ULL << lw) - 1));
                else               sv = (int64_t)l;
                return {(uint64_t)(sv >> (r & 63)), lw};
            }
            return {l >> (r & 63), lw};
        }
        if (op == "==")  return {l == r ? 1ULL : 0ULL, 1};
        if (op == "!=")  return {l != r ? 1ULL : 0ULL, 1};
        if (op == "<")   return {l < r ? 1ULL : 0ULL, 1};
        if (op == ">")   return {l > r ? 1ULL : 0ULL, 1};
        if (op == "<=")  return {l <= r ? 1ULL : 0ULL, 1};
        if (op == ">=")  return {l >= r ? 1ULL : 0ULL, 1};
        if (op == "&&")  return {(l && r) ? 1ULL : 0ULL, 1};
        if (op == "||")  return {(l || r) ? 1ULL : 0ULL, 1};
        return {0, 32};
    }

    case NodeType::UNOP: {
        auto E = evalImpl(node->children[0], signals, widths, signeds);
        uint64_t v = trunc(E.width, E.value);
        const std::string &op = node->value;
        if (op == "!") return {v ? 0ULL : 1ULL, 1};
        if (op == "~") return {~v, E.width};
        if (op == "-") return {(uint64_t)(-(int64_t)v), E.width};
        if (op == "&") {
            uint64_t r = 1;
            for (int i = 0; i < E.width; i++) r &= (v >> i);
            return {r & 1, 1};
        }
        if (op == "|") {
            uint64_t r = 0;
            for (int i = 0; i < E.width; i++) r |= (v >> i);
            return {r & 1, 1};
        }
        if (op == "^") {
            uint64_t r = 0;
            for (int i = 0; i < E.width; i++) r ^= (v >> i);
            return {r & 1, 1};
        }
        return {0, 32};
    }

    case NodeType::TERNARY: {
        auto C = evalImpl(node->children[0], signals, widths, signeds);
        auto T = evalImpl(node->children[1], signals, widths, signeds);
        auto F = evalImpl(node->children[2], signals, widths, signeds);
        return C.value ? T : F;
    }

    case NodeType::CONCAT: {
        uint64_t result = 0;
        int totalWidth = 0;
        for (int i = (int)node->children.size() - 1; i >= 0; i--) {
            auto R = evalImpl(node->children[i], signals, widths, signeds);
            uint64_t v = trunc(R.width, R.value);
            result |= (v << totalWidth);
            totalWidth += R.width;
        }
        return {result, totalWidth};
    }

    case NodeType::BITSEL: {
        auto it = signals.find(node->value);
        uint64_t val = (it != signals.end()) ? it->second : 0;
        /* Check if this is a multi-dimensional wire access (e.g., stage[0]) */
        if (node->children.size() == 1) {
            auto I = evalImpl(node->children[0], signals, widths, signeds);
            std::string fullName = node->value + "[" + std::to_string((int)I.value) + "]";
            auto fit = signals.find(fullName);
            if (fit != signals.end()) {
                /* Multi-dimensional wire element — return full value */
                int w = 32;
                auto wi = widths.find(fullName);
                if (wi != widths.end()) w = wi->second;
                return {fit->second, w};
            }
            /* Regular bit-select */
            return {(val >> (int)I.value) & 1ULL, 1};
        }
        if (node->children.size() >= 3) {
            /* Double bit-select: signal[idx][msb:lsb] or signal[idx][bit] */
            auto Idx = evalImpl(node->children[0], signals, widths, signeds);
            std::string fullName = node->value + "[" + std::to_string((int)Idx.value) + "]";
            auto fit = signals.find(fullName);
            val = (fit != signals.end()) ? fit->second : 0;
            if (node->children.size() == 3) {
                /* Could be signal[idx][msb:lsb] or signal[idx][bit] with sentinel */
                if (node->children[2]->type == NodeType::NUMBER &&
                    node->children[2]->value == "-1") {
                    /* Bit select with sentinel */
                    auto B = evalImpl(node->children[1], signals, widths, signeds);
                    return {(val >> (int)B.value) & 1ULL, 1};
                } else {
                    /* Range select [idx, msb, lsb] */
                    auto M = evalImpl(node->children[1], signals, widths, signeds);
                    auto L = evalImpl(node->children[2], signals, widths, signeds);
                    int msb = (int)M.value, lsb = (int)L.value;
                    if (msb < lsb) std::swap(msb, lsb);
                    int w = msb - lsb + 1;
                    uint64_t mask = (w >= 64) ? ~0ULL : ((1ULL << w) - 1);
                    return {(val >> lsb) & mask, w};
                }
            } else {
                /* signal[idx][bit] — 4 children: [idx, bit, sentinel, ...] */
                auto B = evalImpl(node->children[1], signals, widths, signeds);
                return {(val >> (int)B.value) & 1ULL, 1};
            }
        } else if (node->children.size() == 2) {
            /* Could be signal[msb:lsb] or signal[bit] */
            auto M = evalImpl(node->children[0], signals, widths, signeds);
            auto L = evalImpl(node->children[1], signals, widths, signeds);
            /* If both are small constants, treat as range select */
            int msb = (int)M.value, lsb = (int)L.value;
            if (msb < lsb) std::swap(msb, lsb);
            int w = msb - lsb + 1;
            uint64_t mask = (w >= 64) ? ~0ULL : ((1ULL << w) - 1);
            return {(val >> lsb) & mask, w};
        } else if (node->children.size() == 1) {
            auto I = evalImpl(node->children[0], signals, widths, signeds);
            return {(val >> (int)I.value) & 1ULL, 1};
        }
        return {val, 32};
    }

    case NodeType::SYS_TASK: {
        if (node->value == "$clog2" && !node->children.empty()) {
            auto A = evalImpl(node->children[0], signals, widths, signeds);
            uint64_t v = A.value;
            if (v <= 1) return {0, 32};
            int r = 0;
            uint64_t t = v - 1;
            while (t > 0) { r++; t >>= 1; }
            return {(uint64_t)r, 32};
        }
        return {0, 32};
    }

    default:
        return {0, 32};
    }
}

EvalResult evalExpr(const ASTNode *node, const SignalValues &signals,
                    const SignalWidths &widths, const SignalSigned &signeds) {
    return evalImpl(node, signals, widths, signeds);
}
