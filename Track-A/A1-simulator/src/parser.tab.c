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
  YYSYMBOL_52_ = 52,                       /* '|'  */
  YYSYMBOL_53_ = 53,                       /* '^'  */
  YYSYMBOL_54_ = 54,                       /* '&'  */
  YYSYMBOL_55_ = 55,                       /* '<'  */
  YYSYMBOL_56_ = 56,                       /* '>'  */
  YYSYMBOL_57_ = 57,                       /* '+'  */
  YYSYMBOL_58_ = 58,                       /* '-'  */
  YYSYMBOL_59_ = 59,                       /* '*'  */
  YYSYMBOL_60_ = 60,                       /* '/'  */
  YYSYMBOL_61_ = 61,                       /* '%'  */
  YYSYMBOL_POWER = 62,                     /* POWER  */
  YYSYMBOL_63_ = 63,                       /* '!'  */
  YYSYMBOL_64_ = 64,                       /* '~'  */
  YYSYMBOL_UNARY = 65,                     /* UNARY  */
  YYSYMBOL_66_ = 66,                       /* ';'  */
  YYSYMBOL_67_ = 67,                       /* '#'  */
  YYSYMBOL_68_ = 68,                       /* '('  */
  YYSYMBOL_69_ = 69,                       /* ')'  */
  YYSYMBOL_70_ = 70,                       /* ','  */
  YYSYMBOL_71_ = 71,                       /* '='  */
  YYSYMBOL_72_ = 72,                       /* '@'  */
  YYSYMBOL_73_ = 73,                       /* ':'  */
  YYSYMBOL_74_ = 74,                       /* '.'  */
  YYSYMBOL_75_ = 75,                       /* '['  */
  YYSYMBOL_76_ = 76,                       /* ']'  */
  YYSYMBOL_77_ = 77,                       /* '?'  */
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
#define YYLAST   2584

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
       2,     2,     2,    63,     2,    67,     2,    61,    54,     2,
      68,    69,    59,    57,    70,    58,    74,    60,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    73,    66,
      55,    71,    56,    77,    72,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    76,    53,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    78,    52,    79,    64,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    62,    65
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    87,    88,    92,    99,   111,   112,   116,
     121,   122,   126,   127,   131,   132,   133,   137,   138,   139,
     143,   144,   156,   158,   169,   171,   173,   175,   177,   179,
     181,   183,   185,   187,   189,   191,   193,   195,   197,   199,
     202,   204,   206,   208,   209,   213,   224,   232,   242,   250,
     260,   268,   278,   286,   296,   304,   314,   324,   335,   336,
     340,   341,   347,   354,   360,   370,   376,   382,   389,   395,
     396,   397,   402,   408,   414,   420,   425,   434,   444,   454,
     461,   470,   471,   475,   476,   480,   488,   497,   503,   510,
     518,   519,   523,   524,   525,   529,   530,   531,   532,   536,
     537,   541,   547,   554,   559,   567,   572,   573,   577,   581,
     582,   586,   592,   600,   612,   613,   614,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   633,   634,   635,   640,   641,
     642,   643,   644,   645,   646,   650,   654,   659,   666,   672,
     681,   689,   696,   708,   712,   718,   725,   730,   738,   743,
     750,   756,   764,   771,   781,   782,   786,   787
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
  "XNOR", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "POWER", "'!'", "'~'", "UNARY", "';'", "'#'", "'('", "')'", "','",
  "'='", "'@'", "':'", "'.'", "'['", "']'", "'?'", "'{'", "'}'", "$accept",
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

