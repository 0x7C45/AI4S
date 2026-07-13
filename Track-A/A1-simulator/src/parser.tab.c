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
  YYSYMBOL_SYS_FOPEN = 30,                 /* SYS_FOPEN  */
  YYSYMBOL_SYS_FCLOSE = 31,                /* SYS_FCLOSE  */
  YYSYMBOL_SYS_FSCANF = 32,                /* SYS_FSCANF  */
  YYSYMBOL_SYS_FGETS = 33,                 /* SYS_FGETS  */
  YYSYMBOL_SYS_FDISPLAY = 34,              /* SYS_FDISPLAY  */
  YYSYMBOL_SYS_DISPLAY = 35,               /* SYS_DISPLAY  */
  YYSYMBOL_SYS_FINISH = 36,                /* SYS_FINISH  */
  YYSYMBOL_SYS_CLOG2 = 37,                 /* SYS_CLOG2  */
  YYSYMBOL_EQ = 38,                        /* EQ  */
  YYSYMBOL_NE = 39,                        /* NE  */
  YYSYMBOL_LE = 40,                        /* LE  */
  YYSYMBOL_GE = 41,                        /* GE  */
  YYSYMBOL_LOGAND = 42,                    /* LOGAND  */
  YYSYMBOL_LOGOR = 43,                     /* LOGOR  */
  YYSYMBOL_SHL = 44,                       /* SHL  */
  YYSYMBOL_SHR = 45,                       /* SHR  */
  YYSYMBOL_SSHR = 46,                      /* SSHR  */
  YYSYMBOL_NAND = 47,                      /* NAND  */
  YYSYMBOL_NOR = 48,                       /* NOR  */
  YYSYMBOL_XNOR = 49,                      /* XNOR  */
  YYSYMBOL_50_ = 50,                       /* '|'  */
  YYSYMBOL_51_ = 51,                       /* '^'  */
  YYSYMBOL_52_ = 52,                       /* '&'  */
  YYSYMBOL_53_ = 53,                       /* '<'  */
  YYSYMBOL_54_ = 54,                       /* '>'  */
  YYSYMBOL_55_ = 55,                       /* '+'  */
  YYSYMBOL_56_ = 56,                       /* '-'  */
  YYSYMBOL_57_ = 57,                       /* '*'  */
  YYSYMBOL_58_ = 58,                       /* '/'  */
  YYSYMBOL_59_ = 59,                       /* '%'  */
  YYSYMBOL_POWER = 60,                     /* POWER  */
  YYSYMBOL_61_ = 61,                       /* '!'  */
  YYSYMBOL_62_ = 62,                       /* '~'  */
  YYSYMBOL_UNARY = 63,                     /* UNARY  */
  YYSYMBOL_64_ = 64,                       /* ';'  */
  YYSYMBOL_65_ = 65,                       /* '#'  */
  YYSYMBOL_66_ = 66,                       /* '('  */
  YYSYMBOL_67_ = 67,                       /* ')'  */
  YYSYMBOL_68_ = 68,                       /* ','  */
  YYSYMBOL_69_ = 69,                       /* '='  */
  YYSYMBOL_70_ = 70,                       /* '@'  */
  YYSYMBOL_71_ = 71,                       /* ':'  */
  YYSYMBOL_72_ = 72,                       /* '.'  */
  YYSYMBOL_73_ = 73,                       /* '['  */
  YYSYMBOL_74_ = 74,                       /* ']'  */
  YYSYMBOL_75_ = 75,                       /* '?'  */
  YYSYMBOL_76_ = 76,                       /* '{'  */
  YYSYMBOL_77_ = 77,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_source = 79,                    /* source  */
  YYSYMBOL_module_list = 80,               /* module_list  */
  YYSYMBOL_module = 81,                    /* module  */
  YYSYMBOL_module_param_decls = 82,        /* module_param_decls  */
  YYSYMBOL_module_param_decl = 83,         /* module_param_decl  */
  YYSYMBOL_opt_port_list = 84,             /* opt_port_list  */
  YYSYMBOL_port_list = 85,                 /* port_list  */
  YYSYMBOL_port_decl_in_list = 86,         /* port_decl_in_list  */
  YYSYMBOL_module_items = 87,              /* module_items  */
  YYSYMBOL_module_item = 88,               /* module_item  */
  YYSYMBOL_port_decl = 89,                 /* port_decl  */
  YYSYMBOL_decl_list = 90,                 /* decl_list  */
  YYSYMBOL_stmt = 91,                      /* stmt  */
  YYSYMBOL_stmts = 92,                     /* stmts  */
  YYSYMBOL_gen_items = 93,                 /* gen_items  */
  YYSYMBOL_gen_item = 94,                  /* gen_item  */
  YYSYMBOL_gen_block = 95,                 /* gen_block  */
  YYSYMBOL_gen_body = 96,                  /* gen_body  */
  YYSYMBOL_case_items = 97,                /* case_items  */
  YYSYMBOL_case_item = 98,                 /* case_item  */
  YYSYMBOL_param_override = 99,            /* param_override  */
  YYSYMBOL_param_list = 100,               /* param_list  */
  YYSYMBOL_param_assign = 101,             /* param_assign  */
  YYSYMBOL_port_conn_list = 102,           /* port_conn_list  */
  YYSYMBOL_port_conn = 103,                /* port_conn  */
  YYSYMBOL_range = 104,                    /* range  */
  YYSYMBOL_expr = 105,                     /* expr  */
  YYSYMBOL_prim_expr = 106,                /* prim_expr  */
  YYSYMBOL_lvalue = 107,                   /* lvalue  */
  YYSYMBOL_lvalue_list = 108,              /* lvalue_list  */
  YYSYMBOL_expr_list = 109                 /* expr_list  */
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
#define YYLAST   1990

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  406

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


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
       2,     2,     2,    61,     2,    65,     2,    59,    52,     2,
      66,    67,    57,    55,    68,    56,    72,    58,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    71,    64,
      53,    69,    54,    75,    70,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    73,     2,    74,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,    50,    77,    62,     2,     2,     2,
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
      45,    46,    47,    48,    49,    60,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    87,    88,    92,    99,   111,   112,   116,
     121,   122,   126,   127,   131,   132,   133,   137,   138,   139,
     143,   144,   146,   148,   150,   152,   154,   156,   158,   160,
     162,   164,   166,   168,   170,   172,   174,   175,   179,   187,
     195,   203,   211,   219,   227,   235,   243,   251,   259,   267,
     275,   286,   287,   291,   292,   298,   305,   311,   321,   327,
     333,   340,   346,   347,   348,   353,   359,   364,   373,   383,
     393,   400,   409,   410,   414,   415,   419,   429,   438,   439,
     443,   444,   448,   449,   453,   459,   466,   471,   479,   484,
     485,   489,   493,   494,   498,   504,   512,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   552,   553,   554,   555,   556,   557,   558,   562,   566,
     571,   578,   584,   591,   603,   607,   613,   620,   625,   633,
     638,   645,   651,   661,   662,   666,   667
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
  "DEFAULT", "FOR", "GENERATE", "ENDGENERATE", "GENVAR", "SYS_FOPEN",
  "SYS_FCLOSE", "SYS_FSCANF", "SYS_FGETS", "SYS_FDISPLAY", "SYS_DISPLAY",
  "SYS_FINISH", "SYS_CLOG2", "EQ", "NE", "LE", "GE", "LOGAND", "LOGOR",
  "SHL", "SHR", "SSHR", "NAND", "NOR", "XNOR", "'|'", "'^'", "'&'", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "POWER", "'!'", "'~'", "UNARY",
  "';'", "'#'", "'('", "')'", "','", "'='", "'@'", "':'", "'.'", "'['",
  "']'", "'?'", "'{'", "'}'", "$accept", "source", "module_list", "module",
  "module_param_decls", "module_param_decl", "opt_port_list", "port_list",
  "port_decl_in_list", "module_items", "module_item", "port_decl",
  "decl_list", "stmt", "stmts", "gen_items", "gen_item", "gen_block",
  "gen_body", "case_items", "case_item", "param_override", "param_list",
  "param_assign", "port_conn_list", "port_conn", "range", "expr",
  "prim_expr", "lvalue", "lvalue_list", "expr_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-177)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,    29,    47,    23,  -177,   -50,  -177,  -177,    -4,    61,
      11,    56,  -177,    14,    20,    89,  -177,  -177,   610,    82,
      98,  -177,  -177,     6,    18,   318,    95,  -177,     7,    15,
      18,   102,  -177,    61,     9,     8,    31,   135,   143,   146,
       0,    97,   448,    74,   110,   511,  -177,   114,   138,    32,
     131,    56,  -177,   207,   208,   139,  -177,  -177,   147,   157,
     318,   318,   318,   318,   318,   318,   318,   318,   791,  -177,
    -177,  -177,   221,  -177,    18,   230,   231,  -177,  -177,   171,
     175,  -177,   240,  -177,    18,   241,  -177,   177,   179,   178,
       0,   181,   189,   448,   191,   195,   196,   200,   212,   213,
     215,    -5,    79,  -177,   -26,   216,   217,    37,  -177,   201,
    -177,  -177,  -177,  -177,   318,   220,  -177,  -177,  -177,   318,
     284,   318,   214,   214,   214,   214,   214,   214,   829,   638,
     -55,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     169,   318,   318,   318,   318,  -177,   287,  -177,  -177,    30,
     201,    35,  -177,    71,   290,  -177,    77,   318,   318,   318,
    -177,   -23,   318,   237,  -177,   233,   318,   318,     0,   291,
     318,   353,   383,  -177,   318,   236,   318,    16,   318,   273,
    -177,  -177,   301,   113,  -177,  1779,   610,   677,   115,   867,
    -177,   318,   318,  -177,   595,   595,   366,   366,  1843,  1811,
      75,    75,    75,  1915,  1915,  1892,  1868,  1892,  1915,   366,
     366,    -2,    -2,   318,   214,   214,   214,   905,   943,  -177,
     242,   304,   117,  -177,   119,  -177,   307,    90,  -177,  -177,
     100,  -177,   981,  1019,   715,     0,  -177,  1057,   245,  -177,
    -177,  1095,  1133,   244,   247,  1171,   248,  1779,   121,   250,
     125,  1209,  -177,  1247,   258,   260,   262,  1285,  1323,   326,
     264,  -177,   201,   544,   318,  -177,  -177,   327,  -177,   -17,
    1779,   214,  -177,   318,  -177,   266,   269,   263,   331,  -177,
    -177,   111,  -177,  -177,  -177,   318,  -177,  -177,  -177,   448,
     448,   235,   318,   272,   274,   276,   278,   279,   280,   282,
    -177,   333,   318,   318,  -177,   569,   281,   318,  -177,  -177,
    1361,   292,   270,  1779,   315,  -177,  -177,   283,  -177,  1399,
    -177,   329,   427,   166,  -177,   753,  1437,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,   127,   133,   137,   610,  -177,  -177,
     318,  1475,  -177,  -177,  -177,  -177,  1513,    81,  -177,   448,
     448,  -177,  -177,  -177,   318,   448,   318,   297,   299,   300,
    -177,   590,  1551,  -177,  -177,   309,   141,  -177,  -177,  1589,
    -177,  1627,  -177,  -177,  -177,  -177,  -177,   318,  -177,   314,
     448,     0,  1665,  -177,  -177,   285,   382,   318,   320,  1703,
     318,   448,  1741,  -177,   569,  -177
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,    11,     1,     3,     0,    16,
       0,     0,    14,     0,     0,     0,    13,    15,    19,     0,
       0,     8,    39,     0,     0,     0,     0,    41,     0,     0,
       0,     0,    10,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,     0,     0,
      11,     0,    45,     0,     0,   129,   138,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
      38,    43,     0,    47,     0,     0,     0,    40,    12,     0,
       0,    52,     0,    52,     0,     0,    52,     0,     0,   139,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,    75,     0,
       5,    17,    20,    37,     0,     0,     7,    44,    49,     0,
       0,     0,   125,   126,   124,   121,   122,   123,     0,   146,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,     0,    46,    48,     0,
       0,     0,    52,     0,     0,    52,     0,     0,     0,     0,
     144,     0,     0,     0,    73,     0,     0,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,     0,     0,
      36,    74,     0,     0,    90,     9,    19,     0,     0,     0,
     134,     0,     0,   132,   108,   109,   112,   113,   118,   119,
     114,   115,   116,   106,   107,   105,   103,   104,   102,   110,
     111,    97,    98,     0,    99,   100,   101,     0,     0,    50,
       0,     0,     0,    93,     0,    22,     0,     0,    24,    52,
       0,    26,     0,     0,     0,     0,   142,     0,     0,    53,
      72,     0,     0,     0,     0,     0,   138,   146,     0,   138,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,     0,     0,   131,   135,     0,   137,     0,
     145,   117,    96,     0,    35,     0,     0,     0,     0,    51,
      21,     0,    23,    27,    28,     0,   141,   143,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      59,     0,     0,     0,    58,     0,     0,     0,    89,     6,
       0,     0,     0,   120,     0,    33,    92,     0,    25,     0,
      30,    54,     0,     0,    83,     0,     0,    65,    66,    71,
      70,    61,    60,    63,     0,     0,     0,     0,    79,    77,
       0,     0,   130,   136,   133,    95,     0,     0,   140,     0,
       0,    87,    56,    82,     0,     0,     0,   135,     0,     0,
      81,     0,     0,    91,    94,     0,     0,    55,    86,     0,
      84,     0,    67,    68,    69,    78,    80,     0,    34,     0,
       0,     0,     0,    32,    85,     0,     0,     0,     0,     0,
       0,     0,     0,    57,     0,    76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -177,  -177,  -177,   389,  -177,   342,   345,  -177,   363,   202,
     -44,    17,   -79,   -85,  -177,  -177,   293,    -7,  -177,  -177,
      66,  -177,   246,   129,    45,   120,   466,   -25,  -177,   -38,
    -177,  -176
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     4,    20,    21,    10,    15,    16,    45,
      46,    47,   161,   103,   175,   107,   108,   349,   371,   333,
     334,    48,   193,   194,   232,   233,    26,   257,    69,   104,
     171,   130
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,   111,    91,    89,   163,   258,   260,   166,   174,    52,
      71,    81,    79,   202,   186,     8,     9,    22,    73,    55,
      56,    57,   203,    27,    23,   279,    17,    24,    74,     1,
      28,    29,     5,    30,    83,   122,   123,   124,   125,   126,
     127,   128,   129,   187,    84,   245,   264,     6,   265,   266,
      17,   202,   170,    59,   246,   150,   151,   152,   105,   183,
     322,   184,    11,   106,    12,   190,    60,    61,    62,    13,
      14,    19,    63,   154,    80,    18,    90,    64,    65,    25,
      25,    25,    66,   237,   185,    49,   240,    25,    25,   195,
     250,    25,    67,    25,   197,   105,   199,   230,    70,   235,
     106,   114,   231,   236,    25,    77,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   224,   225,   226,   227,   228,
     148,   149,   150,   151,   152,   238,   345,   346,    86,   236,
     253,   241,   242,   243,   244,   236,    87,   247,   375,    88,
     154,   251,   252,   231,   290,   255,    32,    33,   236,   261,
     291,   263,   267,   268,   292,    50,    51,    92,   236,    55,
      56,    57,    55,    56,    57,   328,   109,   280,   112,   236,
     271,   272,   276,   277,   286,   287,   288,   272,   306,   202,
     362,   332,   308,   202,   367,   277,    58,     9,   281,    58,
     368,   202,   113,    59,   369,   202,    59,   297,   389,   287,
     117,   118,   119,   120,   330,   331,    60,    61,    62,    60,
      61,    62,    63,   121,   155,    63,   223,    64,    65,   111,
      64,    65,    66,   157,   158,    66,    89,   159,    55,    56,
      57,   160,    67,   162,   165,    67,   167,   361,   168,   320,
     172,   169,    93,   249,    94,   173,    95,   176,   323,    96,
     332,   177,   178,    97,    98,    58,   179,    99,   100,   101,
     329,   348,    59,   192,   377,   378,   335,   336,   180,   181,
     380,   182,   188,   189,   196,    60,    61,    62,   198,   154,
     229,    63,   351,   239,   248,   254,    64,    65,   102,   356,
     262,    66,   269,   370,   270,   394,   284,   285,   335,    90,
     289,    67,   299,   302,   303,   305,   403,   307,    55,    56,
      57,    55,    56,    57,   311,   372,   312,   386,   313,   316,
     317,   321,   324,   325,   327,   231,   337,   344,   338,   379,
     339,   381,   340,   341,   342,    58,   343,   354,    58,   357,
     350,   359,    59,   395,   397,    59,    55,   256,    57,   353,
     348,   382,   392,   383,   384,    60,    61,    62,    60,    61,
      62,    63,   399,   388,    63,   402,    64,    65,   393,    64,
      65,    66,   355,    58,    66,   398,    55,   259,    57,   400,
      59,    67,     7,   116,    67,   115,    78,   405,   273,   363,
     191,   318,   376,    60,    61,    62,   234,   326,     0,    63,
     137,   138,   139,    58,    64,    65,     0,     0,     0,    66,
      59,   148,   149,   150,   151,   152,     0,     0,     0,    67,
      89,     0,     0,    60,    61,    62,     0,     0,     0,    63,
       0,   154,     0,     0,    64,    65,    93,     0,    94,    66,
      95,    89,     0,    96,     0,     0,     0,    97,    98,    67,
       0,    99,   100,   101,     0,     0,     0,    93,     0,    94,
       0,    95,     0,     0,    96,     0,     0,     0,    97,    98,
      31,     0,    99,   100,   101,     0,     0,     0,     0,    53,
      54,     0,   102,     0,    72,    75,    76,     0,   360,     0,
       0,    82,    85,    90,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   102,    34,     0,     0,     0,   110,    13,
      14,    35,    36,    37,    90,    38,    39,    40,    41,    42,
       0,     0,     0,     0,     0,     0,     0,     0,    43,     0,
     156,     0,     0,     0,     0,     0,     0,    34,     0,     0,
     164,   319,    13,    14,    35,    36,    37,     0,    38,    39,
      40,    41,    42,     0,     0,     0,     0,     0,     0,     0,
       0,    43,    34,     0,     0,     0,    44,    13,    14,    35,
      36,    37,     0,    38,    39,    40,    41,    42,   347,     0,
       0,     0,     0,    34,     0,     0,    43,     0,    13,    14,
      35,    36,    37,     0,    38,    39,    40,    41,    42,    44,
     385,     0,     0,    34,     0,     0,     0,    43,    13,    14,
      35,    36,    37,     0,    38,    39,    40,    41,    42,     0,
       0,     0,     0,     0,    44,   133,   134,    43,     0,   137,
     138,   139,     0,     0,     0,     0,     0,     0,   146,   147,
     148,   149,   150,   151,   152,    44,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154,     0,     0,     0,     0,    44,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   154,   201,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   274,     0,
       0,   275,   154,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   295,     0,     0,   296,
     154,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
       0,   364,     0,     0,   365,     0,     0,     0,   154,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,   154,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,     0,
       0,     0,     0,     0,     0,     0,   200,     0,     0,     0,
       0,     0,     0,     0,   154,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,     0,     0,     0,   278,     0,     0,     0,     0,     0,
       0,     0,   154,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   282,
     154,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   283,     0,     0,     0,   154,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,   293,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   154,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,     0,
       0,     0,     0,   294,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   154,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,   298,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,   300,     0,     0,     0,     0,     0,     0,     0,
     154,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
     301,     0,     0,     0,     0,     0,     0,     0,   154,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,     0,     0,     0,   304,     0,
       0,     0,     0,     0,     0,     0,   154,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,     0,
       0,     0,     0,     0,     0,     0,   309,     0,     0,     0,
       0,     0,     0,     0,   154,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,   310,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,     0,     0,     0,     0,   314,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
     315,     0,     0,     0,     0,     0,     0,     0,   154,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   352,   154,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   358,   154,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,   366,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,   373,     0,     0,     0,     0,     0,     0,     0,
     154,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
     374,     0,     0,     0,     0,     0,     0,     0,   154,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,   387,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   154,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     390,     0,     0,     0,   154,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,   391,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,     0,     0,     0,     0,   396,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
     401,     0,     0,     0,     0,     0,     0,     0,   154,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,     0,     0,     0,   404,     0,
       0,     0,     0,     0,     0,     0,   154,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     132,   133,   134,   135,   154,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,   133,   134,     0,   154,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,   131,   132,   133,   134,
       0,     0,   137,   138,   139,   140,   141,   142,   154,   144,
     145,   146,   147,   148,   149,   150,   151,   152,     0,     0,
     131,   132,   133,   134,     0,     0,   137,   138,   139,   140,
     141,     0,     0,   154,   145,   146,   147,   148,   149,   150,
     151,   152,     0,   131,   132,   133,   134,     0,     0,   137,
     138,   139,     0,     0,     0,     0,     0,   154,   146,   147,
     148,   149,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154
};

