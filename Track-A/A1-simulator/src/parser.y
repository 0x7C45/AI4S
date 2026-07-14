%code requires {
#ifndef VERILOG_NUM_DEFINED
#define VERILOG_NUM_DEFINED
#include <cstdint>
struct VerilogNum {
    uint64_t value;
    int width;
    int is_signed;
};
#endif
}

%{
#include "ast.h"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#ifndef VERILOG_NUM_DEFINED
#define VERILOG_NUM_DEFINED
struct VerilogNum {
    uint64_t value;
    int width;
    int is_signed;
};
#endif

extern int yylex(void);
extern int yylineno;
void yyerror(const char *msg);
extern FILE *yyin;

std::vector<ASTNode *> g_modules;

static ASTNode *makeNum(VerilogNum *n) {
    ASTNode *node = makeNode(NodeType::NUMBER, std::to_string(n->value), yylineno);
    node->msb = n->width - 1;
    node->lsb = 0;
    free(n);
    return node;
}
%}

%union {
    struct VerilogNum *num;
    char *str;
    struct ASTNode *node;
}

%token <str> IDENTIFIER STRING
%token <num> NUMBER
%token MODULE ENDMODULE INPUT OUTPUT WIRE REG INTEGER_KW SIGNED
%token LOCALPARAM PARAMETER ASSIGN ALWAYS INITIAL_KW
%token BEGINKW END IF ELSE CASE ENDCASE DEFAULT FOR
%token GENERATE ENDGENERATE GENVAR POSEDGE NEGEDGE
%token SYS_FOPEN SYS_FCLOSE SYS_FSCANF SYS_FGETS SYS_FDISPLAY SYS_DISPLAY SYS_FINISH SYS_CLOG2
%token EQ NE LE GE LOGAND LOGOR SHL SHR SSHR NAND NOR XNOR

%type <node> module_list module module_items stmts port_list port_decl_in_list opt_port_list
%type <node> port_decl module_item stmt expr prim_expr lvalue range
%type <node> param_override port_conn case_item
%type <node> param_list param_assign expr_list lvalue_list port_conn_list case_items
%type <node> gen_items gen_item gen_block gen_body
%type <node> module_param_decls module_param_decl

%left LOGOR
%left LOGAND
%right '?' ':'
%left '|'
%left '^' XNOR
%left '&' NAND NOR
%left EQ NE
%left '<' '>' LE GE
%left SHL SHR SSHR
%left '+' '-'
%left '*' '/' '%'
%right POWER
%right '!' '~' UNARY

%%

source:
    module_list
    ;

module_list:
    module_list module { g_modules.push_back($2); }
    | module           { g_modules.push_back($1); }
    ;

module:
    MODULE IDENTIFIER opt_port_list ';' module_items ENDMODULE
    {
        $$ = makeNode(NodeType::MODULE, $2, yylineno);
        free($2);
        if ($3) { for (auto *c : $3->children) addChild($$, c); $3->children.clear(); freeTree($3); }
        if ($5) { for (auto *c : $5->children) { addChild($$, c); } $5->children.clear(); freeTree($5); }
    }
    | MODULE IDENTIFIER '#' '(' module_param_decls ')' opt_port_list ';' module_items ENDMODULE
    {
        $$ = makeNode(NodeType::MODULE, $2, yylineno);
        free($2);
        /* Add parameter declarations as children */
        if ($5) { for (auto *c : $5->children) addChild($$, c); $5->children.clear(); freeTree($5); }
        if ($7) { for (auto *c : $7->children) addChild($$, c); $7->children.clear(); freeTree($7); }
        if ($9) { for (auto *c : $9->children) addChild($$, c); $9->children.clear(); freeTree($9); }
    }
    ;