#define YYPACT_NINF (-374)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,     6,    24,    21,  -374,    38,  -374,  -374,    15,    46,
      78,   161,  -374,    59,   167,    16,  -374,  -374,   831,   213,
      80,  -374,  -374,     7,   124,   524,   228,  -374,    13,    20,
     124,   234,  -374,    46,     4,    18,    60,   238,   240,   248,
       3,   -22,   588,   179,   136,   786,  -374,   197,   206,   202,
     207,   161,  -374,   271,   274,   204,  -374,  -374,   212,   214,
     524,   524,   524,   524,   524,   524,   524,   524,  1088,  -374,
    -374,  -374,   280,  -374,   124,   281,   284,  -374,  -374,   220,
     222,  -374,   288,   221,   124,   290,  -374,   224,   225,   230,
       3,   229,   524,   239,   588,   241,   244,   245,   249,   250,
     252,   253,     9,   301,   257,  -374,   -20,   259,   263,   305,
     227,  -374,   258,  -374,  -374,  -374,  -374,   524,   282,  -374,
    -374,  -374,   524,   343,   524,   272,   272,   272,   272,   272,
     272,  1126,   859,   -26,   524,   524,   524,   524,   524,   524,
     524,   524,   524,   524,   524,   524,   524,   524,   524,   524,
     524,   524,   524,   186,   524,   524,   524,   524,  -374,   350,
    -374,  -374,    33,   258,    67,    65,   524,    72,   352,   286,
      73,   524,   524,   524,  -374,   -13,   524,   403,    17,  -374,
     278,   524,   524,     3,   354,   524,   576,   632,  -374,   524,
     293,   128,   524,    26,   524,    14,  -374,   105,  -374,  -374,
     357,   114,  -374,  2380,   831,   898,   123,  1164,  -374,   524,
     524,  -374,  2507,  2507,   175,   175,   814,  2412,   137,   137,
     137,  2484,  2484,  2461,  2437,  2461,  2484,   175,   175,   102,
     102,   524,   272,   272,   272,  1202,  1240,  -374,   295,   359,
     140,  -374,   160,  -374,   360,   524,   116,   299,  1278,  -374,
    -374,   524,   145,  -374,  1316,  1354,   936,     3,  -374,  1392,
    -374,   363,   364,   300,  -374,  -374,  1430,  1468,   302,   303,
    1506,   306,  2380,   188,   307,   190,  1544,  -374,   368,   371,
    1582,   309,   311,   312,  1620,  1658,   310,   380,  -374,   382,
     318,  -374,   258,   811,   524,   313,  -374,   383,  -374,   -11,
    2380,   272,  -374,   524,  -374,   322,   327,   317,   391,  -374,
    1696,  -374,  -374,  -374,   158,  1734,  -374,  -374,  -374,   524,
     321,  -374,  -374,   328,   330,   588,   588,   462,   524,   334,
     336,   338,   339,   341,   342,   344,   340,   346,  -374,   409,
     524,   524,  -374,   664,   524,   345,  -374,   524,  -374,  -374,
    1772,   524,   348,   349,  2380,   479,  -374,  -374,   355,  -374,
    -374,  -374,  1810,   524,   588,   588,  -374,   396,   532,   149,
    -374,   974,  1848,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
     361,   365,   192,   196,   198,   703,  -374,   398,  1886,   524,
    1924,  -374,  1012,  -374,  -374,  -374,  1962,    34,  -374,  1050,
    -374,  -374,   588,   588,  -374,  -374,  -374,   524,   588,   524,
    -374,  -374,   366,   367,   402,   422,  -374,  -374,   725,   664,
     524,  2000,  -374,   524,  -374,  -374,   405,   201,   524,  -374,
    -374,  -374,  2038,  -374,  2076,  -374,  -374,  -374,   325,  -374,
    -374,  -374,  -374,  2114,   524,  2152,  -374,   406,  2190,   588,
       3,   757,     3,  2228,  -374,  -374,  -374,  -374,   407,  -374,
     408,   427,   524,   524,   414,  2266,  2304,   524,   588,   664,
    2342,  -374,  -374,   664,  -374
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
     133,   123,   124,   122,   120,   121,   119,   127,   128,   114,
     115,     0,   116,   117,   118,     0,     0,    57,     0,     0,
       0,   110,     0,    24,     0,     0,     0,     0,     0,    28,
      59,     0,     0,    30,     0,     0,     0,     0,   163,     0,
      37,     0,     0,     0,    60,    81,     0,     0,     0,     0,
       0,   157,   167,     0,   157,     0,     0,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,     0,
       0,   105,     0,     0,     0,   148,   154,     0,   156,     0,
     166,   134,   113,     0,    42,     0,     0,     0,     0,    58,
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
      62,   103,     0,   101,     0,    76,    77,    78,     0,    92,
      95,    96,    88,     0,     0,     0,    41,     0,     0,     0,
       0,     0,     0,     0,   149,    39,   161,   102,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    86,     0,    85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -374,  -374,  -374,   466,  -374,   423,   426,  -374,   440,   273,
     -17,    23,   -78,   -79,  -374,  -374,   -40,  -374,  -373,    48,
    -374,   119,  -374,   326,   199,    93,   185,   -10,   -25,  -374,
     -38,  -374,  -175
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
      68,    46,    91,   111,    31,   167,    89,    79,   170,     5,
      52,   273,   275,    53,    54,   179,    71,   286,    72,    75,
      76,    81,   192,    73,     6,    82,    85,     1,   114,    55,
      56,    57,    17,    74,   299,   125,   126,   127,   128,   129,
     130,   131,   132,   287,   210,    92,   442,   261,   262,    12,
      93,   193,   174,   211,    13,    14,    17,   257,   281,   210,
     282,   283,    22,    83,   159,    59,   258,   177,   353,    23,
     199,    80,    24,    84,   168,   188,   263,   189,    60,    61,
      62,    90,    25,    11,    63,    32,    33,   246,    25,    64,
      65,   252,   203,    25,    66,    25,   472,   205,   260,   207,
     474,   265,   238,   426,    67,     8,     9,   239,   239,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   232,   233,
     234,   235,   236,   243,    25,    25,   245,   244,   249,   253,
      25,   248,   244,   244,    18,   268,   254,   255,   256,    50,
      51,   259,    55,    56,    57,   247,   266,   267,   278,   279,
     270,   153,   154,   155,   276,   383,   384,   280,   284,   285,
      27,   288,   314,   405,   368,   289,    19,    28,    29,   157,
      30,    58,   311,   291,   292,   300,   244,    46,    59,    55,
      56,    57,   296,   297,   151,   152,   153,   154,   155,    25,
     107,    60,    61,    62,   112,   108,   301,    63,   109,   306,
     307,   316,    64,    65,   157,   244,    49,    66,    58,   321,
     310,   140,   141,   142,   360,    59,   315,    67,   244,   308,
     292,    70,   151,   152,   153,   154,   155,    77,    60,    61,
      62,    86,    25,    87,    63,   231,   366,   367,   107,    64,
      65,    88,   157,   108,    66,   198,   109,   332,   210,   334,
     210,   412,   297,   115,    67,   413,   210,   414,   210,   350,
     447,   307,   116,   117,   120,     9,   114,   121,   354,   122,
     123,    89,   124,   158,   160,   400,   401,   161,   162,   404,
     163,   165,   166,   169,   362,   171,   172,    94,   264,    95,
     176,    96,   371,   372,    97,   173,   190,   178,   196,   181,
      98,    99,   182,   183,   100,   101,   102,   184,   185,   388,
     186,   187,   390,   430,   431,   191,   392,   194,    34,   433,
     396,   195,   200,    13,    14,    35,    36,    37,   399,    38,
      39,    40,    41,    42,   371,   103,   107,   206,   204,   157,
     104,   108,    43,   237,   109,   250,    90,   251,   269,   277,
     290,   304,   305,   309,   421,   312,   323,   324,   416,   325,
     457,   336,   329,   328,   337,   331,   333,   339,   441,   340,
     341,   344,   432,   345,   434,   346,   347,   352,   351,   471,
     355,   239,    44,   356,   358,   443,   363,   364,   445,   365,
     373,   440,   374,   448,   375,   376,    89,   377,   378,   380,
     379,   441,   458,   382,   460,   381,   389,   393,   402,   453,
     419,   416,    94,   397,    95,   438,    96,   410,   394,    97,
     464,   411,   435,   436,   440,    98,    99,   465,   466,   100,
     101,   102,   470,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,    55,    56,    57,   437,     7,
     103,   446,   455,    78,   119,   104,   118,   293,   462,   463,
     157,    90,    55,    56,    57,   467,   451,   368,   406,   242,
     427,   348,   357,     0,    58,     0,     0,     0,     0,     0,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,     0,    60,    61,    62,     0,    59,     0,
      63,     0,     0,     0,     0,    64,    65,    55,    56,    57,
      66,    60,    61,    62,     0,    89,     0,    63,     0,     0,
      67,     0,    64,    65,     0,     0,     0,    66,   395,     0,
       0,    94,     0,    95,     0,    96,    58,    67,    97,     0,
       0,     0,     0,    59,    98,    99,     0,     0,   100,   101,
     102,     0,     0,     0,     0,     0,    60,    61,    62,    55,
     271,    57,    63,     0,     0,     0,     0,    64,    65,     0,
       0,    89,    66,     0,     0,     0,     0,     0,     0,   103,
       0,     0,    67,     0,   104,   403,     0,    94,    58,    95,
      90,    96,     0,     0,    97,    59,     0,     0,     0,     0,
      98,    99,     0,     0,   100,   101,   102,     0,    60,    61,
      62,     0,     0,     0,    63,    55,   274,    57,     0,    64,
      65,     0,     0,     0,    66,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    67,   103,     0,     0,     0,     0,
     104,     0,     0,     0,    58,     0,    90,    34,     0,     0,
       0,    59,    13,    14,    35,    36,    37,     0,    38,    39,
      40,    41,    42,   385,    60,    61,    62,     0,     0,     0,
      63,    43,     0,     0,     0,    64,    65,     0,     0,     0,
      66,     0,     0,     0,     0,     0,    34,     0,     0,     0,
      67,    13,    14,    35,    36,    37,     0,    38,    39,    40,
      41,    42,     0,     0,   107,     0,     0,     0,    34,   108,
      43,    44,   109,    13,    14,    35,    36,    37,     0,    38,
      39,    40,    41,    42,     0,   439,   107,     0,     0,     0,
       0,   108,    43,     0,   109,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,    13,    14,    35,    36,    37,
      44,    38,    39,    40,    41,    42,   415,   459,   107,     0,
       0,     0,     0,   108,    43,     0,   109,     0,     0,    34,
       0,     0,    44,   113,    13,    14,    35,    36,    37,     0,
      38,    39,    40,    41,    42,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    34,     0,     0,     0,   349,    13,
      14,    35,    36,    37,    44,    38,    39,    40,    41,    42,
       0,     0,     0,     0,    34,     0,     0,     0,    43,    13,
      14,    35,    36,    37,     0,    38,    39,    40,    41,    42,
       0,     0,     0,    44,   134,   135,   136,   137,    43,     0,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,     0,    44,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   157,   209,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   294,     0,     0,   295,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   319,
       0,     0,   320,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
       0,     0,     0,     0,   407,     0,     0,   408,     0,     0,
       0,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   423,     0,     0,   424,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   428,     0,     0,   429,   157,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   156,     0,     0,     0,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,     0,
       0,     0,     0,     0,     0,   208,     0,     0,     0,     0,
       0,     0,     0,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
       0,     0,     0,   298,     0,     0,     0,     0,     0,     0,
       0,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   302,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,   157,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,     0,     0,     0,   313,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,     0,
       0,     0,   317,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
     318,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,   322,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,     0,     0,     0,   326,
       0,     0,     0,     0,     0,     0,     0,   157,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,     0,     0,     0,     0,     0,     0,   327,     0,     0,
       0,     0,     0,     0,     0,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,     0,
       0,     0,     0,     0,     0,   330,     0,     0,     0,     0,
       0,     0,     0,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
       0,     0,     0,   335,     0,     0,     0,     0,     0,     0,
       0,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,   338,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,   342,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,     0,     0,     0,     0,     0,     0,   343,     0,     0,
       0,     0,     0,     0,     0,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,     0,
       0,     0,   359,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
     361,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   391,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   398,   157,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,     0,     0,     0,   409,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,     0,
       0,     0,   420,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
       0,     0,     0,   422,     0,     0,     0,     0,     0,     0,
       0,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,     0,     0,
       0,   425,     0,     0,     0,     0,     0,     0,     0,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,   444,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   449,     0,     0,     0,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,     0,
       0,     0,   450,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
     452,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   454,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   456,   157,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
       0,     0,     0,     0,   461,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   157,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,     0,
       0,     0,     0,     0,     0,   468,     0,     0,     0,     0,
       0,     0,     0,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
       0,     0,     0,   469,     0,     0,     0,     0,     0,     0,
       0,   157,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,     0,     0,
       0,   473,     0,     0,     0,     0,     0,     0,     0,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   134,   135,   136,   137,   138,   157,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,     0,     0,     0,   134,   135,   136,
     137,     0,     0,   140,   141,   142,   143,   144,   145,   157,
     147,   148,   149,   150,   151,   152,   153,   154,   155,     0,
       0,   134,   135,   136,   137,     0,     0,   140,   141,   142,
     143,   144,     0,     0,   157,   148,   149,   150,   151,   152,
     153,   154,   155,     0,   134,   135,   136,   137,     0,     0,
     140,   141,   142,     0,     0,     0,     0,     0,   157,   149,
     150,   151,   152,   153,   154,   155,     0,     0,     0,   136,
     137,     0,     0,   140,   141,   142,     0,     0,     0,     0,
       0,   157,   149,   150,   151,   152,   153,   154,   155,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   157
};

