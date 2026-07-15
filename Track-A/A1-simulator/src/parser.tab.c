/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 13 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"

#include "ast.h"
#include "preprocessor.h"
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
struct yy_buffer_state;
using YY_BUFFER_STATE = struct yy_buffer_state *;
extern YY_BUFFER_STATE yy_scan_string(const char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

std::vector<ASTNode *> g_modules;
bool g_parse_ok = true;
static const PreprocessResult *g_preprocess_result = nullptr;

static ASTNode *makeNum(VerilogNum *n) {
    ASTNode *node = makeNode(NodeType::NUMBER, std::to_string(n->value), yylineno);
    node->msb = n->width - 1;
    node->lsb = 0;
    free(n);
    return node;
}

#line 110 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_MODULE = 6,                     /* MODULE  */
  YYSYMBOL_ENDMODULE = 7,                  /* ENDMODULE  */
  YYSYMBOL_INPUT = 8,                      /* INPUT  */
  YYSYMBOL_OUTPUT = 9,                     /* OUTPUT  */
  YYSYMBOL_WIRE = 10,                      /* WIRE  */
  YYSYMBOL_REG = 11,                       /* REG  */
  YYSYMBOL_INTEGER_KW = 12,                /* INTEGER_KW  */
  YYSYMBOL_SIGNED = 13,                    /* SIGNED  */
  YYSYMBOL_LOCALPARAM = 14,                /* LOCALPARAM  */
  YYSYMBOL_PARAMETER = 15,                 /* PARAMETER  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_ALWAYS = 17,                    /* ALWAYS  */
  YYSYMBOL_INITIAL_KW = 18,                /* INITIAL_KW  */
  YYSYMBOL_BEGINKW = 19,                   /* BEGINKW  */
  YYSYMBOL_END = 20,                       /* END  */
  YYSYMBOL_IF = 21,                        /* IF  */
  YYSYMBOL_ELSE = 22,                      /* ELSE  */
  YYSYMBOL_CASE = 23,                      /* CASE  */
  YYSYMBOL_ENDCASE = 24,                   /* ENDCASE  */
  YYSYMBOL_DEFAULT = 25,                   /* DEFAULT  */
  YYSYMBOL_FOR = 26,                       /* FOR  */
  YYSYMBOL_REPEAT = 27,                    /* REPEAT  */
  YYSYMBOL_WHILE = 28,                     /* WHILE  */
  YYSYMBOL_GENERATE = 29,                  /* GENERATE  */
  YYSYMBOL_ENDGENERATE = 30,               /* ENDGENERATE  */
  YYSYMBOL_GENVAR = 31,                    /* GENVAR  */
  YYSYMBOL_FUNCTION = 32,                  /* FUNCTION  */
  YYSYMBOL_ENDFUNCTION = 33,               /* ENDFUNCTION  */
  YYSYMBOL_POSEDGE = 34,                   /* POSEDGE  */
  YYSYMBOL_NEGEDGE = 35,                   /* NEGEDGE  */
  YYSYMBOL_OR = 36,                        /* OR  */
  YYSYMBOL_SYS_FOPEN = 37,                 /* SYS_FOPEN  */
  YYSYMBOL_SYS_FCLOSE = 38,                /* SYS_FCLOSE  */
  YYSYMBOL_SYS_FSCANF = 39,                /* SYS_FSCANF  */
  YYSYMBOL_SYS_FGETS = 40,                 /* SYS_FGETS  */
  YYSYMBOL_SYS_FDISPLAY = 41,              /* SYS_FDISPLAY  */
  YYSYMBOL_SYS_DISPLAY = 42,               /* SYS_DISPLAY  */
  YYSYMBOL_SYS_FINISH = 43,                /* SYS_FINISH  */
  YYSYMBOL_SYS_CLOG2 = 44,                 /* SYS_CLOG2  */
  YYSYMBOL_SYS_READMEMH = 45,              /* SYS_READMEMH  */
  YYSYMBOL_SYS_READMEMB = 46,              /* SYS_READMEMB  */
  YYSYMBOL_SYS_DUMPFILE = 47,              /* SYS_DUMPFILE  */
  YYSYMBOL_SYS_DUMPVARS = 48,              /* SYS_DUMPVARS  */
  YYSYMBOL_SYS_ERROR = 49,                 /* SYS_ERROR  */
  YYSYMBOL_SYS_UNSIGNED = 50,              /* SYS_UNSIGNED  */
  YYSYMBOL_SYS_TIME = 51,                  /* SYS_TIME  */
  YYSYMBOL_EQ = 52,                        /* EQ  */
  YYSYMBOL_NE = 53,                        /* NE  */
  YYSYMBOL_LE = 54,                        /* LE  */
  YYSYMBOL_NONBLOCKING = 55,               /* NONBLOCKING  */
  YYSYMBOL_GE = 56,                        /* GE  */
  YYSYMBOL_LOGAND = 57,                    /* LOGAND  */
  YYSYMBOL_LOGOR = 58,                     /* LOGOR  */
  YYSYMBOL_SHL = 59,                       /* SHL  */
  YYSYMBOL_SHR = 60,                       /* SHR  */
  YYSYMBOL_SSHR = 61,                      /* SSHR  */
  YYSYMBOL_NAND = 62,                      /* NAND  */
  YYSYMBOL_NOR = 63,                       /* NOR  */
  YYSYMBOL_XNOR = 64,                      /* XNOR  */
  YYSYMBOL_PART_PLUS = 65,                 /* PART_PLUS  */
  YYSYMBOL_PART_MINUS = 66,                /* PART_MINUS  */
  YYSYMBOL_67_ = 67,                       /* '?'  */
  YYSYMBOL_68_ = 68,                       /* ':'  */
  YYSYMBOL_69_ = 69,                       /* '|'  */
  YYSYMBOL_70_ = 70,                       /* '^'  */
  YYSYMBOL_71_ = 71,                       /* '&'  */
  YYSYMBOL_72_ = 72,                       /* '<'  */
  YYSYMBOL_73_ = 73,                       /* '>'  */
  YYSYMBOL_74_ = 74,                       /* '+'  */
  YYSYMBOL_75_ = 75,                       /* '-'  */
  YYSYMBOL_76_ = 76,                       /* '*'  */
  YYSYMBOL_77_ = 77,                       /* '/'  */
  YYSYMBOL_78_ = 78,                       /* '%'  */
  YYSYMBOL_POWER = 79,                     /* POWER  */
  YYSYMBOL_80_ = 80,                       /* '!'  */
  YYSYMBOL_81_ = 81,                       /* '~'  */
  YYSYMBOL_UNARY = 82,                     /* UNARY  */
  YYSYMBOL_83_ = 83,                       /* ';'  */
  YYSYMBOL_84_ = 84,                       /* '#'  */
  YYSYMBOL_85_ = 85,                       /* '('  */
  YYSYMBOL_86_ = 86,                       /* ')'  */
  YYSYMBOL_87_ = 87,                       /* ','  */
  YYSYMBOL_88_ = 88,                       /* '='  */
  YYSYMBOL_89_ = 89,                       /* '@'  */
  YYSYMBOL_90_ = 90,                       /* '.'  */
  YYSYMBOL_91_ = 91,                       /* '['  */
  YYSYMBOL_92_ = 92,                       /* ']'  */
  YYSYMBOL_93_ = 93,                       /* '{'  */
  YYSYMBOL_94_ = 94,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_source = 96,                    /* source  */
  YYSYMBOL_module_list = 97,               /* module_list  */
  YYSYMBOL_module = 98,                    /* module  */
  YYSYMBOL_module_param_decls = 99,        /* module_param_decls  */
  YYSYMBOL_module_param_decl = 100,        /* module_param_decl  */
  YYSYMBOL_opt_port_list = 101,            /* opt_port_list  */
  YYSYMBOL_port_list = 102,                /* port_list  */
  YYSYMBOL_port_decl_in_list = 103,        /* port_decl_in_list  */
  YYSYMBOL_module_items = 104,             /* module_items  */
  YYSYMBOL_module_item = 105,              /* module_item  */
  YYSYMBOL_procedural_decl = 106,          /* procedural_decl  */
  YYSYMBOL_function_items = 107,           /* function_items  */
  YYSYMBOL_function_item = 108,            /* function_item  */
  YYSYMBOL_function_port_decl = 109,       /* function_port_decl  */
  YYSYMBOL_function_port_names = 110,      /* function_port_names  */
  YYSYMBOL_gen_case_items = 111,           /* gen_case_items  */
  YYSYMBOL_gen_case_item = 112,            /* gen_case_item  */
  YYSYMBOL_port_decl = 113,                /* port_decl  */
  YYSYMBOL_decl_list = 114,                /* decl_list  */
  YYSYMBOL_stmt = 115,                     /* stmt  */
  YYSYMBOL_stmts = 116,                    /* stmts  */
  YYSYMBOL_event_list = 117,               /* event_list  */
  YYSYMBOL_event_expr = 118,               /* event_expr  */
  YYSYMBOL_readmem_args = 119,             /* readmem_args  */
  YYSYMBOL_gen_items = 120,                /* gen_items  */
  YYSYMBOL_gen_item = 121,                 /* gen_item  */
  YYSYMBOL_genvar_list = 122,              /* genvar_list  */
  YYSYMBOL_gen_block = 123,                /* gen_block  */
  YYSYMBOL_gen_body = 124,                 /* gen_body  */
  YYSYMBOL_case_items = 125,               /* case_items  */
  YYSYMBOL_case_item = 126,                /* case_item  */
  YYSYMBOL_param_override = 127,           /* param_override  */
  YYSYMBOL_param_list = 128,               /* param_list  */
  YYSYMBOL_param_assign = 129,             /* param_assign  */
  YYSYMBOL_port_conn_list = 130,           /* port_conn_list  */
  YYSYMBOL_port_conn = 131,                /* port_conn  */
  YYSYMBOL_range = 132,                    /* range  */
  YYSYMBOL_expr = 133,                     /* expr  */
  YYSYMBOL_prim_expr = 134,                /* prim_expr  */
  YYSYMBOL_lvalue = 135,                   /* lvalue  */
  YYSYMBOL_lvalue_list = 136,              /* lvalue_list  */
  YYSYMBOL_expr_list = 137                 /* expr_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3482

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  223
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  632

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,    84,     2,    78,    71,     2,
      85,    86,    76,    74,    87,    75,    90,    77,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    83,
      72,    88,    73,    67,    89,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    91,     2,    92,    70,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,    69,    94,    81,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    79,    82
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    93,    93,    97,    98,   102,   109,   121,   122,   126,
     131,   132,   136,   137,   141,   142,   143,   147,   148,   149,
     153,   154,   167,   178,   180,   191,   201,   203,   205,   215,
     217,   219,   221,   223,   227,   229,   238,   240,   242,   244,
     257,   259,   268,   274,   276,   278,   281,   283,   285,   287,
     288,   289,   295,   302,   306,   312,   321,   330,   331,   332,
     336,   337,   338,   342,   352,   362,   364,   368,   369,   373,
     375,   381,   392,   400,   410,   418,   428,   436,   446,   454,
     464,   472,   482,   492,   503,   504,   508,   509,   510,   511,
     513,   515,   516,   522,   528,   534,   541,   547,   557,   563,
     570,   576,   583,   589,   596,   603,   609,   616,   623,   624,
     625,   630,   636,   642,   648,   653,   662,   672,   682,   689,
     698,   699,   703,   705,   710,   712,   717,   722,   723,   727,
     735,   744,   750,   757,   763,   771,   772,   776,   777,   778,
     782,   783,   784,   785,   789,   790,   794,   800,   807,   812,
     820,   825,   826,   830,   834,   835,   839,   845,   850,   858,
     870,   871,   872,   873,   874,   875,   876,   877,   878,   879,
     880,   881,   882,   883,   884,   885,   886,   887,   888,   889,
     890,   891,   892,   893,   898,   899,   900,   901,   902,   903,
     904,   905,   906,   910,   914,   916,   921,   929,   931,   936,
     943,   949,   958,   966,   974,   985,   992,  1004,  1008,  1014,
    1021,  1026,  1034,  1039,  1046,  1052,  1060,  1068,  1076,  1086,
    1096,  1097,  1101,  1102
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "STRING",
  "NUMBER", "MODULE", "ENDMODULE", "INPUT", "OUTPUT", "WIRE", "REG",
  "INTEGER_KW", "SIGNED", "LOCALPARAM", "PARAMETER", "ASSIGN", "ALWAYS",
  "INITIAL_KW", "BEGINKW", "END", "IF", "ELSE", "CASE", "ENDCASE",
  "DEFAULT", "FOR", "REPEAT", "WHILE", "GENERATE", "ENDGENERATE", "GENVAR",
  "FUNCTION", "ENDFUNCTION", "POSEDGE", "NEGEDGE", "OR", "SYS_FOPEN",
  "SYS_FCLOSE", "SYS_FSCANF", "SYS_FGETS", "SYS_FDISPLAY", "SYS_DISPLAY",
  "SYS_FINISH", "SYS_CLOG2", "SYS_READMEMH", "SYS_READMEMB",
  "SYS_DUMPFILE", "SYS_DUMPVARS", "SYS_ERROR", "SYS_UNSIGNED", "SYS_TIME",
  "EQ", "NE", "LE", "NONBLOCKING", "GE", "LOGAND", "LOGOR", "SHL", "SHR",
  "SSHR", "NAND", "NOR", "XNOR", "PART_PLUS", "PART_MINUS", "'?'", "':'",
  "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "POWER", "'!'", "'~'", "UNARY", "';'", "'#'", "'('", "')'", "','", "'='",
  "'@'", "'.'", "'['", "']'", "'{'", "'}'", "$accept", "source",
  "module_list", "module", "module_param_decls", "module_param_decl",
  "opt_port_list", "port_list", "port_decl_in_list", "module_items",
  "module_item", "procedural_decl", "function_items", "function_item",
  "function_port_decl", "function_port_names", "gen_case_items",
  "gen_case_item", "port_decl", "decl_list", "stmt", "stmts", "event_list",
  "event_expr", "readmem_args", "gen_items", "gen_item", "genvar_list",
  "gen_block", "gen_body", "case_items", "case_item", "param_override",
  "param_list", "param_assign", "port_conn_list", "port_conn", "range",
  "expr", "prim_expr", "lvalue", "lvalue_list", "expr_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-396)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      56,    11,    39,    56,  -396,    52,  -396,  -396,    49,   107,
      -1,    85,  -396,    74,    23,   -18,  -396,  -396,  1759,   125,
      95,  -396,  -396,     2,    72,  1377,   173,  -396,    14,    47,
      72,   194,  -396,   107,     8,    15,    75,   203,   216,    20,
       6,    -3,   921,   123,    33,   218,    21,   142,  1675,  -396,
     147,   159,   157,   149,    85,  -396,   245,   276,   -19,  -396,
    -396,   204,   209,   211,  -396,  1377,  1377,  1377,  1377,  1377,
    1377,  1377,  1377,  1377,  1377,  3215,  -396,  -396,  -396,   315,
    -396,    72,   322,   326,  -396,  -396,   257,   268,   272,   359,
     277,    72,   363,  -396,   280,   281,   371,   285,     6,   289,
    1377,    -6,   -36,    77,   381,   404,   313,   314,   318,   320,
     321,   323,   324,   325,   327,   -32,   329,   334,   335,   341,
     349,  -396,   395,   350,   353,  -396,   -30,  1377,   352,   354,
     355,   218,   163,  -396,  -396,    46,   360,   401,   364,  -396,
    -396,  -396,  -396,  1377,   372,  -396,  -396,  -396,  1169,  1377,
     452,  1377,  1377,  -396,  -396,  -396,  -396,  -396,  -396,  -396,
    -396,  2181,  1745,   -20,  1377,  1377,  1377,  1377,  1377,  1377,
    1377,  1377,  1377,  1377,  1377,  1377,  1377,  1377,  1377,  1377,
    1377,  1377,  1377,  1377,  1377,  1220,  1377,  1377,  -396,   454,
    -396,  -396,   950,   364,  1377,    92,     3,  1377,   117,   455,
     148,   124,  1377,  1377,   373,  1377,  -396,     9,  1377,   274,
     921,    -5,  1377,  -396,   457,  -396,  -396,   461,  -396,   672,
    1377,  1377,     6,  1377,  1377,   463,  1377,  1427,  1477,  -396,
    1377,  1377,  1377,   464,  1377,  1377,   382,   156,  -396,  1377,
    1012,  2212,  1377,  1377,    34,   126,  -396,  -396,  -396,   466,
     721,   387,   468,   151,  -396,  3323,  1759,  -396,  3323,   169,
    1788,   174,  2243,  2274,  -396,  1377,  1377,  -396,   193,   193,
     198,   198,  3377,  3350,    45,    45,    45,  1457,  1457,  3404,
    3242,  1906,   319,  3404,  1457,   198,   198,    31,    31,  1377,
    -396,  -396,  -396,  -396,   390,   471,   176,  -396,  3323,   196,
    2739,  -396,   472,  1377,   133,   394,  2767,  -396,  -396,  1377,
     139,   396,  -396,  2795,  2823,  1377,  1825,     6,  -396,  2851,
    -396,  -396,   475,   477,   398,   -23,  -396,  2879,   399,  -396,
     399,   770,  -396,  -396,  2305,  2336,   393,  2367,  2398,   403,
    2429,   405,   201,   406,   205,  2460,   408,   409,   413,   414,
     212,   217,  -396,   479,   482,  2907,   410,   416,   419,  2935,
    1702,  2491,  2522,   402,   502,  -396,  -396,    82,   423,   574,
    -396,   424,  -396,   721,   425,  -396,   364,  1729,  -396,  1377,
    1377,  1377,   417,  -396,   505,  -396,  -396,    10,  3323,  1377,
    -396,  -396,  -396,   426,   429,  1270,   510,  -396,  -396,  2963,
    -396,  -396,  -396,   145,  2991,  -396,  -396,  -396,  -396,  3019,
    1377,  1377,  1377,   427,  -396,  -396,  -396,  -396,   921,   271,
     921,  -396,   399,  -396,   819,   921,  1273,  1377,   921,   921,
     431,   433,   434,   436,   437,   438,   439,   440,   441,   442,
     445,   446,   444,   448,  -396,   527,  1377,  1377,  -396,  1557,
    -396,   513,  1702,  1324,  1377,   449,  -396,   529,  -396,  -396,
    -396,  -396,   623,  1377,  -396,  -396,  1933,  1960,  1987,  1377,
     450,   447,  3377,  1374,  -396,  -396,   462,  -396,  -396,  -396,
    -396,  2014,  2041,  2068,  1377,  -396,  -396,  -396,  -396,   518,
     868,  1064,  -396,  2149,  3047,  -396,  -396,  -396,  -396,  -396,
    -396,  -396,  -396,  -396,  -396,  -396,  -396,  -396,  -396,   459,
     465,   221,   223,   227,   467,   218,   543,  -396,  -396,  1582,
    1702,   531,   483,  1116,  -396,  3269,  3075,  1377,   469,  -396,
    -396,  2553,  -396,  -396,  -396,  1852,  -396,  -396,  -396,  2584,
    1166,  -396,  -396,  -396,  1879,   921,   921,  -396,  -396,  -396,
     921,  1377,  1377,  -396,  -396,   474,   476,   478,  1377,   146,
    1644,  -396,  -396,  -396,  -396,  1702,  1702,  -396,  -396,  1702,
    1377,  3103,   551,   469,  -396,  1377,  -396,  -396,   480,   253,
    1377,  -396,  -396,  -396,  -396,  3296,  3131,  -396,  -396,  -396,
    2615,  -396,  1619,  -396,  -396,  -396,  3159,  1377,  -396,  2095,
    -396,   481,  2122,   921,     6,  1702,  -396,     6,  3187,  -396,
    -396,  -396,  -396,   470,   538,   485,   559,  1377,  1702,  1377,
     486,  2646,  -396,  2677,  1377,   921,  1702,  2708,  -396,  -396,
    1702,  -396
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,    11,     1,     3,     0,    16,
       0,     0,    14,     0,     0,     0,    13,    15,    19,     0,
       0,     8,    72,     0,     0,     0,     0,    74,     0,     0,
       0,     0,    10,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
       0,     0,     0,    11,     0,    78,     0,     0,   198,   211,
     193,     0,     0,     0,   194,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,    71,    76,     0,
      80,     0,     0,     0,    73,    12,     0,     0,    85,     0,
      85,     0,     0,    85,     0,     0,     0,   212,     0,     0,
       0,     0,   212,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    86,     0,     0,     0,    44,     0,     0,     0,     0,
       0,     0,     0,   128,   136,     0,     0,     0,     0,     5,
      17,    20,    53,     0,     0,     7,    77,    82,     0,     0,
       0,     0,     0,   187,   188,   190,   191,   189,   184,   185,
     186,     0,   223,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
      79,    81,     0,     0,     0,     0,    85,     0,     0,     0,
      85,     0,     0,     0,     0,     0,   221,     0,     0,     0,
       0,     0,     0,    85,     0,    85,    88,     0,   121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,     0,     0,     0,     0,     0,     0,     0,    91,     0,
       0,     0,     0,     0,     0,     0,    49,   127,    43,     0,
      59,     0,     0,     0,   152,     9,    19,   197,   223,     0,
       0,     0,     0,     0,   207,     0,     0,   205,   171,   172,
     175,   176,   181,   182,   177,   178,   179,   169,   170,   168,
       0,     0,   166,   167,   165,   173,   174,   160,   161,     0,
     162,   163,   164,    83,     0,     0,     0,   155,   158,     0,
       0,    26,     0,     0,     0,     0,     0,    30,    85,     0,
       0,     0,    32,     0,     0,     0,     0,     0,   219,     0,
      40,    38,     0,     0,     0,     0,   123,     0,    56,    85,
      54,     0,    87,   120,     0,     0,     0,     0,     0,     0,
       0,   211,     0,   211,     0,     0,     0,   126,     0,     0,
       0,     0,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   134,   135,     0,     0,     0,
      58,     0,    62,    59,     0,   150,     0,     0,   196,     0,
       0,     0,   200,   208,     0,   210,   195,     0,   222,     0,
     159,   180,    48,     0,     0,     0,     0,    25,    84,     0,
      23,    21,    29,     0,     0,    27,    22,    33,    34,     0,
       0,     0,     0,   214,   220,    36,   124,   125,     0,     0,
       0,    99,    55,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   100,     0,     0,     0,    98,     0,
     139,    51,     0,     0,     0,     0,    66,     0,    61,    42,
      57,    60,     0,     0,   151,     6,     0,     0,     0,     0,
       0,     0,   183,     0,    46,   154,     0,    24,    31,    28,
      35,     0,     0,     0,     0,    37,   122,    39,    89,    94,
       0,     0,   145,     0,     0,    92,    93,   113,   114,   119,
     118,   102,   101,   109,   103,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,     0,     0,   142,   143,     0,
       0,   131,     0,     0,    68,     0,     0,     0,    64,    66,
      41,     0,   202,   203,   199,     0,   209,   206,   157,     0,
       0,   216,   217,   213,     0,     0,     0,   149,    96,   144,
       0,     0,     0,   111,   112,   208,     0,     0,     0,     0,
       0,   137,   140,   141,    52,     0,     0,   133,    67,     0,
       0,     0,     0,    63,   153,     0,   204,   156,     0,     0,
       0,   218,    95,   148,   146,     0,     0,   115,   116,   117,
       0,    43,     0,   132,    70,    69,     0,     0,    65,     0,
      47,     0,     0,     0,     0,     0,   138,     0,     0,   201,
      45,   215,   147,     0,    51,     0,     0,     0,     0,     0,
       0,     0,    52,     0,     0,     0,     0,     0,    97,   130,
       0,   129
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -396,  -396,  -396,   562,  -396,   512,   515,  -396,   536,   328,
     -16,  -238,   202,  -361,  -396,    42,  -396,    55,    43,   -83,
      -7,   248,  -396,   161,   351,  -396,   -43,  -127,  -395,    27,
    -396,    90,  -396,   397,   213,    48,   208,    -8,   -25,  -396,
     -37,  -396,    16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     4,    20,    21,    10,    15,    16,    48,
     450,   124,   369,   370,   371,   528,   523,   524,    50,   195,
     372,   219,   325,   326,   346,   132,   518,   135,   451,   519,
     491,   492,    51,   253,   254,   296,   297,    26,   258,    76,
     126,   207,   347
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      75,   133,    49,    99,   245,    55,    31,   198,   460,    97,
     201,    86,   368,   419,     5,    56,    57,    78,    88,   212,
      79,    82,    83,    95,   136,   239,    27,    89,    92,   322,
     323,    96,   140,    28,    29,   125,    30,   363,   137,     6,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
      80,   229,    17,   230,   128,   205,   129,   521,   240,   130,
      81,   206,     1,   420,   131,   364,   148,   266,    32,    33,
     210,   324,   149,   189,   267,   209,    17,    22,    90,   211,
     213,   100,    18,   199,    23,   456,   101,    24,    91,   247,
     163,   303,    87,    25,    25,   214,   317,   266,   218,    98,
      19,   460,   241,   318,   471,    25,    25,   185,   186,   187,
      12,    25,    25,   304,    25,    13,    14,   310,   255,   183,
     184,   185,   186,   187,   260,   564,   262,   263,    52,   248,
     328,   368,   330,   249,    11,   368,     8,     9,    25,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     290,   291,   292,    25,   259,    25,    25,   298,    25,   300,
     593,   594,   306,    25,   595,   301,    77,   313,   314,   302,
     316,    53,    54,   319,   128,   336,   129,   327,   305,   130,
     353,   354,   311,   246,   131,   334,   335,    84,   337,   338,
     307,   340,   320,   321,   302,   345,    93,   312,   127,   365,
     614,   302,   333,   249,   355,   359,   400,   361,   362,    94,
     302,   134,   405,   622,   368,   403,   302,   138,   478,   591,
     141,   629,   302,   249,     9,   631,   309,   375,   376,    25,
      49,   388,   142,   342,   344,   143,   422,   166,   146,   167,
     350,   351,   170,   171,   172,   378,   266,   170,   171,   172,
     383,   384,   394,   395,   391,   181,   182,   183,   184,   185,
     186,   187,   183,   184,   185,   186,   187,   102,   399,   147,
     414,   387,   396,   376,   404,   103,   104,   433,   266,   150,
     409,   435,   266,   105,   151,   106,   152,   107,   440,   266,
     108,   109,   110,   441,   266,   322,   323,   555,   384,   556,
     266,   111,   112,   557,   266,   113,   114,   115,   188,   116,
     117,   118,   119,   120,   218,   190,   164,   165,   166,   191,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   601,
     395,   176,   192,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   193,   466,   467,   468,   121,   122,   457,
     194,   140,   196,   123,   472,   197,   200,    98,   202,   203,
     298,   164,   165,   166,   204,   167,   205,   208,   170,   171,
     172,   173,   174,   175,   215,   481,   482,   483,   559,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   220,   221,
     236,   493,   494,   222,   251,   223,   224,   102,   225,   226,
     227,   485,   228,   487,   231,   103,   104,   333,   489,   232,
     233,   495,   496,   105,   216,   106,   234,   107,   525,   526,
     108,   109,   110,   517,   235,   237,   238,   242,   531,   243,
     244,   111,   112,   250,   535,   113,   114,   115,   539,   116,
     117,   118,   119,   120,   252,   256,   261,   293,   308,   544,
     329,   315,   512,   513,   331,   352,   493,   339,   349,   366,
     373,   374,   217,   392,   393,   398,   563,   401,   416,   406,
     417,   427,   442,   547,   418,   443,   302,   121,   122,   430,
     454,   432,   434,   123,   437,   445,   266,    98,   525,   438,
     439,   446,   571,   562,   447,   455,   458,   461,   469,   470,
     463,   473,   474,   476,   497,   298,   498,   499,   484,   500,
     501,   502,   503,   504,   505,   506,   585,   586,   507,   508,
     509,   511,   529,   590,   510,   520,   536,   527,   582,   583,
     545,   537,   553,   584,   517,   596,   560,   540,   554,   563,
     599,   566,   558,   565,   598,   602,   572,   587,   617,   588,
     618,   589,   620,   600,   610,     7,   145,   613,   144,    85,
     615,   573,   608,   619,   624,   462,   562,   102,   568,   424,
     486,   549,   367,   348,   377,   103,   104,   592,   579,   464,
     299,     0,   621,   105,   623,   106,   612,   107,     0,   627,
     108,   109,   110,   475,     0,     0,     0,   459,     0,     0,
       0,   111,   112,     0,     0,   113,   114,   115,   628,   116,
     117,   118,   119,   120,     0,     0,   102,     0,     0,     0,
       0,   367,     0,     0,   103,   104,     0,     0,     0,     0,
       0,     0,   105,     0,   106,     0,   107,     0,     0,   108,
     109,   110,     0,     0,     0,     0,   530,   121,   122,     0,
     111,   112,     0,   123,   113,   114,   115,    98,   116,   117,
     118,   119,   120,     0,     0,   102,     0,     0,     0,     0,
       0,     0,     0,   103,   104,     0,     0,     0,     0,     0,
       0,   105,   332,   106,     0,   107,     0,     0,   108,   109,
     110,     0,     0,     0,     0,     0,   121,   122,     0,   111,
     112,     0,   123,   113,   114,   115,    98,   116,   117,   118,
     119,   120,     0,     0,   102,     0,     0,     0,     0,   367,
       0,     0,   103,   104,     0,     0,     0,     0,     0,     0,
     105,     0,   106,     0,   107,     0,     0,   108,   109,   110,
       0,     0,     0,     0,     0,   121,   122,     0,   111,   112,
       0,   123,   113,   114,   115,    98,   116,   117,   118,   119,
     120,     0,     0,   102,     0,     0,     0,     0,     0,     0,
       0,   103,   104,     0,     0,     0,     0,     0,     0,   105,
     423,   106,     0,   107,     0,     0,   108,   109,   110,     0,
       0,     0,     0,     0,   121,   122,     0,   111,   112,     0,
     123,   113,   114,   115,    98,   116,   117,   118,   119,   120,
       0,     0,   102,     0,     0,     0,     0,     0,     0,     0,
     103,   104,     0,     0,     0,     0,     0,     0,   105,   488,
     106,     0,   107,     0,     0,   108,   109,   110,     0,     0,
       0,     0,     0,   121,   122,     0,   111,   112,     0,   123,
     113,   114,   115,    98,   116,   117,   118,   119,   120,     0,
       0,   102,     0,     0,     0,     0,     0,     0,     0,   103,
     104,     0,     0,     0,     0,     0,     0,   105,     0,   106,
       0,   107,     0,     0,   108,   109,   110,     0,     0,     0,
       0,     0,   121,   122,     0,   111,   112,     0,   123,   113,
     114,   115,    98,   116,   117,   118,   119,   120,     0,     0,
       0,     0,     0,     0,   102,     0,     0,     0,     0,     0,
       0,     0,   103,   104,     0,     0,   546,     0,     0,     0,
     105,     0,   106,     0,   107,     0,     0,   108,   109,   110,
       0,   121,   122,    58,    59,    60,     0,   123,   111,   112,
       0,    98,   113,   114,   115,     0,   116,   117,   118,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,     0,
      63,    64,     0,     0,   121,   122,     0,     0,     0,     0,
     123,     0,    65,    66,    98,    58,    59,    60,     0,    67,
      68,    69,     0,     0,     0,    70,     0,     0,     0,     0,
      71,    72,     0,     0,     0,    73,   294,     0,     0,     0,
     295,     0,     0,    74,     0,     0,     0,     0,     0,   356,
       0,   357,   358,     0,     0,     0,    62,     0,     0,     0,
       0,     0,    63,    64,     0,     0,     0,    58,    59,    60,
       0,     0,     0,     0,    65,    66,     0,     0,     0,     0,
       0,    67,    68,    69,     0,     0,     0,    70,   548,   490,
       0,     0,    71,    72,     0,     0,     0,    73,     0,     0,
       0,    61,     0,     0,     0,    74,     0,     0,    62,     0,
       0,     0,     0,     0,    63,    64,     0,     0,     0,    58,
      59,    60,     0,     0,     0,     0,    65,    66,     0,     0,
       0,     0,     0,    67,    68,    69,     0,     0,     0,    70,
     567,   522,     0,     0,    71,    72,     0,     0,     0,    73,
       0,     0,     0,    61,     0,     0,     0,    74,     0,     0,
      62,     0,     0,     0,     0,     0,    63,    64,     0,    58,
      59,    60,    58,    59,    60,     0,     0,     0,    65,    66,
       0,     0,     0,     0,     0,    67,    68,    69,     0,     0,
       0,    70,     0,     0,     0,     0,    71,    72,     0,     0,
       0,    73,     0,    61,     0,     0,    61,     0,     0,    74,
      62,     0,     0,    62,     0,     0,    63,    64,     0,    63,
      64,     0,     0,    58,    59,    60,     0,     0,    65,    66,
       0,    65,    66,     0,     0,    67,    68,    69,    67,    68,
      69,    70,     0,     0,    70,     0,    71,    72,     0,    71,
      72,    73,   578,     0,    73,   257,   295,    61,     0,    74,
       0,     0,    74,     0,    62,     0,     0,     0,     0,     0,
      63,    64,     0,    58,    59,    60,    58,    59,    60,     0,
       0,     0,    65,    66,     0,     0,     0,     0,     0,    67,
      68,    69,     0,     0,     0,    70,   289,     0,   490,     0,
      71,    72,     0,     0,     0,    73,     0,    61,     0,     0,
      61,     0,     0,    74,    62,     0,     0,    62,     0,     0,
      63,    64,     0,    63,    64,     0,     0,    58,    59,    60,
       0,     0,    65,    66,     0,    65,    66,     0,     0,    67,
      68,    69,    67,    68,    69,    70,     0,     0,    70,   522,
      71,    72,     0,    71,    72,    73,     0,     0,    73,     0,
     295,    61,     0,    74,     0,     0,    74,     0,    62,     0,
       0,     0,     0,     0,    63,    64,     0,    58,    59,    60,
      58,    59,    60,     0,     0,     0,    65,    66,     0,     0,
       0,     0,     0,    67,    68,    69,     0,     0,     0,    70,
       0,     0,     0,     0,    71,    72,     0,     0,     0,    73,
       0,    61,     0,     0,    61,     0,     0,    74,    62,     0,
       0,    62,     0,     0,    63,    64,     0,    63,    64,     0,
      58,   341,    60,     0,     0,     0,    65,    66,     0,    65,
      66,     0,     0,    67,    68,    69,    67,    68,    69,    70,
       0,     0,    70,     0,    71,    72,     0,    71,    72,    73,
     538,     0,    73,     0,    61,     0,     0,    74,     0,     0,
      74,    62,     0,     0,     0,     0,     0,    63,    64,     0,
      58,   343,    60,     0,     0,     0,     0,     0,     0,    65,
      66,     0,     0,     0,     0,     0,    67,    68,    69,     0,
       0,     0,    70,     0,     0,     0,     0,    71,    72,   164,
     165,   166,    73,   167,    61,     0,   170,   171,   172,     0,
      74,    62,     0,     0,     0,     0,     0,    63,    64,   181,
     182,   183,   184,   185,   186,   187,     0,     0,     0,    65,
      66,     0,     0,     0,     0,     0,    67,    68,    69,     0,
       0,     0,    70,     0,     0,     0,     0,    71,    72,     0,
      34,     0,    73,     0,     0,    13,    14,    35,    36,    37,
      74,    38,    39,    40,    41,    42,     0,     0,   514,     0,
     129,     0,     0,   130,     0,    34,    44,     0,   515,    46,
      13,    14,    35,    36,    37,     0,    38,    39,    40,    41,
      42,     0,   561,   514,     0,   129,     0,     0,   130,     0,
       0,    44,     0,   515,    46,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,   516,     0,    13,    14,    35,
      36,    37,     0,    38,    39,    40,    41,    42,     0,   606,
     514,    47,   129,     0,     0,   130,     0,    34,    44,     0,
     515,    46,    13,    14,    35,    36,    37,     0,    38,    39,
      40,    41,    42,     0,     0,   514,    47,   129,     0,     0,
     130,     0,     0,    44,     0,   515,    46,     0,    34,     0,
       0,     0,   139,    13,    14,    35,    36,    37,     0,    38,
      39,    40,    41,    42,     0,     0,    43,     0,     0,     0,
       0,     0,     0,    47,    44,    34,    45,    46,     0,     0,
      13,    14,    35,    36,    37,     0,    38,    39,    40,    41,
      42,   449,     0,    43,     0,     0,     0,     0,    47,     0,
       0,    44,    34,    45,    46,     0,   465,    13,    14,    35,
      36,    37,     0,    38,    39,    40,    41,    42,     0,     0,
      43,     0,     0,     0,     0,     0,     0,     0,    44,    47,
      45,    46,    34,     0,     0,     0,     0,    13,    14,    35,
      36,    37,     0,    38,    39,    40,    41,    42,     0,     0,
      43,     0,     0,     0,     0,     0,    47,     0,    44,     0,
      45,    46,     0,     0,     0,     0,     0,   164,   165,   166,
       0,   167,   168,   169,   170,   171,   172,   173,   174,   175,
       0,     0,   176,    47,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   265,     0,
     164,   165,   166,    47,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   379,   380,   176,   381,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   164,   165,   166,
     382,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     410,   411,   176,   412,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   164,   165,   166,     0,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   413,     0,   176,
     575,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   164,   165,   166,     0,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   576,     0,   176,   580,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   164,   165,
     166,     0,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   581,     0,   176,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   164,   165,   166,     0,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   390,     0,
     176,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   164,   165,   166,     0,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   532,     0,   176,     0,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   164,
     165,   166,     0,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   533,     0,   176,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   164,   165,   166,     0,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   534,
       0,   176,     0,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   164,   165,   166,     0,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   541,     0,   176,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     164,   165,   166,     0,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   542,     0,   176,     0,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   164,   165,   166,
       0,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     543,     0,   176,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   164,   165,   166,     0,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   609,     0,   176,
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   164,   165,   166,     0,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   611,     0,   176,   550,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,     0,     0,
       0,     0,     0,   164,   165,   166,   551,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     0,     0,   176,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
       0,     0,     0,     0,   164,   165,   166,   264,   167,   168,
     169,   170,   171,   172,   173,   174,   175,     0,     0,   176,
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,     0,     0,     0,     0,   164,   165,   166,   360,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
     176,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,     0,     0,     0,     0,   164,   165,   166,   385,
     167,   168,   169,   170,   171,   172,   173,   174,   175,     0,
       0,   176,     0,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,     0,     0,     0,     0,   164,   165,   166,
     386,   167,   168,   169,   170,   171,   172,   173,   174,   175,
       0,     0,   176,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,     0,     0,     0,     0,   164,   165,
     166,   425,   167,   168,   169,   170,   171,   172,   173,   174,
     175,     0,     0,   176,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,     0,     0,     0,     0,   164,
     165,   166,   426,   167,   168,   169,   170,   171,   172,   173,
     174,   175,     0,     0,   176,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,     0,     0,     0,     0,
     164,   165,   166,   428,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,     0,   176,     0,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,     0,     0,     0,
       0,   164,   165,   166,   429,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,     0,   176,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,     0,     0,
       0,     0,   164,   165,   166,   431,   167,   168,   169,   170,
     171,   172,   173,   174,   175,     0,     0,   176,     0,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,     0,
       0,     0,     0,   164,   165,   166,   436,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     0,     0,   176,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
       0,     0,     0,     0,   164,   165,   166,   452,   167,   168,
     169,   170,   171,   172,   173,   174,   175,     0,     0,   176,
       0,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,     0,     0,     0,     0,   164,   165,   166,   453,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
     176,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,     0,     0,     0,     0,   164,   165,   166,   574,
     167,   168,   169,   170,   171,   172,   173,   174,   175,     0,
       0,   176,     0,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,     0,     0,     0,     0,   164,   165,   166,
     577,   167,   168,   169,   170,   171,   172,   173,   174,   175,
       0,     0,   176,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,     0,     0,     0,     0,   164,   165,
     166,   605,   167,   168,   169,   170,   171,   172,   173,   174,
     175,     0,     0,   176,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,     0,     0,     0,     0,   164,
     165,   166,   625,   167,   168,   169,   170,   171,   172,   173,
     174,   175,     0,     0,   176,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,     0,     0,     0,     0,
     164,   165,   166,   626,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,     0,   176,     0,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,     0,     0,     0,
       0,   164,   165,   166,   630,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,     0,   176,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,     0,   164,
     165,   166,   397,   167,   168,   169,   170,   171,   172,   173,
     174,   175,     0,     0,   176,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,     0,   164,   165,   166,
     402,   167,   168,   169,   170,   171,   172,   173,   174,   175,
       0,     0,   176,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,     0,   164,   165,   166,   407,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
     176,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,     0,   164,   165,   166,   408,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     0,     0,   176,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
       0,   164,   165,   166,   415,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,     0,   176,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,     0,   164,
     165,   166,   421,   167,   168,   169,   170,   171,   172,   173,
     174,   175,     0,     0,   176,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,     0,   164,   165,   166,
     444,   167,   168,   169,   170,   171,   172,   173,   174,   175,
       0,     0,   176,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,     0,   164,   165,   166,   448,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
     176,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,     0,   164,   165,   166,   477,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     0,     0,   176,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
       0,   164,   165,   166,   479,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,     0,   176,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,     0,   164,
     165,   166,   480,   167,   168,   169,   170,   171,   172,   173,
     174,   175,     0,     0,   176,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,     0,   164,   165,   166,
     552,   167,   168,   169,   170,   171,   172,   173,   174,   175,
       0,     0,   176,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,     0,   164,   165,   166,   570,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
     176,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,     0,   164,   165,   166,   597,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     0,     0,   176,     0,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
       0,   164,   165,   166,   604,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,     0,   176,     0,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,     0,   164,
     165,   166,   607,   167,   168,   169,   170,   171,   172,   173,
     174,   175,     0,     0,   176,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,     0,   164,   165,   166,
     616,   167,   168,   169,   170,   171,   172,   173,   174,   175,
       0,     0,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   164,   165,   166,     0,   167,   168,
     169,   170,   171,   172,   173,   174,   175,     0,     0,   176,
     389,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   164,   165,   166,     0,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,     0,   176,   569,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   164,   165,
     166,     0,   167,   168,   169,   170,   171,   172,   173,   174,
     175,     0,     0,   176,   603,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   164,   165,   166,     0,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
     176,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   164,   165,   166,     0,   167,   168,     0,   170,
     171,   172,   173,   174,   175,     0,     0,   176,     0,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   164,
     165,   166,     0,   167,     0,     0,   170,   171,   172,   173,
     174,   175,     0,     0,   176,     0,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   164,   165,   166,     0,
     167,     0,     0,   170,   171,   172,   173,   174,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   187
};

static const yytype_int16 yycheck[] =
{
      25,    44,    18,    40,   131,     3,    14,    90,   369,     3,
      93,     3,   250,    36,     3,    23,    24,     3,     3,    55,
      28,    29,    30,     3,     3,    55,     3,    35,    36,    34,
      35,    39,    48,    10,    11,    42,    13,     3,    46,     0,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
       3,    83,     9,    85,    21,    91,    23,   452,    88,    26,
      13,    98,     6,    86,    31,    31,    85,    87,    86,    87,
      76,    76,    91,    81,    94,   100,    33,     3,     3,    85,
       3,    84,    83,    91,    10,     3,    89,    13,    13,   132,
      74,    88,    84,    91,    91,   103,    87,    87,   105,    93,
      15,   462,   127,    94,    94,    91,    91,    76,    77,    78,
       3,    91,    91,   196,    91,     8,     9,   200,   143,    74,
      75,    76,    77,    78,   149,   520,   151,   152,     3,    83,
     213,   369,   215,    87,    85,   373,    84,    85,    91,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,    91,   148,    91,    91,   192,    91,   194,
     565,   566,   197,    91,   569,    83,     3,   202,   203,    87,
     205,    86,    87,   208,    21,   222,    23,   212,   196,    26,
      34,    35,   200,    30,    31,   220,   221,     3,   223,   224,
      83,   226,   209,   210,    87,   230,     3,    83,    85,    83,
     605,    87,   219,    87,   239,   240,    83,   242,   243,     3,
      87,     3,    83,   618,   462,   308,    87,    85,    83,    83,
      83,   626,    87,    87,    85,   630,    88,    86,    87,    91,
     256,   266,    83,   227,   228,    88,   329,    54,     3,    56,
     234,   235,    59,    60,    61,    86,    87,    59,    60,    61,
      86,    87,    86,    87,   289,    72,    73,    74,    75,    76,
      77,    78,    74,    75,    76,    77,    78,     3,   303,     3,
     317,   265,    86,    87,   309,    11,    12,    86,    87,    85,
     315,    86,    87,    19,    85,    21,    85,    23,    86,    87,
      26,    27,    28,    86,    87,    34,    35,    86,    87,    86,
      87,    37,    38,    86,    87,    41,    42,    43,     3,    45,
      46,    47,    48,    49,   331,     3,    52,    53,    54,     3,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    86,
      87,    67,    85,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    85,   379,   380,   381,    83,    84,   367,
      88,   377,     3,    89,   389,    88,     3,    93,    88,    88,
     395,    52,    53,    54,     3,    56,    91,    88,    59,    60,
      61,    62,    63,    64,     3,   410,   411,   412,   515,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    85,    85,
       5,   426,   427,    85,     3,    85,    85,     3,    85,    85,
      85,   418,    85,   420,    85,    11,    12,   424,   425,    85,
      85,   428,   429,    19,    20,    21,    85,    23,   453,   454,
      26,    27,    28,   449,    85,    85,    83,    85,   463,    85,
      85,    37,    38,    83,   469,    41,    42,    43,   473,    45,
      46,    47,    48,    49,    90,    83,     4,     3,     3,   484,
       3,    88,   446,   447,     3,    83,   491,     4,     4,     3,
      83,     3,    68,    83,     3,     3,   519,    83,     3,    83,
       3,    88,     3,   490,    86,     3,    87,    83,    84,    86,
      88,    86,    86,    89,    86,    85,    87,    93,   523,    86,
      86,    85,   527,   519,    85,     3,    83,    83,    91,     4,
      85,    85,    83,     3,    83,   540,    83,    83,    91,    83,
      83,    83,    83,    83,    83,    83,   551,   552,    83,    83,
      86,     4,     3,   558,    86,    22,    86,    88,   545,   546,
      22,    94,    83,   550,   560,   570,     3,    85,    83,   592,
     575,    68,    85,    22,     3,   580,    87,    83,    88,    83,
      22,    83,     3,    83,    83,     3,    54,   604,    53,    33,
     607,   529,   597,    88,    88,   373,   592,     3,   523,   331,
     419,   491,     8,   232,   256,    11,    12,   560,   540,   376,
     193,    -1,   617,    19,   619,    21,   603,    23,    -1,   624,
      26,    27,    28,   395,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    37,    38,    -1,    -1,    41,    42,    43,   625,    45,
      46,    47,    48,    49,    -1,    -1,     3,    -1,    -1,    -1,
      -1,     8,    -1,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    -1,    21,    -1,    23,    -1,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    33,    83,    84,    -1,
      37,    38,    -1,    89,    41,    42,    43,    93,    45,    46,
      47,    48,    49,    -1,    -1,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    -1,    23,    -1,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    37,
      38,    -1,    89,    41,    42,    43,    93,    45,    46,    47,
      48,    49,    -1,    -1,     3,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    -1,    21,    -1,    23,    -1,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    37,    38,
      -1,    89,    41,    42,    43,    93,    45,    46,    47,    48,
      49,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    -1,    23,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    83,    84,    -1,    37,    38,    -1,
      89,    41,    42,    43,    93,    45,    46,    47,    48,    49,
      -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    -1,    23,    -1,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    83,    84,    -1,    37,    38,    -1,    89,
      41,    42,    43,    93,    45,    46,    47,    48,    49,    -1,
      -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,
      -1,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    37,    38,    -1,    89,    41,
      42,    43,    93,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    11,    12,    -1,    -1,    68,    -1,    -1,    -1,
      19,    -1,    21,    -1,    23,    -1,    -1,    26,    27,    28,
      -1,    83,    84,     3,     4,     5,    -1,    89,    37,    38,
      -1,    93,    41,    42,    43,    -1,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    83,    84,    -1,    -1,    -1,    -1,
      89,    -1,    62,    63,    93,     3,     4,     5,    -1,    69,
      70,    71,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      80,    81,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,
      90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    39,    40,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    50,    51,    -1,    -1,    -1,     3,     4,     5,
      -1,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    -1,    -1,    -1,    75,    24,    25,
      -1,    -1,    80,    81,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    93,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,     3,
       4,     5,    -1,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    -1,    -1,    -1,    75,
      24,    25,    -1,    -1,    80,    81,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    93,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    50,    51,    -1,     3,
       4,     5,     3,     4,     5,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,
      -1,    85,    -1,    37,    -1,    -1,    37,    -1,    -1,    93,
      44,    -1,    -1,    44,    -1,    -1,    50,    51,    -1,    50,
      51,    -1,    -1,     3,     4,     5,    -1,    -1,    62,    63,
      -1,    62,    63,    -1,    -1,    69,    70,    71,    69,    70,
      71,    75,    -1,    -1,    75,    -1,    80,    81,    -1,    80,
      81,    85,    86,    -1,    85,    86,    90,    37,    -1,    93,
      -1,    -1,    93,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,     3,     4,     5,     3,     4,     5,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    -1,    69,
      70,    71,    -1,    -1,    -1,    75,    76,    -1,    25,    -1,
      80,    81,    -1,    -1,    -1,    85,    -1,    37,    -1,    -1,
      37,    -1,    -1,    93,    44,    -1,    -1,    44,    -1,    -1,
      50,    51,    -1,    50,    51,    -1,    -1,     3,     4,     5,
      -1,    -1,    62,    63,    -1,    62,    63,    -1,    -1,    69,
      70,    71,    69,    70,    71,    75,    -1,    -1,    75,    25,
      80,    81,    -1,    80,    81,    85,    -1,    -1,    85,    -1,
      90,    37,    -1,    93,    -1,    -1,    93,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    50,    51,    -1,     3,     4,     5,
       3,     4,     5,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    85,
      -1,    37,    -1,    -1,    37,    -1,    -1,    93,    44,    -1,
      -1,    44,    -1,    -1,    50,    51,    -1,    50,    51,    -1,
       3,     4,     5,    -1,    -1,    -1,    62,    63,    -1,    62,
      63,    -1,    -1,    69,    70,    71,    69,    70,    71,    75,
      -1,    -1,    75,    -1,    80,    81,    -1,    80,    81,    85,
      86,    -1,    85,    -1,    37,    -1,    -1,    93,    -1,    -1,
      93,    44,    -1,    -1,    -1,    -1,    -1,    50,    51,    -1,
       3,     4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    80,    81,    52,
      53,    54,    85,    56,    37,    -1,    59,    60,    61,    -1,
      93,    44,    -1,    -1,    -1,    -1,    -1,    50,    51,    72,
      73,    74,    75,    76,    77,    78,    -1,    -1,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    80,    81,    -1,
       3,    -1,    85,    -1,    -1,     8,     9,    10,    11,    12,
      93,    14,    15,    16,    17,    18,    -1,    -1,    21,    -1,
      23,    -1,    -1,    26,    -1,     3,    29,    -1,    31,    32,
       8,     9,    10,    11,    12,    -1,    14,    15,    16,    17,
      18,    -1,    20,    21,    -1,    23,    -1,    -1,    26,    -1,
      -1,    29,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    -1,    68,    -1,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    20,
      21,    84,    23,    -1,    -1,    26,    -1,     3,    29,    -1,
      31,    32,     8,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    21,    84,    23,    -1,    -1,
      26,    -1,    -1,    29,    -1,    31,    32,    -1,     3,    -1,
      -1,    -1,     7,     8,     9,    10,    11,    12,    -1,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    29,     3,    31,    32,    -1,    -1,
       8,     9,    10,    11,    12,    -1,    14,    15,    16,    17,
      18,    19,    -1,    21,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    29,     3,    31,    32,    -1,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    84,
      31,    32,     3,    -1,    -1,    -1,    -1,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    84,    -1,    29,    -1,
      31,    32,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    67,    84,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      52,    53,    54,    84,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      92,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    52,    53,    54,    -1,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    92,    -1,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    52,    53,    54,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    92,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    52,    53,
      54,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    92,    -1,    67,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    52,    53,    54,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    92,    -1,
      67,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    52,    53,    54,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    92,    -1,    67,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    52,
      53,    54,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    92,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    52,    53,    54,    -1,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    92,
      -1,    67,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    52,    53,    54,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    92,    -1,    67,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      52,    53,    54,    -1,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    92,    -1,    67,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    52,    53,    54,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      92,    -1,    67,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    52,    53,    54,    -1,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    92,    -1,    67,
      -1,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    52,    53,    54,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    92,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    52,    53,    54,    87,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    67,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    52,    53,    54,    86,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    67,
      -1,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    52,    53,    54,    86,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      67,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    52,    53,    54,    86,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    -1,
      -1,    67,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    -1,    52,    53,    54,
      86,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    67,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    52,    53,
      54,    86,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    67,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,    52,
      53,    54,    86,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      52,    53,    54,    86,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    -1,    67,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    52,    53,    54,    86,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    67,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    52,    53,    54,    86,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    -1,    -1,    67,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    -1,    52,    53,    54,    86,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    67,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    52,    53,    54,    86,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    67,
      -1,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    -1,    52,    53,    54,    86,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      67,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    52,    53,    54,    86,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    -1,
      -1,    67,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    -1,    52,    53,    54,
      86,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    67,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,    -1,    -1,    -1,    52,    53,
      54,    86,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    67,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,    52,
      53,    54,    86,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      52,    53,    54,    86,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    -1,    67,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    -1,    -1,    -1,
      -1,    52,    53,    54,    86,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    67,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    52,
      53,    54,    83,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    -1,    52,    53,    54,
      83,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    67,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,    52,    53,    54,    83,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      67,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    52,    53,    54,    83,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    67,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    52,    53,    54,    83,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    67,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    52,
      53,    54,    83,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    -1,    52,    53,    54,
      83,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    67,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,    52,    53,    54,    83,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      67,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    52,    53,    54,    83,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    67,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    52,    53,    54,    83,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    67,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    52,
      53,    54,    83,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    -1,    52,    53,    54,
      83,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    67,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,    52,    53,    54,    83,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      67,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    52,    53,    54,    83,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    67,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    52,    53,    54,    83,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    67,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    52,
      53,    54,    83,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    -1,    52,    53,    54,
      83,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    52,    53,    54,    -1,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    52,    53,    54,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    52,    53,
      54,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    52,    53,    54,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      67,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    52,    53,    54,    -1,    56,    57,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    67,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    52,
      53,    54,    -1,    56,    -1,    -1,    59,    60,    61,    62,
      63,    64,    -1,    -1,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    52,    53,    54,    -1,
      56,    -1,    -1,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    96,    97,    98,     3,     0,    98,    84,    85,
     101,    85,     3,     8,     9,   102,   103,   113,    83,    15,
      99,   100,     3,    10,    13,    91,   132,     3,    10,    11,
      13,   132,    86,    87,     3,    10,    11,    12,    14,    15,
      16,    17,    18,    21,    29,    31,    32,    84,   104,   105,
     113,   127,     3,    86,    87,     3,   132,   132,     3,     4,
       5,    37,    44,    50,    51,    62,    63,    69,    70,    71,
      75,    80,    81,    85,    93,   133,   134,     3,     3,   132,
       3,    13,   132,   132,     3,   103,     3,    84,     3,   132,
       3,    13,   132,     3,     3,     3,   132,     3,    93,   135,
      84,    89,     3,    11,    12,    19,    21,    23,    26,    27,
      28,    37,    38,    41,    42,    43,    45,    46,    47,    48,
      49,    83,    84,    89,   106,   115,   135,    85,    21,    23,
      26,    31,   120,   121,     3,   122,     3,   132,    85,     7,
     105,    83,    83,    88,   101,   100,     3,     3,    85,    91,
      85,    85,    85,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   137,    52,    53,    54,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     3,   132,
       3,     3,    85,    85,    88,   114,     3,    88,   114,   132,
       3,   114,    88,    88,     3,    91,   135,   136,    88,   133,
      76,    85,    55,     3,   132,     3,    20,    68,   115,   116,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    83,
      85,    85,    85,    85,    85,    85,     5,    85,    83,    55,
      88,   133,    85,    85,    85,   122,    30,   121,    83,    87,
      83,     3,    90,   128,   129,   133,    83,    86,   133,   137,
     133,     4,   133,   133,    86,    93,    87,    94,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,    76,
     133,   133,   133,     3,    86,    90,   130,   131,   133,   128,
     133,    83,    87,    88,   114,   132,   133,    83,     3,    88,
     114,   132,    83,   133,   133,    88,   133,    87,    94,   133,
     115,   115,    34,    35,    76,   117,   118,   133,   114,     3,
     114,     3,    20,   115,   133,   133,   135,   133,   133,     4,
     133,     4,   137,     4,   137,   133,   119,   137,   119,     4,
     137,   137,    83,    34,    35,   133,    37,    39,    40,   133,
      86,   133,   133,     3,    31,    83,     3,     8,   106,   107,
     108,   109,   115,    83,     3,    86,    87,   104,    86,    65,
      66,    68,    92,    86,    87,    86,    86,   137,   133,    68,
      92,   133,    83,     3,    86,    87,    86,    83,     3,   133,
      83,    83,    83,   114,   133,    83,    83,    83,    83,   133,
      65,    66,    68,    92,   135,    83,     3,     3,    86,    36,
      86,    83,   114,    20,   116,    86,    86,    88,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,     3,     3,    83,    85,    85,    85,    83,    19,
     105,   123,    86,    86,    88,     3,     3,   132,    83,    33,
     108,    83,   107,    85,   129,     7,   133,   133,   133,    91,
       4,    94,   133,    85,    83,   131,     3,    83,    83,    83,
      83,   133,   133,   133,    91,   115,   118,   115,    20,   115,
      25,   125,   126,   133,   133,   115,   115,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    86,
      86,     4,   137,   137,    21,    31,    68,   105,   121,   124,
      22,   123,    25,   111,   112,   133,   133,    88,   110,     3,
      33,   133,    92,    92,    92,   133,    86,    94,    86,   133,
      85,    92,    92,    92,   133,    22,    68,   115,    24,   126,
      68,    87,    83,    83,    83,    86,    86,    86,    85,   122,
       3,    20,   105,   121,   123,    22,    68,    24,   112,    68,
      83,   133,    87,   110,    86,    68,    92,    86,    86,   130,
      68,    92,   115,   115,   115,   133,   133,    83,    83,    83,
     133,    83,   124,   123,   123,   123,   133,    83,     3,   133,
      83,    86,   133,    68,    83,    86,    20,    83,   133,    92,
      83,    92,   115,   135,   123,   135,    83,    88,    22,    88,
       3,   133,   123,   133,    88,    86,    86,   133,   115,   123,
      86,   123
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    97,    97,    98,    98,    99,    99,   100,
     101,   101,   102,   102,   103,   103,   103,   104,   104,   104,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   106,   107,   107,   107,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   114,   114,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   120,   120,   121,
     121,   121,   121,   121,   121,   122,   122,   123,   123,   123,
     124,   124,   124,   124,   125,   125,   126,   126,   126,   126,
     127,   128,   128,   129,   130,   130,   131,   131,   131,   132,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   135,   135,   135,   135,   135,   135,   135,   135,
     136,   136,   137,   137
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     6,    10,     3,     1,     4,
       3,     0,     3,     1,     1,     1,     0,     2,     1,     0,
       2,     5,     5,     5,     6,     5,     4,     5,     6,     5,
       4,     6,     4,     5,     5,     6,     5,     6,     4,     6,
       4,     6,     5,     3,     2,    10,     6,     9,     5,     3,
       3,     5,     7,     2,     3,     4,     3,     2,     1,     0,
       2,     2,     1,     4,     3,     3,     0,     2,     1,     3,
       3,     3,     2,     3,     2,     4,     3,     4,     3,     4,
       3,     4,     4,     5,     3,     0,     1,     3,     2,     5,
       4,     2,     5,     5,     5,     7,     6,    13,     4,     4,
       4,     5,     5,     5,     5,     5,     5,     5,     2,     5,
       3,     6,     6,     5,     5,     7,     7,     7,     5,     5,
       2,     1,     3,     1,     2,     2,     1,     2,     1,    14,
      13,     5,     7,     6,     3,     3,     1,     3,     5,     1,
       2,     2,     1,     1,     2,     1,     3,     5,     3,     2,
       4,     3,     1,     5,     3,     1,     5,     4,     1,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     5,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     4,     4,     3,     1,     6,
       4,     9,     6,     6,     7,     3,     6,     3,     4,     6,
       4,     1,     1,     6,     4,     9,     6,     6,     7,     3,
       3,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* module_list: module_list module  */
#line 97 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 2207 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 4: /* module_list: module  */
#line 98 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 2213 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 5: /* module: MODULE IDENTIFIER opt_port_list ';' module_items ENDMODULE  */
#line 103 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-4].str), yylineno);
        free((yyvsp[-4].str));
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) { addChild((yyval.node), c); } (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 2224 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 6: /* module: MODULE IDENTIFIER '#' '(' module_param_decls ')' opt_port_list ';' module_items ENDMODULE  */
#line 110 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-8].str), yylineno);
        free((yyvsp[-8].str));
        /* Add parameter declarations as children */
        if ((yyvsp[-5].node)) { for (auto *c : (yyvsp[-5].node)->children) addChild((yyval.node), c); (yyvsp[-5].node)->children.clear(); freeTree((yyvsp[-5].node)); }
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 2237 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 7: /* module_param_decls: module_param_decls ',' module_param_decl  */
#line 121 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                             { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2243 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 8: /* module_param_decls: module_param_decl  */
#line 122 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2249 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 9: /* module_param_decl: PARAMETER IDENTIFIER '=' expr  */
#line 127 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-2].str), yylineno); free((yyvsp[-2].str)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2255 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 10: /* opt_port_list: '(' port_list ')'  */
#line 131 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 2261 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 11: /* opt_port_list: %empty  */
#line 132 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = nullptr; }
#line 2267 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 12: /* port_list: port_list ',' port_decl_in_list  */
#line 136 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2273 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 13: /* port_list: port_decl_in_list  */
#line 137 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 2279 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 14: /* port_decl_in_list: IDENTIFIER  */
#line 141 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { free((yyvsp[0].str)); (yyval.node) = nullptr; }
#line 2285 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 15: /* port_decl_in_list: port_decl  */
#line 142 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2291 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 16: /* port_decl_in_list: %empty  */
#line 143 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = nullptr; }
#line 2297 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 17: /* module_items: module_items module_item  */
#line 147 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2303 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 18: /* module_items: module_item  */
#line 148 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2309 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 19: /* module_items: %empty  */
#line 149 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2315 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 21: /* module_item: WIRE range IDENTIFIER range ';'  */
#line 155 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Multi-dimensional wire: wire [msb:lsb] name[dim_msb:dim_lsb] */
          (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb;
          /* Store data range expressions + dimension range expressions */
          for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c);
          (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2332 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 22: /* module_item: REG range IDENTIFIER range ';'  */
#line 168 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Unpacked memory: reg [data_msb:data_lsb] name[addr_msb:addr_lsb] */
          (yyval.node) = makeNode(NodeType::MEMORY_DECL, (yyvsp[-2].str), yylineno);
          free((yyvsp[-2].str));
          (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb;
          for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c);
          (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2347 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 23: /* module_item: WIRE range IDENTIFIER decl_list ';'  */
#line 179 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
#line 2353 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 24: /* module_item: WIRE range IDENTIFIER '=' expr ';'  */
#line 181 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Wire with initialization — store expr as child for later assign */
          auto *decl = makeNode(NodeType::NET_DECL, "wire", yylineno);
          addChild(decl, makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno));
          free((yyvsp[-3].str));
          decl->msb = (yyvsp[-4].node)->msb; decl->lsb = (yyvsp[-4].node)->lsb;
          for (auto *c : (yyvsp[-4].node)->children) addChild(decl, c); (yyvsp[-4].node)->children.clear(); freeTree((yyvsp[-4].node));
          addChild(decl, (yyvsp[-1].node));  /* init expression */
          (yyval.node) = decl;
      }
#line 2368 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 25: /* module_item: WIRE IDENTIFIER '=' expr ';'  */
#line 192 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          auto *decl = makeNode(NodeType::NET_DECL, "wire", yylineno);
          addChild(decl, makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno));
          free((yyvsp[-3].str));
          decl->msb = 0;
          decl->lsb = 0;
          addChild(decl, (yyvsp[-1].node));
          (yyval.node) = decl;
      }
