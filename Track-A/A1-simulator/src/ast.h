#ifndef A1_SIMULATOR_AST_H
#define A1_SIMULATOR_AST_H

#include <string>
#include <vector>

enum class NodeType {
    MODULE,
    PORT,
    NET_DECL,
    ASSIGN,
    ALWAYS_BLOCK,
    INITIAL_BLOCK,
    BLOCK,
    IF,
    CASE,
    CASE_ITEM,
    FOR,
    BLOCKING_ASSIGN,
    NONBLOCKING_ASSIGN,
    DELAY,
    EVENT_CTRL,
    CONCAT,
    BITSEL,
    TERNARY,
    BINOP,
    UNOP,
    NUMBER,
    IDENTIFIER,
    STRING,
    FUNC_CALL,
    SYS_TASK,
    MODULE_INST,
    PORT_CONN,
    PARAM_OVERRIDE,
    GENERATE,
    GENERATE_FOR,
    GENERATE_IF,
    LOCALPARAM_DECL,
    GENERATE_BLOCK,
};

struct ASTNode {
    NodeType type;
    std::string value;
    std::vector<ASTNode *> children;
    int msb;
    int lsb;
    int line_no;
};

ASTNode *makeNode(NodeType type, std::string value = {}, int line_no = 0);
void addChild(ASTNode *parent, ASTNode *child);
void freeTree(ASTNode *node);

#endif  // A1_SIMULATOR_AST_H
