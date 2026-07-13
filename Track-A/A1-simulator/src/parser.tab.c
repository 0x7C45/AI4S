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

#line 103 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"

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
  YYSYMBOL_GENERATE = 27,                  /* GENERATE  */
  YYSYMBOL_ENDGENERATE = 28,               /* ENDGENERATE  */
  YYSYMBOL_GENVAR = 29,                    /* GENVAR  */
  YYSYMBOL_POSEDGE = 30,                   /* POSEDGE  */
  YYSYMBOL_NEGEDGE = 31,                   /* NEGEDGE  */
  YYSYMBOL_SYS_FOPEN = 32,                 /* SYS_FOPEN  */
  YYSYMBOL_SYS_FCLOSE = 33,                /* SYS_FCLOSE  */
  YYSYMBOL_SYS_FSCANF = 34,                /* SYS_FSCANF  */
  YYSYMBOL_SYS_FGETS = 35,                 /* SYS_FGETS  */
  YYSYMBOL_SYS_FDISPLAY = 36,              /* SYS_FDISPLAY  */
  YYSYMBOL_SYS_DISPLAY = 37,               /* SYS_DISPLAY  */
  YYSYMBOL_SYS_FINISH = 38,                /* SYS_FINISH  */
  YYSYMBOL_SYS_CLOG2 = 39,                 /* SYS_CLOG2  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_NE = 41,                        /* NE  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_LOGAND = 44,                    /* LOGAND  */
  YYSYMBOL_LOGOR = 45,                     /* LOGOR  */
  YYSYMBOL_SHL = 46,                       /* SHL  */
  YYSYMBOL_SHR = 47,                       /* SHR  */
  YYSYMBOL_SSHR = 48,                      /* SSHR  */
  YYSYMBOL_NAND = 49,                      /* NAND  */
  YYSYMBOL_NOR = 50,                       /* NOR  */
  YYSYMBOL_XNOR = 51,                      /* XNOR  */
  YYSYMBOL_52_ = 52,                       /* '?'  */
  YYSYMBOL_53_ = 53,                       /* ':'  */
  YYSYMBOL_54_ = 54,                       /* '|'  */
  YYSYMBOL_55_ = 55,                       /* '^'  */
  YYSYMBOL_56_ = 56,                       /* '&'  */
  YYSYMBOL_57_ = 57,                       /* '<'  */
  YYSYMBOL_58_ = 58,                       /* '>'  */
  YYSYMBOL_59_ = 59,                       /* '+'  */
  YYSYMBOL_60_ = 60,                       /* '-'  */
  YYSYMBOL_61_ = 61,                       /* '*'  */
  YYSYMBOL_62_ = 62,                       /* '/'  */
  YYSYMBOL_63_ = 63,                       /* '%'  */
  YYSYMBOL_POWER = 64,                     /* POWER  */
  YYSYMBOL_65_ = 65,                       /* '!'  */
  YYSYMBOL_66_ = 66,                       /* '~'  */
  YYSYMBOL_UNARY = 67,                     /* UNARY  */
  YYSYMBOL_68_ = 68,                       /* ';'  */
  YYSYMBOL_69_ = 69,                       /* '#'  */
  YYSYMBOL_70_ = 70,                       /* '('  */
  YYSYMBOL_71_ = 71,                       /* ')'  */
  YYSYMBOL_72_ = 72,                       /* ','  */
  YYSYMBOL_73_ = 73,                       /* '='  */
  YYSYMBOL_74_ = 74,                       /* '@'  */
  YYSYMBOL_75_ = 75,                       /* '.'  */
  YYSYMBOL_76_ = 76,                       /* '['  */
  YYSYMBOL_77_ = 77,                       /* ']'  */
  YYSYMBOL_78_ = 78,                       /* '{'  */
  YYSYMBOL_79_ = 79,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_source = 81,                    /* source  */
  YYSYMBOL_module_list = 82,               /* module_list  */
  YYSYMBOL_module = 83,                    /* module  */
  YYSYMBOL_module_param_decls = 84,        /* module_param_decls  */
  YYSYMBOL_module_param_decl = 85,         /* module_param_decl  */
  YYSYMBOL_opt_port_list = 86,             /* opt_port_list  */
  YYSYMBOL_port_list = 87,                 /* port_list  */
  YYSYMBOL_port_decl_in_list = 88,         /* port_decl_in_list  */
  YYSYMBOL_module_items = 89,              /* module_items  */
  YYSYMBOL_module_item = 90,               /* module_item  */
  YYSYMBOL_port_decl = 91,                 /* port_decl  */
  YYSYMBOL_decl_list = 92,                 /* decl_list  */
  YYSYMBOL_stmt = 93,                      /* stmt  */
  YYSYMBOL_stmts = 94,                     /* stmts  */
  YYSYMBOL_gen_items = 95,                 /* gen_items  */
  YYSYMBOL_gen_item = 96,                  /* gen_item  */
  YYSYMBOL_genvar_list = 97,               /* genvar_list  */
  YYSYMBOL_gen_block = 98,                 /* gen_block  */
  YYSYMBOL_gen_body = 99,                  /* gen_body  */
  YYSYMBOL_case_items = 100,               /* case_items  */
  YYSYMBOL_case_item = 101,                /* case_item  */
  YYSYMBOL_param_override = 102,           /* param_override  */
  YYSYMBOL_param_list = 103,               /* param_list  */
  YYSYMBOL_param_assign = 104,             /* param_assign  */
  YYSYMBOL_port_conn_list = 105,           /* port_conn_list  */
  YYSYMBOL_port_conn = 106,                /* port_conn  */
  YYSYMBOL_range = 107,                    /* range  */
  YYSYMBOL_expr = 108,                     /* expr  */
  YYSYMBOL_prim_expr = 109,                /* prim_expr  */
  YYSYMBOL_lvalue = 110,                   /* lvalue  */
  YYSYMBOL_lvalue_list = 111,              /* lvalue_list  */
  YYSYMBOL_expr_list = 112                 /* expr_list  */
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
#define YYLAST   2182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  475

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


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
       2,     2,     2,    65,     2,    69,     2,    63,    56,     2,
      70,    71,    61,    59,    72,    60,    75,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    68,
      57,    73,    58,    52,    74,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    78,    54,    79,    66,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    64,    67
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,    88,    89,    93,   100,   112,   113,   117,
     122,   123,   127,   128,   132,   133,   134,   138,   139,   140,
     144,   145,   158,   160,   171,   173,   175,   177,   179,   181,
     183,   185,   189,   191,   193,   195,   197,   199,   201,   203,
     206,   208,   210,   212,   213,   217,   228,   236,   246,   254,
     264,   272,   282,   290,   300,   308,   318,   328,   339,   340,
     344,   345,   351,   358,   364,   374,   380,   386,   393,   399,
     400,   401,   406,   412,   418,   424,   429,   438,   448,   458,
     465,   474,   475,   479,   480,   484,   492,   501,   507,   514,
     522,   523,   527,   528,   529,   533,   534,   535,   536,   540,
     541,   545,   551,   558,   563,   571,   576,   577,   581,   585,
     586,   590,   596,   604,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,   633,   634,   635,   636,   637,   638,   639,   644,   645,
     646,   647,   648,   649,   650,   654,   658,   663,   670,   676,
     685,   696,   703,   715,   719,   725,   732,   737,   745,   750,
     757,   763,   771,   781,   791,   792,   796,   797
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
  "DEFAULT", "FOR", "GENERATE", "ENDGENERATE", "GENVAR", "POSEDGE",
  "NEGEDGE", "SYS_FOPEN", "SYS_FCLOSE", "SYS_FSCANF", "SYS_FGETS",
  "SYS_FDISPLAY", "SYS_DISPLAY", "SYS_FINISH", "SYS_CLOG2", "EQ", "NE",
  "LE", "GE", "LOGAND", "LOGOR", "SHL", "SHR", "SSHR", "NAND", "NOR",
  "XNOR", "'?'", "':'", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "POWER", "'!'", "'~'", "UNARY", "';'", "'#'", "'('",
  "')'", "','", "'='", "'@'", "'.'", "'['", "']'", "'{'", "'}'", "$accept",
  "source", "module_list", "module", "module_param_decls",
  "module_param_decl", "opt_port_list", "port_list", "port_decl_in_list",
  "module_items", "module_item", "port_decl", "decl_list", "stmt", "stmts",
  "gen_items", "gen_item", "genvar_list", "gen_block", "gen_body",
  "case_items", "case_item", "param_override", "param_list",
  "param_assign", "port_conn_list", "port_conn", "range", "expr",
  "prim_expr", "lvalue", "lvalue_list", "expr_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-406)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,    62,    34,    -1,  -406,     5,  -406,  -406,   -44,    93,
      27,   124,  -406,   130,    12,   -27,  -406,  -406,   799,   139,
      81,  -406,  -406,     8,   102,   512,   155,  -406,     9,    15,
     102,   181,  -406,    93,    10,    24,    30,   192,   194,   198,
       0,   -20,   560,    37,   147,   245,  -406,   151,   153,   152,
     157,   124,  -406,   229,   236,   188,  -406,  -406,   179,   203,
     512,   512,   512,   512,   512,   512,   512,   512,  1929,  -406,
    -406,  -406,   265,  -406,   102,   276,   280,  -406,  -406,   214,
     215,  -406,   284,   216,   102,   285,  -406,   217,   220,   219,
       0,   224,   512,   228,   560,   230,   231,   235,   237,   238,
     239,   240,   126,   294,   241,  -406,   -12,   248,   250,   303,
      31,  -406,   246,  -406,  -406,  -406,  -406,   512,   247,  -406,
    -406,  -406,   512,   319,   512,  -406,  -406,  -406,  -406,  -406,
    -406,  1139,   795,   -26,   512,   512,   512,   512,   512,   512,
     512,   512,   512,   512,   512,   512,   512,   512,   512,   512,
     512,   512,   512,   512,   512,    16,   512,   512,  -406,   321,
    -406,  -406,    32,   246,    36,     7,   512,    77,   322,   254,
      82,   512,   512,   512,  -406,   -10,   512,   407,   -14,  -406,
     313,   512,   512,     0,   325,   512,   570,   600,  -406,   512,
     263,   159,   512,   168,   512,    21,  -406,    87,  -406,  -406,
     332,   133,  -406,  2001,   799,   834,   138,  1171,  -406,   512,
     512,  -406,  2119,  2119,   346,   346,  2049,  2025,    75,    75,
      75,   314,   314,  2097,  1953,   972,  2073,  2097,   314,   346,
     346,   120,   120,   512,  -406,  -406,  -406,  -406,   269,   337,
     140,  -406,   142,  -406,   338,   512,    98,   274,  1523,  -406,
    -406,   512,   107,  -406,  1552,  1581,   872,     0,  -406,  1610,
    -406,   340,   344,   277,  -406,  -406,  1203,  1235,   279,   282,
    1267,   287,  2001,   144,   292,   169,  1299,  -406,   362,   363,
    1639,   297,   298,   300,  1668,  1331,   306,   377,  -406,   382,
     316,  -406,   246,   759,   512,   312,  -406,   385,  -406,    26,
    2001,   512,  -406,  -406,  -406,   320,   328,   324,   394,  -406,
    1697,  -406,  -406,  -406,   108,  1726,  -406,  -406,  -406,   512,
     336,  -406,  -406,   329,   330,   560,   560,   468,   512,   347,
     348,   349,   350,   352,   353,   355,   333,   354,  -406,   420,
     512,   512,  -406,   779,   512,   356,  -406,   512,  -406,  -406,
     996,   512,   360,   357,  2049,   487,  -406,  -406,   364,  -406,
    -406,  -406,  1020,   512,   560,   560,  -406,   405,   476,   226,
    -406,  1106,  1755,  -406,  -406,  -406,  -406,  -406,  -406,  -406,
     373,   378,   171,   173,   195,   665,  -406,   410,  1784,   512,
    1363,  -406,   910,  -406,  -406,  -406,  1395,    90,  -406,   948,
    -406,  -406,   560,   560,  -406,  -406,  -406,   560,   512,   512,
    -406,  -406,   392,   406,   409,   472,  -406,  -406,   687,   779,
     512,  1813,  -406,   512,  -406,  -406,   412,   199,   512,  -406,
    -406,  -406,  -406,  1977,  1842,  -406,  -406,  -406,   734,  -406,
    -406,  -406,  -406,  1871,   512,  1044,  -406,   414,  1068,   560,
       0,   712,     0,  1900,  -406,  -406,  -406,  -406,   411,  -406,
     413,   475,   512,   512,   415,  1427,  1459,   512,   560,   779,
    1491,  -406,  -406,   779,  -406
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,    11,     1,     3,     0,    16,
       0,     0,    14,     0,     0,     0,    13,    15,    19,     0,
       0,     8,    46,     0,     0,     0,     0,    48,     0,     0,
       0,     0,    10,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,     0,     0,
      11,     0,    52,     0,     0,   146,   157,   145,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
      45,    50,     0,    54,     0,     0,     0,    47,    12,     0,
       0,    59,     0,    59,     0,     0,    59,     0,     0,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    38,     0,     0,     0,     0,
       0,    84,     0,     5,    17,    20,    44,     0,     0,     7,
      51,    56,     0,     0,     0,   142,   143,   141,   138,   139,
     140,     0,   167,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,     0,
      53,    55,     0,     0,     0,    59,     0,     0,     0,    59,
       0,     0,     0,     0,   165,     0,     0,     0,     0,    82,
       0,     0,     0,     0,     0,     0,     0,     0,    69,     0,
       0,     0,     0,     0,     0,     0,    91,     0,    43,    83,
       0,     0,   107,     9,    19,     0,     0,     0,   153,     0,
       0,   151,   125,   126,   129,   130,   135,   136,   131,   132,
     133,   123,   124,   122,     0,     0,   120,   121,   119,   127,
     128,   114,   115,     0,   116,   117,   118,    57,     0,     0,
       0,   110,     0,    24,     0,     0,     0,     0,     0,    28,
      59,     0,     0,    30,     0,     0,     0,     0,   163,     0,
      37,     0,     0,     0,    60,    81,     0,     0,     0,     0,
       0,   157,   167,     0,   157,     0,     0,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,     0,
       0,   105,     0,     0,     0,   148,   154,     0,   156,     0,
     166,     0,   113,   134,    42,     0,     0,     0,     0,    58,
       0,    22,    21,    27,     0,     0,    25,    31,    32,     0,
     160,   164,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
       0,     0,    65,     0,     0,     0,    90,     0,   106,     6,
       0,     0,     0,     0,   137,     0,    40,   109,     0,    23,
      29,    26,     0,     0,     0,     0,    34,    61,     0,     0,
     100,     0,     0,    74,    75,    80,    79,    68,    67,    70,
       0,     0,     0,     0,     0,     0,    94,    87,     0,     0,
       0,   147,     0,   155,   152,   112,     0,     0,   159,     0,
      35,    36,     0,     0,   104,    63,    99,     0,     0,     0,
      72,    73,   154,     0,     0,     0,    97,    98,     0,     0,
       0,     0,   108,     0,   150,   111,     0,     0,     0,   162,
      62,   103,   101,     0,     0,    76,    77,    78,     0,    92,
      95,    96,    88,     0,     0,     0,    41,     0,     0,     0,
       0,     0,     0,     0,   149,    39,   161,   102,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    86,     0,    85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -406,  -406,  -406,   480,  -406,   436,   439,  -406,   461,   299,
     -16,    23,   -76,   -90,  -406,  -406,   -37,  -406,  -405,    58,
    -406,   129,  -406,   341,   209,   109,   204,   163,   -25,  -406,
     -39,  -406,  -178
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     4,    20,    21,    10,    15,    16,    45,
     386,    47,   164,   105,   180,   110,   417,   197,   387,   418,
     369,   370,    48,   201,   202,   240,   241,    26,   272,    69,
     106,   175,   133
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    91,    46,    89,   179,     1,   111,   167,   273,   275,
     170,    52,    71,    79,   442,    27,   261,   262,    73,    55,
      56,    57,    28,    29,   286,    30,    11,    81,    74,   114,
     192,   299,    17,    83,     6,   125,   126,   127,   128,   129,
     130,   131,   132,    84,    32,    33,   210,   263,    58,    92,
     287,   174,   107,   211,    93,    59,    17,   108,   107,   198,
     109,   193,   257,   108,   472,     5,   109,   177,   474,   258,
      60,    61,    62,   199,     8,     9,    63,   233,    90,    80,
     245,    64,    65,    25,    25,    25,    66,   260,    25,   246,
     265,    25,   203,   252,    67,    18,    12,   205,   210,   207,
      25,    13,    14,   238,   243,   353,    25,   239,   244,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     234,   235,   236,    22,   153,   154,   155,   156,   157,    19,
      23,   248,    49,    24,   268,   249,   254,   255,   256,   244,
     253,   259,    50,    51,   244,   288,   266,   267,    70,   289,
     270,   426,   383,   384,   276,   239,   311,   280,   284,   285,
     244,    55,    56,    57,   314,   316,   360,    31,    25,   244,
     244,   155,   156,   157,    77,   300,    53,    54,    46,   278,
     279,    72,    75,    76,   188,    86,   189,    87,    82,    85,
     281,    88,   282,   283,   291,   292,    25,    59,   303,   296,
     297,   306,   307,   308,   292,   332,   210,   112,   321,   115,
     310,   116,    60,    61,    62,   117,   315,     9,    63,    55,
      56,    57,   120,    64,    65,   366,   367,   159,    66,   121,
     334,   210,   412,   297,   413,   210,    67,   168,    34,   123,
     405,   368,   113,    13,    14,    35,    36,    37,    58,    38,
      39,    40,    41,    42,   122,    59,   414,   210,   158,   350,
     447,   307,    43,   124,   400,   401,   354,   114,   404,   160,
      60,    61,    62,   161,   162,   163,    63,   165,   169,   166,
     171,    64,    65,   172,   362,   173,    66,   176,   178,   190,
     181,   182,   371,   372,    67,   183,   196,   184,   185,   186,
     187,   191,   430,   431,    44,   204,    89,   432,   194,   388,
     195,   200,   390,   206,   237,   250,   392,   251,   247,   269,
     396,   277,    94,   264,    95,   290,    96,   304,   399,    97,
     305,   309,   312,   323,   371,    98,    99,   324,   325,   100,
     101,   102,   328,   329,   134,   135,   136,   137,   331,   457,
     140,   141,   142,   333,   421,   336,   337,   339,   340,   416,
     341,   151,   152,   153,   154,   155,   156,   157,   471,   344,
     345,   441,   103,   433,   434,   346,   347,   104,   351,   352,
     355,    90,   140,   141,   142,   443,   356,   358,   445,   239,
     364,   365,   440,   448,   380,   153,   154,   155,   156,   157,
      89,   458,   363,   460,   441,   373,   374,   375,   376,   453,
     377,   378,   416,   379,   382,   381,    94,   402,    95,   389,
      96,   393,   419,    97,   397,   440,   394,   465,   466,    98,
      99,   410,   470,   100,   101,   102,   411,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     435,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,    55,    56,    57,   436,   438,   103,   437,   464,    89,
     446,   104,   455,     7,   462,    90,   463,   119,   467,   118,
      55,    56,    57,   368,    78,    94,   451,    95,   406,    96,
      58,   348,    97,   293,   242,     0,   427,    59,    98,    99,
       0,   357,   100,   101,   102,    55,    56,    57,     0,    58,
       0,     0,    60,    61,    62,     0,    59,     0,    63,   403,
       0,     0,     0,    64,    65,     0,     0,     0,    66,     0,
       0,    60,    61,    62,    58,   103,    67,    63,     0,     0,
     104,    59,    64,    65,    90,     0,     0,    66,   395,     0,
       0,     0,     0,    89,     0,    67,    60,    61,    62,     0,
       0,     0,    63,    55,   271,    57,     0,    64,    65,    94,
       0,    95,    66,    96,     0,     0,    97,     0,     0,     0,
      67,     0,    98,    99,     0,     0,   100,   101,   102,     0,
       0,     0,    58,    55,   274,    57,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,    61,    62,     0,     0,   103,
      63,     0,    58,     0,   104,    64,    65,     0,    90,    59,
      66,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,    60,    61,    62,     0,     0,     0,
      63,     0,     0,     0,     0,    64,    65,     0,    34,     0,
      66,     0,     0,    13,    14,    35,    36,    37,    67,    38,
      39,    40,    41,    42,     0,     0,   107,     0,     0,     0,
      34,   108,    43,     0,   109,    13,    14,    35,    36,    37,
       0,    38,    39,    40,    41,    42,     0,   439,   107,     0,
       0,     0,     0,   108,    43,    34,   109,     0,   415,     0,
      13,    14,    35,    36,    37,     0,    38,    39,    40,    41,
      42,     0,   459,   107,    44,     0,     0,    34,   108,    43,
       0,   109,    13,    14,    35,    36,    37,     0,    38,    39,
      40,    41,    42,     0,     0,   107,    44,     0,     0,     0,
     108,    43,    34,   109,     0,     0,   349,    13,    14,    35,
      36,    37,     0,    38,    39,    40,    41,    42,     0,     0,
       0,    44,    34,     0,     0,     0,    43,    13,    14,    35,
      36,    37,     0,    38,    39,    40,    41,    42,   385,     0,
       0,     0,    34,    44,     0,     0,    43,    13,    14,    35,
      36,    37,     0,    38,    39,    40,    41,    42,     0,     0,
       0,     0,     0,     0,     0,     0,    43,     0,    44,     0,
       0,     0,     0,     0,     0,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,    44,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    44,     0,
       0,     0,     0,   209,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   294,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   295,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   319,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   320,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   423,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   424,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   428,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   429,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   302,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   391,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   398,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   454,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   456,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   407,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
       0,     0,     0,     0,     0,     0,     0,     0,   408,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,     0,     0,     0,     0,     0,     0,     0,
     208,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,     0,     0,     0,     0,     0,
       0,     0,   298,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     0,     0,     0,
       0,     0,     0,     0,   326,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
       0,     0,     0,     0,     0,     0,   327,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
       0,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,     0,     0,     0,     0,     0,     0,     0,   330,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,     0,     0,     0,     0,     0,     0,     0,
     335,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,     0,     0,     0,     0,     0,
       0,     0,   343,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     0,     0,     0,
       0,     0,     0,     0,   422,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
       0,     0,     0,     0,     0,     0,   425,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
       0,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,     0,     0,     0,     0,     0,     0,     0,   468,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,     0,     0,     0,     0,     0,     0,     0,
     469,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,     0,     0,     0,     0,     0,
       0,     0,   473,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     0,     0,     0,
       0,   313,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,     0,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,     0,     0,     0,
     317,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,     0,     0,     0,     0,   318,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,     0,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,     0,     0,     0,   322,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,     0,     0,     0,     0,   338,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,     0,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     0,     0,     0,     0,   342,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
       0,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,     0,     0,     0,     0,   359,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
       0,     0,     0,     0,   361,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
       0,     0,     0,   409,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,     0,     0,
       0,     0,   420,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     0,     0,     0,
       0,   444,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,     0,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     0,     0,     0,     0,
     450,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,     0,     0,     0,     0,   452,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,     0,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,     0,     0,     0,   461,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   301,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     449,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   134,   135,   136,   137,   138,
       0,   140,   141,   142,   143,   144,   145,   146,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   134,
     135,   136,   137,     0,     0,   140,   141,   142,   143,   144,
     145,   146,     0,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   134,   135,   136,   137,     0,     0,   140,
     141,   142,   143,   144,   145,     0,     0,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   134,   135,   136,
     137,     0,     0,   140,   141,   142,   143,   144,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,   155,   156,
     157,   136,   137,     0,     0,   140,   141,   142,     0,     0,
       0,     0,     0,     0,     0,     0,   151,   152,   153,   154,
     155,   156,   157
};

