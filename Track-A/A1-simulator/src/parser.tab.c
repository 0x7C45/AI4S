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
#line 13 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"

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
static const PreprocessResult *g_preprocess_result = nullptr;

static ASTNode *makeNum(VerilogNum *n) {
    ASTNode *node = makeNode(NodeType::NUMBER, std::to_string(n->value), yylineno);
    node->msb = n->width - 1;
    node->lsb = 0;
    free(n);
    return node;
}

#line 109 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"

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
  YYSYMBOL_POSEDGE = 32,                   /* POSEDGE  */
  YYSYMBOL_NEGEDGE = 33,                   /* NEGEDGE  */
  YYSYMBOL_OR = 34,                        /* OR  */
  YYSYMBOL_SYS_FOPEN = 35,                 /* SYS_FOPEN  */
  YYSYMBOL_SYS_FCLOSE = 36,                /* SYS_FCLOSE  */
  YYSYMBOL_SYS_FSCANF = 37,                /* SYS_FSCANF  */
  YYSYMBOL_SYS_FGETS = 38,                 /* SYS_FGETS  */
  YYSYMBOL_SYS_FDISPLAY = 39,              /* SYS_FDISPLAY  */
  YYSYMBOL_SYS_DISPLAY = 40,               /* SYS_DISPLAY  */
  YYSYMBOL_SYS_FINISH = 41,                /* SYS_FINISH  */
  YYSYMBOL_SYS_CLOG2 = 42,                 /* SYS_CLOG2  */
  YYSYMBOL_SYS_READMEMH = 43,              /* SYS_READMEMH  */
  YYSYMBOL_SYS_READMEMB = 44,              /* SYS_READMEMB  */
  YYSYMBOL_EQ = 45,                        /* EQ  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_LE = 47,                        /* LE  */
  YYSYMBOL_NONBLOCKING = 48,               /* NONBLOCKING  */
  YYSYMBOL_GE = 49,                        /* GE  */
  YYSYMBOL_LOGAND = 50,                    /* LOGAND  */
  YYSYMBOL_LOGOR = 51,                     /* LOGOR  */
  YYSYMBOL_SHL = 52,                       /* SHL  */
  YYSYMBOL_SHR = 53,                       /* SHR  */
  YYSYMBOL_SSHR = 54,                      /* SSHR  */
  YYSYMBOL_NAND = 55,                      /* NAND  */
  YYSYMBOL_NOR = 56,                       /* NOR  */
  YYSYMBOL_XNOR = 57,                      /* XNOR  */
  YYSYMBOL_58_ = 58,                       /* '?'  */
  YYSYMBOL_59_ = 59,                       /* ':'  */
  YYSYMBOL_60_ = 60,                       /* '|'  */
  YYSYMBOL_61_ = 61,                       /* '^'  */
  YYSYMBOL_62_ = 62,                       /* '&'  */
  YYSYMBOL_63_ = 63,                       /* '<'  */
  YYSYMBOL_64_ = 64,                       /* '>'  */
  YYSYMBOL_65_ = 65,                       /* '+'  */
  YYSYMBOL_66_ = 66,                       /* '-'  */
  YYSYMBOL_67_ = 67,                       /* '*'  */
  YYSYMBOL_68_ = 68,                       /* '/'  */
  YYSYMBOL_69_ = 69,                       /* '%'  */
  YYSYMBOL_POWER = 70,                     /* POWER  */
  YYSYMBOL_71_ = 71,                       /* '!'  */
  YYSYMBOL_72_ = 72,                       /* '~'  */
  YYSYMBOL_UNARY = 73,                     /* UNARY  */
  YYSYMBOL_74_ = 74,                       /* ';'  */
  YYSYMBOL_75_ = 75,                       /* '#'  */
  YYSYMBOL_76_ = 76,                       /* '('  */
  YYSYMBOL_77_ = 77,                       /* ')'  */
  YYSYMBOL_78_ = 78,                       /* ','  */
  YYSYMBOL_79_ = 79,                       /* '='  */
  YYSYMBOL_80_ = 80,                       /* '@'  */
  YYSYMBOL_81_ = 81,                       /* '.'  */
  YYSYMBOL_82_ = 82,                       /* '['  */
  YYSYMBOL_83_ = 83,                       /* ']'  */
  YYSYMBOL_84_ = 84,                       /* '{'  */
  YYSYMBOL_85_ = 85,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_source = 87,                    /* source  */
  YYSYMBOL_module_list = 88,               /* module_list  */
  YYSYMBOL_module = 89,                    /* module  */
  YYSYMBOL_module_param_decls = 90,        /* module_param_decls  */
  YYSYMBOL_module_param_decl = 91,         /* module_param_decl  */
  YYSYMBOL_opt_port_list = 92,             /* opt_port_list  */
  YYSYMBOL_port_list = 93,                 /* port_list  */
  YYSYMBOL_port_decl_in_list = 94,         /* port_decl_in_list  */
  YYSYMBOL_module_items = 95,              /* module_items  */
  YYSYMBOL_module_item = 96,               /* module_item  */
  YYSYMBOL_port_decl = 97,                 /* port_decl  */
  YYSYMBOL_decl_list = 98,                 /* decl_list  */
  YYSYMBOL_stmt = 99,                      /* stmt  */
  YYSYMBOL_stmts = 100,                    /* stmts  */
  YYSYMBOL_event_list = 101,               /* event_list  */
  YYSYMBOL_event_expr = 102,               /* event_expr  */
  YYSYMBOL_readmem_args = 103,             /* readmem_args  */
  YYSYMBOL_gen_items = 104,                /* gen_items  */
  YYSYMBOL_gen_item = 105,                 /* gen_item  */
  YYSYMBOL_genvar_list = 106,              /* genvar_list  */
  YYSYMBOL_gen_block = 107,                /* gen_block  */
  YYSYMBOL_gen_body = 108,                 /* gen_body  */
  YYSYMBOL_case_items = 109,               /* case_items  */
  YYSYMBOL_case_item = 110,                /* case_item  */
  YYSYMBOL_param_override = 111,           /* param_override  */
  YYSYMBOL_param_list = 112,               /* param_list  */
  YYSYMBOL_param_assign = 113,             /* param_assign  */
  YYSYMBOL_port_conn_list = 114,           /* port_conn_list  */
  YYSYMBOL_port_conn = 115,                /* port_conn  */
  YYSYMBOL_range = 116,                    /* range  */
  YYSYMBOL_expr = 117,                     /* expr  */
  YYSYMBOL_prim_expr = 118,                /* prim_expr  */
  YYSYMBOL_lvalue = 119,                   /* lvalue  */
  YYSYMBOL_lvalue_list = 120,              /* lvalue_list  */
  YYSYMBOL_expr_list = 121                 /* expr_list  */
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
#define YYLAST   2462

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  517

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


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
       2,     2,     2,    71,     2,    75,     2,    69,    62,     2,
      76,    77,    67,    65,    78,    66,    81,    68,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    74,
      63,    79,    64,    58,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    82,     2,    83,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,    60,    85,    72,     2,     2,     2,
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
      55,    56,    57,    70,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    92,    92,    96,    97,   101,   108,   120,   121,   125,
     130,   131,   135,   136,   140,   141,   142,   146,   147,   148,
     152,   153,   166,   178,   180,   191,   201,   203,   205,   207,
     209,   211,   213,   215,   219,   221,   230,   232,   234,   236,
     238,   240,   243,   245,   247,   249,   250,   254,   265,   273,
     283,   291,   301,   309,   319,   327,   337,   345,   355,   365,
     376,   377,   381,   382,   383,   389,   395,   401,   408,   414,
     424,   430,   437,   443,   450,   456,   463,   470,   471,   472,
     477,   483,   489,   495,   500,   509,   519,   529,   536,   545,
     546,   550,   552,   557,   559,   564,   569,   570,   574,   582,
     591,   597,   604,   612,   613,   617,   618,   619,   623,   624,
     625,   626,   630,   631,   635,   641,   648,   653,   661,   666,
     667,   671,   675,   676,   680,   686,   694,   706,   707,   708,
     709,   710,   711,   712,   713,   714,   715,   716,   717,   718,
     719,   720,   721,   722,   723,   724,   725,   726,   727,   728,
     729,   734,   735,   736,   737,   738,   739,   740,   741,   742,
     746,   750,   755,   762,   768,   777,   788,   795,   807,   811,
     817,   824,   829,   837,   842,   849,   855,   863,   873,   883,
     884,   888,   889
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
  "POSEDGE", "NEGEDGE", "OR", "SYS_FOPEN", "SYS_FCLOSE", "SYS_FSCANF",
  "SYS_FGETS", "SYS_FDISPLAY", "SYS_DISPLAY", "SYS_FINISH", "SYS_CLOG2",
  "SYS_READMEMH", "SYS_READMEMB", "EQ", "NE", "LE", "NONBLOCKING", "GE",
  "LOGAND", "LOGOR", "SHL", "SHR", "SSHR", "NAND", "NOR", "XNOR", "'?'",
  "':'", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "POWER", "'!'", "'~'", "UNARY", "';'", "'#'", "'('", "')'", "','",
  "'='", "'@'", "'.'", "'['", "']'", "'{'", "'}'", "$accept", "source",
  "module_list", "module", "module_param_decls", "module_param_decl",
  "opt_port_list", "port_list", "port_decl_in_list", "module_items",
  "module_item", "port_decl", "decl_list", "stmt", "stmts", "event_list",
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