#line 2382 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 26: /* module_item: WIRE IDENTIFIER decl_list ';'  */
#line 202 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2388 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 27: /* module_item: REG range IDENTIFIER decl_list ';'  */
#line 204 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
#line 2394 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 28: /* module_item: REG range IDENTIFIER '=' expr ';'  */
#line 206 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno));
          free((yyvsp[-3].str));
          (yyval.node)->msb = (yyvsp[-4].node)->msb; (yyval.node)->lsb = (yyvsp[-4].node)->lsb;
          for (auto *c : (yyvsp[-4].node)->children) addChild((yyval.node), c);
          (yyvsp[-4].node)->children.clear(); freeTree((yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2408 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 29: /* module_item: REG IDENTIFIER '=' expr ';'  */
#line 216 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2414 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 30: /* module_item: REG IDENTIFIER decl_list ';'  */
#line 218 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2420 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 31: /* module_item: REG SIGNED range IDENTIFIER decl_list ';'  */
#line 220 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg signed", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
#line 2426 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 32: /* module_item: INTEGER_KW IDENTIFIER decl_list ';'  */
#line 222 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "integer", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 31; (yyval.node)->lsb = 0; }
#line 2432 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 33: /* module_item: LOCALPARAM IDENTIFIER '=' expr ';'  */
#line 224 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2440 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 34: /* module_item: PARAMETER IDENTIFIER '=' expr ';'  */
#line 228 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2446 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 35: /* module_item: PARAMETER range IDENTIFIER '=' expr ';'  */
#line 230 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
          for (auto *c : (yyvsp[-4].node)->children) addChild((yyval.node), c);
          (yyvsp[-4].node)->children.clear();
          freeTree((yyvsp[-4].node));
      }
#line 2459 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 36: /* module_item: ASSIGN lvalue '=' expr ';'  */
#line 239 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ASSIGN, "", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2465 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 37: /* module_item: ALWAYS '@' '(' '*' ')' stmt  */
#line 241 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(*)", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2471 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 38: /* module_item: ALWAYS '@' '*' stmt  */
#line 243 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(*)", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2477 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 39: /* module_item: ALWAYS '@' '(' event_list ')' stmt  */
#line 245 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          ASTNode *event = (yyvsp[-2].node)->children.empty() ? nullptr : (yyvsp[-2].node)->children[0];
          if (event != nullptr && !event->children.empty()) {
              std::string trigger = "@(" + event->value + " " +
                                    event->children[0]->value + ")";
              (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, trigger, yylineno);
          } else {
              (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@events", yylineno);
          }
          addChild((yyval.node), (yyvsp[0].node));
          freeTree((yyvsp[-2].node));
      }
#line 2494 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 40: /* module_item: ALWAYS '#' expr stmt  */
#line 258 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "#delay", yylineno); addChild((yyval.node), (yyvsp[-1].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2500 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 41: /* module_item: FUNCTION range IDENTIFIER ';' function_items ENDFUNCTION  */
#line 260 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FUNCTION_DECL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          (yyval.node)->msb = (yyvsp[-4].node)->msb; (yyval.node)->lsb = (yyvsp[-4].node)->lsb;
          for (auto *c : (yyvsp[-4].node)->children) addChild((yyval.node), c);
          (yyvsp[-4].node)->children.clear(); freeTree((yyvsp[-4].node));
          if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
      }