static const yytype_int16 yycheck[] =
{
      25,    45,    40,     3,    83,   181,   182,    86,    93,     3,
       3,     3,     3,    68,    40,    65,    66,     3,     3,     3,
       4,     5,    77,     3,    10,   201,     9,    13,    13,     6,
      10,    11,     3,    13,     3,    60,    61,    62,    63,    64,
      65,    66,    67,    69,    13,    68,    30,     0,    32,    33,
      33,    68,    90,    37,    77,    57,    58,    59,    21,    64,
      77,    66,    66,    26,     3,    28,    50,    51,    52,     8,
       9,    15,    56,    75,    65,    64,    76,    61,    62,    73,
      73,    73,    66,   162,     5,     3,   165,    73,    73,   114,
     175,    73,    76,    73,   119,    21,   121,    67,     3,    64,
      26,    69,    72,    68,    73,     3,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
      55,    56,    57,    58,    59,    64,   312,   313,     3,    68,
     178,    64,   167,   168,   169,    68,     3,   172,    67,     3,
      75,   176,   177,    72,    64,   180,    67,    68,    68,   184,
     239,   186,   187,   188,    64,    67,    68,    70,    68,     3,
       4,     5,     3,     4,     5,    64,    66,   202,    64,    68,
      67,    68,    67,    68,    67,    68,    67,    68,    67,    68,
      24,    25,    67,    68,    67,    68,    30,    66,   223,    30,
      67,    68,    64,    37,    67,    68,    37,   245,    67,    68,
       3,     3,    73,    66,   299,   300,    50,    51,    52,    50,
      51,    52,    56,    66,     3,    56,    57,    61,    62,   273,
      61,    62,    66,     3,     3,    66,     3,    66,     3,     4,
       5,    66,    76,     3,     3,    76,    69,   332,    69,   274,
      69,    73,    19,    20,    21,    66,    23,    66,   283,    26,
      25,    66,    66,    30,    31,    30,    66,    34,    35,    36,
     295,   315,    37,    72,   359,   360,   301,   302,    66,    66,
     365,    66,    66,    66,    64,    50,    51,    52,     4,    75,
       3,    56,   317,     3,    57,     4,    61,    62,    65,   324,
      64,    66,    29,   347,     3,   390,    64,     3,   333,    76,
       3,    76,    67,    69,    67,    67,   401,    67,     3,     4,
       5,     3,     4,     5,    66,   350,    66,   371,    66,     3,
      66,     4,    66,    64,     3,    72,    64,     4,    64,   364,
      64,   366,    64,    64,    64,    30,    64,    77,    30,    66,
      69,    22,    37,   391,    69,    37,     3,     4,     5,    67,
     404,    64,   387,    64,    64,    50,    51,    52,    50,    51,
      52,    56,   397,    64,    56,   400,    61,    62,    64,    61,
      62,    66,    67,    30,    66,     3,     3,     4,     5,    69,
      37,    76,     3,    51,    76,    50,    33,   404,   196,   333,
     107,   272,   357,    50,    51,    52,   160,   287,    -1,    56,
      44,    45,    46,    30,    61,    62,    -1,    -1,    -1,    66,
      37,    55,    56,    57,    58,    59,    -1,    -1,    -1,    76,
       3,    -1,    -1,    50,    51,    52,    -1,    -1,    -1,    56,
      -1,    75,    -1,    -1,    61,    62,    19,    -1,    21,    66,
      23,     3,    -1,    26,    -1,    -1,    -1,    30,    31,    76,
      -1,    34,    35,    36,    -1,    -1,    -1,    19,    -1,    21,
      -1,    23,    -1,    -1,    26,    -1,    -1,    -1,    30,    31,
      14,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,    23,
      24,    -1,    65,    -1,    28,    29,    30,    -1,    71,    -1,
      -1,    35,    36,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,     3,    -1,    -1,    -1,     7,     8,
       9,    10,    11,    12,    76,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      84,     7,     8,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,     3,    -1,    -1,    -1,    65,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    27,    -1,     8,     9,
      10,    11,    12,    -1,    14,    15,    16,    17,    18,    65,
      20,    -1,    -1,     3,    -1,    -1,    -1,    27,     8,     9,
      10,    11,    12,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    65,    40,    41,    27,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    59,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    65,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    74,    75,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    74,
      75,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    -1,    -1,    -1,    75,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    75,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      75,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    75,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    75,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    -1,    75,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    75,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    75,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    75,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      38,    39,    40,    41,    -1,    -1,    44,    45,    46,    47,
      48,    -1,    -1,    75,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    38,    39,    40,    41,    -1,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    75,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    79,    80,    81,     3,     0,    81,    65,    66,
      84,    66,     3,     8,     9,    85,    86,    89,    64,    15,
      82,    83,     3,    10,    13,    73,   104,     3,    10,    11,
      13,   104,    67,    68,     3,    10,    11,    12,    14,    15,
      16,    17,    18,    27,    65,    87,    88,    89,    99,     3,
      67,    68,     3,   104,   104,     3,     4,     5,    30,    37,
      50,    51,    52,    56,    61,    62,    66,    76,   105,   106,
       3,     3,   104,     3,    13,   104,   104,     3,    86,     3,
      65,     3,   104,     3,    13,   104,     3,     3,     3,     3,
      76,   107,    70,    19,    21,    23,    26,    30,    31,    34,
      35,    36,    65,    91,   107,    21,    26,    93,    94,    66,
       7,    88,    64,    64,    69,    84,    83,     3,     3,    73,
      66,    66,   105,   105,   105,   105,   105,   105,   105,   105,
     109,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    71,    75,     3,   104,     3,     3,    66,
      66,    90,     3,    90,   104,     3,    90,    69,    69,    73,
     107,   108,    69,    66,    91,    92,    66,    66,    66,    66,
      66,    66,    66,    64,    66,     5,    40,    69,    66,    66,
      28,    94,    72,   100,   101,   105,    64,   105,     4,   105,
      67,    76,    68,    77,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,    57,   105,   105,   105,   105,   105,     3,
      67,    72,   102,   103,   100,    64,    68,    90,    64,     3,
      90,    64,   105,   105,   105,    68,    77,   105,    57,    20,
      91,   105,   105,   107,     4,   105,     4,   105,   109,     4,
     109,   105,    64,   105,    30,    32,    33,   105,   105,    29,
       3,    67,    68,    87,    71,    74,    67,    68,    67,   109,
     105,   105,    74,    71,    64,     3,    67,    68,    67,     3,
      64,    90,    64,    64,    64,    71,    74,   107,    64,    67,
      67,    67,    69,    67,    67,    67,    67,    67,    67,    67,
      64,    66,    66,    66,    64,    67,     3,    66,   101,     7,
     105,     4,    77,   105,    66,    64,   103,     3,    64,   105,
      91,    91,    25,    97,    98,   105,   105,    64,    64,    64,
      64,    64,    64,    64,     4,   109,   109,    19,    88,    95,
      69,   105,    74,    67,    77,    67,   105,    66,    74,    22,
      71,    91,    24,    98,    68,    71,    64,    67,    67,    67,
      88,    96,   105,    67,    67,    67,   102,    91,    91,   105,
      91,   105,    64,    64,    64,    20,    88,    64,    64,    67,
      71,    64,   105,    64,    91,   107,    64,    69,     3,   105,
      69,    67,   105,    91,    67,    95
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    78,    79,    80,    80,    81,    81,    82,    82,    83,
      84,    84,    85,    85,    86,    86,    86,    87,    87,    87,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    92,    93,    93,    94,    94,    95,    95,
      96,    96,    97,    97,    98,    98,    98,    98,    99,   100,
     100,   101,   102,   102,   103,   103,   104,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   107,
     107,   107,   107,   108,   108,   109,   109
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     6,    10,     3,     1,     4,
       3,     0,     3,     1,     1,     1,     0,     2,     1,     0,
       2,     5,     4,     5,     4,     6,     4,     5,     5,     5,
       6,     2,    10,     6,     9,     5,     3,     2,     3,     2,
       3,     2,     4,     3,     4,     3,     4,     3,     4,     4,
       5,     3,     0,     3,     5,     7,     6,    13,     4,     4,
       5,     5,     2,     5,     3,     5,     5,     7,     7,     7,
       5,     5,     2,     1,     2,     1,    14,     5,     3,     1,
       2,     1,     2,     1,     3,     5,     3,     2,     4,     3,
       1,     5,     3,     1,     5,     4,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     3,
       5,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       6,     4,     3,     6,     3,     4,     6,     4,     1,     1,
       6,     4,     3,     3,     1,     3,     1
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
#line 87 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1771 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 4: /* module_list: module  */
#line 88 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1777 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 5: /* module: MODULE IDENTIFIER opt_port_list ';' module_items ENDMODULE  */
#line 93 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-4].str), yylineno);
        free((yyvsp[-4].str));
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) { addChild((yyval.node), c); } (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 1788 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 6: /* module: MODULE IDENTIFIER '#' '(' module_param_decls ')' opt_port_list ';' module_items ENDMODULE  */
#line 100 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-8].str), yylineno);
        free((yyvsp[-8].str));
        /* Add parameter declarations as children */
        if ((yyvsp[-5].node)) { for (auto *c : (yyvsp[-5].node)->children) addChild((yyval.node), c); (yyvsp[-5].node)->children.clear(); freeTree((yyvsp[-5].node)); }
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 1801 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 7: /* module_param_decls: module_param_decls ',' module_param_decl  */
#line 111 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                             { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1807 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 8: /* module_param_decls: module_param_decl  */
#line 112 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1813 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 9: /* module_param_decl: PARAMETER IDENTIFIER '=' expr  */
#line 117 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-2].str), yylineno); free((yyvsp[-2].str)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1819 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 10: /* opt_port_list: '(' port_list ')'  */
#line 121 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 1825 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 11: /* opt_port_list: %empty  */
#line 122 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = nullptr; }
#line 1831 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 12: /* port_list: port_list ',' port_decl_in_list  */
#line 126 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1837 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 13: /* port_list: port_decl_in_list  */
#line 127 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 1843 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 14: /* port_decl_in_list: IDENTIFIER  */
#line 131 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { free((yyvsp[0].str)); (yyval.node) = nullptr; }
#line 1849 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 15: /* port_decl_in_list: port_decl  */
#line 132 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1855 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 16: /* port_decl_in_list: %empty  */
#line 133 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = nullptr; }
#line 1861 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 17: /* module_items: module_items module_item  */
#line 137 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1867 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 18: /* module_items: module_item  */
#line 138 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1873 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 19: /* module_items: %empty  */
#line 139 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 1879 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 21: /* module_item: WIRE range IDENTIFIER decl_list ';'  */
#line 145 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 1885 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 22: /* module_item: WIRE IDENTIFIER decl_list ';'  */
#line 147 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 1891 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 23: /* module_item: REG range IDENTIFIER decl_list ';'  */
#line 149 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 1897 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 24: /* module_item: REG IDENTIFIER decl_list ';'  */
#line 151 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 1903 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 25: /* module_item: REG SIGNED range IDENTIFIER decl_list ';'  */
#line 153 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg signed", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 1909 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 26: /* module_item: INTEGER_KW IDENTIFIER decl_list ';'  */
#line 155 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "integer", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 31; (yyval.node)->lsb = 0; }
#line 1915 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 27: /* module_item: LOCALPARAM IDENTIFIER '=' expr ';'  */
#line 157 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1921 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 28: /* module_item: PARAMETER IDENTIFIER '=' expr ';'  */
#line 159 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1927 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 29: /* module_item: ASSIGN lvalue '=' expr ';'  */
#line 161 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ASSIGN, "", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1933 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 30: /* module_item: ALWAYS '@' '(' '*' ')' stmt  */
#line 163 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(*)", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1939 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 31: /* module_item: INITIAL_KW stmt  */
#line 165 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::INITIAL_BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1945 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 32: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' port_conn_list ')' ';'  */
#line 167 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-9].str), yylineno); free((yyvsp[-9].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 1951 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 33: /* module_item: IDENTIFIER IDENTIFIER '(' port_conn_list ')' ';'  */
#line 169 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-5].str), yylineno); free((yyvsp[-5].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 1957 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 34: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' ')' ';'  */
#line 171 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-8].str), yylineno); free((yyvsp[-8].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); }
#line 1963 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 35: /* module_item: IDENTIFIER IDENTIFIER '(' ')' ';'  */
#line 173 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-4].str), yylineno); free((yyvsp[-4].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); }
#line 1969 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 36: /* module_item: GENERATE gen_items ENDGENERATE  */
#line 174 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 1975 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 37: /* module_item: param_override ';'  */
#line 175 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1981 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 38: /* port_decl: INPUT range IDENTIFIER  */
#line 180 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 1993 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 39: /* port_decl: INPUT IDENTIFIER  */
#line 188 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2005 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 40: /* port_decl: OUTPUT range IDENTIFIER  */
#line 196 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2017 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 41: /* port_decl: OUTPUT IDENTIFIER  */
#line 204 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2029 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 42: /* port_decl: OUTPUT WIRE range IDENTIFIER  */
#line 212 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2041 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 43: /* port_decl: OUTPUT WIRE IDENTIFIER  */
#line 220 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2053 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 44: /* port_decl: INPUT WIRE range IDENTIFIER  */
#line 228 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2065 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 45: /* port_decl: INPUT WIRE IDENTIFIER  */
#line 236 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2077 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 46: /* port_decl: OUTPUT REG range IDENTIFIER  */
#line 244 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2089 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 47: /* port_decl: OUTPUT REG IDENTIFIER  */
#line 252 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2101 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 48: /* port_decl: OUTPUT SIGNED range IDENTIFIER  */
#line 260 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2113 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 49: /* port_decl: INPUT SIGNED range IDENTIFIER  */
#line 268 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2125 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 50: /* port_decl: OUTPUT REG SIGNED range IDENTIFIER  */
#line 276 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2137 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 51: /* decl_list: decl_list ',' IDENTIFIER  */
#line 286 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { free((yyvsp[0].str)); }
#line 2143 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 53: /* stmt: BEGINKW stmts END  */
#line 291 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 2149 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 54: /* stmt: IF '(' expr ')' stmt  */
#line 293 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2159 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 55: /* stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 299 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2170 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 56: /* stmt: CASE '(' expr ')' case_items ENDCASE  */
#line 306 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2180 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 57: /* stmt: FOR '(' lvalue '=' expr ';' expr ';' lvalue '=' expr ')' stmt  */
#line 312 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "", yylineno);
          addChild((yyval.node), (yyvsp[-10].node));  /* init lvalue */
          addChild((yyval.node), (yyvsp[-8].node));  /* init expr */
          addChild((yyval.node), (yyvsp[-6].node));  /* cond */
          addChild((yyval.node), (yyvsp[-4].node));  /* update lvalue */
          addChild((yyval.node), (yyvsp[-2].node)); /* update expr */
          addChild((yyval.node), (yyvsp[0].node)); /* body */
      }
