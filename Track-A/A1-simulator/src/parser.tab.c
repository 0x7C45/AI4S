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
  YYSYMBOL_60_ = 60,                       /* '!'  */
  YYSYMBOL_61_ = 61,                       /* '~'  */
  YYSYMBOL_UNARY = 62,                     /* UNARY  */
  YYSYMBOL_63_ = 63,                       /* ';'  */
  YYSYMBOL_64_ = 64,                       /* '('  */
  YYSYMBOL_65_ = 65,                       /* ')'  */
  YYSYMBOL_66_ = 66,                       /* ','  */
  YYSYMBOL_67_ = 67,                       /* '='  */
  YYSYMBOL_68_ = 68,                       /* '@'  */
  YYSYMBOL_69_ = 69,                       /* '#'  */
  YYSYMBOL_70_ = 70,                       /* ':'  */
  YYSYMBOL_71_ = 71,                       /* '.'  */
  YYSYMBOL_72_ = 72,                       /* '['  */
  YYSYMBOL_73_ = 73,                       /* ']'  */
  YYSYMBOL_74_ = 74,                       /* '?'  */
  YYSYMBOL_75_ = 75,                       /* '{'  */
  YYSYMBOL_76_ = 76,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_source = 78,                    /* source  */
  YYSYMBOL_module_list = 79,               /* module_list  */
  YYSYMBOL_module = 80,                    /* module  */
  YYSYMBOL_opt_port_list = 81,             /* opt_port_list  */
  YYSYMBOL_port_list = 82,                 /* port_list  */
  YYSYMBOL_port_decl_in_list = 83,         /* port_decl_in_list  */
  YYSYMBOL_module_items = 84,              /* module_items  */
  YYSYMBOL_module_item = 85,               /* module_item  */
  YYSYMBOL_port_decl = 86,                 /* port_decl  */
  YYSYMBOL_decl_list = 87,                 /* decl_list  */
  YYSYMBOL_stmt = 88,                      /* stmt  */
  YYSYMBOL_stmts = 89,                     /* stmts  */
  YYSYMBOL_gen_items = 90,                 /* gen_items  */
  YYSYMBOL_gen_item = 91,                  /* gen_item  */
  YYSYMBOL_gen_block = 92,                 /* gen_block  */
  YYSYMBOL_gen_body = 93,                  /* gen_body  */
  YYSYMBOL_case_items = 94,                /* case_items  */
  YYSYMBOL_case_item = 95,                 /* case_item  */
  YYSYMBOL_param_override = 96,            /* param_override  */
  YYSYMBOL_param_list = 97,                /* param_list  */
  YYSYMBOL_param_assign = 98,              /* param_assign  */
  YYSYMBOL_port_conn_list = 99,            /* port_conn_list  */
  YYSYMBOL_port_conn = 100,                /* port_conn  */
  YYSYMBOL_range = 101,                    /* range  */
  YYSYMBOL_expr = 102,                     /* expr  */
  YYSYMBOL_prim_expr = 103,                /* prim_expr  */
  YYSYMBOL_lvalue = 104,                   /* lvalue  */
  YYSYMBOL_lvalue_list = 105,              /* lvalue_list  */
  YYSYMBOL_expr_list = 106                 /* expr_list  */
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
#define YYLAST   1820

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  376

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
       2,     2,     2,    60,     2,    69,     2,    59,    52,     2,
      64,    65,    57,    55,    66,    56,    71,    58,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    70,    63,
      53,    67,    54,    74,    68,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,    50,    76,    61,     2,     2,     2,
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
      45,    46,    47,    48,    49,    62
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    85,    86,    90,   100,   101,   105,   106,
     110,   111,   112,   116,   117,   118,   122,   123,   125,   127,
     129,   131,   133,   135,   137,   139,   141,   143,   145,   147,
     149,   151,   153,   154,   158,   166,   174,   182,   190,   198,
     206,   214,   222,   233,   234,   238,   239,   245,   252,   258,
     268,   274,   280,   287,   293,   294,   295,   300,   306,   311,
     320,   330,   340,   347,   356,   357,   361,   362,   366,   376,
     385,   386,   390,   391,   395,   396,   400,   406,   413,   418,
     426,   431,   432,   436,   440,   441,   445,   451,   459,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   498,   499,   500,   501,   502,   503,   504,   508,
     512,   517,   524,   530,   537,   541,   547,   554,   559,   567,
     572,   579,   585,   595,   596,   600,   601
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
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'~'", "UNARY", "';'",
  "'('", "')'", "','", "'='", "'@'", "'#'", "':'", "'.'", "'['", "']'",
  "'?'", "'{'", "'}'", "$accept", "source", "module_list", "module",
  "opt_port_list", "port_list", "port_decl_in_list", "module_items",
  "module_item", "port_decl", "decl_list", "stmt", "stmts", "gen_items",
  "gen_item", "gen_block", "gen_body", "case_items", "case_item",
  "param_override", "param_list", "param_assign", "port_conn_list",
  "port_conn", "range", "expr", "prim_expr", "lvalue", "lvalue_list",
  "expr_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-154)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      46,    68,    67,    46,  -154,    25,  -154,  -154,    54,    28,
    -154,    14,     3,   -43,  -154,  -154,   154,  -154,     7,   305,
     118,  -154,    15,     7,   140,  -154,    54,     5,    16,    48,
     142,   144,   164,     2,   107,   421,    -1,    29,   451,  -154,
     126,   135,   179,   132,  -154,  -154,   150,   151,   305,   305,
     305,   305,   305,   305,   305,   305,   626,  -154,  -154,  -154,
       7,   205,   216,  -154,  -154,   158,   161,  -154,   228,  -154,
       7,   232,  -154,   169,   172,   170,     2,   173,   180,   421,
     181,   182,   184,   196,   197,   198,   202,    72,   262,  -154,
     -25,   204,   206,    64,  -154,   201,  -154,  -154,  -154,  -154,
    -154,   305,   271,   305,   207,   207,   207,   207,   207,   207,
     663,  1588,   -40,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   275,  -154,  -154,
     -28,   201,    10,  -154,    56,   276,  -154,    60,   305,   305,
     305,  -154,   -10,   305,   223,  -154,   157,   305,   305,     2,
     278,   305,   355,   371,  -154,   305,   220,   305,     8,   305,
     257,  -154,  -154,   284,    90,  -154,   515,    93,   700,  -154,
     305,  -154,  1741,  1741,  1746,  1746,  1650,  1619,    -9,    -9,
      -9,  1719,  1719,  1697,  1674,  1697,  1719,  1746,  1746,    -4,
      -4,   207,   207,   207,   737,   774,  -154,   227,   288,   119,
    -154,   129,  -154,   293,    62,  -154,  -154,    74,  -154,   811,
     848,   552,     2,  -154,   885,   233,  -154,  -154,   922,   959,
     230,   235,   996,   236,   137,   238,   141,  1033,  -154,  1070,
     241,   242,   243,  1107,  1144,   308,   248,  -154,   201,   305,
    -154,  -154,   309,  -154,  1588,  -154,   305,  -154,   250,   253,
     247,   317,  -154,  -154,    78,  -154,  -154,  -154,   305,  -154,
    -154,  -154,   421,   421,   213,   305,   258,   259,   260,   261,
     265,   267,   268,  -154,   321,   305,   305,  -154,   483,   266,
     305,  -154,  1181,   269,  1588,   289,  -154,  -154,   272,  -154,
    1218,  -154,   310,   368,   149,  -154,   589,  1255,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,   146,   155,   163,   154,  -154,
    -154,   305,  1292,  -154,  -154,  -154,  1329,    53,  -154,   421,
     421,  -154,  -154,  -154,   305,   421,   305,   274,   280,   281,
    -154,   513,  1366,  -154,  -154,   283,   168,  -154,  -154,  1403,
    -154,  1440,  -154,  -154,  -154,  -154,  -154,   305,  -154,   299,
     421,     2,  1477,  -154,  -154,   285,   344,   305,   296,  1514,
     305,   421,  1551,  -154,   483,  -154
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,     7,     1,     3,    12,     0,
      10,     0,     0,     0,     9,    11,    15,    35,     0,     0,
       0,    37,     0,     0,     0,     6,    12,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,     0,     0,   120,   128,   119,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   118,    34,    39,
       0,     0,     0,    36,     8,     0,     0,    44,     0,    44,
       0,     0,    44,     0,     0,   129,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
       0,     0,     0,     0,    67,     0,     5,    13,    16,    33,
      41,     0,     0,     0,   116,   117,   115,   112,   113,   114,
       0,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    40,
       0,     0,     0,    44,     0,     0,    44,     0,     0,     0,
       0,   134,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
       0,    32,    66,     0,     0,    82,     0,     0,     0,   124,
       0,   123,   100,   101,   104,   105,   109,   110,   106,   107,
     108,    98,    99,    97,    95,    96,    94,   102,   103,    89,
      90,    91,    92,    93,     0,     0,    42,     0,     0,     0,
      85,     0,    18,     0,     0,    20,    44,     0,    22,     0,
       0,     0,     0,   132,     0,     0,    45,    64,     0,     0,
       0,     0,     0,   128,     0,   128,     0,     0,    56,     0,
       0,     0,     0,     0,     0,     0,     0,    80,     0,     0,
     122,   125,     0,   127,   135,    88,     0,    31,     0,     0,
       0,     0,    43,    17,     0,    19,    23,    24,     0,   131,
     133,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,    50,     0,     0,
       0,    81,     0,     0,   111,     0,    29,    84,     0,    21,
       0,    26,    46,     0,     0,    75,     0,     0,    57,    58,
      63,    62,    53,    52,    55,     0,     0,     0,     0,    71,
      69,     0,     0,   121,   126,    87,     0,     0,   130,     0,
       0,    79,    48,    74,     0,     0,     0,   125,     0,     0,
      73,     0,     0,    83,    86,     0,     0,    47,    78,     0,
      76,     0,    59,    60,    61,    70,    72,     0,    30,     0,
       0,     0,     0,    28,    77,     0,     0,     0,     0,     0,
       0,     0,     0,    49,     0,    68
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,  -154,  -154,   364,  -154,  -154,   342,  -154,   -14,    13,
     -65,   -76,  -154,  -154,   277,    -2,  -154,  -154,    69,  -154,
     237,   131,    50,   121,   229,   -19,  -154,   -32,  -154,  -153
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     4,     9,    13,    14,    38,   319,    40,
     142,    89,   156,    93,    94,   320,   341,   304,   305,    41,
     174,   175,   209,   210,    20,   111,    57,    90,   152,   112
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    77,    39,   155,   144,    75,    21,   147,    65,   234,
     236,    43,    44,    45,    22,   167,    23,    17,    59,    67,
      91,    15,    25,    26,    97,    92,   180,    18,    60,   104,
     105,   106,   107,   108,   109,   110,   181,   207,   240,    15,
     241,   242,   168,   208,   151,    47,   130,   131,   132,   133,
     134,    69,     1,   132,   133,   134,   222,    10,    48,    49,
      50,    70,    11,    12,    51,   136,   223,     6,    52,    53,
     136,     5,    54,   212,    66,    19,   213,    76,   214,    19,
     227,   217,   176,    55,   178,    91,    19,    19,    19,     8,
      92,    16,   171,    95,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   345,   215,
      19,    58,   213,   218,   208,   263,   213,   230,   213,   219,
     220,   221,   316,   317,   224,   164,   165,   265,   228,   229,
     213,   299,   232,    63,   213,    72,   237,    73,   239,   243,
     244,   264,    43,    44,    45,   247,   248,    27,   251,   252,
      75,   254,    11,    12,    28,    29,    30,    74,    31,    32,
      33,    34,    35,   332,   303,    78,    79,   226,    80,    46,
      81,    36,   100,    82,   259,   260,    47,    83,    84,    98,
     270,    85,    86,    87,   261,   248,   301,   302,    99,    48,
      49,    50,   279,   180,   101,    51,   281,   180,   138,    52,
      53,   337,   252,    54,   102,   103,    43,    44,    45,   139,
     338,   180,   140,    37,    55,   141,    88,   331,   339,   180,
     292,   143,    76,   359,   260,   146,   148,   294,   303,   149,
     153,    24,   150,    46,   154,   157,   158,    42,   159,   300,
      47,    61,    62,   347,   348,   306,   307,    68,    71,   350,
     160,   161,   162,    48,    49,    50,   163,   166,   169,    51,
     170,   322,   173,    52,    53,   177,   326,    54,   206,   216,
     225,   136,   231,   238,   364,   306,   245,   246,    55,   137,
     257,   258,    43,    44,    45,   373,   262,   275,   272,   145,
     276,   278,   342,   280,   340,   284,   285,   286,    43,    44,
      45,   289,   290,   293,   295,   349,   296,   351,   208,    46,
     298,   308,   309,   310,   311,   315,    47,   356,   312,   365,
     313,   314,   329,   321,   324,    46,   327,   352,   362,    48,
      49,    50,    47,   353,   354,    51,   358,   368,   369,    52,
      53,   372,   367,    54,   325,    48,    49,    50,    43,   233,
      45,    51,   363,   370,    55,    52,    53,     7,    64,    54,
     172,    75,   375,   333,    43,   235,    45,   346,   211,   291,
      55,   297,     0,     0,     0,    46,     0,    79,     0,    80,
       0,    81,    47,     0,    82,     0,     0,     0,    83,    84,
       0,    46,    85,    86,    87,    48,    49,    50,    47,     0,
       0,    51,     0,     0,     0,    52,    53,     0,     0,    54,
       0,    48,    49,    50,    75,     0,     0,    51,     0,     0,
      55,    52,    53,     0,     0,    54,     0,    88,   330,     0,
      79,     0,    80,    76,    81,     0,    55,    82,     0,     0,
       0,    83,    84,     0,    27,    85,    86,    87,    96,    11,
      12,    28,    29,    30,     0,    31,    32,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,    27,     0,     0,     0,
      88,    11,    12,    28,    29,    30,    76,    31,    32,    33,
      34,    35,   318,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,    27,     0,     0,     0,
      37,    11,    12,    28,    29,    30,     0,    31,    32,    33,
      34,    35,     0,   355,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,     0,     0,     0,     0,     0,
       0,     0,    37,     0,     0,   249,     0,     0,   250,   136,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   268,     0,     0,   269,   136,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,     0,
       0,     0,     0,     0,     0,   334,     0,     0,     0,   335,
       0,     0,     0,   136,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,     0,     0,     0,
     136,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,     0,     0,     0,     0,     0,   179,     0,
       0,     0,     0,     0,     0,     0,     0,   136,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
       0,     0,     0,     0,     0,   253,     0,     0,     0,     0,
       0,     0,     0,     0,   136,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     255,   136,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   256,     0,     0,     0,   136,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,     0,     0,     0,   266,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,     0,     0,
       0,   267,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   136,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,     0,     0,     0,   271,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   136,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,     0,     0,     0,     0,     0,   273,     0,     0,
       0,     0,     0,     0,     0,     0,   136,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,     0,
       0,     0,     0,     0,   274,     0,     0,     0,     0,     0,
       0,     0,     0,   136,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,     0,     0,     0,     0,
       0,   277,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,     0,     0,     0,     0,     0,   282,     0,
       0,     0,     0,     0,     0,     0,     0,   136,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
       0,     0,     0,   283,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   136,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,     0,     0,     0,
     287,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   136,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,     0,     0,     0,     0,     0,   288,
       0,     0,     0,     0,     0,     0,     0,     0,   136,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   323,   136,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   328,   136,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,     0,     0,     0,   336,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   136,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,     0,     0,     0,     0,     0,   343,     0,     0,
       0,     0,     0,     0,     0,     0,   136,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,     0,
       0,     0,     0,     0,   344,     0,     0,     0,     0,     0,
       0,     0,     0,   136,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,     0,     0,     0,   357,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   360,     0,     0,     0,   136,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
       0,     0,     0,   361,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   136,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,     0,     0,     0,
     366,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   136,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,     0,     0,     0,     0,     0,   371,
       0,     0,     0,     0,     0,     0,     0,     0,   136,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,     0,     0,     0,     0,     0,   374,     0,     0,     0,
       0,     0,     0,     0,     0,   136,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   136,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
     115,   116,     0,   136,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
       0,     0,   113,   114,   115,   116,     0,     0,   119,   120,
     121,   122,   123,   124,   136,   126,   127,   128,   129,   130,
     131,   132,   133,   134,     0,   113,   114,   115,   116,     0,
       0,   119,   120,   121,   122,   123,     0,     0,   136,   127,
     128,   129,   130,   131,   132,   133,   134,   113,   114,   115,
     116,     0,     0,   119,   120,   121,     0,     0,     0,     0,
       0,   136,   128,   129,   130,   131,   132,   133,   134,     0,
       0,   115,   116,     0,     0,   119,   120,   121,     0,     0,
     119,   120,   121,   136,   128,   129,   130,   131,   132,   133,
     134,   130,   131,   132,   133,   134,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,     0,     0,     0,     0,
     136
};