#define YYPACT_NINF (-455)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      28,    77,    90,    28,  -455,   -12,  -455,  -455,    36,   107,
      81,   104,  -455,    11,     9,   146,  -455,  -455,   967,   100,
     150,  -455,  -455,     5,    83,   680,   188,  -455,    23,    10,
      83,   199,  -455,   107,     7,    25,    12,   201,   217,    27,
       2,     8,   539,   125,    87,   896,  -455,   115,   155,   102,
     164,   104,  -455,   239,   249,   182,  -455,  -455,   190,   202,
     680,   680,   680,   680,   680,   680,   680,   680,   680,   680,
    2193,  -455,  -455,  -455,   284,  -455,    83,   285,   286,  -455,
    -455,   214,   218,   222,   290,   223,    83,   300,  -455,   225,
     229,   304,   227,     2,   231,   680,   235,   -17,   539,   236,
     237,   240,   241,   242,   243,   244,   247,   248,    73,   251,
     252,  -455,   310,   253,  -455,   -21,   257,   258,   322,    41,
    -455,   254,  -455,  -455,  -455,  -455,   680,   265,  -455,  -455,
    -455,   680,   328,   680,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  1345,   960,   -33,   680,   680,   680,   680,   680,
     680,   680,   680,   680,   680,   680,   680,   680,   680,   680,
     680,   680,   680,   680,   680,   680,   338,   680,   680,  -455,
     341,  -455,  -455,   -28,   254,   680,    21,    75,   680,    39,
     342,    96,    40,   680,   680,   267,   680,  -455,   -19,   680,
     446,    14,   680,  -455,   256,   680,   680,     2,   680,   680,
     343,   680,   683,   723,  -455,   680,   680,   680,   274,   175,
     680,    13,   680,    29,  -455,    74,  -455,  -455,   346,   158,
    -455,  2268,   967,  1000,   160,  1374,  -455,   680,   680,  -455,
     130,   130,   165,   165,  2318,  2293,   181,   181,   181,  2393,
    2393,  2368,  2218,  1140,  2343,  2368,  2393,   165,   165,   144,
     144,   680,  -455,  -455,  -455,  -455,   278,   350,   166,  -455,
     176,  1751,  -455,   351,   680,    88,   282,  1777,  -455,  -455,
     680,    94,   283,  -455,  1803,  1829,   680,  1035,     2,  -455,
    1855,  -455,   356,   357,   287,    -1,  -455,  1881,  -455,  -455,
    1403,  1432,   289,  1461,  1490,   293,  1519,   294,  2268,   178,
     295,   180,  1548,   297,   288,   298,  -455,   359,   373,  1907,
     301,   303,   305,  1933,  1577,   306,   379,  -455,   380,   311,
    -455,   254,   920,   680,   307,  -455,   382,  -455,    26,  2268,
     680,  -455,  -455,  -455,   312,   316,   314,   388,  -455,  -455,
    1959,  -455,  -455,  -455,   114,  1985,  -455,  -455,  -455,  -455,
    2011,   680,   319,  -455,  -455,  -455,  -455,   539,   228,   539,
    -455,   539,   605,   680,   539,   539,   318,   329,   332,   333,
     337,   345,   347,   349,   353,   325,   335,  -455,   392,   680,
     680,  -455,   944,   680,   336,  -455,   680,  -455,  -455,  1175,
     680,   340,   339,  2318,   640,  -455,  -455,   344,  -455,  -455,
    -455,  -455,  1210,   680,  -455,  -455,  -455,   406,   513,   565,
    -455,  1315,  2037,  -455,  -455,  -455,  -455,  -455,  -455,  -455,
    -455,  -455,  -455,  -455,   355,   358,   191,   196,   203,   794,
    -455,   408,  2063,   680,  1606,  -455,  1070,  -455,  -455,  -455,
    1635,   124,  -455,  1105,   539,   539,  -455,  -455,  -455,   539,
     680,   680,  -455,  -455,   360,   361,   362,   428,  -455,  -455,
     818,   944,   680,  2089,  -455,   680,  -455,  -455,   364,   208,
     680,  -455,  -455,  -455,  -455,  2243,  2115,  -455,  -455,  -455,
     871,  -455,  -455,  -455,  -455,  2141,   680,  1245,  -455,   365,
    1280,   539,     2,   847,     2,  2167,  -455,  -455,  -455,  -455,
     354,  -455,   363,   438,   680,   680,   367,  1664,  1693,   680,
     539,   944,  1722,  -455,  -455,   944,  -455
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,    11,     1,     3,     0,    16,
       0,     0,    14,     0,     0,     0,    13,    15,    19,     0,
       0,     8,    48,     0,     0,     0,     0,    50,     0,     0,
       0,     0,    10,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,     0,     0,
      11,     0,    54,     0,     0,   161,   172,   160,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,    47,    52,     0,    56,     0,     0,     0,    49,
      12,     0,     0,    61,     0,    61,     0,     0,    61,     0,
       0,     0,   173,     0,     0,     0,     0,   173,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,     0,     0,    40,     0,     0,     0,     0,     0,
      97,     0,     5,    17,    20,    46,     0,     0,     7,    53,
      58,     0,     0,     0,   154,   155,   157,   158,   156,   151,
     152,   153,     0,   182,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,    55,    57,     0,     0,     0,     0,    61,     0,     0,
       0,    61,     0,     0,     0,     0,     0,   180,     0,     0,
       0,     0,     0,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   104,     0,    45,    96,     0,     0,
     120,     9,    19,     0,     0,     0,   168,     0,     0,   166,
     138,   139,   142,   143,   148,   149,   144,   145,   146,   136,
     137,   135,     0,     0,   133,   134,   132,   140,   141,   127,
     128,     0,   129,   130,   131,    59,     0,     0,     0,   123,
       0,     0,    26,     0,     0,     0,     0,     0,    30,    61,
       0,     0,     0,    32,     0,     0,     0,     0,     0,   178,
       0,    39,     0,     0,     0,     0,    92,     0,    63,    89,
       0,     0,     0,     0,     0,     0,     0,   172,   182,     0,
     172,     0,     0,     0,    95,     0,    79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,     0,     0,
     118,     0,     0,     0,   163,   169,     0,   171,     0,   181,
       0,   126,   147,    44,     0,     0,     0,     0,    25,    60,
       0,    23,    21,    29,     0,     0,    27,    22,    33,    34,
       0,     0,   175,   179,    36,    93,    94,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    72,     0,     0,
       0,    70,     0,     0,     0,   103,     0,   119,     6,     0,
       0,     0,     0,   150,     0,    42,   122,     0,    24,    31,
      28,    35,     0,     0,    37,    91,    38,    66,     0,     0,
     113,     0,     0,    64,    65,    82,    83,    88,    87,    74,
      73,    78,    75,    76,     0,     0,     0,     0,     0,     0,
     107,   100,     0,     0,     0,   162,     0,   170,   167,   125,
       0,     0,   174,     0,     0,     0,   117,    68,   112,     0,
       0,     0,    80,    81,   169,     0,     0,     0,   110,   111,
       0,     0,     0,     0,   121,     0,   165,   124,     0,     0,
       0,   177,    67,   116,   114,     0,     0,    84,    85,    86,
       0,   105,   108,   109,   101,     0,     0,     0,    43,     0,
       0,     0,     0,     0,     0,     0,   164,    41,   176,   115,
       0,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,    99,     0,    98
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -455,  -455,  -455,   440,  -455,   396,   398,  -455,   417,   230,
     -16,    45,   -79,   -94,  -455,  -455,    95,   255,  -455,   -42,
    -455,  -454,   -26,  -455,    47,  -455,   292,   137,    18,   127,
     186,   -25,  -455,   -37,  -455,   -58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     4,    20,    21,    10,    15,    16,    45,
     430,    47,   176,   114,   194,   285,   286,   303,   119,   459,
     215,   431,   460,   409,   410,    48,   219,   220,   258,   259,
      26,   298,    71,   115,   188,   304
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   120,    46,    94,   193,    92,   179,   484,    52,   182,
      81,   144,    27,    75,    22,    85,    55,    56,    57,    28,
      29,    23,    30,    76,    24,    86,    73,   210,    83,   123,
      90,   192,   315,   358,     1,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   228,   282,   283,   310,   256,
     311,   312,   229,   257,    17,    59,   187,   514,   211,   278,
     316,   516,   116,     8,     9,   186,   279,   117,    60,    61,
     190,   216,   118,    62,    63,    64,   359,   217,    17,    65,
       5,   284,    82,    95,    66,    67,    93,    25,    96,    68,
       6,    25,    25,    25,    25,   262,   281,    69,   265,   263,
     289,   221,   271,    49,   228,    25,   223,    25,   225,    25,
      12,   392,    11,   268,   273,    13,    14,   263,   263,    19,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   252,   253,   254,   299,   301,   116,   204,   317,   205,
     261,   117,   318,   267,   264,    18,   118,    25,   274,   275,
     292,   277,   341,   121,   280,    25,   263,   287,   346,   328,
     290,   291,   263,   293,   294,   270,   296,   147,    25,   148,
     302,   126,   151,   152,   153,   309,   313,   314,   399,   124,
     344,    72,   263,   162,   163,   164,   165,   166,   167,   168,
      31,   468,    79,   329,    88,   257,    46,   307,   308,    53,
      54,   166,   167,   168,    74,    77,    78,   151,   152,   153,
      89,    84,    87,    32,    33,    91,   332,    50,    51,   125,
     164,   165,   166,   167,   168,   320,   321,   325,   326,   340,
       9,   353,   129,   335,   336,   345,   164,   165,   166,   167,
     168,   350,   130,   337,   321,   369,   228,   371,   228,    97,
     282,   283,   170,   404,   131,   406,   132,   407,   454,   326,
     413,   414,   180,   455,   228,    98,   288,    99,   133,   100,
     456,   228,   101,   102,   103,   489,   336,   169,   171,   172,
     173,   104,   105,   177,   174,   106,   107,   108,   389,   109,
     110,   175,   178,   181,   183,   393,   123,   185,   184,   186,
     189,   191,   195,   196,   446,   208,   197,   198,   199,   200,
     201,   427,   428,   202,   203,   214,   402,   206,   207,   209,
     111,   112,   224,   212,   213,   218,   113,   411,   412,   222,
      93,    55,    56,    57,   255,   269,   276,   295,   306,   319,
     472,   473,   333,   334,   339,   474,   342,   347,   432,   355,
     356,   434,   375,   266,   357,   436,   228,   272,   363,   440,
     366,   368,   370,    58,   373,   374,   376,   378,   443,   379,
      59,   380,   384,   385,   411,   383,   391,   386,   394,   390,
     395,   397,   415,    60,    61,   257,   426,   499,    62,    63,
      64,   403,   424,   416,    65,   251,   417,   418,   463,    66,
      67,   419,   425,   458,    68,   433,   513,   437,   483,   420,
     441,   421,    69,   422,   438,   475,   476,   423,   444,   452,
     461,   480,   453,   504,   477,   478,   479,   485,   488,   497,
     487,   506,   505,     7,   482,   490,   509,   128,   127,    97,
      80,   483,   322,   405,   493,   500,   448,   502,   387,   469,
       0,   495,   305,   396,   458,    98,   260,    99,     0,   100,
       0,     0,   101,   102,   103,     0,     0,   482,     0,   507,
     508,   104,   105,     0,   512,   106,   107,   108,     0,   109,
     110,   145,   146,   147,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,     0,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,    97,     0,     0,     0,
     111,   112,     0,     0,     0,     0,   113,     0,     0,     0,
      93,     0,    98,     0,    99,     0,   100,     0,     0,   101,
     102,   103,    97,     0,     0,     0,     0,     0,   104,   105,
       0,     0,   106,   107,   108,     0,   109,   110,    98,     0,
      99,     0,   100,     0,     0,   101,   102,   103,    55,    56,
      57,     0,   445,     0,   104,   105,     0,     0,   106,   107,
     108,     0,   109,   110,     0,     0,     0,   111,   112,   447,
     408,     0,     0,   113,     0,     0,     0,    93,     0,     0,
      58,     0,     0,     0,     0,     0,     0,    59,    55,    56,
      57,     0,     0,   111,   112,     0,     0,     0,     0,   113,
      60,    61,     0,    93,     0,    62,    63,    64,     0,     0,
     408,    65,     0,     0,     0,     0,    66,    67,     0,     0,
      58,    68,     0,    55,    56,    57,     0,    59,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    61,     0,     0,     0,    62,    63,    64,     0,     0,
       0,    65,     0,     0,     0,    58,    66,    67,     0,     0,
       0,    68,    59,    55,    56,    57,    55,   297,    57,    69,
       0,     0,     0,     0,     0,    60,    61,     0,     0,     0,
      62,    63,    64,     0,     0,     0,    65,     0,     0,     0,
       0,    66,    67,     0,     0,    58,    68,   439,    58,     0,
       0,     0,    59,     0,    69,    59,    55,   300,    57,     0,
       0,     0,     0,     0,     0,    60,    61,     0,    60,    61,
      62,    63,    64,    62,    63,    64,    65,     0,     0,    65,
       0,    66,    67,     0,    66,    67,    68,     0,    58,    68,
       0,     0,     0,     0,    69,    59,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
       0,     0,     0,    62,    63,    64,     0,     0,     0,    65,
       0,     0,     0,     0,    66,    67,     0,    34,     0,    68,
       0,     0,    13,    14,    35,    36,    37,    69,    38,    39,
      40,    41,    42,     0,     0,   116,     0,     0,     0,     0,
     117,    34,     0,    43,     0,   118,    13,    14,    35,    36,
      37,     0,    38,    39,    40,    41,    42,     0,   481,   116,
       0,     0,     0,     0,   117,     0,     0,    43,     0,   118,
      34,     0,     0,   457,     0,    13,    14,    35,    36,    37,
       0,    38,    39,    40,    41,    42,     0,   501,   116,    44,
       0,     0,     0,   117,    34,     0,    43,     0,   118,    13,
      14,    35,    36,    37,     0,    38,    39,    40,    41,    42,
       0,     0,   116,    44,     0,     0,     0,   117,     0,    34,
      43,     0,   118,   122,    13,    14,    35,    36,    37,     0,
      38,    39,    40,    41,    42,     0,     0,     0,     0,     0,
       0,     0,    44,    34,     0,    43,     0,   388,    13,    14,
      35,    36,    37,     0,    38,    39,    40,    41,    42,     0,
       0,     0,     0,     0,     0,     0,    44,    34,     0,    43,
       0,     0,    13,    14,    35,    36,    37,     0,    38,    39,
      40,    41,    42,   429,     0,     0,     0,     0,     0,     0,
      34,    44,     0,    43,     0,    13,    14,    35,    36,    37,
       0,    38,    39,    40,    41,    42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    44,    43,     0,     0,     0,
       0,     0,     0,     0,     0,   145,   146,   147,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,    44,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,   227,   145,   146,   147,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   323,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,   146,   147,   324,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   351,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,   146,   147,   352,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   465,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,   146,   147,   466,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   470,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,   146,   147,   471,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,   146,   147,   331,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,   146,   147,   435,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,   146,   147,   442,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,   146,   147,   496,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,   146,   147,   498,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   449,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,     0,
     145,   146,   147,   450,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,   145,
     146,   147,   226,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,     0,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,     0,     0,     0,     0,   145,   146,
     147,   327,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     0,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,     0,     0,     0,     0,   145,   146,   147,
     361,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,     0,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,     0,     0,     0,     0,   145,   146,   147,   362,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,     0,     0,     0,     0,   145,   146,   147,   364,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,   145,   146,   147,   365,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,     0,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,     0,
       0,     0,     0,   145,   146,   147,   367,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     0,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,     0,     0,
       0,     0,   145,   146,   147,   372,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,     0,     0,     0,
       0,   145,   146,   147,   382,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,     0,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,     0,     0,     0,     0,
     145,   146,   147,   464,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,     0,   145,
     146,   147,   467,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,     0,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,     0,     0,     0,     0,   145,   146,
     147,   510,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     0,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,     0,     0,     0,     0,   145,   146,   147,
     511,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,     0,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,     0,     0,     0,     0,   145,   146,   147,   515,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,     0,   145,   146,   147,   338,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,     0,   145,   146,
     147,   343,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     0,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,     0,   145,   146,   147,   348,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,     0,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,     0,
     145,   146,   147,   349,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,   145,   146,   147,   354,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,     0,   145,   146,   147,   360,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,     0,   145,   146,
     147,   377,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     0,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,     0,   145,   146,   147,   381,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,     0,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,     0,
     145,   146,   147,   398,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,   145,   146,   147,   400,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,     0,   145,   146,   147,   401,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,     0,   145,   146,
     147,   451,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     0,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,     0,   145,   146,   147,   462,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,     0,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,     0,
     145,   146,   147,   486,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,     0,   145,   146,   147,   492,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,     0,   145,   146,   147,   494,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,     0,   145,   146,
     147,   503,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   145,   146,   147,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   330,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   145,   146,
     147,     0,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   491,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   145,   146,   147,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     0,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   145,   146,
     147,     0,   148,   149,     0,   151,   152,   153,   154,   155,
     156,   157,     0,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   145,   146,   147,     0,   148,     0,     0,
     151,   152,   153,   154,   155,   156,   157,     0,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   145,   146,
     147,     0,   148,     0,     0,   151,   152,   153,   154,   155,
     156,     0,     0,     0,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   145,   146,   147,     0,   148,     0,     0,
     151,   152,   153,   154,   155,     0,     0,     0,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   145,   146,
     147,     0,   148,     0,     0,   151,   152,   153,     0,     0,
       0,     0,     0,     0,     0,     0,   162,   163,   164,   165,
     166,   167,   168
};