static const yytype_int16 yycheck[] =
{
      25,    40,    18,     3,    94,     6,    43,    83,   186,   187,
      86,     3,     3,     3,   419,     3,    30,    31,     3,     3,
       4,     5,    10,    11,     3,    13,    70,     3,    13,    45,
      42,   209,     9,     3,     0,    60,    61,    62,    63,    64,
      65,    66,    67,    13,    71,    72,    72,    61,    32,    69,
      29,    90,    21,    79,    74,    39,    33,    26,    21,    28,
      29,    73,    72,    26,   469,     3,    29,    92,   473,    79,
      54,    55,    56,   110,    69,    70,    60,    61,    78,    69,
      73,    65,    66,    76,    76,    76,    70,   177,    76,   165,
     180,    76,   117,   169,    78,    68,     3,   122,    72,   124,
      76,     8,     9,    71,    68,    79,    76,    75,    72,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,     3,    59,    60,    61,    62,    63,    15,
      10,   166,     3,    13,   183,    68,   171,   172,   173,    72,
      68,   176,    71,    72,    72,    68,   181,   182,     3,    72,
     185,    71,   340,   341,   189,    75,    68,   192,   193,   194,
      72,     3,     4,     5,   250,    68,    68,    14,    76,    72,
      72,    61,    62,    63,     3,   210,    23,    24,   204,    30,
      31,    28,    29,    30,    68,     3,    70,     3,    35,    36,
      32,     3,    34,    35,    71,    72,    76,    39,   233,    71,
      72,    71,    72,    71,    72,    71,    72,    70,   257,    68,
     245,    68,    54,    55,    56,    73,   251,    70,    60,     3,
       4,     5,     3,    65,    66,   325,   326,    74,    70,     3,
      71,    72,    71,    72,    71,    72,    78,    84,     3,    70,
      24,    25,     7,     8,     9,    10,    11,    12,    32,    14,
      15,    16,    17,    18,    76,    39,    71,    72,     3,   294,
      71,    72,    27,    70,   364,   365,   301,   293,   368,     3,
      54,    55,    56,     3,    70,    70,    60,     3,     3,    73,
      73,    65,    66,    73,   319,    76,    70,    73,    70,     5,
      70,    70,   327,   328,    78,    70,     3,    70,    70,    70,
      70,    70,   402,   403,    69,    68,     3,   407,    70,   344,
      70,    75,   347,     4,     3,     3,   351,    73,   165,     4,
     355,    68,    19,    20,    21,     3,    23,    68,   363,    26,
       3,     3,    68,     3,   369,    32,    33,     3,    71,    36,
      37,    38,    73,    71,    40,    41,    42,    43,    71,   449,
      46,    47,    48,    71,   389,     3,     3,    70,    70,   385,
      70,    57,    58,    59,    60,    61,    62,    63,   468,    73,
       3,   418,    69,   408,   409,     3,    70,    74,    76,     4,
      70,    78,    46,    47,    48,   420,    68,     3,   423,    75,
      71,    71,   418,   428,    71,    59,    60,    61,    62,    63,
       3,   450,    76,   452,   451,    68,    68,    68,    68,   444,
      68,    68,   438,    68,     4,    71,    19,    22,    21,    73,
      23,    71,    22,    26,    70,   451,    79,   462,   463,    32,
      33,    68,   467,    36,    37,    38,    68,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      68,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     3,     4,     5,    68,     3,    69,    68,     3,     3,
      68,    74,    68,     3,    73,    78,    73,    51,    73,    50,
       3,     4,     5,    25,    33,    19,   438,    21,   369,    23,
      32,   292,    26,   204,   163,    -1,   397,    39,    32,    33,
      -1,   307,    36,    37,    38,     3,     4,     5,    -1,    32,
      -1,    -1,    54,    55,    56,    -1,    39,    -1,    60,    53,
      -1,    -1,    -1,    65,    66,    -1,    -1,    -1,    70,    -1,
      -1,    54,    55,    56,    32,    69,    78,    60,    -1,    -1,
      74,    39,    65,    66,    78,    -1,    -1,    70,    71,    -1,
      -1,    -1,    -1,     3,    -1,    78,    54,    55,    56,    -1,
      -1,    -1,    60,     3,     4,     5,    -1,    65,    66,    19,
      -1,    21,    70,    23,    -1,    -1,    26,    -1,    -1,    -1,
      78,    -1,    32,    33,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    32,     3,     4,     5,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    69,
      60,    -1,    32,    -1,    74,    65,    66,    -1,    78,    39,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,     3,    -1,
      70,    -1,    -1,     8,     9,    10,    11,    12,    78,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,
       3,    26,    27,    -1,    29,     8,     9,    10,    11,    12,
      -1,    14,    15,    16,    17,    18,    -1,    20,    21,    -1,
      -1,    -1,    -1,    26,    27,     3,    29,    -1,    53,    -1,
       8,     9,    10,    11,    12,    -1,    14,    15,    16,    17,
      18,    -1,    20,    21,    69,    -1,    -1,     3,    26,    27,
      -1,    29,     8,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    21,    69,    -1,    -1,    -1,
      26,    27,     3,    29,    -1,    -1,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    69,     3,    -1,    -1,    -1,    27,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,     3,    69,    -1,    -1,    27,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    69,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      -1,    -1,    -1,    78,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    77,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    77,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    77,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    77,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    77,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    68,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      68,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    68,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    -1,    68,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    -1,    68,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    68,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      68,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    40,    41,    42,    43,    44,
      -1,    46,    47,    48,    49,    50,    51,    52,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    40,
      41,    42,    43,    -1,    -1,    46,    47,    48,    49,    50,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    49,    50,    51,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    40,    41,    42,
      43,    -1,    -1,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    42,    43,    -1,    -1,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    62,    63
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    81,    82,    83,     3,     0,    83,    69,    70,
      86,    70,     3,     8,     9,    87,    88,    91,    68,    15,
      84,    85,     3,    10,    13,    76,   107,     3,    10,    11,
      13,   107,    71,    72,     3,    10,    11,    12,    14,    15,
      16,    17,    18,    27,    69,    89,    90,    91,   102,     3,
      71,    72,     3,   107,   107,     3,     4,     5,    32,    39,
      54,    55,    56,    60,    65,    66,    70,    78,   108,   109,
       3,     3,   107,     3,    13,   107,   107,     3,    88,     3,
      69,     3,   107,     3,    13,   107,     3,     3,     3,     3,
      78,   110,    69,    74,    19,    21,    23,    26,    32,    33,
      36,    37,    38,    69,    74,    93,   110,    21,    26,    29,
      95,    96,    70,     7,    90,    68,    68,    73,    86,    85,
       3,     3,    76,    70,    70,   108,   108,   108,   108,   108,
     108,   108,   108,   112,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     3,   107,
       3,     3,    70,    70,    92,     3,    73,    92,   107,     3,
      92,    73,    73,    76,   110,   111,    73,   108,    70,    93,
      94,    70,    70,    70,    70,    70,    70,    70,    68,    70,
       5,    70,    42,    73,    70,    70,     3,    97,    28,    96,
      75,   103,   104,   108,    68,   108,     4,   108,    71,    78,
      72,    79,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,    61,   108,   108,   108,     3,    71,    75,
     105,   106,   103,    68,    72,    73,    92,   107,   108,    68,
       3,    73,    92,    68,   108,   108,   108,    72,    79,   108,
      93,    30,    31,    61,    20,    93,   108,   108,   110,     4,
     108,     4,   108,   112,     4,   112,   108,    68,    30,    31,
     108,    32,    34,    35,   108,   108,     3,    29,    68,    72,
       3,    71,    72,    89,    53,    77,    71,    72,    71,   112,
     108,    53,    77,   108,    68,     3,    71,    72,    71,     3,
     108,    68,    68,    68,    92,   108,    68,    68,    68,    53,
      77,   110,    68,     3,     3,    71,    71,    71,    73,    71,
      71,    71,    71,    71,    71,    71,     3,     3,    68,    70,
      70,    70,    68,    71,    73,     3,     3,    70,   104,     7,
     108,    76,     4,    79,   108,    70,    68,   106,     3,    68,
      68,    68,   108,    76,    71,    71,    93,    93,    25,   100,
     101,   108,   108,    68,    68,    68,    68,    68,    68,    68,
      71,    71,     4,   112,   112,    19,    90,    98,   108,    73,
     108,    77,   108,    71,    79,    71,   108,    70,    77,   108,
      93,    93,    22,    53,    93,    24,   101,    53,    72,    68,
      68,    68,    71,    71,    71,    53,    90,    96,    99,    22,
      68,   108,    71,    53,    77,    71,    71,   105,    53,    77,
      93,    93,    93,   108,   108,    68,    68,    68,     3,    20,
      90,    96,    98,   108,    68,   108,    68,    71,   108,    53,
      68,    99,    68,   108,    77,    68,    77,    93,   110,    20,
     110,    68,    73,    73,     3,   108,   108,    73,    71,    71,
     108,    93,    98,    71,    98
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    80,    81,    82,    82,    83,    83,    84,    84,    85,
      86,    86,    87,    87,    88,    88,    88,    89,    89,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    94,    94,    95,    95,    96,    96,    96,    96,    96,
      97,    97,    98,    98,    98,    99,    99,    99,    99,   100,
     100,   101,   101,   101,   101,   102,   103,   103,   104,   105,
     105,   106,   106,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   110,   110,
     110,   110,   110,   110,   111,   111,   112,   112
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     6,    10,     3,     1,     4,
       3,     0,     3,     1,     1,     1,     0,     2,     1,     0,
       2,     5,     5,     6,     4,     5,     6,     5,     4,     6,
       4,     5,     5,     5,     6,     7,     7,     4,     2,    10,
       6,     9,     5,     3,     2,     3,     2,     3,     2,     4,
       3,     4,     3,     4,     3,     4,     4,     5,     3,     0,
       3,     5,     7,     6,    13,     4,     4,     5,     5,     2,
       5,     3,     6,     6,     5,     5,     7,     7,     7,     5,
       5,     2,     1,     2,     1,    14,    13,     5,     7,     3,
       3,     1,     3,     5,     1,     2,     2,     1,     1,     2,
       1,     3,     5,     3,     2,     4,     3,     1,     5,     3,
       1,     5,     4,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     3,     3,     5,     2,     2,
       2,     2,     2,     2,     1,     1,     1,     6,     4,     9,
       7,     3,     6,     3,     4,     6,     4,     1,     1,     6,
       4,     9,     7,     3,     3,     1,     3,     1
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
#line 88 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1840 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 4: /* module_list: module  */
#line 89 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1846 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 5: /* module: MODULE IDENTIFIER opt_port_list ';' module_items ENDMODULE  */
#line 94 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-4].str), yylineno);
        free((yyvsp[-4].str));
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) { addChild((yyval.node), c); } (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 1857 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 6: /* module: MODULE IDENTIFIER '#' '(' module_param_decls ')' opt_port_list ';' module_items ENDMODULE  */
#line 101 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-8].str), yylineno);
        free((yyvsp[-8].str));
        /* Add parameter declarations as children */
        if ((yyvsp[-5].node)) { for (auto *c : (yyvsp[-5].node)->children) addChild((yyval.node), c); (yyvsp[-5].node)->children.clear(); freeTree((yyvsp[-5].node)); }
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 1870 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 7: /* module_param_decls: module_param_decls ',' module_param_decl  */
#line 112 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                             { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1876 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 8: /* module_param_decls: module_param_decl  */
#line 113 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1882 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 9: /* module_param_decl: PARAMETER IDENTIFIER '=' expr  */
#line 118 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-2].str), yylineno); free((yyvsp[-2].str)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1888 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 10: /* opt_port_list: '(' port_list ')'  */
#line 122 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 1894 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 11: /* opt_port_list: %empty  */
#line 123 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = nullptr; }
#line 1900 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 12: /* port_list: port_list ',' port_decl_in_list  */
#line 127 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1906 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 13: /* port_list: port_decl_in_list  */
#line 128 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 1912 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 14: /* port_decl_in_list: IDENTIFIER  */
#line 132 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { free((yyvsp[0].str)); (yyval.node) = nullptr; }
#line 1918 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 15: /* port_decl_in_list: port_decl  */
#line 133 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1924 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 16: /* port_decl_in_list: %empty  */
#line 134 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = nullptr; }
#line 1930 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 17: /* module_items: module_items module_item  */
#line 138 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1936 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 18: /* module_items: module_item  */
#line 139 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1942 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 19: /* module_items: %empty  */
#line 140 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 1948 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 21: /* module_item: WIRE range IDENTIFIER range ';'  */
#line 146 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
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
#line 1965 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 22: /* module_item: WIRE range IDENTIFIER decl_list ';'  */
#line 159 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 1971 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 23: /* module_item: WIRE range IDENTIFIER '=' expr ';'  */
#line 161 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
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
#line 1986 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 24: /* module_item: WIRE IDENTIFIER decl_list ';'  */
#line 172 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 1992 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 25: /* module_item: REG range IDENTIFIER decl_list ';'  */
#line 174 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
#line 1998 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 26: /* module_item: REG range IDENTIFIER '=' expr ';'  */
#line 176 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); (yyval.node)->msb = (yyvsp[-4].node)->msb; (yyval.node)->lsb = (yyvsp[-4].node)->lsb; for (auto *c : (yyvsp[-4].node)->children) addChild((yyval.node), c); (yyvsp[-4].node)->children.clear(); freeTree((yyvsp[-4].node)); }
#line 2004 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 27: /* module_item: REG IDENTIFIER '=' expr ';'  */
#line 178 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2010 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 28: /* module_item: REG IDENTIFIER decl_list ';'  */
#line 180 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2016 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 29: /* module_item: REG SIGNED range IDENTIFIER decl_list ';'  */
#line 182 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg signed", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
#line 2022 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 30: /* module_item: INTEGER_KW IDENTIFIER decl_list ';'  */
#line 184 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "integer", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 31; (yyval.node)->lsb = 0; }
#line 2028 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 31: /* module_item: LOCALPARAM IDENTIFIER '=' expr ';'  */
#line 186 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2036 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 32: /* module_item: PARAMETER IDENTIFIER '=' expr ';'  */
#line 190 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2042 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 33: /* module_item: ASSIGN lvalue '=' expr ';'  */
#line 192 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ASSIGN, "", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2048 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 34: /* module_item: ALWAYS '@' '(' '*' ')' stmt  */
#line 194 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(*)", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2054 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 35: /* module_item: ALWAYS '@' '(' POSEDGE IDENTIFIER ')' stmt  */
#line 196 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(posedge " + std::string((yyvsp[-2].str)) + ")", yylineno); addChild((yyval.node), (yyvsp[0].node)); free((yyvsp[-2].str)); }
#line 2060 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 36: /* module_item: ALWAYS '@' '(' NEGEDGE IDENTIFIER ')' stmt  */
#line 198 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(negedge " + std::string((yyvsp[-2].str)) + ")", yylineno); addChild((yyval.node), (yyvsp[0].node)); free((yyvsp[-2].str)); }
#line 2066 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 37: /* module_item: ALWAYS '#' expr stmt  */
#line 200 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "#delay", yylineno); addChild((yyval.node), (yyvsp[-1].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2072 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 38: /* module_item: INITIAL_KW stmt  */
#line 202 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::INITIAL_BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2078 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 39: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' port_conn_list ')' ';'  */
#line 205 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-9].str), yylineno); free((yyvsp[-9].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-6].node)->children) addChild((yyval.node), c); (yyvsp[-6].node)->children.clear(); freeTree((yyvsp[-6].node)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 2084 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 40: /* module_item: IDENTIFIER IDENTIFIER '(' port_conn_list ')' ';'  */
#line 207 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-5].str), yylineno); free((yyvsp[-5].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 2090 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 41: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' ')' ';'  */
#line 209 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-8].str), yylineno); free((yyvsp[-8].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); for (auto *c : (yyvsp[-5].node)->children) addChild((yyval.node), c); (yyvsp[-5].node)->children.clear(); freeTree((yyvsp[-5].node)); }
#line 2096 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 42: /* module_item: IDENTIFIER IDENTIFIER '(' ')' ';'  */
#line 211 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-4].str), yylineno); free((yyvsp[-4].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); }
#line 2102 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 43: /* module_item: GENERATE gen_items ENDGENERATE  */
#line 212 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2108 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 44: /* module_item: param_override ';'  */
#line 213 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2114 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 45: /* port_decl: INPUT range IDENTIFIER  */
#line 218 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
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
#line 2129 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 46: /* port_decl: INPUT IDENTIFIER  */
#line 229 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2141 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 47: /* port_decl: OUTPUT range IDENTIFIER  */
#line 237 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2155 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 48: /* port_decl: OUTPUT IDENTIFIER  */
#line 247 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2167 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 49: /* port_decl: OUTPUT WIRE range IDENTIFIER  */
#line 255 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2181 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 50: /* port_decl: OUTPUT WIRE IDENTIFIER  */
#line 265 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2193 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 51: /* port_decl: INPUT WIRE range IDENTIFIER  */
#line 273 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2207 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 52: /* port_decl: INPUT WIRE IDENTIFIER  */
#line 283 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2219 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 53: /* port_decl: OUTPUT REG range IDENTIFIER  */
#line 291 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2233 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 54: /* port_decl: OUTPUT REG IDENTIFIER  */
#line 301 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2245 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 55: /* port_decl: OUTPUT SIGNED range IDENTIFIER  */
#line 309 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2259 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 56: /* port_decl: INPUT SIGNED range IDENTIFIER  */
#line 319 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2273 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 57: /* port_decl: OUTPUT REG SIGNED range IDENTIFIER  */
#line 329 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2285 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 58: /* decl_list: decl_list ',' IDENTIFIER  */
#line 339 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { free((yyvsp[0].str)); }
#line 2291 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 60: /* stmt: BEGINKW stmts END  */
#line 344 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 2297 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 61: /* stmt: IF '(' expr ')' stmt  */
#line 346 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2307 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 62: /* stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 352 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2318 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 63: /* stmt: CASE '(' expr ')' case_items ENDCASE  */
#line 359 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2328 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 64: /* stmt: FOR '(' lvalue '=' expr ';' expr ';' lvalue '=' expr ')' stmt  */
#line 365 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "", yylineno);
          addChild((yyval.node), (yyvsp[-10].node));  /* init lvalue */
          addChild((yyval.node), (yyvsp[-8].node));  /* init expr */
          addChild((yyval.node), (yyvsp[-6].node));  /* cond */
          addChild((yyval.node), (yyvsp[-4].node));  /* update lvalue */
          addChild((yyval.node), (yyvsp[-2].node)); /* update expr */
          addChild((yyval.node), (yyvsp[0].node)); /* body */
      }