static const yytype_int16 yycheck[] =
{
      19,    33,    16,    79,    69,     3,     3,    72,     3,   162,
     163,     3,     4,     5,    11,    40,    13,     3,     3,     3,
      21,     8,    65,    66,    38,    26,    66,    13,    13,    48,
      49,    50,    51,    52,    53,    54,    76,    65,    30,    26,
      32,    33,    67,    71,    76,    37,    55,    56,    57,    58,
      59,     3,     6,    57,    58,    59,    66,     3,    50,    51,
      52,    13,     8,     9,    56,    74,    76,     0,    60,    61,
      74,     3,    64,    63,    69,    72,    66,    75,   143,    72,
     156,   146,   101,    75,   103,    21,    72,    72,    72,    64,
      26,    63,    28,    64,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,    65,    63,
      72,     3,    66,    63,    71,    63,    66,   159,    66,   148,
     149,   150,   285,   286,   153,    63,    64,    63,   157,   158,
      66,    63,   161,     3,    66,     3,   165,     3,   167,   168,
     169,   216,     3,     4,     5,    65,    66,     3,    65,    66,
       3,   180,     8,     9,    10,    11,    12,     3,    14,    15,
      16,    17,    18,    24,    25,    68,    19,    20,    21,    30,
      23,    27,     3,    26,    65,    66,    37,    30,    31,    63,
     222,    34,    35,    36,    65,    66,   272,   273,    63,    50,
      51,    52,    65,    66,    72,    56,    65,    66,     3,    60,
      61,    65,    66,    64,    64,    64,     3,     4,     5,     3,
      65,    66,    64,    69,    75,    64,    69,   303,    65,    66,
     249,     3,    75,    65,    66,     3,    67,   256,    25,    67,
      67,    12,    72,    30,    64,    64,    64,    18,    64,   268,
      37,    22,    23,   329,   330,   274,   275,    28,    29,   335,
      64,    64,    64,    50,    51,    52,    64,     5,    64,    56,
      64,   290,    71,    60,    61,     4,   295,    64,     3,     3,
      57,    74,     4,    63,   360,   304,    29,     3,    75,    60,
      63,     3,     3,     4,     5,   371,     3,    67,    65,    70,
      65,    65,   321,    65,   318,    64,    64,    64,     3,     4,
       5,     3,    64,     4,    64,   334,    63,   336,    71,    30,
       3,    63,    63,    63,    63,     4,    37,   341,    63,   361,
      63,    63,    22,    67,    65,    30,    64,    63,   357,    50,
      51,    52,    37,    63,    63,    56,    63,     3,   367,    60,
      61,   370,    67,    64,    65,    50,    51,    52,     3,     4,
       5,    56,    63,    67,    75,    60,    61,     3,    26,    64,
      93,     3,   374,   304,     3,     4,     5,   327,   141,   248,
      75,   260,    -1,    -1,    -1,    30,    -1,    19,    -1,    21,
      -1,    23,    37,    -1,    26,    -1,    -1,    -1,    30,    31,
      -1,    30,    34,    35,    36,    50,    51,    52,    37,    -1,
      -1,    56,    -1,    -1,    -1,    60,    61,    -1,    -1,    64,
      -1,    50,    51,    52,     3,    -1,    -1,    56,    -1,    -1,
      75,    60,    61,    -1,    -1,    64,    -1,    69,    70,    -1,
      19,    -1,    21,    75,    23,    -1,    75,    26,    -1,    -1,
      -1,    30,    31,    -1,     3,    34,    35,    36,     7,     8,
       9,    10,    11,    12,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,
      69,     8,     9,    10,    11,    12,    75,    14,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,
      69,     8,     9,    10,    11,    12,    -1,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    -1,    -1,    70,    -1,    -1,    73,    74,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    73,    74,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    70,
      -1,    -1,    -1,    74,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      74,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    74,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    74,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    74,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    -1,    74,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    38,    39,    40,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    74,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    38,    39,    40,    41,    -1,
      -1,    44,    45,    46,    47,    48,    -1,    -1,    74,    52,
      53,    54,    55,    56,    57,    58,    59,    38,    39,    40,
      41,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    74,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    40,    41,    -1,    -1,    44,    45,    46,    -1,    -1,
      44,    45,    46,    74,    53,    54,    55,    56,    57,    58,
      59,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    78,    79,    80,     3,     0,    80,    64,    81,
       3,     8,     9,    82,    83,    86,    63,     3,    13,    72,
     101,     3,    11,    13,   101,    65,    66,     3,    10,    11,
      12,    14,    15,    16,    17,    18,    27,    69,    84,    85,
      86,    96,   101,     3,     4,     5,    30,    37,    50,    51,
      52,    56,    60,    61,    64,    75,   102,   103,     3,     3,
      13,   101,   101,     3,    83,     3,    69,     3,   101,     3,
      13,   101,     3,     3,     3,     3,    75,   104,    68,    19,
      21,    23,    26,    30,    31,    34,    35,    36,    69,    88,
     104,    21,    26,    90,    91,    64,     7,    85,    63,    63,
       3,    72,    64,    64,   102,   102,   102,   102,   102,   102,
     102,   102,   106,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    70,    74,   101,     3,     3,
      64,    64,    87,     3,    87,   101,     3,    87,    67,    67,
      72,   104,   105,    67,    64,    88,    89,    64,    64,    64,
      64,    64,    64,    64,    63,    64,     5,    40,    67,    64,
      64,    28,    91,    71,    97,    98,   102,     4,   102,    65,
      66,    76,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,     3,    65,    71,    99,
     100,    97,    63,    66,    87,    63,     3,    87,    63,   102,
     102,   102,    66,    76,   102,    57,    20,    88,   102,   102,
     104,     4,   102,     4,   106,     4,   106,   102,    63,   102,
      30,    32,    33,   102,   102,    29,     3,    65,    66,    70,
      73,    65,    66,    65,   102,    73,    70,    63,     3,    65,
      66,    65,     3,    63,    87,    63,    63,    63,    70,    73,
     104,    63,    65,    65,    65,    67,    65,    65,    65,    65,
      65,    65,    65,    63,    64,    64,    64,    63,    65,     3,
      64,    98,   102,     4,   102,    64,    63,   100,     3,    63,
     102,    88,    88,    25,    94,    95,   102,   102,    63,    63,
      63,    63,    63,    63,    63,     4,   106,   106,    19,    85,
      92,    67,   102,    73,    65,    65,   102,    64,    73,    22,
      70,    88,    24,    95,    66,    70,    63,    65,    65,    65,
      85,    93,   102,    65,    65,    65,    99,    88,    88,   102,
      88,   102,    63,    63,    63,    20,    85,    63,    63,    65,
      70,    63,   102,    63,    88,   104,    63,    67,     3,   102,
      67,    65,   102,    88,    65,    92
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    77,    78,    79,    79,    80,    81,    81,    82,    82,
      83,    83,    83,    84,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    89,    89,    90,    90,    91,    91,
      92,    92,    93,    93,    94,    94,    95,    95,    95,    95,
      96,    97,    97,    98,    99,    99,   100,   100,   101,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   104,
     104,   104,   104,   105,   105,   106,   106
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     6,     3,     0,     3,     1,
       1,     1,     0,     2,     1,     0,     2,     5,     4,     5,
       4,     6,     4,     5,     5,     5,     6,     2,    10,     6,
       9,     5,     3,     2,     3,     2,     3,     2,     4,     3,
       4,     4,     5,     3,     0,     3,     5,     7,     6,    13,
       4,     4,     5,     5,     2,     5,     3,     5,     5,     7,
       7,     7,     5,     5,     2,     1,     2,     1,    14,     5,
       3,     1,     2,     1,     2,     1,     3,     5,     3,     2,
       4,     3,     1,     5,     3,     1,     5,     4,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     6,     4,     3,     3,     4,     6,     4,     1,     1,
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
#line 85 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1720 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 4: /* module_list: module  */
#line 86 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1726 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 5: /* module: MODULE IDENTIFIER opt_port_list ';' module_items ENDMODULE  */
#line 91 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-4].str), yylineno);
        free((yyvsp[-4].str));
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) { addChild((yyval.node), c); } (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 1737 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 6: /* opt_port_list: '(' port_list ')'  */
#line 100 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 1743 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 7: /* opt_port_list: %empty  */
#line 101 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = nullptr; }
#line 1749 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 8: /* port_list: port_list ',' port_decl_in_list  */
#line 105 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1755 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 9: /* port_list: port_decl_in_list  */
#line 106 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 1761 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 10: /* port_decl_in_list: IDENTIFIER  */
#line 110 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { free((yyvsp[0].str)); (yyval.node) = nullptr; }
#line 1767 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 11: /* port_decl_in_list: port_decl  */
#line 111 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1773 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 12: /* port_decl_in_list: %empty  */
#line 112 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = nullptr; }
#line 1779 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 13: /* module_items: module_items module_item  */
#line 116 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1785 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 14: /* module_items: module_item  */
#line 117 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1791 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 15: /* module_items: %empty  */
#line 118 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 1797 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 17: /* module_item: WIRE range IDENTIFIER decl_list ';'  */
#line 124 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 1803 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 18: /* module_item: WIRE IDENTIFIER decl_list ';'  */
#line 126 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 1809 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 19: /* module_item: REG range IDENTIFIER decl_list ';'  */
#line 128 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 1815 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 20: /* module_item: REG IDENTIFIER decl_list ';'  */
#line 130 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 1821 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 21: /* module_item: REG SIGNED range IDENTIFIER decl_list ';'  */
#line 132 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg signed", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 1827 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 22: /* module_item: INTEGER_KW IDENTIFIER decl_list ';'  */
#line 134 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "integer", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 31; (yyval.node)->lsb = 0; }
#line 1833 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 23: /* module_item: LOCALPARAM IDENTIFIER '=' expr ';'  */
#line 136 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1839 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 24: /* module_item: PARAMETER IDENTIFIER '=' expr ';'  */
#line 138 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1845 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 25: /* module_item: ASSIGN lvalue '=' expr ';'  */
#line 140 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ASSIGN, "", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1851 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 26: /* module_item: ALWAYS '@' '(' '*' ')' stmt  */
#line 142 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(*)", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1857 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 27: /* module_item: INITIAL_KW stmt  */
#line 144 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::INITIAL_BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1863 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 28: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' port_conn_list ')' ';'  */
#line 146 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-9].str), yylineno); free((yyvsp[-9].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 1869 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 29: /* module_item: IDENTIFIER IDENTIFIER '(' port_conn_list ')' ';'  */
#line 148 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-5].str), yylineno); free((yyvsp[-5].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 1875 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 30: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' ')' ';'  */
#line 150 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-8].str), yylineno); free((yyvsp[-8].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); }
#line 1881 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 31: /* module_item: IDENTIFIER IDENTIFIER '(' ')' ';'  */
#line 152 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-4].str), yylineno); free((yyvsp[-4].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); }
#line 1887 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 32: /* module_item: GENERATE gen_items ENDGENERATE  */
#line 153 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 1893 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 33: /* module_item: param_override ';'  */
#line 154 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1899 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 34: /* port_decl: INPUT range IDENTIFIER  */
#line 159 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 1911 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 35: /* port_decl: INPUT IDENTIFIER  */
#line 167 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 1923 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 36: /* port_decl: OUTPUT range IDENTIFIER  */
#line 175 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 1935 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 37: /* port_decl: OUTPUT IDENTIFIER  */
#line 183 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 1947 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 38: /* port_decl: OUTPUT REG range IDENTIFIER  */
#line 191 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 1959 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 39: /* port_decl: OUTPUT REG IDENTIFIER  */
#line 199 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 1971 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 40: /* port_decl: OUTPUT SIGNED range IDENTIFIER  */
#line 207 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 1983 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 41: /* port_decl: INPUT SIGNED range IDENTIFIER  */
#line 215 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 1995 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 42: /* port_decl: OUTPUT REG SIGNED range IDENTIFIER  */
#line 223 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2007 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 43: /* decl_list: decl_list ',' IDENTIFIER  */
#line 233 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { free((yyvsp[0].str)); }
#line 2013 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 45: /* stmt: BEGINKW stmts END  */
#line 238 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 2019 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 46: /* stmt: IF '(' expr ')' stmt  */
#line 240 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2029 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 47: /* stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 246 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2040 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 48: /* stmt: CASE '(' expr ')' case_items ENDCASE  */
#line 253 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2050 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 49: /* stmt: FOR '(' lvalue '=' expr ';' expr ';' lvalue '=' expr ')' stmt  */
#line 259 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "", yylineno);
          addChild((yyval.node), (yyvsp[-10].node));  /* init lvalue */
          addChild((yyval.node), (yyvsp[-8].node));  /* init expr */
          addChild((yyval.node), (yyvsp[-6].node));  /* cond */
          addChild((yyval.node), (yyvsp[-4].node));  /* update lvalue */
          addChild((yyval.node), (yyvsp[-2].node)); /* update expr */
          addChild((yyval.node), (yyvsp[0].node)); /* body */
      }