static const yytype_int16 yycheck[] =
{
      25,    43,    18,    40,    98,     3,    85,   461,     3,    88,
       3,    69,     3,     3,     3,     3,     3,     4,     5,    10,
      11,    10,    13,    13,    13,    13,     3,    48,     3,    45,
       3,    48,     3,    34,     6,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    78,    32,    33,    35,    77,
      37,    38,    85,    81,     9,    42,    93,   511,    79,    78,
      31,   515,    21,    75,    76,    82,    85,    26,    55,    56,
      95,    30,    31,    60,    61,    62,    77,   119,    33,    66,
       3,    67,    75,    75,    71,    72,    84,    82,    80,    76,
       0,    82,    82,    82,    82,    74,   190,    84,   177,    78,
     194,   126,   181,     3,    78,    82,   131,    82,   133,    82,
       3,    85,    76,    74,    74,     8,     9,    78,    78,    15,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   202,   203,    21,    74,    74,    76,
     175,    26,    78,   178,    79,    74,    31,    82,   183,   184,
     197,   186,    74,    76,   189,    82,    78,   192,    74,   227,
     195,   196,    78,   198,   199,    79,   201,    47,    82,    49,
     205,    79,    52,    53,    54,   210,   211,   212,    74,    74,
     269,     3,    78,    63,    64,    65,    66,    67,    68,    69,
      14,    77,     3,   228,     3,    81,   222,    32,    33,    23,
      24,    67,    68,    69,    28,    29,    30,    52,    53,    54,
       3,    35,    36,    77,    78,    39,   251,    77,    78,    74,
      65,    66,    67,    68,    69,    77,    78,    77,    78,   264,
      76,   278,     3,    77,    78,   270,    65,    66,    67,    68,
      69,   276,     3,    77,    78,    77,    78,    77,    78,     3,
      32,    33,    76,   357,    82,   359,    76,   361,    77,    78,
     364,   365,    86,    77,    78,    19,    20,    21,    76,    23,
      77,    78,    26,    27,    28,    77,    78,     3,     3,     3,
      76,    35,    36,     3,    76,    39,    40,    41,   323,    43,
      44,    79,    79,     3,    79,   330,   322,     3,    79,    82,
      79,    76,    76,    76,   408,     5,    76,    76,    76,    76,
      76,   379,   380,    76,    76,     3,   351,    76,    76,    76,
      74,    75,     4,    76,    76,    81,    80,   362,   363,    74,
      84,     3,     4,     5,     3,     3,    79,     4,    74,     3,
     444,   445,    74,     3,     3,   449,    74,    74,   383,     3,
       3,   386,     3,   177,    77,   390,    78,   181,    79,   394,
      77,    77,    77,    35,    77,    77,     3,    76,   403,    76,
      42,    76,     3,     3,   409,    79,     4,    76,    76,    82,
      74,     3,    74,    55,    56,    81,     4,   491,    60,    61,
      62,    82,    77,    74,    66,    67,    74,    74,   433,    71,
      72,    74,    77,   429,    76,    79,   510,    77,   460,    74,
      76,    74,    84,    74,    85,   450,   451,    74,    22,    74,
      22,     3,    74,    79,    74,    74,    74,   462,    74,    74,
     465,     3,    79,     3,   460,   470,    79,    51,    50,     3,
      33,   493,   222,   358,   480,   492,   409,   494,   321,   441,
      -1,   486,   207,   336,   480,    19,   174,    21,    -1,    23,
      -1,    -1,    26,    27,    28,    -1,    -1,   493,    -1,   504,
     505,    35,    36,    -1,   509,    39,    40,    41,    -1,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,     3,    -1,    -1,    -1,
      74,    75,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      84,    -1,    19,    -1,    21,    -1,    23,    -1,    -1,    26,
      27,    28,     3,    -1,    -1,    -1,    -1,    -1,    35,    36,
      -1,    -1,    39,    40,    41,    -1,    43,    44,    19,    -1,
      21,    -1,    23,    -1,    -1,    26,    27,    28,     3,     4,
       5,    -1,    59,    -1,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,    -1,    -1,    -1,    74,    75,    24,
      25,    -1,    -1,    80,    -1,    -1,    -1,    84,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    80,
      55,    56,    -1,    84,    -1,    60,    61,    62,    -1,    -1,
      25,    66,    -1,    -1,    -1,    -1,    71,    72,    -1,    -1,
      35,    76,    -1,     3,     4,     5,    -1,    42,    -1,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    -1,    -1,    -1,    60,    61,    62,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    35,    71,    72,    -1,    -1,
      -1,    76,    42,     3,     4,     5,     3,     4,     5,    84,
      -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,
      60,    61,    62,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    71,    72,    -1,    -1,    35,    76,    77,    35,    -1,
      -1,    -1,    42,    -1,    84,    42,     3,     4,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    55,    56,
      60,    61,    62,    60,    61,    62,    66,    -1,    -1,    66,
      -1,    71,    72,    -1,    71,    72,    76,    -1,    35,    76,
      -1,    -1,    -1,    -1,    84,    42,    -1,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    60,    61,    62,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    71,    72,    -1,     3,    -1,    76,
      -1,    -1,     8,     9,    10,    11,    12,    84,    14,    15,
      16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      26,     3,    -1,    29,    -1,    31,     8,     9,    10,    11,
      12,    -1,    14,    15,    16,    17,    18,    -1,    20,    21,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    29,    -1,    31,
       3,    -1,    -1,    59,    -1,     8,     9,    10,    11,    12,
      -1,    14,    15,    16,    17,    18,    -1,    20,    21,    75,
      -1,    -1,    -1,    26,     3,    -1,    29,    -1,    31,     8,
       9,    10,    11,    12,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    21,    75,    -1,    -1,    -1,    26,    -1,     3,
      29,    -1,    31,     7,     8,     9,    10,    11,    12,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,     3,    -1,    29,    -1,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,     3,    -1,    29,
      -1,    -1,     8,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    75,    -1,    29,    -1,     8,     9,    10,    11,    12,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    75,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    84,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    83,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    83,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    83,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    83,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    83,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    83,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    83,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    83,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    83,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    78,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    45,
      46,    47,    77,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    45,    46,
      47,    77,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    45,    46,    47,
      77,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    45,    46,    47,    77,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    45,    46,    47,    77,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    45,    46,    47,    77,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    45,    46,    47,    77,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    45,    46,    47,    77,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    45,    46,    47,    77,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      45,    46,    47,    77,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    45,
      46,    47,    77,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    45,    46,
      47,    77,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    45,    46,    47,
      77,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    45,    46,    47,    77,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    45,    46,    47,    74,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    -1,    45,    46,
      47,    74,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    45,    46,    47,    74,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      45,    46,    47,    74,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    45,    46,    47,    74,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    45,    46,    47,    74,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    -1,    45,    46,
      47,    74,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    45,    46,    47,    74,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      45,    46,    47,    74,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    45,    46,    47,    74,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    45,    46,    47,    74,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    -1,    45,    46,
      47,    74,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    45,    46,    47,    74,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      45,    46,    47,    74,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    45,    46,    47,    74,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    45,    46,    47,    74,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    -1,    45,    46,
      47,    74,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    45,    46,
      47,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    45,    46,
      47,    -1,    49,    50,    -1,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    45,    46,    47,    -1,    49,    -1,    -1,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    45,    46,
      47,    -1,    49,    -1,    -1,    52,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    45,    46,    47,    -1,    49,    -1,    -1,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    45,    46,
      47,    -1,    49,    -1,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    87,    88,    89,     3,     0,    89,    75,    76,
      92,    76,     3,     8,     9,    93,    94,    97,    74,    15,
      90,    91,     3,    10,    13,    82,   116,     3,    10,    11,
      13,   116,    77,    78,     3,    10,    11,    12,    14,    15,
      16,    17,    18,    29,    75,    95,    96,    97,   111,     3,
      77,    78,     3,   116,   116,     3,     4,     5,    35,    42,
      55,    56,    60,    61,    62,    66,    71,    72,    76,    84,
     117,   118,     3,     3,   116,     3,    13,   116,   116,     3,
      94,     3,    75,     3,   116,     3,    13,   116,     3,     3,
       3,   116,     3,    84,   119,    75,    80,     3,    19,    21,
      23,    26,    27,    28,    35,    36,    39,    40,    41,    43,
      44,    74,    75,    80,    99,   119,    21,    26,    31,   104,
     105,    76,     7,    96,    74,    74,    79,    92,    91,     3,
       3,    82,    76,    76,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   121,    45,    46,    47,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     3,
     116,     3,     3,    76,    76,    79,    98,     3,    79,    98,
     116,     3,    98,    79,    79,     3,    82,   119,   120,    79,
     117,    76,    48,    99,   100,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    74,    76,    76,    76,     5,    76,
      48,    79,    76,    76,     3,   106,    30,   105,    81,   112,
     113,   117,    74,   117,     4,   117,    77,    84,    78,    85,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,    67,   117,   117,   117,     3,    77,    81,   114,   115,
     112,   117,    74,    78,    79,    98,   116,   117,    74,     3,
      79,    98,   116,    74,   117,   117,    79,   117,    78,    85,
     117,    99,    32,    33,    67,   101,   102,   117,    20,    99,
     117,   117,   119,   117,   117,     4,   117,     4,   117,   121,
       4,   121,   117,   103,   121,   103,    74,    32,    33,   117,
      35,    37,    38,   117,   117,     3,    31,    74,    78,     3,
      77,    78,    95,    59,    83,    77,    78,    77,   121,   117,
      59,    83,   117,    74,     3,    77,    78,    77,    74,     3,
     117,    74,    74,    74,    98,   117,    74,    74,    74,    74,
     117,    59,    83,   119,    74,     3,     3,    77,    34,    77,
      74,    77,    77,    79,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,     3,     3,    74,    76,    76,
      76,    74,    77,    79,     3,     3,    76,   113,     7,   117,
      82,     4,    85,   117,    76,    74,   115,     3,    74,    74,
      74,    74,   117,    82,    99,   102,    99,    99,    25,   109,
     110,   117,   117,    99,    99,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    77,    77,     4,   121,   121,    19,
      96,   107,   117,    79,   117,    83,   117,    77,    85,    77,
     117,    76,    83,   117,    22,    59,    99,    24,   110,    59,
      78,    74,    74,    74,    77,    77,    77,    59,    96,   105,
     108,    22,    74,   117,    77,    59,    83,    77,    77,   114,
      59,    83,    99,    99,    99,   117,   117,    74,    74,    74,
       3,    20,    96,   105,   107,   117,    74,   117,    74,    77,
     117,    59,    74,   108,    74,   117,    83,    74,    83,    99,
     119,    20,   119,    74,    79,    79,     3,   117,   117,    79,
      77,    77,   117,    99,   107,    77,   107
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    86,    87,    88,    88,    89,    89,    90,    90,    91,
      92,    92,    93,    93,    94,    94,    94,    95,    95,    95,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      98,    98,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     100,   101,   101,   102,   102,   103,   104,   104,   105,   105,
     105,   105,   105,   106,   106,   107,   107,   107,   108,   108,
     108,   108,   109,   109,   110,   110,   110,   110,   111,   112,
     112,   113,   114,   114,   115,   115,   116,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   119,   119,   119,   119,   119,   119,   120,
     120,   121,   121
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     6,    10,     3,     1,     4,
       3,     0,     3,     1,     1,     1,     0,     2,     1,     0,
       2,     5,     5,     5,     6,     5,     4,     5,     6,     5,
       4,     6,     4,     5,     5,     6,     5,     6,     6,     4,
       2,    10,     6,     9,     5,     3,     2,     3,     2,     3,
       2,     4,     3,     4,     3,     4,     3,     4,     4,     5,
       3,     0,     1,     3,     5,     5,     5,     7,     6,    13,
       4,     4,     4,     5,     5,     5,     5,     2,     5,     3,
       6,     6,     5,     5,     7,     7,     7,     5,     5,     2,
       1,     3,     1,     2,     2,     1,     2,     1,    14,    13,
       5,     7,     3,     3,     1,     3,     5,     1,     2,     2,
       1,     1,     2,     1,     3,     5,     3,     2,     4,     3,
       1,     5,     3,     1,     5,     4,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     3,
       5,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     6,     4,     9,     7,     3,     6,     3,     4,
       6,     4,     1,     1,     6,     4,     9,     7,     3,     3,
       1,     3,     1
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
#line 96 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1931 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 4: /* module_list: module  */
#line 97 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1937 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 5: /* module: MODULE IDENTIFIER opt_port_list ';' module_items ENDMODULE  */
#line 102 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-4].str), yylineno);
        free((yyvsp[-4].str));
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) { addChild((yyval.node), c); } (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 1948 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 6: /* module: MODULE IDENTIFIER '#' '(' module_param_decls ')' opt_port_list ';' module_items ENDMODULE  */
#line 109 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-8].str), yylineno);
        free((yyvsp[-8].str));
        /* Add parameter declarations as children */
        if ((yyvsp[-5].node)) { for (auto *c : (yyvsp[-5].node)->children) addChild((yyval.node), c); (yyvsp[-5].node)->children.clear(); freeTree((yyvsp[-5].node)); }
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 1961 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 7: /* module_param_decls: module_param_decls ',' module_param_decl  */
#line 120 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                             { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1967 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 8: /* module_param_decls: module_param_decl  */
#line 121 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1973 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 9: /* module_param_decl: PARAMETER IDENTIFIER '=' expr  */
#line 126 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-2].str), yylineno); free((yyvsp[-2].str)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1979 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 10: /* opt_port_list: '(' port_list ')'  */
#line 130 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 1985 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 11: /* opt_port_list: %empty  */
#line 131 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = nullptr; }
#line 1991 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 12: /* port_list: port_list ',' port_decl_in_list  */
#line 135 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                    { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1997 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 13: /* port_list: port_decl_in_list  */
#line 136 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                    { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 2003 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 14: /* port_decl_in_list: IDENTIFIER  */
#line 140 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                            { free((yyvsp[0].str)); (yyval.node) = nullptr; }
#line 2009 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 15: /* port_decl_in_list: port_decl  */
#line 141 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2015 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 16: /* port_decl_in_list: %empty  */
#line 142 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = nullptr; }
#line 2021 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 17: /* module_items: module_items module_item  */
#line 146 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                             { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2027 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 18: /* module_items: module_item  */
#line 147 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2033 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 19: /* module_items: %empty  */
#line 148 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2039 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 21: /* module_item: WIRE range IDENTIFIER range ';'  */
#line 154 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
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
#line 2056 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 22: /* module_item: REG range IDENTIFIER range ';'  */
#line 167 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          /* Unpacked memory: reg [data_msb:data_lsb] name[addr_msb:addr_lsb] */
          (yyval.node) = makeNode(NodeType::NET_DECL, "reg memory", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb;
          for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c);
          (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2072 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 23: /* module_item: WIRE range IDENTIFIER decl_list ';'  */
#line 179 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
#line 2078 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 24: /* module_item: WIRE range IDENTIFIER '=' expr ';'  */
#line 181 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
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
#line 2093 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 25: /* module_item: WIRE IDENTIFIER '=' expr ';'  */
#line 192 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          auto *decl = makeNode(NodeType::NET_DECL, "wire", yylineno);
          addChild(decl, makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno));
          free((yyvsp[-3].str));
          decl->msb = 0;
          decl->lsb = 0;
          addChild(decl, (yyvsp[-1].node));
          (yyval.node) = decl;
      }