#line 2342 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 65: /* stmt: lvalue '=' expr ';'  */
#line 375 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2352 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 66: /* stmt: lvalue LE expr ';'  */
#line 381 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2362 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 67: /* stmt: SYS_DISPLAY '(' expr_list ')' ';'  */
#line 387 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2373 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 68: /* stmt: SYS_DISPLAY '(' STRING ')' ';'  */
#line 394 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2383 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 69: /* stmt: SYS_FINISH ';'  */
#line 399 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); }
#line 2389 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 70: /* stmt: SYS_FINISH '(' expr ')' ';'  */
#line 400 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); addChild((yyval.node), (yyvsp[-2].node)); }
#line 2395 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 71: /* stmt: '#' NUMBER ';'  */
#line 402 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, std::to_string((yyvsp[-1].num)->value), yylineno);
          free((yyvsp[-1].num));
      }
#line 2404 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 72: /* stmt: '@' '(' POSEDGE IDENTIFIER ')' ';'  */
#line 407 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, "posedge", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2414 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 73: /* stmt: '@' '(' NEGEDGE IDENTIFIER ')' ';'  */
#line 413 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, "negedge", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2424 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 74: /* stmt: SYS_FOPEN '(' STRING ')' ';'  */
#line 419 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2434 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 75: /* stmt: SYS_FCLOSE '(' expr ')' ';'  */
#line 425 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fclose", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
      }