#line 2513 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 42: /* module_item: FUNCTION IDENTIFIER ';' function_items ENDFUNCTION  */
#line 269 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FUNCTION_DECL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
      }
#line 2523 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 43: /* module_item: GENVAR genvar_list ';'  */
#line 275 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::PROCEDURAL_DECL, "genvar", yylineno); }
#line 2529 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 44: /* module_item: INITIAL_KW stmt  */
#line 277 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::INITIAL_BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2535 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 45: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' port_conn_list ')' ';'  */
#line 280 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-9].str), yylineno); free((yyvsp[-9].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-6].node)->children) addChild((yyval.node), c); (yyvsp[-6].node)->children.clear(); freeTree((yyvsp[-6].node)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 2541 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 46: /* module_item: IDENTIFIER IDENTIFIER '(' port_conn_list ')' ';'  */
#line 282 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-5].str), yylineno); free((yyvsp[-5].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 2547 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 47: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' ')' ';'  */
#line 284 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-8].str), yylineno); free((yyvsp[-8].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); for (auto *c : (yyvsp[-5].node)->children) addChild((yyval.node), c); (yyvsp[-5].node)->children.clear(); freeTree((yyvsp[-5].node)); }
#line 2553 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 48: /* module_item: IDENTIFIER IDENTIFIER '(' ')' ';'  */
#line 286 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-4].str), yylineno); free((yyvsp[-4].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); }
#line 2559 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 49: /* module_item: GENERATE gen_items ENDGENERATE  */
#line 287 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2565 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 50: /* module_item: GENVAR genvar_list ';'  */
#line 288 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2571 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 51: /* module_item: IF '(' expr ')' gen_block  */
#line 290 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2581 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 52: /* module_item: IF '(' expr ')' gen_block ELSE gen_block  */
#line 296 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2592 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 53: /* module_item: param_override ';'  */
#line 302 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2598 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 54: /* procedural_decl: INTEGER_KW IDENTIFIER decl_list  */
#line 307 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PROCEDURAL_DECL, "integer", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
      }