#line 2107 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 26: /* module_item: WIRE IDENTIFIER decl_list ';'  */
#line 202 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2113 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 27: /* module_item: REG range IDENTIFIER decl_list ';'  */
#line 204 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
#line 2119 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 28: /* module_item: REG range IDENTIFIER '=' expr ';'  */
#line 206 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); (yyval.node)->msb = (yyvsp[-4].node)->msb; (yyval.node)->lsb = (yyvsp[-4].node)->lsb; for (auto *c : (yyvsp[-4].node)->children) addChild((yyval.node), c); (yyvsp[-4].node)->children.clear(); freeTree((yyvsp[-4].node)); }
#line 2125 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 29: /* module_item: REG IDENTIFIER '=' expr ';'  */
#line 208 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2131 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 30: /* module_item: REG IDENTIFIER decl_list ';'  */
#line 210 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2137 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 31: /* module_item: REG SIGNED range IDENTIFIER decl_list ';'  */
#line 212 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg signed", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
#line 2143 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 32: /* module_item: INTEGER_KW IDENTIFIER decl_list ';'  */
#line 214 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "integer", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 31; (yyval.node)->lsb = 0; }
#line 2149 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 33: /* module_item: LOCALPARAM IDENTIFIER '=' expr ';'  */
#line 216 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2157 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 34: /* module_item: PARAMETER IDENTIFIER '=' expr ';'  */
#line 220 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2163 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 35: /* module_item: PARAMETER range IDENTIFIER '=' expr ';'  */
#line 222 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
          for (auto *c : (yyvsp[-4].node)->children) addChild((yyval.node), c);
          (yyvsp[-4].node)->children.clear();
          freeTree((yyvsp[-4].node));
      }