#line 2443 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 76: /* stmt: lvalue '=' SYS_FOPEN '(' STRING ')' ';'  */
#line 430 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild(fc, makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          addChild((yyval.node), fc);
      }
#line 2456 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 77: /* stmt: lvalue '=' SYS_FSCANF '(' expr_list ')' ';'  */
#line 439 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fscanf", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2470 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 78: /* stmt: lvalue '=' SYS_FGETS '(' expr_list ')' ';'  */
#line 449 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fgets", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2484 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 79: /* stmt: SYS_FDISPLAY '(' expr_list ')' ';'  */
#line 459 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2495 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 80: /* stmt: SYS_FDISPLAY '(' STRING ')' ';'  */
#line 466 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2505 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 81: /* stmts: stmts stmt  */
#line 474 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2511 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 82: /* stmts: stmt  */
#line 475 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2517 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 83: /* gen_items: gen_items gen_item  */
#line 479 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2523 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 84: /* gen_items: gen_item  */
#line 480 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::GENERATE, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2529 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 85: /* gen_item: FOR '(' GENVAR IDENTIFIER '=' expr ';' expr ';' IDENTIFIER '=' expr ')' gen_block  */
#line 485 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2541 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 86: /* gen_item: FOR '(' IDENTIFIER '=' expr ';' expr ';' lvalue '=' expr ')' gen_block  */
#line 493 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        /* for (name = expr; cond; name = expr) — genvar already declared */
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2554 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 87: /* gen_item: IF '(' expr ')' gen_block  */
#line 502 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2564 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 88: /* gen_item: IF '(' expr ')' gen_block ELSE gen_block  */
#line 508 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2575 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 89: /* gen_item: GENVAR genvar_list ';'  */
#line 515 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        /* genvar declaration — skip */
        (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno);
    }