#line 2194 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 58: /* stmt: lvalue '=' expr ';'  */
#line 322 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2204 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 59: /* stmt: lvalue LE expr ';'  */
#line 328 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2214 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 60: /* stmt: SYS_DISPLAY '(' expr_list ')' ';'  */
#line 334 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2225 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 61: /* stmt: SYS_DISPLAY '(' STRING ')' ';'  */
#line 341 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2235 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 62: /* stmt: SYS_FINISH ';'  */
#line 346 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); }
#line 2241 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 63: /* stmt: SYS_FINISH '(' expr ')' ';'  */
#line 347 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); addChild((yyval.node), (yyvsp[-2].node)); }
#line 2247 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 64: /* stmt: '#' NUMBER ';'  */
#line 349 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, std::to_string((yyvsp[-1].num)->value), yylineno);
          free((yyvsp[-1].num));
      }
#line 2256 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 65: /* stmt: SYS_FOPEN '(' STRING ')' ';'  */
#line 354 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2266 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 66: /* stmt: SYS_FCLOSE '(' expr ')' ';'  */
#line 360 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fclose", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
      }
#line 2275 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 67: /* stmt: lvalue '=' SYS_FOPEN '(' STRING ')' ';'  */
#line 365 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild(fc, makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          addChild((yyval.node), fc);
      }