#line 2176 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 36: /* module_item: ASSIGN lvalue '=' expr ';'  */
#line 231 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ASSIGN, "", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2182 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 37: /* module_item: ALWAYS '@' '(' '*' ')' stmt  */
#line 233 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(*)", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2188 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 38: /* module_item: ALWAYS '@' '(' event_list ')' stmt  */
#line 235 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@events", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2194 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 39: /* module_item: ALWAYS '#' expr stmt  */
#line 237 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "#delay", yylineno); addChild((yyval.node), (yyvsp[-1].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2200 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 40: /* module_item: INITIAL_KW stmt  */
#line 239 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::INITIAL_BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2206 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 41: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' port_conn_list ')' ';'  */
#line 242 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-9].str), yylineno); free((yyvsp[-9].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-6].node)->children) addChild((yyval.node), c); (yyvsp[-6].node)->children.clear(); freeTree((yyvsp[-6].node)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 2212 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 42: /* module_item: IDENTIFIER IDENTIFIER '(' port_conn_list ')' ';'  */
#line 244 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-5].str), yylineno); free((yyvsp[-5].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 2218 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 43: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' ')' ';'  */
#line 246 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-8].str), yylineno); free((yyvsp[-8].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); for (auto *c : (yyvsp[-5].node)->children) addChild((yyval.node), c); (yyvsp[-5].node)->children.clear(); freeTree((yyvsp[-5].node)); }
#line 2224 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 44: /* module_item: IDENTIFIER IDENTIFIER '(' ')' ';'  */
#line 248 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-4].str), yylineno); free((yyvsp[-4].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); }
#line 2230 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 45: /* module_item: GENERATE gen_items ENDGENERATE  */
#line 249 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2236 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 46: /* module_item: param_override ';'  */
#line 250 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2242 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 47: /* port_decl: INPUT range IDENTIFIER  */
#line 255 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
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
#line 2257 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 48: /* port_decl: INPUT IDENTIFIER  */
#line 266 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2269 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 49: /* port_decl: OUTPUT range IDENTIFIER  */
#line 274 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2283 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 50: /* port_decl: OUTPUT IDENTIFIER  */
#line 284 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2295 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 51: /* port_decl: OUTPUT WIRE range IDENTIFIER  */
#line 292 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2309 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 52: /* port_decl: OUTPUT WIRE IDENTIFIER  */
#line 302 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2321 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 53: /* port_decl: INPUT WIRE range IDENTIFIER  */
#line 310 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2335 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 54: /* port_decl: INPUT WIRE IDENTIFIER  */
#line 320 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2347 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 55: /* port_decl: OUTPUT REG range IDENTIFIER  */
#line 328 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2361 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 56: /* port_decl: OUTPUT REG IDENTIFIER  */
#line 338 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2373 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 57: /* port_decl: OUTPUT SIGNED range IDENTIFIER  */
#line 346 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2387 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 58: /* port_decl: INPUT SIGNED range IDENTIFIER  */
#line 356 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2401 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 59: /* port_decl: OUTPUT REG SIGNED range IDENTIFIER  */
#line 366 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2413 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 60: /* decl_list: decl_list ',' IDENTIFIER  */
#line 376 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                             { free((yyvsp[0].str)); }
#line 2419 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 62: /* stmt: ';'  */
#line 381 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2425 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 63: /* stmt: BEGINKW stmts END  */
#line 382 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 2431 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 64: /* stmt: REPEAT '(' expr ')' stmt  */
#line 384 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "repeat", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2441 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 65: /* stmt: WHILE '(' expr ')' stmt  */
#line 390 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "while", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2451 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 66: /* stmt: IF '(' expr ')' stmt  */
#line 396 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2461 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 67: /* stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 402 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2472 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 68: /* stmt: CASE '(' expr ')' case_items ENDCASE  */
#line 409 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2482 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 69: /* stmt: FOR '(' lvalue '=' expr ';' expr ';' lvalue '=' expr ')' stmt  */
#line 415 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "", yylineno);
          addChild((yyval.node), (yyvsp[-10].node));  /* init lvalue */
          addChild((yyval.node), (yyvsp[-8].node));  /* init expr */
          addChild((yyval.node), (yyvsp[-6].node));  /* cond */
          addChild((yyval.node), (yyvsp[-4].node));  /* update lvalue */
          addChild((yyval.node), (yyvsp[-2].node)); /* update expr */
          addChild((yyval.node), (yyvsp[0].node)); /* body */
      }