static const yytype_int16 yycheck[] =
{
      25,    18,    40,    43,    14,    83,     3,     3,    86,     3,
       3,   186,   187,    23,    24,    94,     3,     3,    28,    29,
      30,     3,    42,     3,     0,    35,    36,     6,    45,     3,
       4,     5,     9,    13,   209,    60,    61,    62,    63,    64,
      65,    66,    67,    29,    70,    67,   419,    30,    31,     3,
      72,    71,    90,    79,     8,     9,    33,    70,    32,    70,
      34,    35,     3,     3,    74,    39,    79,    92,    79,    10,
     110,    67,    13,    13,    84,    66,    59,    68,    52,    53,
      54,    78,    75,    68,    58,    69,    70,   165,    75,    63,
      64,   169,   117,    75,    68,    75,   469,   122,   177,   124,
     473,   180,    69,    69,    78,    67,    68,    74,    74,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,    66,    75,    75,    71,    70,    66,    66,
      75,   166,    70,    70,    66,   183,   171,   172,   173,    69,
      70,   176,     3,     4,     5,   165,   181,   182,    30,    31,
     185,    59,    60,    61,   189,   340,   341,   192,   193,   194,
       3,    66,   250,    24,    25,    70,    15,    10,    11,    77,
      13,    32,    66,    69,    70,   210,    70,   204,    39,     3,
       4,     5,    69,    70,    57,    58,    59,    60,    61,    75,
      21,    52,    53,    54,    68,    26,   231,    58,    29,    69,
      70,    66,    63,    64,    77,    70,     3,    68,    32,   257,
     245,    46,    47,    48,    66,    39,   251,    78,    70,    69,
      70,     3,    57,    58,    59,    60,    61,     3,    52,    53,
      54,     3,    75,     3,    58,    59,   325,   326,    21,    63,
      64,     3,    77,    26,    68,    28,    29,    69,    70,    69,
      70,    69,    70,    66,    78,    69,    70,    69,    70,   294,
      69,    70,    66,    71,     3,    68,   293,     3,   303,    75,
      68,     3,    68,     3,     3,   364,   365,     3,    68,   368,
      68,     3,    71,     3,   319,    71,    71,    19,    20,    21,
      71,    23,   327,   328,    26,    75,     5,    68,     3,    68,
      32,    33,    68,    68,    36,    37,    38,    68,    68,   344,
      68,    68,   347,   402,   403,    68,   351,    68,     3,   408,
     355,    68,    74,     8,     9,    10,    11,    12,   363,    14,
      15,    16,    17,    18,   369,    67,    21,     4,    66,    77,
      72,    26,    27,     3,    29,     3,    78,    71,     4,    66,
       3,    66,     3,     3,   389,    66,     3,     3,   385,    69,
     449,     3,    69,    71,     3,    69,    69,    68,   418,    68,
      68,    71,   407,     3,   409,     3,    68,     4,    75,   468,
      68,    74,    67,    66,     3,   420,    75,    69,   423,    69,
      66,   418,    66,   428,    66,    66,     3,    66,    66,    69,
      66,   451,   450,     4,   452,    69,    71,    69,    22,   444,
      22,   438,    19,    68,    21,     3,    23,    66,    79,    26,
       3,    66,    66,    66,   451,    32,    33,   462,   463,    36,
      37,    38,   467,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,     3,     4,     5,    66,     3,
      67,    66,    66,    33,    51,    72,    50,   204,    71,    71,
      77,    78,     3,     4,     5,    71,   438,    25,   369,   163,
     397,   292,   307,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    52,    53,    54,    -1,    39,    -1,
      58,    -1,    -1,    -1,    -1,    63,    64,     3,     4,     5,
      68,    52,    53,    54,    -1,     3,    -1,    58,    -1,    -1,
      78,    -1,    63,    64,    -1,    -1,    -1,    68,    69,    -1,
      -1,    19,    -1,    21,    -1,    23,    32,    78,    26,    -1,
      -1,    -1,    -1,    39,    32,    33,    -1,    -1,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,     3,
       4,     5,    58,    -1,    -1,    -1,    -1,    63,    64,    -1,
      -1,     3,    68,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    78,    -1,    72,    73,    -1,    19,    32,    21,
      78,    23,    -1,    -1,    26,    39,    -1,    -1,    -1,    -1,
      32,    33,    -1,    -1,    36,    37,    38,    -1,    52,    53,
      54,    -1,    -1,    -1,    58,     3,     4,     5,    -1,    63,
      64,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    67,    -1,    -1,    -1,    -1,
      72,    -1,    -1,    -1,    32,    -1,    78,     3,    -1,    -1,
      -1,    39,     8,     9,    10,    11,    12,    -1,    14,    15,
      16,    17,    18,    19,    52,    53,    54,    -1,    -1,    -1,
      58,    27,    -1,    -1,    -1,    63,    64,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,
      78,     8,     9,    10,    11,    12,    -1,    14,    15,    16,
      17,    18,    -1,    -1,    21,    -1,    -1,    -1,     3,    26,
      27,    67,    29,     8,     9,    10,    11,    12,    -1,    14,
      15,    16,    17,    18,    -1,    20,    21,    -1,    -1,    -1,
      -1,    26,    27,    -1,    29,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    -1,    -1,     8,     9,    10,    11,    12,
      67,    14,    15,    16,    17,    18,    73,    20,    21,    -1,
      -1,    -1,    -1,    26,    27,    -1,    29,    -1,    -1,     3,
      -1,    -1,    67,     7,     8,     9,    10,    11,    12,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,     3,    -1,    -1,    -1,     7,     8,
       9,    10,    11,    12,    67,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    27,     8,
       9,    10,    11,    12,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    67,    40,    41,    42,    43,    27,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    67,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    -1,    76,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    76,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    73,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,    76,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    -1,    76,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    -1,    -1,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    -1,    -1,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    -1,    -1,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    77,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    48,    49,    50,    51,    77,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      49,    50,    -1,    -1,    77,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    40,    41,    42,    43,    -1,    -1,
      46,    47,    48,    -1,    -1,    -1,    -1,    -1,    77,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    42,
      43,    -1,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    77,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    81,    82,    83,     3,     0,    83,    67,    68,
      86,    68,     3,     8,     9,    87,    88,    91,    66,    15,
      84,    85,     3,    10,    13,    75,   107,     3,    10,    11,
      13,   107,    69,    70,     3,    10,    11,    12,    14,    15,
      16,    17,    18,    27,    67,    89,    90,    91,   102,     3,
      69,    70,     3,   107,   107,     3,     4,     5,    32,    39,
      52,    53,    54,    58,    63,    64,    68,    78,   108,   109,
       3,     3,   107,     3,    13,   107,   107,     3,    88,     3,
      67,     3,   107,     3,    13,   107,     3,     3,     3,     3,
      78,   110,    67,    72,    19,    21,    23,    26,    32,    33,
      36,    37,    38,    67,    72,    93,   110,    21,    26,    29,
      95,    96,    68,     7,    90,    66,    66,    71,    86,    85,
       3,     3,    75,    68,    68,   108,   108,   108,   108,   108,
     108,   108,   108,   112,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    73,    77,     3,   107,
       3,     3,    68,    68,    92,     3,    71,    92,   107,     3,
      92,    71,    71,    75,   110,   111,    71,   108,    68,    93,
      94,    68,    68,    68,    68,    68,    68,    68,    66,    68,
       5,    68,    42,    71,    68,    68,     3,    97,    28,    96,
      74,   103,   104,   108,    66,   108,     4,   108,    69,    78,
      70,    79,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,    59,   108,   108,   108,   108,   108,     3,    69,    74,
     105,   106,   103,    66,    70,    71,    92,   107,   108,    66,
       3,    71,    92,    66,   108,   108,   108,    70,    79,   108,
      93,    30,    31,    59,    20,    93,   108,   108,   110,     4,
     108,     4,   108,   112,     4,   112,   108,    66,    30,    31,
     108,    32,    34,    35,   108,   108,     3,    29,    66,    70,
       3,    69,    70,    89,    73,    76,    69,    70,    69,   112,
     108,   108,    76,    73,    66,     3,    69,    70,    69,     3,
     108,    66,    66,    66,    92,   108,    66,    66,    66,    73,
      76,   110,    66,     3,     3,    69,    69,    69,    71,    69,
      69,    69,    69,    69,    69,    69,     3,     3,    66,    68,
      68,    68,    66,    69,    71,     3,     3,    68,   104,     7,
     108,    75,     4,    79,   108,    68,    66,   106,     3,    66,
      66,    66,   108,    75,    69,    69,    93,    93,    25,   100,
     101,   108,   108,    66,    66,    66,    66,    66,    66,    66,
      69,    69,     4,   112,   112,    19,    90,    98,   108,    71,
     108,    76,   108,    69,    79,    69,   108,    68,    76,   108,
      93,    93,    22,    73,    93,    24,   101,    70,    73,    66,
      66,    66,    69,    69,    69,    73,    90,    96,    99,    22,
      66,   108,    69,    73,    76,    69,    69,   105,    73,    76,
      93,    93,   108,    93,   108,    66,    66,    66,     3,    20,
      90,    96,    98,   108,    66,   108,    66,    69,   108,    73,
      66,    99,    66,   108,    76,    66,    76,    93,   110,    20,
     110,    66,    71,    71,     3,   108,   108,    71,    69,    69,
     108,    93,    98,    69,    98
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
#line 87 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1920 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 4: /* module_list: module  */
#line 88 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { g_modules.push_back((yyvsp[0].node)); }
#line 1926 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 5: /* module: MODULE IDENTIFIER opt_port_list ';' module_items ENDMODULE  */
#line 93 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::MODULE, (yyvsp[-4].str), yylineno);
        free((yyvsp[-4].str));
        if ((yyvsp[-3].node)) { for (auto *c : (yyvsp[-3].node)->children) addChild((yyval.node), c); (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node)); }
        if ((yyvsp[-1].node)) { for (auto *c : (yyvsp[-1].node)->children) { addChild((yyval.node), c); } (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
    }
#line 1937 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
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
#line 1950 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 7: /* module_param_decls: module_param_decls ',' module_param_decl  */
#line 111 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                             { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1956 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 8: /* module_param_decls: module_param_decl  */
#line 112 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 1962 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 9: /* module_param_decl: PARAMETER IDENTIFIER '=' expr  */
#line 117 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-2].str), yylineno); free((yyvsp[-2].str)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1968 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 10: /* opt_port_list: '(' port_list ')'  */
#line 121 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 1974 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 11: /* opt_port_list: %empty  */
#line 122 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                      { (yyval.node) = nullptr; }
#line 1980 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 12: /* port_list: port_list ',' port_decl_in_list  */
#line 126 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1986 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 13: /* port_list: port_decl_in_list  */
#line 127 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                    { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 1992 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 14: /* port_decl_in_list: IDENTIFIER  */
#line 131 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { free((yyvsp[0].str)); (yyval.node) = nullptr; }
#line 1998 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 15: /* port_decl_in_list: port_decl  */
#line 132 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2004 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 16: /* port_decl_in_list: %empty  */
#line 133 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                            { (yyval.node) = nullptr; }
#line 2010 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 17: /* module_items: module_items module_item  */
#line 137 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2016 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 18: /* module_items: module_item  */
#line 138 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2022 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 19: /* module_items: %empty  */
#line 139 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); }
#line 2028 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 21: /* module_item: WIRE range IDENTIFIER range ';'  */
#line 145 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Multi-dimensional wire: wire [msb:lsb] name[dim_msb:dim_lsb] */
          (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb;
          /* Store dimension range expressions */
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-3].node)->children.clear(); freeTree((yyvsp[-3].node));
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2044 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 22: /* module_item: WIRE range IDENTIFIER decl_list ';'  */
#line 157 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 2050 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 23: /* module_item: WIRE range IDENTIFIER '=' expr ';'  */
#line 159 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Wire with initialization — store expr as child for later assign */
          auto *decl = makeNode(NodeType::NET_DECL, "wire", yylineno);
          addChild(decl, makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno));
          free((yyvsp[-3].str));
          decl->msb = (yyvsp[-4].node)->msb; decl->lsb = (yyvsp[-4].node)->lsb;
          freeTree((yyvsp[-4].node));
          addChild(decl, (yyvsp[-1].node));  /* init expression */
          (yyval.node) = decl;
      }