module_param_decls:
    module_param_decls ',' module_param_decl { addChild($1, $3); $$ = $1; }
    | module_param_decl                      { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    ;

module_param_decl:
    PARAMETER IDENTIFIER '=' expr
      { $$ = makeNode(NodeType::LOCALPARAM_DECL, $2, yylineno); free($2); addChild($$, $4); }
    ;

opt_port_list:
    '(' port_list ')' { $$ = $2; }
    | /* empty */     { $$ = nullptr; }
    ;

port_list:
    port_list ',' port_decl_in_list { if ($3) addChild($1, $3); $$ = $1; }
    | port_decl_in_list             { $$ = makeNode(NodeType::BLOCK, "", yylineno); if ($1) addChild($$, $1); }
    ;

port_decl_in_list:
    IDENTIFIER              { free($1); $$ = nullptr; }
    | port_decl             { $$ = $1; }
    | /* empty */           { $$ = nullptr; }
    ;

module_items:
    module_items module_item { addChild($1, $2); $$ = $1; }
    | module_item            { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    | /* empty */            { $$ = makeNode(NodeType::BLOCK, "", yylineno); }
    ;

module_item:
    port_decl ';'
    | WIRE range IDENTIFIER range ';'
      {
          /* Multi-dimensional wire: wire [msb:lsb] name[dim_msb:dim_lsb] */
          $$ = makeNode(NodeType::NET_DECL, "wire", yylineno);
          addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno));
          free($3);
          $$->msb = $2->msb; $$->lsb = $2->lsb;
          /* Store data range expressions + dimension range expressions */
          for (auto *c : $2->children) addChild($$, c);
          $2->children.clear(); freeTree($2);
          for (auto *c : $4->children) addChild($$, c);
          $4->children.clear(); freeTree($4);
      }
    | WIRE range IDENTIFIER decl_list ';'
      { $$ = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno)); free($3); $$->msb = $2->msb; $$->lsb = $2->lsb; for (auto *c : $2->children) addChild($$, c); $2->children.clear(); freeTree($2); }
    | WIRE range IDENTIFIER '=' expr ';'
      {
          /* Wire with initialization — store expr as child for later assign */
          auto *decl = makeNode(NodeType::NET_DECL, "wire", yylineno);
          addChild(decl, makeNode(NodeType::IDENTIFIER, $3, yylineno));
          free($3);
          decl->msb = $2->msb; decl->lsb = $2->lsb;
          for (auto *c : $2->children) addChild(decl, c); $2->children.clear(); freeTree($2);
          addChild(decl, $5);  /* init expression */
          $$ = decl;
      }
    | WIRE IDENTIFIER decl_list ';'
      { $$ = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild($$, makeNode(NodeType::IDENTIFIER, $2, yylineno)); free($2); $$->msb = 0; $$->lsb = 0; }
    | REG range IDENTIFIER decl_list ';'
      { $$ = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno)); free($3); $$->msb = $2->msb; $$->lsb = $2->lsb; for (auto *c : $2->children) addChild($$, c); $2->children.clear(); freeTree($2); }
    | REG range IDENTIFIER '=' expr ';'
      { $$ = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno)); free($3); $$->msb = $2->msb; $$->lsb = $2->lsb; for (auto *c : $2->children) addChild($$, c); $2->children.clear(); freeTree($2); }
    | REG IDENTIFIER '=' expr ';'
      { $$ = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild($$, makeNode(NodeType::IDENTIFIER, $2, yylineno)); free($2); $$->msb = 0; $$->lsb = 0; }
    | REG IDENTIFIER decl_list ';'
      { $$ = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild($$, makeNode(NodeType::IDENTIFIER, $2, yylineno)); free($2); $$->msb = 0; $$->lsb = 0; }
    | REG SIGNED range IDENTIFIER decl_list ';'
      { $$ = makeNode(NodeType::NET_DECL, "reg signed", yylineno); addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno)); free($4); $$->msb = $3->msb; $$->lsb = $3->lsb; for (auto *c : $3->children) addChild($$, c); $3->children.clear(); freeTree($3); }
    | INTEGER_KW IDENTIFIER decl_list ';'
      { $$ = makeNode(NodeType::NET_DECL, "integer", yylineno); addChild($$, makeNode(NodeType::IDENTIFIER, $2, yylineno)); free($2); $$->msb = 31; $$->lsb = 0; }
    | LOCALPARAM IDENTIFIER '=' expr ';'
      {
          $$ = makeNode(NodeType::LOCALPARAM_DECL, $2, yylineno); free($2); addChild($$, $4);
      }
    | PARAMETER IDENTIFIER '=' expr ';'
      { $$ = makeNode(NodeType::LOCALPARAM_DECL, $2, yylineno); free($2); addChild($$, $4); }
    | ASSIGN lvalue '=' expr ';'
      { $$ = makeNode(NodeType::ASSIGN, "", yylineno); addChild($$, $2); addChild($$, $4); }
    | ALWAYS '@' '(' '*' ')' stmt
      { $$ = makeNode(NodeType::ALWAYS_BLOCK, "@(*)", yylineno); addChild($$, $6); }
    | ALWAYS '@' '(' POSEDGE IDENTIFIER ')' stmt
      { $$ = makeNode(NodeType::ALWAYS_BLOCK, "@(posedge " + std::string($5) + ")", yylineno); addChild($$, $7); free($5); }
    | ALWAYS '@' '(' NEGEDGE IDENTIFIER ')' stmt
      { $$ = makeNode(NodeType::ALWAYS_BLOCK, "@(negedge " + std::string($5) + ")", yylineno); addChild($$, $7); free($5); }
    | ALWAYS '#' expr stmt
      { $$ = makeNode(NodeType::ALWAYS_BLOCK, "#delay", yylineno); addChild($$, $3); addChild($$, $4); }
    | INITIAL_KW stmt
      { $$ = makeNode(NodeType::INITIAL_BLOCK, "", yylineno); addChild($$, $2); }
    | IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' port_conn_list ')'
      ';'
      { $$ = makeNode(NodeType::MODULE_INST, $1, yylineno); free($1); addChild($$, makeNode(NodeType::IDENTIFIER, $6, yylineno)); free($6); for (auto *c : $4->children) addChild($$, c); $4->children.clear(); freeTree($4); for (auto *c : $8->children) addChild($$, c); $8->children.clear(); freeTree($8); }
    | IDENTIFIER IDENTIFIER '(' port_conn_list ')' ';'
      { $$ = makeNode(NodeType::MODULE_INST, $1, yylineno); free($1); addChild($$, makeNode(NodeType::IDENTIFIER, $2, yylineno)); free($2); for (auto *c : $4->children) addChild($$, c); $4->children.clear(); freeTree($4); }
    | IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' ')' ';'
      { $$ = makeNode(NodeType::MODULE_INST, $1, yylineno); free($1); addChild($$, makeNode(NodeType::IDENTIFIER, $6, yylineno)); free($6); for (auto *c : $4->children) addChild($$, c); $4->children.clear(); freeTree($4); }
    | IDENTIFIER IDENTIFIER '(' ')' ';'
      { $$ = makeNode(NodeType::MODULE_INST, $1, yylineno); free($1); addChild($$, makeNode(NodeType::IDENTIFIER, $2, yylineno)); free($2); }
    | GENERATE gen_items ENDGENERATE { $$ = $2; }
    | param_override ';' { $$ = $1; }
    ;