#line 2064 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 50: /* stmt: lvalue '=' expr ';'  */
#line 269 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2074 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 51: /* stmt: lvalue LE expr ';'  */
#line 275 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2084 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 52: /* stmt: SYS_DISPLAY '(' expr_list ')' ';'  */
#line 281 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2095 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 53: /* stmt: SYS_DISPLAY '(' STRING ')' ';'  */
#line 288 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2105 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 54: /* stmt: SYS_FINISH ';'  */
#line 293 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); }
#line 2111 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 55: /* stmt: SYS_FINISH '(' expr ')' ';'  */
#line 294 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); addChild((yyval.node), (yyvsp[-2].node)); }
#line 2117 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 56: /* stmt: '#' NUMBER ';'  */
#line 296 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, std::to_string((yyvsp[-1].num)->value), yylineno);
          free((yyvsp[-1].num));
      }
#line 2126 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 57: /* stmt: SYS_FOPEN '(' STRING ')' ';'  */
#line 301 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2136 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 58: /* stmt: SYS_FCLOSE '(' expr ')' ';'  */
#line 307 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fclose", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
      }
#line 2145 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 59: /* stmt: lvalue '=' SYS_FOPEN '(' STRING ')' ';'  */
#line 312 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild(fc, makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          addChild((yyval.node), fc);
      }