#line 2065 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 24: /* module_item: WIRE IDENTIFIER decl_list ';'  */
#line 170 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "wire", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2071 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 25: /* module_item: REG range IDENTIFIER decl_list ';'  */
#line 172 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 2077 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 26: /* module_item: REG range IDENTIFIER '=' expr ';'  */
#line 174 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); (yyval.node)->msb = (yyvsp[-4].node)->msb; (yyval.node)->lsb = (yyvsp[-4].node)->lsb; freeTree((yyvsp[-4].node)); }
#line 2083 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 27: /* module_item: REG IDENTIFIER '=' expr ';'  */
#line 176 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2089 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 28: /* module_item: REG IDENTIFIER decl_list ';'  */
#line 178 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 0; (yyval.node)->lsb = 0; }
#line 2095 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 29: /* module_item: REG SIGNED range IDENTIFIER decl_list ';'  */
#line 180 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "reg signed", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = (yyvsp[-3].node)->msb; (yyval.node)->lsb = (yyvsp[-3].node)->lsb; freeTree((yyvsp[-3].node)); }
#line 2101 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 30: /* module_item: INTEGER_KW IDENTIFIER decl_list ';'  */
#line 182 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::NET_DECL, "integer", yylineno); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno)); free((yyvsp[-2].str)); (yyval.node)->msb = 31; (yyval.node)->lsb = 0; }
#line 2107 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 31: /* module_item: LOCALPARAM IDENTIFIER '=' expr ';'  */
#line 184 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2113 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 32: /* module_item: PARAMETER IDENTIFIER '=' expr ';'  */
#line 186 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::LOCALPARAM_DECL, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2119 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 33: /* module_item: ASSIGN lvalue '=' expr ';'  */
#line 188 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ASSIGN, "", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2125 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 34: /* module_item: ALWAYS '@' '(' '*' ')' stmt  */
#line 190 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(*)", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2131 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 35: /* module_item: ALWAYS '@' '(' POSEDGE IDENTIFIER ')' stmt  */
#line 192 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(posedge " + std::string((yyvsp[-2].str)) + ")", yylineno); addChild((yyval.node), (yyvsp[0].node)); free((yyvsp[-2].str)); }
#line 2137 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 36: /* module_item: ALWAYS '@' '(' NEGEDGE IDENTIFIER ')' stmt  */
#line 194 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "@(negedge " + std::string((yyvsp[-2].str)) + ")", yylineno); addChild((yyval.node), (yyvsp[0].node)); free((yyvsp[-2].str)); }
#line 2143 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 37: /* module_item: ALWAYS '#' expr stmt  */
#line 196 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::ALWAYS_BLOCK, "#delay", yylineno); addChild((yyval.node), (yyvsp[-1].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2149 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 38: /* module_item: INITIAL_KW stmt  */
#line 198 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::INITIAL_BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2155 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 39: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' port_conn_list ')' ';'  */
#line 201 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-9].str), yylineno); free((yyvsp[-9].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-6].node)->children) addChild((yyval.node), c); (yyvsp[-6].node)->children.clear(); freeTree((yyvsp[-6].node)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 2161 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 40: /* module_item: IDENTIFIER IDENTIFIER '(' port_conn_list ')' ';'  */
#line 203 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-5].str), yylineno); free((yyvsp[-5].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-4].str), yylineno)); free((yyvsp[-4].str)); for (auto *c : (yyvsp[-2].node)->children) addChild((yyval.node), c); (yyvsp[-2].node)->children.clear(); freeTree((yyvsp[-2].node)); }
#line 2167 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 41: /* module_item: IDENTIFIER '#' '(' param_list ')' IDENTIFIER '(' ')' ';'  */
#line 205 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-8].str), yylineno); free((yyvsp[-8].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); for (auto *c : (yyvsp[-5].node)->children) addChild((yyval.node), c); (yyvsp[-5].node)->children.clear(); freeTree((yyvsp[-5].node)); }
#line 2173 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 42: /* module_item: IDENTIFIER IDENTIFIER '(' ')' ';'  */
#line 207 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      { (yyval.node) = makeNode(NodeType::MODULE_INST, (yyvsp[-4].str), yylineno); free((yyvsp[-4].str)); addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno)); free((yyvsp[-3].str)); }
#line 2179 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 43: /* module_item: GENERATE gen_items ENDGENERATE  */
#line 208 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 2185 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 44: /* module_item: param_override ';'  */
#line 209 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2191 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 45: /* port_decl: INPUT range IDENTIFIER  */
#line 214 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
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
#line 2206 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 46: /* port_decl: INPUT IDENTIFIER  */
#line 225 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2218 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 47: /* port_decl: OUTPUT range IDENTIFIER  */
#line 233 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2232 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 48: /* port_decl: OUTPUT IDENTIFIER  */
#line 243 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2244 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 49: /* port_decl: OUTPUT WIRE range IDENTIFIER  */
#line 251 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2258 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 50: /* port_decl: OUTPUT WIRE IDENTIFIER  */
#line 261 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2270 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 51: /* port_decl: INPUT WIRE range IDENTIFIER  */
#line 269 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2284 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 52: /* port_decl: INPUT WIRE IDENTIFIER  */
#line 279 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2296 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 53: /* port_decl: OUTPUT REG range IDENTIFIER  */
#line 287 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2310 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 54: /* port_decl: OUTPUT REG IDENTIFIER  */
#line 297 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg";
          (yyval.node)->msb = 0; (yyval.node)->lsb = 0;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
      }