#line 2288 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 68: /* stmt: lvalue '=' SYS_FSCANF '(' expr_list ')' ';'  */
#line 374 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fscanf", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2302 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 69: /* stmt: lvalue '=' SYS_FGETS '(' expr_list ')' ';'  */
#line 384 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fgets", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2316 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 70: /* stmt: SYS_FDISPLAY '(' expr_list ')' ';'  */
#line 394 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2327 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 71: /* stmt: SYS_FDISPLAY '(' STRING ')' ';'  */
#line 401 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2337 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 72: /* stmts: stmts stmt  */
#line 409 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2343 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 73: /* stmts: stmt  */
#line 410 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2349 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 74: /* gen_items: gen_items gen_item  */
#line 414 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2355 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 75: /* gen_items: gen_item  */
#line 415 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::GENERATE, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2361 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 76: /* gen_item: FOR '(' GENVAR IDENTIFIER '=' expr ';' expr ';' IDENTIFIER '=' expr ')' gen_block  */
#line 420 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2375 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 77: /* gen_item: IF '(' expr ')' gen_block  */
#line 430 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2385 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 78: /* gen_block: BEGINKW gen_body END  */
#line 438 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2391 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 79: /* gen_block: module_item  */
#line 439 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2397 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 80: /* gen_body: gen_body module_item  */
#line 443 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2403 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 81: /* gen_body: module_item  */
#line 444 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2409 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 82: /* case_items: case_items case_item  */
#line 448 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2415 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 83: /* case_items: case_item  */
#line 449 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2421 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 84: /* case_item: expr ':' stmt  */
#line 454 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2431 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 85: /* case_item: expr ',' expr ':' stmt  */
#line 460 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2442 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 86: /* case_item: DEFAULT ':' stmt  */
#line 467 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2451 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 87: /* case_item: DEFAULT stmt  */
#line 472 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2460 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 88: /* param_override: '#' '(' param_list ')'  */
#line 480 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    { (yyval.node) = makeNode(NodeType::PARAM_OVERRIDE, "", yylineno); }
#line 2466 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 91: /* param_assign: '.' IDENTIFIER '(' expr ')'  */
#line 489 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { free((yyvsp[-3].str)); }
#line 2472 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 92: /* port_conn_list: port_conn_list ',' port_conn  */
#line 493 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2478 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 93: /* port_conn_list: port_conn  */
#line 494 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2484 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 94: /* port_conn: '.' IDENTIFIER '(' expr ')'  */
#line 499 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2494 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 95: /* port_conn: '.' IDENTIFIER '(' ')'  */
#line 505 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-2].str), yylineno);
          free((yyvsp[-2].str));
      }
