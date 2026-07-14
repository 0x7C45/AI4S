#include "ast.h"

#include <utility>

ASTNode *makeNode(NodeType type, std::string value, int line_no) {
    auto *node = new ASTNode();
    node->type = type;
    node->value = std::move(value);
    node->line_no = line_no;
    return node;
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