#line 2322 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 55: /* port_decl: OUTPUT SIGNED range IDENTIFIER  */
#line 305 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2336 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 56: /* port_decl: INPUT SIGNED range IDENTIFIER  */
#line 315 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "input signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str));
          for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c);
          (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node));
      }
#line 2350 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 57: /* port_decl: OUTPUT REG SIGNED range IDENTIFIER  */
#line 325 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT, "", yylineno);
          (yyval.node)->value = "output reg signed";
          (yyval.node)->msb = (yyvsp[-1].node)->msb; (yyval.node)->lsb = (yyvsp[-1].node)->lsb;
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno));
          free((yyvsp[0].str)); freeTree((yyvsp[-1].node));
      }
#line 2362 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 58: /* decl_list: decl_list ',' IDENTIFIER  */
#line 335 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                             { free((yyvsp[0].str)); }
#line 2368 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 60: /* stmt: BEGINKW stmts END  */
#line 340 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 2374 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 61: /* stmt: IF '(' expr ')' stmt  */
#line 342 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2384 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 62: /* stmt: IF '(' expr ')' stmt ELSE stmt  */
#line 348 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IF, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2395 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 63: /* stmt: CASE '(' expr ')' case_items ENDCASE  */
#line 355 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2405 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 64: /* stmt: FOR '(' lvalue '=' expr ';' expr ';' lvalue '=' expr ')' stmt  */
#line 361 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::FOR, "", yylineno);
          addChild((yyval.node), (yyvsp[-10].node));  /* init lvalue */
          addChild((yyval.node), (yyvsp[-8].node));  /* init expr */
          addChild((yyval.node), (yyvsp[-6].node));  /* cond */
          addChild((yyval.node), (yyvsp[-4].node));  /* update lvalue */
          addChild((yyval.node), (yyvsp[-2].node)); /* update expr */
          addChild((yyval.node), (yyvsp[0].node)); /* body */
      }
