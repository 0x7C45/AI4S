#include "ast.h"

#include <utility>

ASTNode *makeNode(NodeType type, std::string value, int line_no) {
    return new ASTNode{type, std::move(value), {}, 0, 0, line_no};
}

void addChild(ASTNode *parent, ASTNode *child) {
    if (parent != nullptr && child != nullptr) {
        parent->children.push_back(child);
    }
}

void freeTree(ASTNode *node) {
    if (node == nullptr) {
        return;
    }

    for (ASTNode *child : node->children) {
        freeTree(child);
    }
    delete node;
}