#line 2584 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 90: /* genvar_list: genvar_list ',' IDENTIFIER  */
#line 522 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                               { free((yyvsp[0].str)); }
#line 2590 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 91: /* genvar_list: IDENTIFIER  */
#line 523 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                 { free((yyvsp[0].str)); }
#line 2596 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 92: /* gen_block: BEGINKW gen_body END  */
#line 527 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2602 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 93: /* gen_block: BEGINKW ':' IDENTIFIER gen_body END  */
#line 528 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                          { (yyval.node) = (yyvsp[-1].node); free((yyvsp[-2].str)); }
#line 2608 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 94: /* gen_block: module_item  */
#line 529 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2614 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 95: /* gen_body: gen_body module_item  */
#line 533 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2620 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 96: /* gen_body: gen_body gen_item  */
#line 534 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2626 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 97: /* gen_body: module_item  */
#line 535 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2632 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 98: /* gen_body: gen_item  */
#line 536 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2638 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 99: /* case_items: case_items case_item  */
#line 540 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2644 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 100: /* case_items: case_item  */
#line 541 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2650 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 101: /* case_item: expr ':' stmt  */
#line 546 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2660 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 102: /* case_item: expr ',' expr ':' stmt  */
#line 552 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2671 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 103: /* case_item: DEFAULT ':' stmt  */
#line 559 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2680 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 104: /* case_item: DEFAULT stmt  */
#line 564 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2689 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 105: /* param_override: '#' '(' param_list ')'  */
#line 572 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    { (yyval.node) = makeNode(NodeType::PARAM_OVERRIDE, "", yylineno); for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
#line 2695 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 106: /* param_list: param_list ',' param_assign  */
#line 576 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2701 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 107: /* param_list: param_assign  */
#line 577 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 2707 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 108: /* param_assign: '.' IDENTIFIER '(' expr ')'  */
#line 581 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2713 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 109: /* port_conn_list: port_conn_list ',' port_conn  */
#line 585 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2719 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 110: /* port_conn_list: port_conn  */
#line 586 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2725 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 111: /* port_conn: '.' IDENTIFIER '(' expr ')'  */
#line 591 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2735 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 112: /* port_conn: '.' IDENTIFIER '(' ')'  */
#line 597 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-2].str), yylineno);
          free((yyvsp[-2].str));
      }