#line 2419 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 65: /* stmt: lvalue '=' expr ';'  */
#line 371 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2429 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 66: /* stmt: lvalue LE expr ';'  */
#line 377 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::NONBLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2439 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 67: /* stmt: SYS_DISPLAY '(' expr_list ')' ';'  */
#line 383 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2450 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 68: /* stmt: SYS_DISPLAY '(' STRING ')' ';'  */
#line 390 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$display", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2460 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 69: /* stmt: SYS_FINISH ';'  */
#line 395 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); }
#line 2466 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 70: /* stmt: SYS_FINISH '(' expr ')' ';'  */
#line 396 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                   { (yyval.node) = makeNode(NodeType::SYS_TASK, "$finish", yylineno); addChild((yyval.node), (yyvsp[-2].node)); }
#line 2472 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 71: /* stmt: '#' NUMBER ';'  */
#line 398 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, std::to_string((yyvsp[-1].num)->value), yylineno);
          free((yyvsp[-1].num));
      }
#line 2481 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 72: /* stmt: '@' '(' POSEDGE IDENTIFIER ')' ';'  */
#line 403 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, "posedge", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2491 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 73: /* stmt: '@' '(' NEGEDGE IDENTIFIER ')' ';'  */
#line 409 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::DELAY, "negedge", yylineno);
          addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2501 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 74: /* stmt: SYS_FOPEN '(' STRING ')' ';'  */
#line 415 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2511 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 75: /* stmt: SYS_FCLOSE '(' expr ')' ';'  */
#line 421 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fclose", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
      }
