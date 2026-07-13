#include "eval_expr.h"

#include "ast.h"

std::uint64_t evalExpr(const ASTNode *node, const SignalValues &signals) {
    if (node == nullptr) {
        return 0;
    }

    if (node->type == NodeType::IDENTIFIER) {
        const auto found = signals.find(node->value);
        return found == signals.end() ? 0 : found->second;
    }

    return 0;
}