#line 2744 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 113: /* range: '[' expr ':' expr ']'  */
#line 605 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
          /* Evaluate constant range bounds */
          if ((yyvsp[-3].node)->type == NodeType::NUMBER) (yyval.node)->msb = std::stoi((yyvsp[-3].node)->value);
          if ((yyvsp[-1].node)->type == NodeType::NUMBER) (yyval.node)->lsb = std::stoi((yyvsp[-1].node)->value);
      }
#line 2757 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 114: /* expr: expr '+' expr  */
#line 616 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "+", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2763 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 115: /* expr: expr '-' expr  */
#line 617 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "-", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2769 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 116: /* expr: expr '*' expr  */
#line 618 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "*", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2775 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 117: /* expr: expr '/' expr  */
#line 619 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "/", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2781 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 118: /* expr: expr '%' expr  */
#line 620 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "%", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2787 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 119: /* expr: expr '&' expr  */
#line 621 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2793 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 120: /* expr: expr '|' expr  */
#line 622 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2799 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 121: /* expr: expr '^' expr  */
#line 623 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2805 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 122: /* expr: expr XNOR expr  */
#line 624 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2811 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 123: /* expr: expr NAND expr  */
#line 625 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2817 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 124: /* expr: expr NOR expr  */
#line 626 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2823 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 125: /* expr: expr EQ expr  */
#line 627 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "==", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2829 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 126: /* expr: expr NE expr  */
#line 628 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "!=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2835 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 127: /* expr: expr '<' expr  */
#line 629 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2841 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 128: /* expr: expr '>' expr  */
#line 630 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2847 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 129: /* expr: expr LE expr  */
#line 631 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2853 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 130: /* expr: expr GE expr  */
#line 632 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2859 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 131: /* expr: expr SHL expr  */
#line 633 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2865 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 132: /* expr: expr SHR expr  */
#line 634 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2871 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 133: /* expr: expr SSHR expr  */
#line 635 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2877 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 134: /* expr: expr '*' '*' expr  */
#line 636 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = makeNode(NodeType::BINOP, "**", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2883 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 135: /* expr: expr LOGAND expr  */
#line 637 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2889 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 136: /* expr: expr LOGOR expr  */
#line 638 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "||", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2895 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 137: /* expr: expr '?' expr ':' expr  */
#line 640 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::TERNARY, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));
      }