#line 2496 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 70: /* stmt: lvalue '=' expr ';'  */
#line 425 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2506 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 71: /* stmt: IDENTIFIER NONBLOCKING expr ';'  */
#line 431 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno));
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2517 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 72: /* stmt: lvalue NONBLOCKING expr ';'  */
#line 438 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2527 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 73: /* stmt: SYS_DISPLAY '(' expr_list ')' ';'  */
#line 444 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2538 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 74: /* stmt: SYS_DISPLAY '(' STRING ')' ';'  */
#line 451 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2548 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 75: /* stmt: SYS_READMEMH '(' readmem_args ')' ';'  */
#line 457 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$readmemh", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2559 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 76: /* stmt: SYS_READMEMB '(' readmem_args ')' ';'  */
#line 464 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$readmemb", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2570 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 77: /* stmt: SYS_FINISH ';'  */
#line 470 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); }
#line 2576 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 78: /* stmt: SYS_FINISH '(' expr ')' ';'  */
#line 471 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); addChild((yyval.node), (yyvsp[-2].node)); }
#line 2582 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 79: /* stmt: '#' NUMBER ';'  */
#line 473 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, std::to_string((yyvsp[-1].num)->value), yylineno);
          free((yyvsp[-1].num));
      }
#line 2591 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 80: /* stmt: '@' '(' POSEDGE IDENTIFIER ')' ';'  */
#line 478 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, "posedge", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2601 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 81: /* stmt: '@' '(' NEGEDGE IDENTIFIER ')' ';'  */
#line 484 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, "negedge", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2611 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 82: /* stmt: SYS_FOPEN '(' STRING ')' ';'  */
#line 490 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2621 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 83: /* stmt: SYS_FCLOSE '(' expr ')' ';'  */
#line 496 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fclose", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
      }