port_decl:
    INPUT range IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "input";
          $$->msb = $2->msb; $$->lsb = $2->lsb;
          addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno));
          free($3);
          /* Keep range expressions as children for deferred evaluation */
          for (auto *c : $2->children) addChild($$, c);
          $2->children.clear(); freeTree($2);
      }
    | INPUT IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "input";
          $$->msb = 0; $$->lsb = 0;
          addChild($$, makeNode(NodeType::IDENTIFIER, $2, yylineno));
          free($2);
      }
    | OUTPUT range IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "output";
          $$->msb = $2->msb; $$->lsb = $2->lsb;
          addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno));
          free($3);
          for (auto *c : $2->children) addChild($$, c);
          $2->children.clear(); freeTree($2);
      }
    | OUTPUT IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "output";
          $$->msb = 0; $$->lsb = 0;
          addChild($$, makeNode(NodeType::IDENTIFIER, $2, yylineno));
          free($2);
      }
    | OUTPUT WIRE range IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "output";
          $$->msb = $3->msb; $$->lsb = $3->lsb;
          addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno));
          free($4);
          for (auto *c : $3->children) addChild($$, c);
          $3->children.clear(); freeTree($3);
      }
    | OUTPUT WIRE IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "output";
          $$->msb = 0; $$->lsb = 0;
          addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno));
          free($3);
      }
    | INPUT WIRE range IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "input";
          $$->msb = $3->msb; $$->lsb = $3->lsb;
          addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno));
          free($4);
          for (auto *c : $3->children) addChild($$, c);
          $3->children.clear(); freeTree($3);
      }
    | INPUT WIRE IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "input";
          $$->msb = 0; $$->lsb = 0;
          addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno));
          free($3);
      }
    | OUTPUT REG range IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "output reg";
          $$->msb = $3->msb; $$->lsb = $3->lsb;
          addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno));
          free($4);
          for (auto *c : $3->children) addChild($$, c);
          $3->children.clear(); freeTree($3);
      }
    | OUTPUT REG IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "output reg";
          $$->msb = 0; $$->lsb = 0;
          addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno));
          free($3);
      }
    | OUTPUT SIGNED range IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "output signed";
          $$->msb = $3->msb; $$->lsb = $3->lsb;
          addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno));
          free($4);
          for (auto *c : $3->children) addChild($$, c);
          $3->children.clear(); freeTree($3);
      }
    | INPUT SIGNED range IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "input signed";
          $$->msb = $3->msb; $$->lsb = $3->lsb;
          addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno));
          free($4);
          for (auto *c : $3->children) addChild($$, c);
          $3->children.clear(); freeTree($3);
      }
    | OUTPUT REG SIGNED range IDENTIFIER
      {
          $$ = makeNode(NodeType::PORT, "", yylineno);
          $$->value = "output reg signed";
          $$->msb = $4->msb; $$->lsb = $4->lsb;
          addChild($$, makeNode(NodeType::IDENTIFIER, $5, yylineno));
          free($5); freeTree($4);
      }
    ;