#line 2520 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 76: /* stmt: lvalue '=' SYS_FOPEN '(' STRING ')' ';'  */
#line 426 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild(fc, makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
          addChild((yyval.node), fc);
      }
#line 2533 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 77: /* stmt: lvalue '=' SYS_FSCANF '(' expr_list ')' ';'  */
#line 435 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fscanf", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2547 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 78: /* stmt: lvalue '=' SYS_FGETS '(' expr_list ')' ';'  */
#line 445 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BLOCKING_ASSIGN, "", yylineno);
          addChild((yyval.node), (yyvsp[-6].node));
          ASTNode *fc = makeNode(NodeType::SYS_TASK, "$fgets", yylineno);
          fc->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
          addChild((yyval.node), fc);
      }
#line 2561 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 79: /* stmt: SYS_FDISPLAY '(' expr_list ')' ';'  */
#line 455 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          (yyval.node)->children = (yyvsp[-2].node)->children;
          (yyvsp[-2].node)->children.clear();
          freeTree((yyvsp[-2].node));
      }
#line 2572 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 80: /* stmt: SYS_FDISPLAY '(' STRING ')' ';'  */
#line 462 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fdisplay", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-2].str), yylineno));
          free((yyvsp[-2].str));
      }
#line 2582 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 81: /* stmts: stmts stmt  */
#line 470 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2588 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 82: /* stmts: stmt  */
#line 471 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
               { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2594 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 83: /* gen_items: gen_items gen_item  */
#line 475 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2600 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 84: /* gen_items: gen_item  */
#line 476 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::GENERATE, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2606 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 85: /* gen_item: FOR '(' GENVAR IDENTIFIER '=' expr ';' expr ';' IDENTIFIER '=' expr ')' gen_block  */
#line 481 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2618 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 86: /* gen_item: FOR '(' IDENTIFIER '=' expr ';' expr ';' lvalue '=' expr ')' gen_block  */
#line 489 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        /* for (name = expr; cond; name = expr) — genvar already declared */
        (yyval.node) = makeNode(NodeType::GENERATE_FOR, "", yylineno);
        addChild((yyval.node), makeNode(NodeType::IDENTIFIER, (yyvsp[-10].str), yylineno)); free((yyvsp[-10].str));
        addChild((yyval.node), (yyvsp[-8].node));
        addChild((yyval.node), (yyvsp[-6].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2631 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 87: /* gen_item: IF '(' expr ')' gen_block  */
#line 498 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2641 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 88: /* gen_item: IF '(' expr ')' gen_block ELSE gen_block  */
#line 504 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        (yyval.node) = makeNode(NodeType::GENERATE_IF, "", yylineno);
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2652 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 89: /* gen_item: GENVAR genvar_list ';'  */
#line 511 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    {
        /* genvar declaration — skip */
        (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno);
    }
#line 2661 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 90: /* genvar_list: genvar_list ',' IDENTIFIER  */
#line 518 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                               { free((yyvsp[0].str)); }
#line 2667 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 91: /* genvar_list: IDENTIFIER  */
#line 519 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                 { free((yyvsp[0].str)); }
#line 2673 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 92: /* gen_block: BEGINKW gen_body END  */
#line 523 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2679 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 93: /* gen_block: BEGINKW ':' IDENTIFIER gen_body END  */
#line 524 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                          { (yyval.node) = (yyvsp[-1].node); free((yyvsp[-2].str)); }
#line 2685 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 94: /* gen_block: module_item  */
#line 525 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2691 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 95: /* gen_body: gen_body module_item  */
#line 529 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2697 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 96: /* gen_body: gen_body gen_item  */
#line 530 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2703 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 97: /* gen_body: module_item  */
#line 531 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2709 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 98: /* gen_body: gen_item  */
#line 532 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2715 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 99: /* case_items: case_items case_item  */
#line 536 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 2721 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 100: /* case_items: case_item  */
#line 537 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                         { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2727 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 101: /* case_item: expr ':' stmt  */
#line 542 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2737 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 102: /* case_item: expr ',' expr ':' stmt  */
#line 548 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-2].node));
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2748 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 103: /* case_item: DEFAULT ':' stmt  */
#line 555 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2757 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 104: /* case_item: DEFAULT stmt  */
#line 560 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CASE_ITEM, "default", yylineno);
          addChild((yyval.node), (yyvsp[0].node));
      }
#line 2766 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 105: /* param_override: '#' '(' param_list ')'  */
#line 568 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
    { (yyval.node) = makeNode(NodeType::PARAM_OVERRIDE, "", yylineno); for (auto *c : (yyvsp[-1].node)->children) addChild((yyval.node), c); (yyvsp[-1].node)->children.clear(); freeTree((yyvsp[-1].node)); }
#line 2772 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 106: /* param_list: param_list ',' param_assign  */
#line 572 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { if ((yyvsp[0].node)) addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2778 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 107: /* param_list: param_assign  */
#line 573 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); if ((yyvsp[0].node)) addChild((yyval.node), (yyvsp[0].node)); }
#line 2784 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 108: /* param_assign: '.' IDENTIFIER '(' expr ')'  */
#line 577 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                { (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[-3].str), yylineno); free((yyvsp[-3].str)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 2790 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 109: /* port_conn_list: port_conn_list ',' port_conn  */
#line 581 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2796 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 110: /* port_conn_list: port_conn  */
#line 582 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                 { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2802 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 111: /* port_conn: '.' IDENTIFIER '(' expr ')'  */
#line 587 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 2812 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 112: /* port_conn: '.' IDENTIFIER '(' ')'  */
#line 593 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::PORT_CONN, (yyvsp[-2].str), yylineno);
          free((yyvsp[-2].str));
      }
#line 2821 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 113: /* range: '[' expr ':' expr ']'  */
#line 601 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, "", yylineno);
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
          /* Evaluate constant range bounds */
          if ((yyvsp[-3].node)->type == NodeType::NUMBER) (yyval.node)->msb = std::stoi((yyvsp[-3].node)->value);
          if ((yyvsp[-1].node)->type == NodeType::NUMBER) (yyval.node)->lsb = std::stoi((yyvsp[-1].node)->value);
      }
