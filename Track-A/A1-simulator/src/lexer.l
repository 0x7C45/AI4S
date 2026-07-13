%option noyywrap nodefault
%option yylineno

%{
#include "parser.tab.h"
#include <cstdlib>
#include <cstring>

static char *stralloc(const char *s) {
    return strdup(s);
}
%}

%%

"//"[^\n]*                      ;
"/*"([^*]|\*+[^*/])*\*+"/"      ;

`timescale[^`\n]*               ;
`resetall                       ;
`default_nettype[^\n]*          ;

"module"        { return MODULE; }
"endmodule"     { return ENDMODULE; }
"input"         { return INPUT; }
"output"        { return OUTPUT; }
"wire"          { return WIRE; }
"reg"          { return REG; }
"integer"       { return INTEGER_KW; }
"signed"        { return SIGNED; }
"localparam"    { return LOCALPARAM; }
"parameter"     { return PARAMETER; }
"assign"        { return ASSIGN; }
"always"        { return ALWAYS; }
"initial"       { return INITIAL_KW; }
"begin"         { return BEGINKW; }
"end"           { return END; }
"if"            { return IF; }
"else"          { return ELSE; }
"case"          { return CASE; }
"casez"         { return CASE; }
"casex"         { return CASE; }
"endcase"       { return ENDCASE; }
"default"       { return DEFAULT; }
"for"           { return FOR; }
"generate"      { return GENERATE; }
"endgenerate"   { return ENDGENERATE; }
"genvar"        { return GENVAR; }
"posedge"       { return POSEDGE; }
"negedge"       { return NEGEDGE; }

"$fopen"        { return SYS_FOPEN; }
"$fclose"       { return SYS_FCLOSE; }
"$fscanf"       { return SYS_FSCANF; }
"$fgets"        { return SYS_FGETS; }
"$fdisplay"     { return SYS_FDISPLAY; }
"$display"      { return SYS_DISPLAY; }
"$finish"       { return SYS_FINISH; }
"$clog2"        { return SYS_CLOG2; }

","             { return ','; }
":"             { return ':'; }
";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }
"["             { return '['; }
"]"             { return ']'; }
"{"             { return '{'; }
"}"             { return '}'; }
"."             { return '.'; }
"#"             { return '#'; }
"@"             { return '@'; }

"=="            { return EQ; }
"!="            { return NE; }
"<="            { return LE; }
">="            { return GE; }
"&&"            { return LOGAND; }
"||"            { return LOGOR; }
"<<"            { return SHL; }
">>"            { return SHR; }
">>>"           { return SSHR; }
"~&"            { return NAND; }
"~|"            { return NOR; }
"~^"            { return XNOR; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
"&"             { return '&'; }
"|"             { return '|'; }
"^"             { return '^'; }
"~"             { return '~'; }
"!"             { return '!'; }
"<"             { return '<'; }
">"             { return '>'; }
"?"             { return '?'; }
"="             { return '='; }

[0-9]+\'[bB][01_xXzZ]+[ \t]* {
    yylval.num = (VerilogNum *)malloc(sizeof(VerilogNum));
    yylval.num->value = 0;
    yylval.num->width = 0;
    yylval.num->is_signed = 0;
    const char *p = yytext;
    if (*p == '\'') {
        yylval.num->width = 0;
    } else {
        yylval.num->width = atoi(p);
        while (*p && *p != '\'') p++;
    }
    p++;
    p++;
    while (*p && *p != ' ' && *p != '\t') {
        yylval.num->value = (yylval.num->value << 1);
        if (*p == '1') yylval.num->value |= 1;
        p++;
    }
    if (yylval.num->width == 0) {
        int bits = 0;
        const char *q = yytext;
        while (*q && *q != '\'') { bits = bits * 10 + (*q - '0'); q++; }
        yylval.num->width = bits > 0 ? bits : 32;
    }
    return NUMBER;
}

[0-9]+\'[hH][0-9a-fA-F_xXzZ]+[ \t]* {
    yylval.num = (VerilogNum *)malloc(sizeof(VerilogNum));
    yylval.num->value = 0;
    yylval.num->width = 0;
    yylval.num->is_signed = 0;
    const char *p = yytext;
    if (*p == '\'') {
        yylval.num->width = 0;
    } else {
        yylval.num->width = atoi(p);
        while (*p && *p != '\'') p++;
    }
    p++; p++;
    while (*p && *p != ' ' && *p != '\t') {
        yylval.num->value = (yylval.num->value << 4);
        if (*p >= '0' && *p <= '9') yylval.num->value |= (*p - '0');
        else if (*p >= 'a' && *p <= 'f') yylval.num->value |= (*p - 'a' + 10);
        else if (*p >= 'A' && *p <= 'F') yylval.num->value |= (*p - 'A' + 10);
        p++;
    }
    if (yylval.num->width == 0) {
        int bits = 0;
        const char *q = yytext;
        while (*q && *q != '\'') { bits = bits * 10 + (*q - '0'); q++; }
        yylval.num->width = bits > 0 ? bits : 32;
    }
    return NUMBER;
}

[0-9]+\'[dD][0-9_xXzZ]+[ \t]* {
    yylval.num = (VerilogNum *)malloc(sizeof(VerilogNum));
    yylval.num->value = 0;
    yylval.num->width = 0;
    yylval.num->is_signed = 0;
    const char *p = yytext;
    if (*p == '\'') {
        yylval.num->width = 0;
    } else {
        yylval.num->width = atoi(p);
        while (*p && *p != '\'') p++;
    }
    p++; p++;
    yylval.num->value = strtoull(p, NULL, 10);
    if (yylval.num->width == 0) {
        int bits = 0;
        const char *q = yytext;
        while (*q && *q != '\'') { bits = bits * 10 + (*q - '0'); q++; }
        yylval.num->width = bits > 0 ? bits : 32;
    }
    return NUMBER;
}

[0-9]+ {
    yylval.num = (VerilogNum *)malloc(sizeof(VerilogNum));
    yylval.num->value = strtoull(yytext, NULL, 10);
    yylval.num->width = 32;
    yylval.num->is_signed = 0;
    return NUMBER;
}

[a-zA-Z_][a-zA-Z0-9_$]* {
    yylval.str = stralloc(yytext);
    return IDENTIFIER;
}

\"[^"]*\" {
    yylval.str = stralloc(yytext);
    return STRING;
}

[ \t\r]+    ;
\n          ;
.           { /* ignore unknown */ }

%%