#line 2608 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 55: /* procedural_decl: REG range IDENTIFIER decl_list  */
#line 313 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PROCEDURAL_DECL, "reg", yylineno);
          (yyval.node)->msb = (yyvsp[-2].node)->msb; (yyval.node)->lsb = (yyvsp[-2].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
          for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c);
          (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node));
      }
#line 2621 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 56: /* procedural_decl: REG IDENTIFIER decl_list  */
#line 322 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PROCEDURAL_DECL, "reg", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
      }
#line 2631 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 57: /* function_items: function_items function_item  */
#line 330 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2637 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 58: /* function_items: function_item  */
#line 331 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                    { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2643 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 59: /* function_items: %empty  */
#line 332 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                  { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2649 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 60: /* function_item: function_port_decl ';'  */
#line 336 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 2655 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 61: /* function_item: procedural_decl ';'  */
#line 337 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 2661 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 62: /* function_item: stmt  */
#line 338 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2667 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 63: /* function_port_decl: INPUT range IDENTIFIER function_port_names  */
#line 343 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "input", yylineno);
          (yyval.node)->msb = (yyvsp[-2].node)->msb; (yyval.node)->lsb = (yyvsp[-2].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
          for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c);
          (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node));
          if ((yyvsp[0].node)) { for (auto *c : (yyvsp[0].node)->children) addChild((yyval.node), c); (yyvsp[0].node)->children.clear(); freeTree((yyvsp[0].node)); }
      }
