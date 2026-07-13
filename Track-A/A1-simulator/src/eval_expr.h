#ifndef A1_SIMULATOR_EVAL_EXPR_H
#define A1_SIMULATOR_EVAL_EXPR_H

#include <cstdint>
#include <map>
#include <string>

struct ASTNode;

using SignalValues = std::map<std::string, std::uint64_t>;

std::uint64_t evalExpr(const ASTNode *node, const SignalValues &signals);

#endif  // A1_SIMULATOR_EVAL_EXPR_H