#line 2503 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 96: /* range: '[' expr ':' expr ']'  */
#line 513 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
          /* Evaluate constant range bounds */
          if ((yyvsp[-3].node)->type == NodeType::NUMBER) (yyval.node)->msb = std::stoi((yyvsp[-3].node)->value);
          if ((yyvsp[-1].node)->type == NodeType::NUMBER) (yyval.node)->lsb = std::stoi((yyvsp[-1].node)->value);
      }
#line 2516 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 97: /* expr: expr '+' expr  */
#line 524 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "+", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2522 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 98: /* expr: expr '-' expr  */
#line 525 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "-", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2528 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 99: /* expr: expr '*' expr  */
#line 526 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "*", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2534 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 100: /* expr: expr '/' expr  */
#line 527 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "/", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2540 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 101: /* expr: expr '%' expr  */
#line 528 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "%", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2546 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 102: /* expr: expr '&' expr  */
#line 529 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2552 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 103: /* expr: expr '|' expr  */
#line 530 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2558 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 104: /* expr: expr '^' expr  */
#line 531 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2564 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 105: /* expr: expr XNOR expr  */
#line 532 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2570 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 106: /* expr: expr NAND expr  */
#line 533 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2576 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 107: /* expr: expr NOR expr  */
#line 534 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2582 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 108: /* expr: expr EQ expr  */
#line 535 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "==", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2588 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 109: /* expr: expr NE expr  */
#line 536 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "!=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2594 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 110: /* expr: expr '<' expr  */
#line 537 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2600 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 111: /* expr: expr '>' expr  */
#line 538 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2606 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 112: /* expr: expr LE expr  */
#line 539 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2612 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 113: /* expr: expr GE expr  */
#line 540 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2618 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 114: /* expr: expr SHL expr  */
#line 541 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2624 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 115: /* expr: expr SHR expr  */
#line 542 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2630 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 116: /* expr: expr SSHR expr  */
#line 543 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2636 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 117: /* expr: expr '*' '*' expr  */
#line 544 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = makeNode(NodeType::BINOP, "**", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2642 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 118: /* expr: expr LOGAND expr  */
#line 545 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2648 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 119: /* expr: expr LOGOR expr  */
#line 546 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "||", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2654 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 120: /* expr: expr '?' expr ':' expr  */
#line 548 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::TERNARY, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));
      }