#line 2681 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 64: /* function_port_decl: INPUT IDENTIFIER function_port_names  */
#line 353 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "input", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
          if ((yyvsp[0].node)) { for (auto *c : (yyvsp[0].node)->children) addChild((yyval.node), c); (yyvsp[0].node)->children.clear(); freeTree((yyvsp[0].node)); }
      }
#line 2692 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 65: /* function_port_names: function_port_names ',' IDENTIFIER  */
#line 363 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { addChild((yyvsp[-2].node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno)); free((yyvsp[0].str)); (yyval.node) = (yyvsp[-2].node); }
#line 2698 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 66: /* function_port_names: %empty  */
#line 364 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                  { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2704 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 67: /* gen_case_items: gen_case_items gen_case_item  */
#line 368 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2710 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 68: /* gen_case_items: gen_case_item  */
#line 369 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                    { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2716 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 69: /* gen_case_item: expr ':' gen_block  */
#line 374 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2722 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 70: /* gen_case_item: DEFAULT ':' gen_block  */
#line 376 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2728 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 71: /* port_decl: INPUT range IDENTIFIER  */
#line 382 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          /* Keep range expressions as children for deferred evaluation */
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2743 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 72: /* port_decl: INPUT IDENTIFIER  */
#line 393 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2755 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 73: /* port_decl: OUTPUT range IDENTIFIER  */
#line 401 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2769 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 74: /* port_decl: OUTPUT IDENTIFIER  */
#line 411 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2781 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 75: /* port_decl: OUTPUT WIRE range IDENTIFIER  */
#line 419 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2795 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 76: /* port_decl: OUTPUT WIRE IDENTIFIER  */
#line 429 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2807 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 77: /* port_decl: INPUT WIRE range IDENTIFIER  */
#line 437 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2821 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 78: /* port_decl: INPUT WIRE IDENTIFIER  */
#line 447 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2833 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 79: /* port_decl: OUTPUT REG range IDENTIFIER  */
#line 455 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2847 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 80: /* port_decl: OUTPUT REG IDENTIFIER  */
#line 465 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2859 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 81: /* port_decl: OUTPUT SIGNED range IDENTIFIER  */
#line 473 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2873 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 82: /* port_decl: INPUT SIGNED range IDENTIFIER  */
#line 483 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2887 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 83: /* port_decl: OUTPUT REG SIGNED range IDENTIFIER  */
#line 493 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2899 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 84: /* decl_list: decl_list ',' IDENTIFIER  */
#line 503 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { free((yyvsp[0].str)); }
#line 2905 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 86: /* stmt: ';'  */
#line 508 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2911 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 87: /* stmt: BEGINKW stmts END  */
#line 509 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 2917 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 88: /* stmt: BEGINKW END  */
#line 510 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2923 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 89: /* stmt: BEGINKW ':' IDENTIFIER stmts END  */
#line 512 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = (yyvsp[-1].node); (yyval.node)->value = (yyvsp[-2].str); free((yyvsp[-2].str)); }
#line 2929 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 90: /* stmt: BEGINKW ':' IDENTIFIER END  */
#line 514 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::BLOCK, (yyvsp[-1].str), yylineno); free((yyvsp[-1].str)); }
#line 2935 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 91: /* stmt: procedural_decl ';'  */
#line 515 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 2941 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 92: /* stmt: REPEAT '(' expr ')' stmt  */
#line 517 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "repeat", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2951 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 93: /* stmt: WHILE '(' expr ')' stmt  */
#line 523 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "while", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2961 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 94: /* stmt: IF '(' expr ')' stmt  */
#line 529 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2971 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 95: /* stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 535 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2982 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 96: /* stmt: CASE '(' expr ')' case_items ENDCASE  */
#line 542 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2992 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 97: /* stmt: FOR '(' lvalue '=' expr ';' expr ';' lvalue '=' expr ')' stmt  */
#line 548 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "", yylineno);
          addChild((yyval.node), (yyvsp[-10].node));  /* init lvalue */
          addChild((yyval.node), (yyvsp[-8].node));  /* init expr */
          addChild((yyval.node), (yyvsp[-6].node));  /* cond */
          addChild((yyval.node), (yyvsp[-4].node));  /* update lvalue */
          addChild((yyval.node), (yyvsp[-2].node)); /* update expr */
          addChild((yyval.node), (yyvsp[0].node)); /* body */
      }