#line 2158 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 60: /* stmt: lvalue '=' SYS_FSCANF '(' expr_list ')' ';'  */
#line 321 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fscanf", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2172 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 61: /* stmt: lvalue '=' SYS_FGETS '(' expr_list ')' ';'  */
#line 331 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fgets", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2186 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 62: /* stmt: SYS_FDISPLAY '(' expr_list ')' ';'  */
#line 341 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2197 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 63: /* stmt: SYS_FDISPLAY '(' STRING ')' ';'  */
#line 348 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2207 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 64: /* stmts: stmts stmt  */
#line 356 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2213 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 65: /* stmts: stmt  */
#line 357 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2219 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 66: /* gen_items: gen_items gen_item  */
#line 361 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2225 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 67: /* gen_items: gen_item  */
#line 362 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::GENERATE, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2231 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 68: /* gen_item: FOR '(' GENVAR IDENTIFIER '=' expr ';' expr ';' IDENTIFIER '=' expr ')' gen_block  */
#line 367 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2245 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 69: /* gen_item: IF '(' expr ')' gen_block  */
#line 377 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2255 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 70: /* gen_block: BEGINKW gen_body END  */
#line 385 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2261 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 71: /* gen_block: module_item  */
#line 386 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2267 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 72: /* gen_body: gen_body module_item  */
#line 390 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2273 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 73: /* gen_body: module_item  */
#line 391 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2279 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 74: /* case_items: case_items case_item  */
#line 395 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2285 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 75: /* case_items: case_item  */
#line 396 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2291 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 76: /* case_item: expr ':' stmt  */
#line 401 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2301 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 77: /* case_item: expr ',' expr ':' stmt  */
#line 407 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2312 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 78: /* case_item: DEFAULT ':' stmt  */
#line 414 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2321 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 79: /* case_item: DEFAULT stmt  */
#line 419 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2330 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 80: /* param_override: '#' '(' param_list ')'  */
#line 427 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    { (yyval.node) = makeNode(NodeType::PARAM_OVERRIDE, "", yylineno); }
#line 2336 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 83: /* param_assign: '.' IDENTIFIER '(' expr ')'  */
#line 436 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { free((yyvsp[-3].str)); }
#line 2342 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 84: /* port_conn_list: port_conn_list ',' port_conn  */
#line 440 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2348 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 85: /* port_conn_list: port_conn  */
#line 441 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2354 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 86: /* port_conn: '.' IDENTIFIER '(' expr ')'  */
#line 446 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2364 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 87: /* port_conn: '.' IDENTIFIER '(' ')'  */
#line 452 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-2].str), yylineno);
          free((yyvsp[-2].str));
      }