#line 2630 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 84: /* stmt: lvalue '=' SYS_FOPEN '(' STRING ')' ';'  */
#line 501 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild(fc, makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          addChild((yyval.node), fc);
      }
#line 2643 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 85: /* stmt: lvalue '=' SYS_FSCANF '(' expr_list ')' ';'  */
#line 510 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fscanf", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2657 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 86: /* stmt: lvalue '=' SYS_FGETS '(' expr_list ')' ';'  */
#line 520 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fgets", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2671 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 87: /* stmt: SYS_FDISPLAY '(' expr_list ')' ';'  */
#line 530 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2682 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 88: /* stmt: SYS_FDISPLAY '(' STRING ')' ';'  */
#line 537 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2692 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 89: /* stmts: stmts stmt  */
#line 545 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
               { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2698 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 90: /* stmts: stmt  */
#line 546 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
               { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2704 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 91: /* event_list: event_list OR event_expr  */
#line 551 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2710 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 92: /* event_list: event_expr  */
#line 553 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::EVENT_CTRL, "events", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2716 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 93: /* event_expr: POSEDGE IDENTIFIER  */
#line 558 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::EVENT_CTRL, "posedge", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno)); free((yyvsp[0].str)); }
#line 2722 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 94: /* event_expr: NEGEDGE IDENTIFIER  */
#line 560 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::EVENT_CTRL, "negedge", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno)); free((yyvsp[0].str)); }
#line 2728 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 95: /* readmem_args: expr_list  */
#line 565 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 2734 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 96: /* gen_items: gen_items gen_item  */
#line 569 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2740 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 97: /* gen_items: gen_item  */
#line 570 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::GENERATE, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2746 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 98: /* gen_item: FOR '(' GENVAR IDENTIFIER '=' expr ';' expr ';' IDENTIFIER '=' expr ')' gen_block  */
#line 575 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2758 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 99: /* gen_item: FOR '(' IDENTIFIER '=' expr ';' expr ';' lvalue '=' expr ')' gen_block  */
#line 583 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
    {
        /* for (name = expr; cond; name = expr) — genvar already declared */
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2771 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 100: /* gen_item: IF '(' expr ')' gen_block  */
#line 592 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2781 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 101: /* gen_item: IF '(' expr ')' gen_block ELSE gen_block  */
#line 598 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2792 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 102: /* gen_item: GENVAR genvar_list ';'  */
#line 605 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
    {
        /* genvar declaration — skip */
        (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno);
    }
#line 2801 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 103: /* genvar_list: genvar_list ',' IDENTIFIER  */
#line 612 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                               { free((yyvsp[0].str)); }
#line 2807 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 104: /* genvar_list: IDENTIFIER  */
#line 613 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                 { free((yyvsp[0].str)); }
#line 2813 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 105: /* gen_block: BEGINKW gen_body END  */
#line 617 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2819 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 106: /* gen_block: BEGINKW ':' IDENTIFIER gen_body END  */
#line 618 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                          { (yyval.node) = (yyvsp[-1].node); free((yyvsp[-2].str)); }
#line 2825 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 107: /* gen_block: module_item  */
#line 619 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2831 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 108: /* gen_body: gen_body module_item  */
#line 623 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2837 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 109: /* gen_body: gen_body gen_item  */
#line 624 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2843 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 110: /* gen_body: module_item  */
#line 625 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2849 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 111: /* gen_body: gen_item  */
#line 626 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2855 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 112: /* case_items: case_items case_item  */
#line 630 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2861 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 113: /* case_items: case_item  */
#line 631 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2867 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 114: /* case_item: expr ':' stmt  */
#line 636 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2877 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 115: /* case_item: expr ',' expr ':' stmt  */
#line 642 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2888 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 116: /* case_item: DEFAULT ':' stmt  */
#line 649 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2897 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 117: /* case_item: DEFAULT stmt  */
#line 654 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2906 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 118: /* param_override: '#' '(' param_list ')'  */
#line 662 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
    { (yyval.node) = makeNode(NodeType::PARAM_OVERRIDE, "", yylineno); for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
#line 2912 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 119: /* param_list: param_list ',' param_assign  */
#line 666 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2918 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 120: /* param_list: param_assign  */
#line 667 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 2924 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 121: /* param_assign: '.' IDENTIFIER '(' expr ')'  */
#line 671 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                { (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2930 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 122: /* port_conn_list: port_conn_list ',' port_conn  */
#line 675 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                 { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2936 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 123: /* port_conn_list: port_conn  */
#line 676 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                 { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2942 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 124: /* port_conn: '.' IDENTIFIER '(' expr ')'  */
#line 681 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2952 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 125: /* port_conn: '.' IDENTIFIER '(' ')'  */
#line 687 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-2].str), yylineno);
          free((yyvsp[-2].str));
      }
#line 2961 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 126: /* range: '[' expr ':' expr ']'  */
#line 695 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
          /* Evaluate constant range bounds */
          if ((yyvsp[-3].node)->type == NodeType::NUMBER) (yyval.node)->msb = std::stoi((yyvsp[-3].node)->value);
          if ((yyvsp[-1].node)->type == NodeType::NUMBER) (yyval.node)->lsb = std::stoi((yyvsp[-1].node)->value);
      }
#line 2974 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 127: /* expr: expr '+' expr  */
#line 706 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "+", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2980 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 128: /* expr: expr '-' expr  */
#line 707 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "-", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2986 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 129: /* expr: expr '*' expr  */
#line 708 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "*", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2992 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 130: /* expr: expr '/' expr  */
#line 709 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "/", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2998 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 131: /* expr: expr '%' expr  */
#line 710 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "%", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3004 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 132: /* expr: expr '&' expr  */
#line 711 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3010 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 133: /* expr: expr '|' expr  */
#line 712 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3016 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 134: /* expr: expr '^' expr  */
#line 713 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3022 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 135: /* expr: expr XNOR expr  */
#line 714 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3028 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 136: /* expr: expr NAND expr  */
#line 715 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3034 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 137: /* expr: expr NOR expr  */
#line 716 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3040 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 138: /* expr: expr EQ expr  */
#line 717 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "==", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3046 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 139: /* expr: expr NE expr  */
#line 718 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "!=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3052 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 140: /* expr: expr '<' expr  */
#line 719 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3058 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 141: /* expr: expr '>' expr  */
#line 720 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3064 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 142: /* expr: expr LE expr  */
#line 721 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3070 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 143: /* expr: expr GE expr  */
#line 722 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3076 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 144: /* expr: expr SHL expr  */
#line 723 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3082 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 145: /* expr: expr SHR expr  */
#line 724 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3088 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 146: /* expr: expr SSHR expr  */
#line 725 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3094 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 147: /* expr: expr '*' '*' expr  */
#line 726 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = makeNode(NodeType::BINOP, "**", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3100 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 148: /* expr: expr LOGAND expr  */
#line 727 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3106 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 149: /* expr: expr LOGOR expr  */
#line 728 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "||", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 3112 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 150: /* expr: expr '?' expr ':' expr  */
#line 730 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::TERNARY, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));
      }
#line 3121 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 151: /* expr: '-' expr  */
#line 734 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "-", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3127 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 152: /* expr: '!' expr  */
#line 735 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "!", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3133 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 153: /* expr: '~' expr  */
#line 736 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3139 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 154: /* expr: NAND expr  */
#line 737 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~&", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3145 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 155: /* expr: NOR expr  */
#line 738 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~|", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3151 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 156: /* expr: '&' expr  */
#line 739 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "&", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3157 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 157: /* expr: '|' expr  */
#line 740 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "|", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3163 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 158: /* expr: '^' expr  */
#line 741 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "^", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3169 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 160: /* prim_expr: NUMBER  */
#line 747 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNum((yyvsp[0].num));
      }