#line 3006 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 98: /* stmt: lvalue '=' expr ';'  */
#line 558 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3016 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 99: /* stmt: IDENTIFIER NONBLOCKING expr ';'  */
#line 564 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno));
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3027 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 100: /* stmt: lvalue NONBLOCKING expr ';'  */
#line 571 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3037 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 101: /* stmt: SYS_DISPLAY '(' expr_list ')' ';'  */
#line 577 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 3048 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 102: /* stmt: SYS_DISPLAY '(' STRING ')' ';'  */
#line 584 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 3058 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 103: /* stmt: SYS_READMEMH '(' readmem_args ')' ';'  */
#line 590 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$readmemh", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 3069 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 104: /* stmt: SYS_READMEMB '(' readmem_args ')' ';'  */
#line 597 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$readmemb", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 3080 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 105: /* stmt: SYS_DUMPFILE '(' STRING ')' ';'  */
#line 604 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$dumpfile", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 3090 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 106: /* stmt: SYS_DUMPVARS '(' expr_list ')' ';'  */
#line 610 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$dumpvars", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 3101 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 107: /* stmt: SYS_ERROR '(' expr_list ')' ';'  */
#line 617 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$error", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 3112 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 108: /* stmt: SYS_FINISH ';'  */
#line 623 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); }
#line 3118 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 109: /* stmt: SYS_FINISH '(' expr ')' ';'  */
#line 624 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); addChild((yyval.node), (yyvsp[-2].node)); }
#line 3124 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 110: /* stmt: '#' NUMBER ';'  */
#line 626 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, std::to_string((yyvsp[-1].num)->value), yylineno);
          free((yyvsp[-1].num));
      }