#line 2373 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 88: /* range: '[' expr ':' expr ']'  */
#line 460 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
          /* Evaluate constant range bounds */
          if ((yyvsp[-3].node)->type == NodeType::NUMBER) (yyval.node)->msb = std::stoi((yyvsp[-3].node)->value);
          if ((yyvsp[-1].node)->type == NodeType::NUMBER) (yyval.node)->lsb = std::stoi((yyvsp[-1].node)->value);
      }
#line 2386 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 89: /* expr: expr '+' expr  */
#line 471 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "+", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2392 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 90: /* expr: expr '-' expr  */
#line 472 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "-", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2398 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 91: /* expr: expr '*' expr  */
#line 473 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "*", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2404 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 92: /* expr: expr '/' expr  */
#line 474 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "/", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2410 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 93: /* expr: expr '%' expr  */
#line 475 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "%", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2416 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 94: /* expr: expr '&' expr  */
#line 476 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2422 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 95: /* expr: expr '|' expr  */
#line 477 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2428 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 96: /* expr: expr '^' expr  */
#line 478 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2434 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 97: /* expr: expr XNOR expr  */
#line 479 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2440 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 98: /* expr: expr NAND expr  */
#line 480 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2446 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 99: /* expr: expr NOR expr  */
#line 481 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2452 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 100: /* expr: expr EQ expr  */
#line 482 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "==", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2458 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 101: /* expr: expr NE expr  */
#line 483 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "!=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2464 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 102: /* expr: expr '<' expr  */
#line 484 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2470 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 103: /* expr: expr '>' expr  */
#line 485 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2476 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 104: /* expr: expr LE expr  */
#line 486 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2482 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 105: /* expr: expr GE expr  */
#line 487 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2488 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 106: /* expr: expr SHL expr  */
#line 488 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2494 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 107: /* expr: expr SHR expr  */
#line 489 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2500 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 108: /* expr: expr SSHR expr  */
#line 490 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2506 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 109: /* expr: expr LOGAND expr  */
#line 491 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2512 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 110: /* expr: expr LOGOR expr  */
#line 492 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "||", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2518 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 111: /* expr: expr '?' expr ':' expr  */
#line 494 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::TERNARY, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));
      }
