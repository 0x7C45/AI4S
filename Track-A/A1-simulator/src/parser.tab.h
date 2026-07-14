/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_KALI_DOCUMENTS_GITHUB_AI4S_CLAUDE_WORKTREES_AGENT_AC2EB0B62000F7378_TRACK_A_A1_SIMULATOR_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_HOME_KALI_DOCUMENTS_GITHUB_AI4S_CLAUDE_WORKTREES_AGENT_AC2EB0B62000F7378_TRACK_A_A1_SIMULATOR_SRC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"

#ifndef VERILOG_NUM_DEFINED
#define VERILOG_NUM_DEFINED
#include <cstdint>
struct VerilogNum {
    uint64_t value;
    int width;
    int is_signed;
};
#endif

#line 61 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING = 259,                  /* STRING  */
    NUMBER = 260,                  /* NUMBER  */
    MODULE = 261,                  /* MODULE  */
    ENDMODULE = 262,               /* ENDMODULE  */
    INPUT = 263,                   /* INPUT  */
    OUTPUT = 264,                  /* OUTPUT  */
    WIRE = 265,                    /* WIRE  */
    REG = 266,                     /* REG  */
    INTEGER_KW = 267,              /* INTEGER_KW  */
    SIGNED = 268,                  /* SIGNED  */
    LOCALPARAM = 269,              /* LOCALPARAM  */
    PARAMETER = 270,               /* PARAMETER  */
    ASSIGN = 271,                  /* ASSIGN  */
    ALWAYS = 272,                  /* ALWAYS  */
    INITIAL_KW = 273,              /* INITIAL_KW  */
    BEGINKW = 274,                 /* BEGINKW  */
    END = 275,                     /* END  */
    IF = 276,                      /* IF  */
    ELSE = 277,                    /* ELSE  */
    CASE = 278,                    /* CASE  */
    ENDCASE = 279,                 /* ENDCASE  */
    DEFAULT = 280,                 /* DEFAULT  */
    FOR = 281,                     /* FOR  */
    REPEAT = 282,                  /* REPEAT  */
    WHILE = 283,                   /* WHILE  */
    GENERATE = 284,                /* GENERATE  */
    ENDGENERATE = 285,             /* ENDGENERATE  */
    GENVAR = 286,                  /* GENVAR  */
    POSEDGE = 287,                 /* POSEDGE  */
    NEGEDGE = 288,                 /* NEGEDGE  */
    OR = 289,                      /* OR  */
    SYS_FOPEN = 290,               /* SYS_FOPEN  */
    SYS_FCLOSE = 291,              /* SYS_FCLOSE  */
    SYS_FSCANF = 292,              /* SYS_FSCANF  */
    SYS_FGETS = 293,               /* SYS_FGETS  */
    SYS_FDISPLAY = 294,            /* SYS_FDISPLAY  */
    SYS_DISPLAY = 295,             /* SYS_DISPLAY  */
    SYS_FINISH = 296,              /* SYS_FINISH  */
    SYS_CLOG2 = 297,               /* SYS_CLOG2  */
    SYS_READMEMH = 298,            /* SYS_READMEMH  */
    SYS_READMEMB = 299,            /* SYS_READMEMB  */
    EQ = 300,                      /* EQ  */
    NE = 301,                      /* NE  */
    LE = 302,                      /* LE  */
    NONBLOCKING = 303,             /* NONBLOCKING  */
    GE = 304,                      /* GE  */
    LOGAND = 305,                  /* LOGAND  */
    LOGOR = 306,                   /* LOGOR  */
    SHL = 307,                     /* SHL  */
    SHR = 308,                     /* SHR  */
    SSHR = 309,                    /* SSHR  */
    NAND = 310,                    /* NAND  */
    NOR = 311,                     /* NOR  */
    XNOR = 312,                    /* XNOR  */
    POWER = 313,                   /* POWER  */
    UNARY = 314                    /* UNARY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 51 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"

    struct VerilogNum *num;
    char *str;
    struct ASTNode *node;

#line 143 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_KALI_DOCUMENTS_GITHUB_AI4S_CLAUDE_WORKTREES_AGENT_AC2EB0B62000F7378_TRACK_A_A1_SIMULATOR_SRC_PARSER_TAB_H_INCLUDED  */