#line 2904 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 138: /* expr: '-' expr  */
#line 644 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "-", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2910 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 139: /* expr: '!' expr  */
#line 645 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "!", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2916 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 140: /* expr: '~' expr  */
#line 646 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2922 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 141: /* expr: '&' expr  */
#line 647 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "&", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2928 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 142: /* expr: '|' expr  */
#line 648 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "|", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2934 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 143: /* expr: '^' expr  */
#line 649 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "^", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2940 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 145: /* prim_expr: NUMBER  */
#line 655 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNum((yyvsp[0].num));
      }
#line 2948 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 146: /* prim_expr: IDENTIFIER  */
#line 659 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 2957 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 147: /* prim_expr: IDENTIFIER '[' expr ':' expr ']'  */
#line 664 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2968 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 148: /* prim_expr: IDENTIFIER '[' expr ']'  */
#line 671 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2978 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 149: /* prim_expr: IDENTIFIER '[' expr ']' '[' expr ':' expr ']'  */
#line 677 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Double range-select: signal[idx][msb:lsb] — mark with msb=-1 to distinguish */
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-8].str), yylineno);
          free((yyvsp[-8].str));
          addChild((yyval.node), (yyvsp[-6].node));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2991 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 150: /* prim_expr: IDENTIFIER '[' expr ']' '[' expr ']'  */