#line 2663 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 121: /* expr: '-' expr  */
#line 552 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "-", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2669 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 122: /* expr: '!' expr  */
#line 553 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "!", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2675 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 123: /* expr: '~' expr  */
#line 554 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2681 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 124: /* expr: '&' expr  */
#line 555 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "&", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2687 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 125: /* expr: '|' expr  */
#line 556 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "|", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2693 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 126: /* expr: '^' expr  */
#line 557 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "^", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2699 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 128: /* prim_expr: NUMBER  */
#line 563 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNum((yyvsp[0].num));
      }
#line 2707 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 129: /* prim_expr: IDENTIFIER  */
#line 567 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 2716 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 130: /* prim_expr: IDENTIFIER '[' expr ':' expr ']'  */
#line 572 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2727 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 131: /* prim_expr: IDENTIFIER '[' expr ']'  */
#line 579 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2737 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 132: /* prim_expr: '{' expr_list '}'  */
#line 585 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 2748 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 133: /* prim_expr: '{' expr '{' expr_list '}' '}'  */
#line 592 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
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
#line 2764 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 134: /* prim_expr: '(' expr ')'  */
#line 604 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2772 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 135: /* prim_expr: SYS_FOPEN '(' STRING ')'  */
#line 608 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
      }
#line 2782 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 136: /* prim_expr: SYS_FOPEN '(' STRING ',' STRING ')'  */
#line 614 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-3].str), yylineno));
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-3].str)); free((yyvsp[-1].str));
      }