#line 3133 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 111: /* stmt: '@' '(' POSEDGE IDENTIFIER ')' ';'  */
#line 631 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, "posedge", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 3143 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 112: /* stmt: '@' '(' NEGEDGE IDENTIFIER ')' ';'  */
#line 637 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, "negedge", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 3153 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 113: /* stmt: SYS_FOPEN '(' STRING ')' ';'  */
#line 643 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 3163 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 114: /* stmt: SYS_FCLOSE '(' expr ')' ';'  */
#line 649 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fclose", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
      }
#line 3172 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 115: /* stmt: lvalue '=' SYS_FOPEN '(' STRING ')' ';'  */
#line 654 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild(fc, makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          addChild((yyval.node), fc);
      }
#line 3185 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 116: /* stmt: lvalue '=' SYS_FSCANF '(' expr_list ')' ';'  */
#line 663 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fscanf", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 3199 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 117: /* stmt: lvalue '=' SYS_FGETS '(' expr_list ')' ';'  */
#line 673 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fgets", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 3213 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 118: /* stmt: SYS_FDISPLAY '(' expr_list ')' ';'  */
#line 683 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 3224 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 119: /* stmt: SYS_FDISPLAY '(' STRING ')' ';'  */
#line 690 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 3234 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 120: /* stmts: stmts stmt  */
#line 698 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 3240 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 121: /* stmts: stmt  */
#line 699 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3246 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 122: /* event_list: event_list OR event_expr  */
#line 704 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3252 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 123: /* event_list: event_expr  */
#line 706 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::EVENT_CTRL, "events", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3258 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 124: /* event_expr: POSEDGE IDENTIFIER  */
#line 711 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::EVENT_CTRL, "posedge", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno)); free((yyvsp[0].str)); }
#line 3264 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 125: /* event_expr: NEGEDGE IDENTIFIER  */
#line 713 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::EVENT_CTRL, "negedge", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno)); free((yyvsp[0].str)); }
#line 3270 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 126: /* readmem_args: expr_list  */
#line 718 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 3276 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 127: /* gen_items: gen_items gen_item  */
#line 722 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 3282 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 128: /* gen_items: gen_item  */
#line 723 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::GENERATE, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3288 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 129: /* gen_item: FOR '(' GENVAR IDENTIFIER '=' expr ';' expr ';' IDENTIFIER '=' expr ')' gen_block  */
#line 728 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 3300 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 130: /* gen_item: FOR '(' IDENTIFIER '=' expr ';' expr ';' lvalue '=' expr ')' gen_block  */
#line 736 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        /* for (name = expr; cond; name = expr) — genvar already declared */
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 3313 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 131: /* gen_item: IF '(' expr ')' gen_block  */
#line 745 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 3323 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 132: /* gen_item: IF '(' expr ')' gen_block ELSE gen_block  */
#line 751 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 3334 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 133: /* gen_item: CASE '(' expr ')' gen_case_items ENDCASE  */
#line 758 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::CASE, "generate", yylineno);
        addChild((yyval.node), (yyvsp[-3].node));
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 3344 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 134: /* gen_item: GENVAR genvar_list ';'  */
#line 764 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        /* genvar declaration — skip */
        (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno);
    }