#line 686 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
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
#line 3006 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 151: /* prim_expr: '{' expr_list '}'  */
#line 697 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 3017 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 152: /* prim_expr: '{' expr '{' expr_list '}' '}'  */
#line 704 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
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
#line 3033 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 153: /* prim_expr: '(' expr ')'  */
#line 716 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 3041 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 154: /* prim_expr: SYS_FOPEN '(' STRING ')'  */
#line 720 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
      }
#line 3051 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 155: /* prim_expr: SYS_FOPEN '(' STRING ',' STRING ')'  */
#line 726 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-3].str), yylineno));
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-3].str)); free((yyvsp[-1].str));
      }
#line 3062 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 156: /* prim_expr: SYS_CLOG2 '(' expr ')'  */
#line 733 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$clog2", yylineno);
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3071 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 157: /* prim_expr: STRING  */
#line 738 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::STRING, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3080 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 158: /* lvalue: IDENTIFIER  */
#line 746 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3089 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 159: /* lvalue: IDENTIFIER '[' expr ':' expr ']'  */
#line 751 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3100 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 160: /* lvalue: IDENTIFIER '[' expr ']'  */
#line 758 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3110 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 161: /* lvalue: IDENTIFIER '[' expr ']' '[' expr ':' expr ']'  */
#line 764 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-8].str), yylineno);
          free((yyvsp[-8].str));
          addChild((yyval.node), (yyvsp[-6].node));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3122 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 162: /* lvalue: IDENTIFIER '[' expr ']' '[' expr ']'  */
#line 772 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-6].str), yylineno);
          free((yyvsp[-6].str));
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-1].node));
          auto *sentinel = makeNode(NodeType::NUMBER, "-1", yylineno);
          sentinel->msb = -1;
          addChild((yyval.node), sentinel);
      }
#line 3136 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 163: /* lvalue: '{' lvalue_list '}'  */
#line 782 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 3147 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 164: /* lvalue_list: lvalue_list ',' lvalue  */
#line 791 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3153 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 165: /* lvalue_list: lvalue  */
#line 792 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3159 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 166: /* expr_list: expr_list ',' expr  */
#line 796 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3165 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 167: /* expr_list: expr  */
#line 797 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3171 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;


#line 3175 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"

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

#line 800 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"


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