#line 2793 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 137: /* prim_expr: SYS_CLOG2 '(' expr ')'  */
#line 621 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$clog2", yylineno);
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2802 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 138: /* prim_expr: STRING  */
#line 626 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::STRING, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 2811 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 139: /* lvalue: IDENTIFIER  */
#line 634 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 2820 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 140: /* lvalue: IDENTIFIER '[' expr ':' expr ']'  */
#line 639 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2831 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 141: /* lvalue: IDENTIFIER '[' expr ']'  */
#line 646 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2841 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 142: /* lvalue: '{' lvalue_list '}'  */
#line 652 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 2852 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 143: /* lvalue_list: lvalue_list ',' lvalue  */
#line 661 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2858 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 144: /* lvalue_list: lvalue  */
#line 662 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2864 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 145: /* expr_list: expr_list ',' expr  */
#line 666 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2870 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 146: /* expr_list: expr  */
#line 667 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2876 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;


#line 2880 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"

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

#line 670 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"


void yyerror(const char *msg) {
    fprintf(stderr, "Parse error at line %d: %s (token=%d)\n", yylineno, msg, yychar);
}

extern int yydebug;
std::vector<ASTNode *> parseFiles(const std::vector<std::string> &files) {
    g_modules.clear();
    for (auto &f : files) {
        yylineno = 1;
        yyin = fopen(f.c_str(), "r");
        if (!yyin) {
            fprintf(stderr, "Cannot open %s\n", f.c_str());
            continue;
        }
        yyparse();
        fclose(yyin);
    }
    return g_modules;
}