decl_list:
    decl_list ',' IDENTIFIER { free($3); }
    | /* empty */
    ;

stmt:
    BEGINKW stmts END      { $$ = $2; }
    | IF '(' expr ')' stmt
      {
          $$ = makeNode(NodeType::IF, "", yylineno);
          addChild($$, $3);
          addChild($$, $5);
      }
    | IF '(' expr ')' stmt ELSE stmt
      {
          $$ = makeNode(NodeType::IF, "", yylineno);
          addChild($$, $3);
          addChild($$, $5);
          addChild($$, $7);
      }
    | CASE '(' expr ')' case_items ENDCASE
      {
          $$ = makeNode(NodeType::CASE, "", yylineno);
          addChild($$, $3);
          addChild($$, $5);
      }
    | FOR '(' lvalue '=' expr ';' expr ';' lvalue '=' expr ')' stmt
      {
          $$ = makeNode(NodeType::FOR, "", yylineno);
          addChild($$, $3);  /* init lvalue */
          addChild($$, $5);  /* init expr */
          addChild($$, $7);  /* cond */
          addChild($$, $9);  /* update lvalue */
          addChild($$, $11); /* update expr */
          addChild($$, $13); /* body */
      }
    | lvalue '=' expr ';'
      {
          $$ = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild($$, $1);
          addChild($$, $3);
      }
    | lvalue LE expr ';'
      {
          $$ = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild($$, $1);
          addChild($$, $3);
      }
    | SYS_DISPLAY '(' expr_list ')' ';'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          $$->children = $3->children;
          $3->children.clear();
          freeTree($3);
      }
    | SYS_DISPLAY '(' STRING ')' ';'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          addChild($$, makeNode(NodeType::STRING, $3, yylineno));
          free($3);
      }
    | SYS_FINISH ';'               { $$ = makeNode(NodeType::SYS_TASK, "$finish", yylineno); }
    | SYS_FINISH '(' expr ')' ';'  { $$ = makeNode(NodeType::SYS_TASK, "$finish", yylineno); addChild($$, $3); }
    | '#' NUMBER ';'
      {
          $$ = makeNode(NodeType::DELAY, std::to_string($2->value), yylineno);
          free($2);
      }
    | '@' '(' POSEDGE IDENTIFIER ')' ';'
      {
          $$ = makeNode(NodeType::DELAY, "posedge", yylineno);
          addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno));
          free($4);
      }
    | '@' '(' NEGEDGE IDENTIFIER ')' ';'
      {
          $$ = makeNode(NodeType::DELAY, "negedge", yylineno);
          addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno));
          free($4);
      }
    | SYS_FOPEN '(' STRING ')' ';'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild($$, makeNode(NodeType::STRING, $3, yylineno));
          free($3);
      }
    | SYS_FCLOSE '(' expr ')' ';'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$fclose", yylineno);
          addChild($$, $3);
      }
    | lvalue '=' SYS_FOPEN '(' STRING ')' ';'
      {
          $$ = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild($$, $1);
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild(fc, makeNode(NodeType::STRING, $5, yylineno));
          free($5);
          addChild($$, fc);
      }
    | lvalue '=' SYS_FSCANF '(' expr_list ')' ';'
      {
          $$ = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild($$, $1);
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fscanf", yylineno);
          fc->children = $5->children;
          $5->children.clear();
          freeTree($5);
          addChild($$, fc);
      }
    | lvalue '=' SYS_FGETS '(' expr_list ')' ';'
      {
          $$ = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild($$, $1);
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fgets", yylineno);
          fc->children = $5->children;
          $5->children.clear();
          freeTree($5);
          addChild($$, fc);
      }
    | SYS_FDISPLAY '(' expr_list ')' ';'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          $$->children = $3->children;
          $3->children.clear();
          freeTree($3);
      }
    | SYS_FDISPLAY '(' STRING ')' ';'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          addChild($$, makeNode(NodeType::STRING, $3, yylineno));
          free($3);
      }
    ;