#line 3353 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 135: /* genvar_list: genvar_list ',' IDENTIFIER  */
#line 771 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                               { free((yyvsp[0].str)); }
#line 3359 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 136: /* genvar_list: IDENTIFIER  */
#line 772 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                 { free((yyvsp[0].str)); }
#line 3365 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 137: /* gen_block: BEGINKW gen_body END  */
#line 776 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 3371 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 138: /* gen_block: BEGINKW ':' IDENTIFIER gen_body END  */
#line 777 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                          { (yyval.node) = (yyvsp[-1].node); free((yyvsp[-2].str)); }
#line 3377 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 139: /* gen_block: module_item  */
#line 778 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 3383 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 140: /* gen_body: gen_body module_item  */
#line 782 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 3389 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 141: /* gen_body: gen_body gen_item  */
#line 783 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 3395 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 142: /* gen_body: module_item  */
#line 784 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3401 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 143: /* gen_body: gen_item  */
#line 785 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3407 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 144: /* case_items: case_items case_item  */
#line 789 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 3413 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 145: /* case_items: case_item  */
#line 790 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3419 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 146: /* case_item: expr ':' stmt  */
#line 795 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 3429 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 147: /* case_item: expr ',' expr ':' stmt  */
#line 801 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 3440 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 148: /* case_item: DEFAULT ':' stmt  */
#line 808 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 3449 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 149: /* case_item: DEFAULT stmt  */
#line 813 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 3458 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 150: /* param_override: '#' '(' param_list ')'  */
#line 821 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    { (yyval.node) = makeNode(NodeType::PARAM_OVERRIDE, "", yylineno); for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
#line 3464 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 151: /* param_list: param_list ',' param_assign  */
#line 825 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3470 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 152: /* param_list: param_assign  */
#line 826 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 3476 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 153: /* param_assign: '.' IDENTIFIER '(' expr ')'  */
#line 830 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 3482 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 154: /* port_conn_list: port_conn_list ',' port_conn  */
#line 834 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3488 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 155: /* port_conn_list: port_conn  */
#line 835 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3494 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 156: /* port_conn: '.' IDENTIFIER '(' expr ')'  */
#line 840 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3504 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 157: /* port_conn: '.' IDENTIFIER '(' ')'  */
#line 846 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-2].str), yylineno);
          free((yyvsp[-2].str));
      }
#line 3513 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 158: /* port_conn: expr  */
#line 851 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, "", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 3522 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 159: /* range: '[' expr ':' expr ']'  */
#line 859 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
          /* Evaluate constant range bounds */
          if ((yyvsp[-3].node)->type == NodeType::NUMBER) (yyval.node)->msb = std::stoi((yyvsp[-3].node)->value);
          if ((yyvsp[-1].node)->type == NodeType::NUMBER) (yyval.node)->lsb = std::stoi((yyvsp[-1].node)->value);
      }
#line 3535 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 160: /* expr: expr '+' expr  */
#line 870 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "+", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3541 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 161: /* expr: expr '-' expr  */
#line 871 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "-", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3547 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 162: /* expr: expr '*' expr  */
#line 872 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "*", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3553 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 163: /* expr: expr '/' expr  */
#line 873 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "/", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3559 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 164: /* expr: expr '%' expr  */
#line 874 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "%", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3565 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 165: /* expr: expr '&' expr  */
#line 875 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3571 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 166: /* expr: expr '|' expr  */
#line 876 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3577 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 167: /* expr: expr '^' expr  */
#line 877 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3583 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 168: /* expr: expr XNOR expr  */
#line 878 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3589 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 169: /* expr: expr NAND expr  */
#line 879 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3595 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 170: /* expr: expr NOR expr  */
#line 880 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3601 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 171: /* expr: expr EQ expr  */
#line 881 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "==", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3607 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 172: /* expr: expr NE expr  */
#line 882 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "!=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3613 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 173: /* expr: expr '<' expr  */
#line 883 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3619 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 174: /* expr: expr '>' expr  */
#line 884 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3625 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 175: /* expr: expr LE expr  */
#line 885 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3631 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 176: /* expr: expr GE expr  */
#line 886 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3637 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 177: /* expr: expr SHL expr  */
#line 887 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3643 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 178: /* expr: expr SHR expr  */
#line 888 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3649 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 179: /* expr: expr SSHR expr  */
#line 889 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3655 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 180: /* expr: expr '*' '*' expr  */
#line 890 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = makeNode(NodeType::BINOP, "**", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3661 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 181: /* expr: expr LOGAND expr  */
#line 891 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3667 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 182: /* expr: expr LOGOR expr  */
#line 892 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "||", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3673 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 183: /* expr: expr '?' expr ':' expr  */
#line 894 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::TERNARY, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));
      }
#line 3682 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 184: /* expr: '-' expr  */
#line 898 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "-", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3688 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 185: /* expr: '!' expr  */
#line 899 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "!", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3694 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 186: /* expr: '~' expr  */
#line 900 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3700 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 187: /* expr: NAND expr  */
#line 901 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~&", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3706 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 188: /* expr: NOR expr  */
#line 902 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~|", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3712 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 189: /* expr: '&' expr  */
#line 903 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "&", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3718 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 190: /* expr: '|' expr  */
#line 904 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "|", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3724 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 191: /* expr: '^' expr  */
#line 905 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "^", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3730 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 193: /* prim_expr: NUMBER  */
#line 911 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNum((yyvsp[0].num));
      }
#line 3738 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 194: /* prim_expr: SYS_TIME  */
#line 915 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::SYS_TASK, "$time", yylineno); }
#line 3744 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 195: /* prim_expr: SYS_UNSIGNED '(' expr ')'  */
#line 917 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$unsigned", yylineno);
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3753 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 196: /* prim_expr: IDENTIFIER '(' expr_list ')'  */
#line 922 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FUNCTION_CALL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 3765 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 197: /* prim_expr: IDENTIFIER '(' ')'  */
#line 930 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::FUNCTION_CALL, (yyvsp[-2].str), yylineno); free((yyvsp[-2].str)); }
#line 3771 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 198: /* prim_expr: IDENTIFIER  */
#line 932 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3780 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 199: /* prim_expr: IDENTIFIER '[' expr ':' expr ']'  */
#line 937 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3791 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 200: /* prim_expr: IDENTIFIER '[' expr ']'  */
#line 944 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3801 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 201: /* prim_expr: IDENTIFIER '[' expr ']' '[' expr ':' expr ']'  */
#line 950 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Double range-select: signal[idx][msb:lsb] — mark with msb=-1 to distinguish */
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-8].str), yylineno);
          free((yyvsp[-8].str));
          addChild((yyval.node), (yyvsp[-6].node));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3814 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 202: /* prim_expr: IDENTIFIER '[' expr PART_PLUS expr ']'  */
#line 959 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          (yyval.node)->part_select_direction = PartSelectDirection::PLUS;
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3826 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 203: /* prim_expr: IDENTIFIER '[' expr PART_MINUS expr ']'  */
#line 967 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          (yyval.node)->part_select_direction = PartSelectDirection::MINUS;
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3838 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 204: /* prim_expr: IDENTIFIER '[' expr ']' '[' expr ']'  */
#line 975 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Double bit-select: signal[idx][bit] — 3 children: [idx, bit, sentinel] */
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-6].str), yylineno);
          free((yyvsp[-6].str));
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-1].node));
          auto *sentinel = makeNode(NodeType::NUMBER, "-1", yylineno);
          sentinel->msb = -1;
          addChild((yyval.node), sentinel);
      }
#line 3853 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 205: /* prim_expr: '{' expr_list '}'  */
#line 986 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 3864 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 206: /* prim_expr: '{' expr '{' expr_list '}' '}'  */
#line 993 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Replication: {count{expr_list}} — expand into count copies */
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          int count = 0;
          try { count = (int)std::stoull((yyvsp[-4].node)->value); } catch (...) { count = 1; }
          for (int i = 0; i < count; i++) {
              for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c);
          }
          freeTree((yyvsp[-4].node));
          (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node));
      }
#line 3880 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 207: /* prim_expr: '(' expr ')'  */
#line 1005 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 3888 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 208: /* prim_expr: SYS_FOPEN '(' STRING ')'  */
#line 1009 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
      }
#line 3898 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 209: /* prim_expr: SYS_FOPEN '(' STRING ',' STRING ')'  */
#line 1015 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-3].str), yylineno));
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-3].str)); free((yyvsp[-1].str));
      }
#line 3909 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 210: /* prim_expr: SYS_CLOG2 '(' expr ')'  */
#line 1022 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$clog2", yylineno);
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3918 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 211: /* prim_expr: STRING  */
#line 1027 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::STRING, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3927 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 212: /* lvalue: IDENTIFIER  */
#line 1035 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3936 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 213: /* lvalue: IDENTIFIER '[' expr ':' expr ']'  */
#line 1040 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3947 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 214: /* lvalue: IDENTIFIER '[' expr ']'  */
#line 1047 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3957 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 215: /* lvalue: IDENTIFIER '[' expr ']' '[' expr ':' expr ']'  */
#line 1053 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-8].str), yylineno);
          free((yyvsp[-8].str));
          addChild((yyval.node), (yyvsp[-6].node));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3969 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 216: /* lvalue: IDENTIFIER '[' expr PART_PLUS expr ']'  */
#line 1061 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          (yyval.node)->part_select_direction = PartSelectDirection::PLUS;
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3981 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 217: /* lvalue: IDENTIFIER '[' expr PART_MINUS expr ']'  */
#line 1069 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          (yyval.node)->part_select_direction = PartSelectDirection::MINUS;
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3993 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 218: /* lvalue: IDENTIFIER '[' expr ']' '[' expr ']'  */
#line 1077 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-6].str), yylineno);
          free((yyvsp[-6].str));
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-1].node));
          auto *sentinel = makeNode(NodeType::NUMBER, "-1", yylineno);
          sentinel->msb = -1;
          addChild((yyval.node), sentinel);
      }
#line 4007 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 219: /* lvalue: '{' lvalue_list '}'  */
#line 1087 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 4018 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 220: /* lvalue_list: lvalue_list ',' lvalue  */
#line 1096 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 4024 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 221: /* lvalue_list: lvalue  */
#line 1097 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 4030 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 222: /* expr_list: expr_list ',' expr  */
#line 1101 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 4036 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 223: /* expr_list: expr  */
#line 1102 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 4042 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;


#line 4046 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1105 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"


void yyerror(const char *msg) {
    g_parse_ok = false;
    const SourceRecord *record = g_preprocess_result == nullptr
                                     ? nullptr
                                     : sourceRecordForOutputLine(*g_preprocess_result,
                                                                  static_cast<std::size_t>(yylineno));
    if (record != nullptr) {
        std::fprintf(stderr, "%s:%zu: parser error: %s\n",
                     record->location.file.c_str(), record->location.line, msg);
    } else {
        std::fprintf(stderr, "parser error at generated line %d: %s\n", yylineno, msg);
    }
}

extern int yydebug;
std::vector<ASTNode *> parseFiles(const std::vector<std::string> &files) {
    g_modules.clear();
    g_parse_ok = true;
    PreprocessResult result = preprocessFiles(files);
    if (!result.ok) {
        for (const auto &message : result.diagnostics) {
            std::fprintf(stderr, "preprocessor: %s\n", message.c_str());
        }
        return g_modules;
    }
    g_preprocess_result = &result;
    yylineno = 1;
    YY_BUFFER_STATE buffer = yy_scan_string(result.source.c_str());
    yyparse();
    yy_delete_buffer(buffer);
    g_preprocess_result = nullptr;
    return g_modules;
}
