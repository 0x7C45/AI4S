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

#ifndef YY_YY_HOME_KALI_DOCUMENTS_GITHUB_AI4S_TRACK_A_A1_SIMULATOR_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_HOME_KALI_DOCUMENTS_GITHUB_AI4S_TRACK_A_A1_SIMULATOR_SRC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"

#ifndef VERILOG_NUM_DEFINED
#define VERILOG_NUM_DEFINED
#include <cstdint>
struct VerilogNum {
    uint64_t value;
    int width;
    int is_signed;
};
#endif

#line 61 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.h"

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
    GENERATE = 282,                /* GENERATE  */
    ENDGENERATE = 283,             /* ENDGENERATE  */
    GENVAR = 284,                  /* GENVAR  */
    SYS_FOPEN = 285,               /* SYS_FOPEN  */
    SYS_FCLOSE = 286,              /* SYS_FCLOSE  */
    SYS_FSCANF = 287,              /* SYS_FSCANF  */
    SYS_FGETS = 288,               /* SYS_FGETS  */
    SYS_FDISPLAY = 289,            /* SYS_FDISPLAY  */
    SYS_DISPLAY = 290,             /* SYS_DISPLAY  */
    SYS_FINISH = 291,              /* SYS_FINISH  */
    SYS_CLOG2 = 292,               /* SYS_CLOG2  */
    EQ = 293,                      /* EQ  */
    NE = 294,                      /* NE  */
    LE = 295,                      /* LE  */
    GE = 296,                      /* GE  */
    LOGAND = 297,                  /* LOGAND  */
    LOGOR = 298,                   /* LOGOR  */
    SHL = 299,                     /* SHL  */
    SHR = 300,                     /* SHR  */
    SSHR = 301,                    /* SSHR  */
    NAND = 302,                    /* NAND  */
    NOR = 303,                     /* NOR  */
    XNOR = 304,                    /* XNOR  */
    POWER = 305,                   /* POWER  */
    UNARY = 306                    /* UNARY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 45 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"

    struct VerilogNum *num;
    char *str;
    struct ASTNode *node;

#line 135 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_KALI_DOCUMENTS_GITHUB_AI4S_TRACK_A_A1_SIMULATOR_SRC_PARSER_TAB_H_INCLUDED  */