#line 2834 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 114: /* expr: expr '+' expr  */
#line 612 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "+", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2840 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 115: /* expr: expr '-' expr  */
#line 613 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "-", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2846 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 116: /* expr: expr '*' expr  */
#line 614 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "*", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2852 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 117: /* expr: expr '/' expr  */
#line 615 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "/", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2858 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 118: /* expr: expr '%' expr  */
#line 616 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "%", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2864 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 119: /* expr: expr '&' expr  */
#line 617 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2870 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 120: /* expr: expr '|' expr  */
#line 618 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2876 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 121: /* expr: expr '^' expr  */
#line 619 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2882 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 122: /* expr: expr XNOR expr  */
#line 620 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~^", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2888 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 123: /* expr: expr NAND expr  */
#line 621 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2894 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 124: /* expr: expr NOR expr  */
#line 622 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "~|", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2900 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 125: /* expr: expr EQ expr  */
#line 623 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "==", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2906 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 126: /* expr: expr NE expr  */
#line 624 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "!=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2912 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 127: /* expr: expr '<' expr  */
#line 625 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2918 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 128: /* expr: expr '>' expr  */
#line 626 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2924 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 129: /* expr: expr LE expr  */
#line 627 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2930 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 130: /* expr: expr GE expr  */
#line 628 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">=", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2936 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 131: /* expr: expr SHL expr  */
#line 629 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "<<", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2942 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 132: /* expr: expr SHR expr  */
#line 630 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2948 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 133: /* expr: expr SSHR expr  */
#line 631 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, ">>>", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2954 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 134: /* expr: expr '*' '*' expr  */
#line 632 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                                     { (yyval.node) = makeNode(NodeType::BINOP, "**", yylineno); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2960 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 135: /* expr: expr LOGAND expr  */
#line 633 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "&&", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2966 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 136: /* expr: expr LOGOR expr  */
#line 634 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                        { (yyval.node) = makeNode(NodeType::BINOP, "||", yylineno); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 2972 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 137: /* expr: expr '?' expr ':' expr  */
#line 636 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::TERNARY, "", yylineno);
          addChild((yyval.node), (yyvsp[-4].node)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));
      }
#line 2981 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 138: /* expr: '-' expr  */
#line 640 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "-", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2987 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 139: /* expr: '!' expr  */
#line 641 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "!", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2993 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 140: /* expr: '~' expr  */
#line 642 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "~", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 2999 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 141: /* expr: '&' expr  */
#line 643 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "&", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3005 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 142: /* expr: '|' expr  */
#line 644 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "|", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3011 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 143: /* expr: '^' expr  */
#line 645 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                              { (yyval.node) = makeNode(NodeType::UNOP, "^", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3017 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 145: /* prim_expr: NUMBER  */
#line 651 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNum((yyvsp[0].num));
      }
#line 3025 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 146: /* prim_expr: IDENTIFIER  */
#line 655 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3034 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 147: /* prim_expr: IDENTIFIER '[' expr ':' expr ']'  */
#line 660 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3045 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 148: /* prim_expr: IDENTIFIER '[' expr ']'  */
#line 667 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3055 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 149: /* prim_expr: IDENTIFIER '[' expr ']' '[' expr ':' expr ']'  */
#line 673 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Double range-select: signal[idx][msb:lsb] */
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-8].str), yylineno);
          free((yyvsp[-8].str));
          addChild((yyval.node), (yyvsp[-6].node));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3068 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 150: /* prim_expr: IDENTIFIER '[' expr ']' '[' expr ']'  */
#line 682 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          /* Double bit-select: signal[idx][bit] */
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-6].str), yylineno);
          free((yyvsp[-6].str));
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3080 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 151: /* prim_expr: '{' expr_list '}'  */
#line 690 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 3091 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 152: /* prim_expr: '{' expr '{' expr_list '}' '}'  */
#line 697 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
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
#line 3107 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 153: /* prim_expr: '(' expr ')'  */
#line 709 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 3115 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 154: /* prim_expr: SYS_FOPEN '(' STRING ')'  */
#line 713 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-1].str));
      }
#line 3125 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 155: /* prim_expr: SYS_FOPEN '(' STRING ',' STRING ')'  */
#line 719 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$fopen", yylineno);
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-3].str), yylineno));
          addChild((yyval.node), makeNode(NodeType::STRING, (yyvsp[-1].str), yylineno));
          free((yyvsp[-3].str)); free((yyvsp[-1].str));
      }
#line 3136 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 156: /* prim_expr: SYS_CLOG2 '(' expr ')'  */
#line 726 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::SYS_TASK, "$clog2", yylineno);
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3145 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 157: /* prim_expr: STRING  */
#line 731 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::STRING, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3154 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 158: /* lvalue: IDENTIFIER  */
#line 739 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::IDENTIFIER, (yyvsp[0].str), yylineno);
          free((yyvsp[0].str));
      }
#line 3163 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 159: /* lvalue: IDENTIFIER '[' expr ':' expr ']'  */
#line 744 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-5].str), yylineno);
          free((yyvsp[-5].str));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3174 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 160: /* lvalue: IDENTIFIER '[' expr ']'  */
#line 751 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-3].str), yylineno);
          free((yyvsp[-3].str));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3184 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 161: /* lvalue: IDENTIFIER '[' expr ']' '[' expr ':' expr ']'  */
#line 757 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-8].str), yylineno);
          free((yyvsp[-8].str));
          addChild((yyval.node), (yyvsp[-6].node));
          addChild((yyval.node), (yyvsp[-3].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3196 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 162: /* lvalue: IDENTIFIER '[' expr ']' '[' expr ']'  */
#line 765 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::BITSEL, (yyvsp[-6].str), yylineno);
          free((yyvsp[-6].str));
          addChild((yyval.node), (yyvsp[-4].node));
          addChild((yyval.node), (yyvsp[-1].node));
      }
#line 3207 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 163: /* lvalue: '{' lvalue_list '}'  */
#line 772 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
      {
          (yyval.node) = makeNode(NodeType::CONCAT, "", yylineno);
          (yyval.node)->children = (yyvsp[-1].node)->children;
          (yyvsp[-1].node)->children.clear();
          freeTree((yyvsp[-1].node));
      }
#line 3218 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 164: /* lvalue_list: lvalue_list ',' lvalue  */
#line 781 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3224 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 165: /* lvalue_list: lvalue  */
#line 782 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                           { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3230 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 166: /* expr_list: expr_list ',' expr  */
#line 786 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { addChild((yyvsp[-2].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 3236 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;

  case 167: /* expr_list: expr  */
#line 787 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"
                       { (yyval.node) = makeNode(NodeType::BLOCK, "", yylineno); addChild((yyval.node), (yyvsp[0].node)); }
#line 3242 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"
    break;


#line 3246 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.tab.c"

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

#line 790 "/home/kali/Documents/github/AI4S/Track-A/A1-simulator/src/parser.y"


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