stmts:
    stmts stmt { addChild($1, $2); $$ = $1; }
    | stmt     { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    ;

gen_items:
    gen_items gen_item { addChild($1, $2); $$ = $1; }
    | gen_item         { $$ = makeNode(NodeType::GENERATE, "", yylineno); addChild($$, $1); }
    ;

gen_item:
    FOR '(' GENVAR IDENTIFIER '=' expr ';' expr ';' IDENTIFIER '=' expr ')' gen_block
    {
        $$ = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild($$, makeNode(NodeType::IDENTIFIER, $4, yylineno)); free($4);
        addChild($$, $6);
        addChild($$, $8);
        addChild($$, $14);
    }
    | FOR '(' IDENTIFIER '=' expr ';' expr ';' lvalue '=' expr ')' gen_block
    {
        /* for (name = expr; cond; name = expr) — genvar already declared */
        $$ = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild($$, makeNode(NodeType::IDENTIFIER, $3, yylineno)); free($3);
        addChild($$, $5);
        addChild($$, $7);
        addChild($$, $13);
    }
    | IF '(' expr ')' gen_block
    {
        $$ = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild($$, $3);
        addChild($$, $5);
    }
    | IF '(' expr ')' gen_block ELSE gen_block
    {
        $$ = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild($$, $3);
        addChild($$, $5);
        addChild($$, $7);
    }
    | GENVAR genvar_list ';'
    {
        /* genvar declaration — skip */
        $$ = makeNode(NodeType::BLOCK, "", yylineno);
    }
    ;

genvar_list:
    genvar_list ',' IDENTIFIER { free($3); }
    | IDENTIFIER { free($1); }
    ;

gen_block:
    BEGINKW gen_body END { $$ = $2; }
    | BEGINKW ':' IDENTIFIER gen_body END { $$ = $4; free($3); }
    | module_item        { $$ = $1; }
    ;

gen_body:
    gen_body module_item { addChild($1, $2); $$ = $1; }
    | gen_body gen_item { addChild($1, $2); $$ = $1; }
    | module_item        { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    | gen_item           { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    ;

case_items:
    case_items case_item { addChild($1, $2); $$ = $1; }
    | case_item          { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    ;

case_item:
    expr ':' stmt
      {
          $$ = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild($$, $1);
          addChild($$, $3);
      }
    | expr ',' expr ':' stmt
      {
          $$ = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild($$, $1);
          addChild($$, $3);
          addChild($$, $5);
      }
    | DEFAULT ':' stmt
      {
          $$ = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild($$, $3);
      }
    | DEFAULT stmt
      {
          $$ = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild($$, $2);
      }
    ;

param_override:
    '#' '(' param_list ')'
    { $$ = makeNode(NodeType::PARAM_OVERRIDE, "", yylineno); for (auto *c : $3->children) addChild($$, c); $3->children.clear(); freeTree($3); }
    ;

param_list:
    param_list ',' param_assign { if ($3) addChild($1, $3); $$ = $1; }
    | param_assign              { $$ = makeNode(NodeType::BLOCK, "", yylineno); if ($1) addChild($$, $1); }
    ;

param_assign:
    '.' IDENTIFIER '(' expr ')' { $$ = makeNode(NodeType::IDENTIFIER, $2, yylineno); free($2); addChild($$, $4); }
    ;

port_conn_list:
    port_conn_list ',' port_conn { addChild($1, $3); $$ = $1; }
    | port_conn                  { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    ;

port_conn:
    '.' IDENTIFIER '(' expr ')'
      {
          $$ = makeNode(NodeType::PORT_CONN, $2, yylineno);
          free($2);
          addChild($$, $4);
      }
    | '.' IDENTIFIER '(' ')'
      {
          $$ = makeNode(NodeType::PORT_CONN, $2, yylineno);
          free($2);
      }
    ;

range:
    '[' expr ':' expr ']'
      {
          $$ = makeNode(NodeType::BITSEL, "", yylineno);
          addChild($$, $2);
          addChild($$, $4);
          /* Evaluate constant range bounds */
          if ($2->type == NodeType::NUMBER) $$->msb = std::stoi($2->value);
          if ($4->type == NodeType::NUMBER) $$->lsb = std::stoi($4->value);
      }
    ;

expr:
    expr '+' expr       { $$ = makeNode(NodeType::BINOP, "+", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '-' expr     { $$ = makeNode(NodeType::BINOP, "-", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '*' expr     { $$ = makeNode(NodeType::BINOP, "*", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '/' expr     { $$ = makeNode(NodeType::BINOP, "/", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '%' expr     { $$ = makeNode(NodeType::BINOP, "%", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '&' expr     { $$ = makeNode(NodeType::BINOP, "&", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '|' expr     { $$ = makeNode(NodeType::BINOP, "|", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '^' expr     { $$ = makeNode(NodeType::BINOP, "^", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr XNOR expr    { $$ = makeNode(NodeType::BINOP, "~^", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr NAND expr    { $$ = makeNode(NodeType::BINOP, "~&", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr NOR expr     { $$ = makeNode(NodeType::BINOP, "~|", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr EQ expr      { $$ = makeNode(NodeType::BINOP, "==", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr NE expr      { $$ = makeNode(NodeType::BINOP, "!=", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '<' expr     { $$ = makeNode(NodeType::BINOP, "<", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '>' expr     { $$ = makeNode(NodeType::BINOP, ">", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr LE expr      { $$ = makeNode(NodeType::BINOP, "<=", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr GE expr      { $$ = makeNode(NodeType::BINOP, ">=", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr SHL expr     { $$ = makeNode(NodeType::BINOP, "<<", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr SHR expr     { $$ = makeNode(NodeType::BINOP, ">>", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr SSHR expr    { $$ = makeNode(NodeType::BINOP, ">>>", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '*' '*' expr %prec POWER  { $$ = makeNode(NodeType::BINOP, "**", yylineno); addChild($$, $1); addChild($$, $4); }
    | expr LOGAND expr  { $$ = makeNode(NodeType::BINOP, "&&", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr LOGOR expr   { $$ = makeNode(NodeType::BINOP, "||", yylineno); addChild($$, $1); addChild($$, $3); }
    | expr '?' expr ':' expr
      {
          $$ = makeNode(NodeType::TERNARY, "", yylineno);
          addChild($$, $1); addChild($$, $3); addChild($$, $5);
      }
    | '-' expr %prec UNARY    { $$ = makeNode(NodeType::UNOP, "-", yylineno); addChild($$, $2); }
    | '!' expr %prec UNARY    { $$ = makeNode(NodeType::UNOP, "!", yylineno); addChild($$, $2); }
    | '~' expr %prec UNARY    { $$ = makeNode(NodeType::UNOP, "~", yylineno); addChild($$, $2); }
    | '&' expr %prec UNARY    { $$ = makeNode(NodeType::UNOP, "&", yylineno); addChild($$, $2); }
    | '|' expr %prec UNARY    { $$ = makeNode(NodeType::UNOP, "|", yylineno); addChild($$, $2); }
    | '^' expr %prec UNARY    { $$ = makeNode(NodeType::UNOP, "^", yylineno); addChild($$, $2); }
    | prim_expr
    ;

prim_expr:
    NUMBER
      {
          $$ = makeNum($1);
      }
    | IDENTIFIER
      {
          $$ = makeNode(NodeType::IDENTIFIER, $1, yylineno);
          free($1);
      }
    | IDENTIFIER '[' expr ':' expr ']'
      {
          $$ = makeNode(NodeType::BITSEL, $1, yylineno);
          free($1);
          addChild($$, $3);
          addChild($$, $5);
      }
    | IDENTIFIER '[' expr ']'
      {
          $$ = makeNode(NodeType::BITSEL, $1, yylineno);
          free($1);
          addChild($$, $3);
      }
    | IDENTIFIER '[' expr ']' '[' expr ':' expr ']'
      {
          /* Double range-select: signal[idx][msb:lsb] — mark with msb=-1 to distinguish */
          $$ = makeNode(NodeType::BITSEL, $1, yylineno);
          free($1);
          addChild($$, $3);
          addChild($$, $6);
          addChild($$, $8);
      }
    | IDENTIFIER '[' expr ']' '[' expr ']'
      {
          /* Double bit-select: signal[idx][bit] — 3 children: [idx, bit, sentinel] */
          $$ = makeNode(NodeType::BITSEL, $1, yylineno);
          free($1);
          addChild($$, $3);
          addChild($$, $6);
          auto *sentinel = makeNode(NodeType::NUMBER, "-1", yylineno);
          sentinel->msb = -1;
          addChild($$, sentinel);
      }
    | '{' expr_list '}'
      {
          $$ = makeNode(NodeType::CONCAT, "", yylineno);
          $$->children = $2->children;
          $2->children.clear();
          freeTree($2);
      }
    | '{' expr '{' expr_list '}' '}'
      {
          /* Replication: {count{expr_list}} — expand into count copies */
          $$ = makeNode(NodeType::CONCAT, "", yylineno);
          int count = 0;
          try { count = (int)std::stoull($2->value); } catch (...) { count = 1; }
          for (int i = 0; i < count; i++) {
              for (auto *c : $4->children) addChild($$, c);
          }
          freeTree($2);
          $4->children.clear(); freeTree($4);
      }
    | '(' expr ')'
      {
          $$ = $2;
      }
    | SYS_FOPEN '(' STRING ')'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild($$, makeNode(NodeType::STRING, $3, yylineno));
          free($3);
      }
    | SYS_FOPEN '(' STRING ',' STRING ')'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild($$, makeNode(NodeType::STRING, $3, yylineno));
          addChild($$, makeNode(NodeType::STRING, $5, yylineno));
          free($3); free($5);
      }
    | SYS_CLOG2 '(' expr ')'
      {
          $$ = makeNode(NodeType::SYS_TASK, "$clog2", yylineno);
          addChild($$, $3);
      }
    | STRING
      {
          $$ = makeNode(NodeType::STRING, $1, yylineno);
          free($1);
      }
    ;

lvalue:
    IDENTIFIER
      {
          $$ = makeNode(NodeType::IDENTIFIER, $1, yylineno);
          free($1);
      }
    | IDENTIFIER '[' expr ':' expr ']'
      {
          $$ = makeNode(NodeType::BITSEL, $1, yylineno);
          free($1);
          addChild($$, $3);
          addChild($$, $5);
      }
    | IDENTIFIER '[' expr ']'
      {
          $$ = makeNode(NodeType::BITSEL, $1, yylineno);
          free($1);
          addChild($$, $3);
      }
    | IDENTIFIER '[' expr ']' '[' expr ':' expr ']'
      {
          $$ = makeNode(NodeType::BITSEL, $1, yylineno);
          free($1);
          addChild($$, $3);
          addChild($$, $6);
          addChild($$, $8);
      }
    | IDENTIFIER '[' expr ']' '[' expr ']'
      {
          $$ = makeNode(NodeType::BITSEL, $1, yylineno);
          free($1);
          addChild($$, $3);
          addChild($$, $6);
          auto *sentinel = makeNode(NodeType::NUMBER, "-1", yylineno);
          sentinel->msb = -1;
          addChild($$, sentinel);
      }
    | '{' lvalue_list '}'
      {
          $$ = makeNode(NodeType::CONCAT, "", yylineno);
          $$->children = $2->children;
          $2->children.clear();
          freeTree($2);
      }
    ;

lvalue_list:
    lvalue_list ',' lvalue { addChild($1, $3); $$ = $1; }
    | lvalue               { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    ;

expr_list:
    expr_list ',' expr { addChild($1, $3); $$ = $1; }
    | expr             { $$ = makeNode(NodeType::BLOCK, "", yylineno); addChild($$, $1); }
    ;

%%

void yyerror(const char *msg) {
}

extern int yydebug;
std::vector<ASTNode *> parseFiles(const std::vector<std::string> &files) {
    g_modules.clear();
    for (auto &f : files) {
        yylineno = 1;
        yyin = fopen(f.c_str(), "r");
        if (!yyin) {
            continue;
        }
        yyparse();
        fclose(yyin);
    }
    return g_modules;
}