#line 3177 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 161: /* prim_expr: IDENTIFIER  */
#line 751 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3186 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 162: /* prim_expr: IDENTIFIER '[' expr ':' expr ']'  */
#line 756 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3197 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 163: /* prim_expr: IDENTIFIER '[' expr ']'  */
#line 763 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3207 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 164: /* prim_expr: IDENTIFIER '[' expr ']' '[' expr ':' expr ']'  */
#line 769 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          /* Double range-select: signal[idx][msb:lsb] — mark with msb=-1 to distinguish */
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-8].str), yylineno);
          free((yyvsp[-8].str));
          addChild((yyval.node), (yyvsp[-6].node));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3220 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 165: /* prim_expr: IDENTIFIER '[' expr ']' '[' expr ']'  */
#line 778 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
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
#line 3235 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 166: /* prim_expr: '{' expr_list '}'  */
#line 789 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 3246 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 167: /* prim_expr: '{' expr '{' expr_list '}' '}'  */
#line 796 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
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
#line 3262 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 168: /* prim_expr: '(' expr ')'  */
#line 808 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 3270 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 169: /* prim_expr: SYS_FOPEN '(' STRING ')'  */
#line 812 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
      }
#line 3280 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 170: /* prim_expr: SYS_FOPEN '(' STRING ',' STRING ')'  */
#line 818 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-3].str), yylineno));
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-3].str)); free((yyvsp[-1].str));
      }
#line 3291 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 171: /* prim_expr: SYS_CLOG2 '(' expr ')'  */
#line 825 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$clog2", yylineno);
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3300 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 172: /* prim_expr: STRING  */
#line 830 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::STRING, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3309 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 173: /* lvalue: IDENTIFIER  */
#line 838 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3318 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 174: /* lvalue: IDENTIFIER '[' expr ':' expr ']'  */
#line 843 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3329 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 175: /* lvalue: IDENTIFIER '[' expr ']'  */
#line 850 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3339 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 176: /* lvalue: IDENTIFIER '[' expr ']' '[' expr ':' expr ']'  */
#line 856 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-8].str), yylineno);
          free((yyvsp[-8].str));
          addChild((yyval.node), (yyvsp[-6].node));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3351 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 177: /* lvalue: IDENTIFIER '[' expr ']' '[' expr ']'  */
#line 864 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-6].str), yylineno);
          free((yyvsp[-6].str));
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-1].node));
          auto *sentinel = makeNode(NodeType::NUMBER, "-1", yylineno);
          sentinel->msb = -1;
          addChild((yyval.node), sentinel);
      }
#line 3365 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 178: /* lvalue: '{' lvalue_list '}'  */
#line 874 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 3376 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 179: /* lvalue_list: lvalue_list ',' lvalue  */
#line 883 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                           { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3382 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 180: /* lvalue_list: lvalue  */
#line 884 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3388 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 181: /* expr_list: expr_list ',' expr  */
#line 888 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3394 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 182: /* expr_list: expr  */
#line 889 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3400 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"
    break;


#line 3404 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.tab.c"

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

#line 892 "/home/kali/Documents/github/AI4S/.claude/worktrees/agent-ac2eb0b62000f7378/Track-A/A1-simulator/src/parser.y"


void yyerror(const char *msg) {
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
