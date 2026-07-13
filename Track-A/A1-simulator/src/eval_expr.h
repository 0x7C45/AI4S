#ifndef A1_SIMULATOR_EVAL_EXPR_H
#define A1_SIMULATOR_EVAL_EXPR_H

#include <cstdint>
#include <map>
#include <string>
#include <utility>

struct ASTNode;

struct EvalResult {
    uint64_t value;
    int width;
    EvalResult(uint64_t v = 0, int w = 32) : value(v), width(w) {}
};

using SignalValues = std::map<std::string, uint64_t>;
using SignalWidths = std::map<std::string, int>;
using SignalSigned = std::map<std::string, bool>;

EvalResult evalExpr(const ASTNode *node, const SignalValues &signals,
                    const SignalWidths &widths,
                    const SignalSigned &signeds = SignalSigned());

#endif
