#ifndef A1_SIMULATOR_AST_H
#define A1_SIMULATOR_AST_H

#include <cstdint>
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
    EVENT_LIST,
    FUNCTION_DECL,
    FUNCTION_RETURN,
    FUNCTION_CALL,
    PROCEDURAL_DECL,
    MEMORY_DECL,
};

enum class EventEdge : uint8_t {
    NONE = 0,
    POSEDGE = 1,
    NEGEDGE = 2,
    LEVEL = 3,
};

enum class PartSelectDirection : uint8_t {
    NONE = 0,
    PLUS = 1,
    MINUS = 2,
};

struct ASTNode {
    NodeType type = NodeType::BLOCK;
    std::string value;
    std::vector<ASTNode *> children;
    int msb = 0;
    int lsb = 0;
    int line_no = 0;
    std::string source_file;
    EventEdge event_edge = EventEdge::NONE;
    PartSelectDirection part_select_direction = PartSelectDirection::NONE;
};

ASTNode *makeNode(NodeType type, std::string value = {}, int line_no = 0);
void addChild(ASTNode *parent, ASTNode *child);
void freeTree(ASTNode *node);

#endif  // A1_SIMULATOR_AST_H