#line 2527 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 112: /* expr: '-' expr  */
#line 498 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "-", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2533 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 113: /* expr: '!' expr  */
#line 499 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "!", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2539 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 114: /* expr: '~' expr  */
#line 500 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2545 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 115: /* expr: '&' expr  */
#line 501 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "&", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2551 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 116: /* expr: '|' expr  */
#line 502 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "|", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2557 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 117: /* expr: '^' expr  */
#line 503 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "^", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2563 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 119: /* prim_expr: NUMBER  */
#line 509 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNum((yyvsp[0].num));
      }
#line 2571 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 120: /* prim_expr: IDENTIFIER  */
#line 513 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 2580 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 121: /* prim_expr: IDENTIFIER '[' expr ':' expr ']'  */
#line 518 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2591 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 122: /* prim_expr: IDENTIFIER '[' expr ']'  */
#line 525 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2601 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 123: /* prim_expr: '{' expr_list '}'  */
#line 531 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 2612 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 124: /* prim_expr: '(' expr ')'  */
#line 538 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2620 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 125: /* prim_expr: SYS_FOPEN '(' STRING ')'  */
#line 542 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
      }
#line 2630 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 126: /* prim_expr: SYS_FOPEN '(' STRING ',' STRING ')'  */
#line 548 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-3].str), yylineno));
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-3].str)); free((yyvsp[-1].str));
      }
#line 2641 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 127: /* prim_expr: SYS_CLOG2 '(' expr ')'  */
#line 555 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$clog2", yylineno);
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2650 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 128: /* prim_expr: STRING  */
#line 560 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::STRING, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 2659 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 129: /* lvalue: IDENTIFIER  */
#line 568 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 2668 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 130: /* lvalue: IDENTIFIER '[' expr ':' expr ']'  */
#line 573 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2679 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 131: /* lvalue: IDENTIFIER '[' expr ']'  */
#line 580 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2689 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 132: /* lvalue: '{' lvalue_list '}'  */
#line 586 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 2700 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 133: /* lvalue_list: lvalue_list ',' lvalue  */
#line 595 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2706 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 134: /* lvalue_list: lvalue  */
#line 596 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2712 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 135: /* expr_list: expr_list ',' expr  */
#line 600 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2718 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 136: /* expr_list: expr  */
#line 601 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2724 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;


#line 2728 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"

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

#line 604 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"


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
