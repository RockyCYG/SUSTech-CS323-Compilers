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
#line 1 "src/syntax.y"

	#include <string.h>
	#include <string>
	#include <iostream>
	#include <vector>

	struct Node {
		int line;
		bool flag; // 是否是token
		std::string name;
		std::vector<Node *> children;

		Node(int line, bool flag, std::string name) : line(line), flag(flag), name(std::move(name)) {}

		void addEdge(Node *child) {
			children.push_back(child);
		}
	};

	Node* root;

	#define YYSTYPE Node*
    #include "lex.yy.c"

    void yyerror(char*);

	void printAST(Node* node, int level) {
		for (int i = 0; i < level; i++) {
			printf("  ");
		}
		std::cout << node->name;
		if (!node->flag) {
			printf(" (%d)", node->line);
		}
		printf("\n");
		for (Node* child: node->children) {
			printAST(child, level + 1);
		}
	}

#line 112 "syntax.tab.c"

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

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_CHAR = 5,                       /* CHAR  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_TYPE = 7,                       /* TYPE  */
  YYSYMBOL_STRUCT = 8,                     /* STRUCT  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_DOT = 13,                       /* DOT  */
  YYSYMBOL_SEMI = 14,                      /* SEMI  */
  YYSYMBOL_COMMA = 15,                     /* COMMA  */
  YYSYMBOL_LC = 16,                        /* LC  */
  YYSYMBOL_RC = 17,                        /* RC  */
  YYSYMBOL_TYPE_INT = 18,                  /* TYPE_INT  */
  YYSYMBOL_TYPE_FLOAT = 19,                /* TYPE_FLOAT  */
  YYSYMBOL_TYPE_CHAR = 20,                 /* TYPE_CHAR  */
  YYSYMBOL_HEXNUM = 21,                    /* HEXNUM  */
  YYSYMBOL_HEXCHAR = 22,                   /* HEXCHAR  */
  YYSYMBOL_ERR = 23,                       /* ERR  */
  YYSYMBOL_LOWER_ELSE = 24,                /* LOWER_ELSE  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_OR = 26,                        /* OR  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_LT = 28,                        /* LT  */
  YYSYMBOL_LE = 29,                        /* LE  */
  YYSYMBOL_GT = 30,                        /* GT  */
  YYSYMBOL_GE = 31,                        /* GE  */
  YYSYMBOL_NE = 32,                        /* NE  */
  YYSYMBOL_EQ = 33,                        /* EQ  */
  YYSYMBOL_PLUS = 34,                      /* PLUS  */
  YYSYMBOL_MINUS = 35,                     /* MINUS  */
  YYSYMBOL_MUL = 36,                       /* MUL  */
  YYSYMBOL_DIV = 37,                       /* DIV  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_LP = 39,                        /* LP  */
  YYSYMBOL_RP = 40,                        /* RP  */
  YYSYMBOL_LB = 41,                        /* LB  */
  YYSYMBOL_RB = 42,                        /* RB  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_Program = 44,                   /* Program  */
  YYSYMBOL_ExtDefList = 45,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 46,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 47,                /* ExtDecList  */
  YYSYMBOL_Specifier = 48,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 49,           /* StructSpecifier  */
  YYSYMBOL_VarDec = 50,                    /* VarDec  */
  YYSYMBOL_FunDec = 51,                    /* FunDec  */
  YYSYMBOL_VarList = 52,                   /* VarList  */
  YYSYMBOL_ParamDec = 53,                  /* ParamDec  */
  YYSYMBOL_CompSt = 54,                    /* CompSt  */
  YYSYMBOL_StmtList = 55,                  /* StmtList  */
  YYSYMBOL_Stmt = 56,                      /* Stmt  */
  YYSYMBOL_DefList = 57,                   /* DefList  */
  YYSYMBOL_Def = 58,                       /* Def  */
  YYSYMBOL_DecList = 59,                   /* DecList  */
  YYSYMBOL_Dec = 60,                       /* Dec  */
  YYSYMBOL_Exp = 61,                       /* Exp  */
  YYSYMBOL_Args = 62                       /* Args  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   429

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  154

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    57,    57,    65,    68,    85,    92,   101,   102,   110,
     114,   118,   127,   130,   137,   151,   158,   166,   173,   182,
     193,   194,   206,   213,   215,   225,   226,   229,   239,   248,
     250,   253,   261,   270,   281,   292,   293,   296,   305,   312,
     320,   324,   325,   332,   341,   342,   353,   366,   382,   391,
     398,   407,   414,   421,   432,   439,   451,   460,   469,   478,
     488,   498,   508,   518,   528,   538,   548,   558,   568,   578,
     588,   589,   598,   607,   617,   618,   627,   628,   639,   640,
     649,   656,   663,   670,   677,   684,   691,   692,   695,   704
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "CHAR",
  "ID", "TYPE", "STRUCT", "IF", "ELSE", "WHILE", "RETURN", "DOT", "SEMI",
  "COMMA", "LC", "RC", "TYPE_INT", "TYPE_FLOAT", "TYPE_CHAR", "HEXNUM",
  "HEXCHAR", "ERR", "LOWER_ELSE", "ASSIGN", "OR", "AND", "LT", "LE", "GT",
  "GE", "NE", "EQ", "PLUS", "MINUS", "MUL", "DIV", "NOT", "LP", "RP", "LB",
  "RB", "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList",
  "Specifier", "StructSpecifier", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-27)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     134,    -4,     4,   -77,   -77,   -77,    29,   -77,   171,    96,
     -77,   -25,    19,    21,   -77,    -4,   -77,    60,   -25,   -77,
     -77,    64,   -11,    19,    14,   129,   -77,   129,   -77,   -77,
      57,    59,    50,   -77,   -77,    57,    20,    53,    57,   248,
     129,     0,   -77,   -77,   -77,    15,    71,    32,   -77,   -77,
     129,    36,    65,    88,   -77,   -77,   -77,    67,    68,    72,
     269,   103,   -77,   -77,   -77,   269,   269,   269,   -77,    97,
     248,    95,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   269,
     -77,   -77,    57,   210,   269,   269,   132,   -77,   388,    -5,
     169,   -77,   -77,   111,   -77,   -77,   107,   -77,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   361,   -77,   -77,   -77,   286,    27,   311,
     336,   -77,   -77,   -77,   -77,   -77,   -77,   361,   361,   386,
     206,   243,   243,   243,   243,   243,   243,   388,   388,    -5,
      -5,    58,   269,   -77,   -77,   248,   248,   -77,   -77,   -77,
     128,   -77,   248,   -77
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     3,     0,    15,    16,    17,     0,     2,     0,     0,
      18,     0,     0,    21,     1,     0,     4,    10,    22,     8,
      23,     0,    13,     0,     0,    49,    12,    49,     7,     6,
       0,     0,    11,    30,    28,     0,     0,    32,     0,    38,
      49,     0,    26,    22,    14,     0,     0,    33,    29,    27,
       0,    54,     0,    52,    81,    82,    83,    80,     0,     0,
       0,     0,    84,    85,    86,     0,     0,     0,    42,     0,
      38,     0,    48,    20,    19,    25,    24,     9,    31,     0,
      51,    50,     0,     0,     0,     0,     0,    40,    71,    72,
       0,    35,    34,     0,    37,    41,     0,    39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,    53,    76,    75,    89,     0,     0,
       0,    44,    43,    70,    69,    36,    79,    87,    56,    58,
      57,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,     0,     0,    74,    73,     0,     0,    78,    77,    88,
      45,    47,     0,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -77,   -77,   131,   -77,   110,     3,   -77,   -26,   135,    91,
     -77,     8,    73,   -76,   -14,   -77,    69,   -77,   -60,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,    21,    38,    10,    22,    12,    36,
      37,    68,    69,    70,    39,    40,    52,    53,    71,   118
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      86,    73,    11,     9,    30,    88,    89,    90,    96,    47,
      13,     9,    51,    41,    24,    33,    75,    74,    98,   113,
      26,    48,     2,   117,   119,   120,    72,    35,   143,    14,
      31,    32,     3,     4,     5,    25,   112,    27,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,    35,    34,    93,    51,    76,    42,   147,
      49,    79,    45,    43,    46,    28,    80,   144,    50,   150,
     151,    96,    77,    31,   -26,   -26,   153,    31,    29,    81,
      20,    98,   117,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,    95,    17,    91,   112,
     148,   -26,    18,    82,    87,     2,    83,    84,    96,    97,
      19,    85,   125,   126,    92,     3,     4,     5,    98,    20,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   121,    -5,     1,   112,     2,   152,    16,
      44,    78,     2,    94,    23,    96,   122,     3,     4,     5,
       0,   114,     3,     4,     5,    98,     0,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     123,    -5,    15,   112,     0,   149,     0,     0,     0,     2,
       0,     0,    96,     0,     0,     0,     0,     0,     0,     3,
       4,     5,    98,     0,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,     0,     0,   124,
     112,   115,     0,    54,    55,    56,    57,     0,     0,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
       0,    62,    63,    64,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,    65,     0,   112,    66,    67,
     116,    54,    55,    56,    57,     0,    96,    58,     0,    59,
      60,     0,    61,     0,    25,     0,    98,     0,     0,    62,
      63,    64,    54,    55,    56,    57,     0,   108,   109,   110,
     111,     0,     0,    65,   112,     0,    66,    67,     0,     0,
      62,    63,    64,     0,     0,     0,     0,     0,     0,    96,
       0,   142,     0,     0,    65,     0,     0,    66,    67,    98,
       0,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,    96,     0,     0,   112,     0,     0,
       0,     0,     0,     0,    98,     0,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,    96,
       0,   145,   112,     0,     0,     0,     0,     0,     0,    98,
       0,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,    96,     0,   146,   112,     0,     0,
       0,     0,     0,     0,    98,     0,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,    96,
       0,    96,   112,     0,     0,     0,     0,     0,     0,    98,
       0,    98,     0,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   110,   111,     0,   112,     0,   112
};

static const yytype_int16 yycheck[] =
{
      60,     1,     6,     0,    15,    65,    66,    67,    13,    35,
       6,     8,    38,    27,    39,     1,     1,    17,    23,    79,
      12,     1,     8,    83,    84,    85,    40,    24,     1,     0,
      41,    23,    18,    19,    20,    16,    41,    16,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,    50,    40,    69,    82,    42,     1,     1,
      40,    25,     3,     6,    14,     1,     1,    40,    15,   145,
     146,    13,     1,    41,    14,    15,   152,    41,    14,    14,
      23,    23,   142,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     1,     1,     1,    41,
      42,    41,     6,    15,     1,     8,    39,    39,    13,    14,
      14,    39,     1,     6,    17,    18,    19,    20,    23,    23,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     1,     0,     1,    41,     8,    10,     8,
      30,    50,     8,    70,     9,    13,    14,    18,    19,    20,
      -1,    82,    18,    19,    20,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
       1,     0,     1,    41,    -1,   142,    -1,    -1,    -1,     8,
      -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      19,    20,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    40,
      41,     1,    -1,     3,     4,     5,     6,    -1,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    21,    22,    23,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    35,    -1,    41,    38,    39,
      40,     3,     4,     5,     6,    -1,    13,     9,    -1,    11,
      12,    -1,    14,    -1,    16,    -1,    23,    -1,    -1,    21,
      22,    23,     3,     4,     5,     6,    -1,    34,    35,    36,
      37,    -1,    -1,    35,    41,    -1,    38,    39,    -1,    -1,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    13,
      -1,    15,    -1,    -1,    35,    -1,    -1,    38,    39,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    13,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    13,
      -1,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    13,    -1,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    13,
      -1,    13,    41,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    23,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    36,    37,    -1,    41,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     8,    18,    19,    20,    44,    45,    46,    48,
      49,     6,    51,     6,     0,     1,    45,     1,     6,    14,
      23,    47,    50,    51,    39,    16,    54,    16,     1,    14,
      15,    41,    54,     1,    40,    48,    52,    53,    48,    57,
      58,    57,     1,     6,    47,     3,    14,    50,     1,    40,
      15,    50,    59,    60,     3,     4,     5,     6,     9,    11,
      12,    14,    21,    22,    23,    35,    38,    39,    54,    55,
      56,    61,    57,     1,    17,     1,    42,     1,    52,    25,
       1,    14,    15,    39,    39,    39,    61,     1,    61,    61,
      61,     1,    17,    57,    55,     1,    13,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    41,    61,    59,     1,    40,    61,    62,    61,
      61,     1,    14,     1,    40,     1,     6,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    15,     1,    40,    40,    40,     1,    42,    62,
      56,    56,    10,    56
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    46,    46,    46,    46,
      46,    46,    46,    47,    47,    48,    48,    48,    48,    49,
      49,    49,    50,    50,    50,    50,    50,    51,    51,    51,
      51,    52,    52,    53,    54,    54,    54,    55,    55,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     3,     3,     2,     5,
       2,     3,     3,     1,     3,     1,     1,     1,     1,     5,
       5,     2,     1,     1,     4,     4,     1,     4,     3,     4,
       3,     3,     1,     2,     4,     4,     5,     2,     0,     2,
       2,     2,     1,     3,     3,     5,     7,     5,     2,     0,
       3,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     4,     3,     3,     4,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     1
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
  case 2: /* Program: ExtDefList  */
#line 58 "src/syntax.y"
                {
			int line = yyvsp[0]-> line;
			Node* res=new Node(line,false,"Program");
			res->addEdge(yyvsp[0]);
			yyval = res;
			root= yyval;
		}
#line 1319 "syntax.tab.c"
    break;

  case 3: /* Program: error  */
#line 65 "src/syntax.y"
                        {printf("Error type B at Line %d: syntax error.\n",lines); }
#line 1325 "syntax.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 69 "src/syntax.y"
                {	
			if (yyvsp[0]->line == 0){
				int line = yyvsp[-1]-> line;
				Node* res=new Node(line,false,"ExtDefList");
				res->addEdge(yyvsp[-1]);
				yyval = res;
			}
			else {
				int line = yyvsp[-1]->line;
				Node* res=new Node(line,false,"ExtDefList");
				res->addEdge(yyvsp[-1]);
				res->addEdge(yyvsp[0]);
				yyval = res;
			}
		}
#line 1345 "syntax.tab.c"
    break;

  case 5: /* ExtDefList: %empty  */
#line 85 "src/syntax.y"
                {
			int line = 0;
			Node* res=new Node(line,false,"ExtDefList");
			yyval = res;
		}
#line 1355 "syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier ExtDecList SEMI  */
#line 93 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"ExtDef");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval =res;
		}
#line 1368 "syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier ExtDecList error  */
#line 101 "src/syntax.y"
                                           { printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("missing SEMI\n");}
#line 1374 "syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier SEMI  */
#line 103 "src/syntax.y"
                {
			int line=yyvsp[-1]->line;
			Node* res=new Node(line,false,"ExtDef");
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1386 "syntax.tab.c"
    break;

  case 9: /* ExtDef: Specifier FunDec CompSt SEMI error  */
#line 111 "src/syntax.y"
        {
		printf("Error type B at Line %d: syntax error, probably ",yyvsp[-4]->line); printf("redundant SEMI\n");
	}
#line 1394 "syntax.tab.c"
    break;

  case 10: /* ExtDef: Specifier error  */
#line 115 "src/syntax.y"
        {
		printf("Error type B at Line %d: syntax error, probably ",yyvsp[0]->line); printf("missing SEMI\n");
	}
#line 1402 "syntax.tab.c"
    break;

  case 11: /* ExtDef: Specifier FunDec CompSt  */
#line 119 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"ExtDef");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval =res;
		}
#line 1415 "syntax.tab.c"
    break;

  case 12: /* ExtDef: error FunDec CompSt  */
#line 127 "src/syntax.y"
                                    { printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("missing specifier\n");}
#line 1421 "syntax.tab.c"
    break;

  case 13: /* ExtDecList: VarDec  */
#line 131 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"ExtDecList");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1432 "syntax.tab.c"
    break;

  case 14: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 138 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"ExtDecList");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1445 "syntax.tab.c"
    break;

  case 15: /* Specifier: TYPE_INT  */
#line 152 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Specifier");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1456 "syntax.tab.c"
    break;

  case 16: /* Specifier: TYPE_FLOAT  */
#line 159 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Specifier");
			res->addEdge(yyvsp[0]);
			yyval=res;
		
		}
#line 1468 "syntax.tab.c"
    break;

  case 17: /* Specifier: TYPE_CHAR  */
#line 167 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Specifier");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1479 "syntax.tab.c"
    break;

  case 18: /* Specifier: StructSpecifier  */
#line 174 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Specifier");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1490 "syntax.tab.c"
    break;

  case 19: /* StructSpecifier: STRUCT ID LC DefList RC  */
#line 183 "src/syntax.y"
                {
			int line = yyvsp[-4]->line;
			Node* res=new Node(line,false,"StructSpecifier");
			res->addEdge(yyvsp[-4]);
			res->addEdge(yyvsp[-3]);
			res->addEdge(yyvsp[-2]);
			if (yyvsp[-1]->line!=0)res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1505 "syntax.tab.c"
    break;

  case 20: /* StructSpecifier: STRUCT ID LC DefList error  */
#line 193 "src/syntax.y"
                                           { printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("missing RC\n");}
#line 1511 "syntax.tab.c"
    break;

  case 21: /* StructSpecifier: STRUCT ID  */
#line 195 "src/syntax.y"
                {
			int line = yyvsp[-1]->line;
			Node* res=new Node(line,false,"StructSpecifier");
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1523 "syntax.tab.c"
    break;

  case 22: /* VarDec: ID  */
#line 207 "src/syntax.y"
                {
			int line = yyvsp[0]->line;
			Node* res=new Node(line,false,"VarDec");
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1534 "syntax.tab.c"
    break;

  case 24: /* VarDec: VarDec LB INT RB  */
#line 216 "src/syntax.y"
                {
			int line = yyvsp[-3]->line;
			Node* res=new Node(line,false,"VarDec");
			res->addEdge(yyvsp[-3]);
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1548 "syntax.tab.c"
    break;

  case 25: /* VarDec: VarDec LB INT error  */
#line 225 "src/syntax.y"
                                    { printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("missing RB\n"); }
#line 1554 "syntax.tab.c"
    break;

  case 26: /* VarDec: error  */
#line 226 "src/syntax.y"
                      {printf("Error type B at Line %d: syntax error, probably ",yyvsp[0]->line); printf("Var can not be Exp\n"); }
#line 1560 "syntax.tab.c"
    break;

  case 27: /* FunDec: ID LP VarList RP  */
#line 230 "src/syntax.y"
                {
			int line = yyvsp[-3]->line;
			Node* res=new Node(line,false,"FunDec");
			res->addEdge(yyvsp[-3]);
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1574 "syntax.tab.c"
    break;

  case 28: /* FunDec: ID LP RP  */
#line 240 "src/syntax.y"
                {
			int line = yyvsp[-2]->line;
			Node* res=new Node(line,false,"FunDec");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1587 "syntax.tab.c"
    break;

  case 29: /* FunDec: ID LP VarList error  */
#line 248 "src/syntax.y"
                                    {printf("Error type B at Line %d:",yyvsp[-1]->line); printf("missing RP\n");}
#line 1593 "syntax.tab.c"
    break;

  case 30: /* FunDec: ID LP error  */
#line 250 "src/syntax.y"
                            { printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("missing RP\n");}
#line 1599 "syntax.tab.c"
    break;

  case 31: /* VarList: ParamDec COMMA VarList  */
#line 254 "src/syntax.y"
                {	int line = yyvsp[-2]->line;
			Node* res=new Node(line,false,"VarList");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1611 "syntax.tab.c"
    break;

  case 32: /* VarList: ParamDec  */
#line 262 "src/syntax.y"
                {
			int line = yyvsp[0]->line;
			Node* res=new Node(line,false,"VarList");
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1622 "syntax.tab.c"
    break;

  case 33: /* ParamDec: Specifier VarDec  */
#line 271 "src/syntax.y"
                {
			int line = yyvsp[-1]->line;
			Node* res=new Node(line,false,"ParamDec");
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1634 "syntax.tab.c"
    break;

  case 34: /* CompSt: LC DefList StmtList RC  */
#line 282 "src/syntax.y"
                {

			int line = yyvsp[-3]->line;
			Node* res=new Node(line,false,"CompSt");
			res->addEdge(yyvsp[-3]);
			if (yyvsp[-2]->line!=0)res->addEdge(yyvsp[-2]);
			if (yyvsp[-1]->line!=0)res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1649 "syntax.tab.c"
    break;

  case 35: /* CompSt: LC DefList StmtList error  */
#line 292 "src/syntax.y"
                                          { printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("missing RC\n");}
#line 1655 "syntax.tab.c"
    break;

  case 36: /* CompSt: LC DefList StmtList DefList error  */
#line 293 "src/syntax.y"
                                                  {printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("missing specifier\n");}
#line 1661 "syntax.tab.c"
    break;

  case 37: /* StmtList: Stmt StmtList  */
#line 297 "src/syntax.y"
                {
			int line = yyvsp[-1]->line;
			Node* res=new Node(line,false,"StmtList");
			res->addEdge(yyvsp[-1]);
			if (yyvsp[0]->line!=0)res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 1673 "syntax.tab.c"
    break;

  case 38: /* StmtList: %empty  */
#line 305 "src/syntax.y"
                {
			int line = 0;
			Node* res=new Node(line,false,"StmtList");
			yyval = res;
		}
#line 1683 "syntax.tab.c"
    break;

  case 39: /* Stmt: Exp SEMI  */
#line 313 "src/syntax.y"
                {
			int line = yyvsp[-1]->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval =res;
		}
#line 1695 "syntax.tab.c"
    break;

  case 40: /* Stmt: SEMI error  */
#line 321 "src/syntax.y"
                {
			printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("Missing Expression\n");
		}
#line 1703 "syntax.tab.c"
    break;

  case 41: /* Stmt: Exp error  */
#line 324 "src/syntax.y"
                          { printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); printf("Missing SEMI\n");}
#line 1709 "syntax.tab.c"
    break;

  case 42: /* Stmt: CompSt  */
#line 326 "src/syntax.y"
                {
			int line = yyvsp[0]->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge(yyvsp[0]);
			yyval =res;
		}
#line 1720 "syntax.tab.c"
    break;

  case 43: /* Stmt: RETURN Exp SEMI  */
#line 333 "src/syntax.y"
                {
			int line = yyvsp[-2]->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval =res;		
		}
#line 1733 "syntax.tab.c"
    break;

  case 44: /* Stmt: RETURN Exp error  */
#line 341 "src/syntax.y"
                                  {printf("Error type B at Line %d: syntax error, probably ",yyvsp[-2]->line);  printf("Missing SEMI\n");}
#line 1739 "syntax.tab.c"
    break;

  case 45: /* Stmt: IF LP Exp RP Stmt  */
#line 343 "src/syntax.y"
                {
			int line = yyvsp[-4]->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge(yyvsp[-4]);
			res->addEdge(yyvsp[-3]);
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval =res;		
		}
#line 1754 "syntax.tab.c"
    break;

  case 46: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 354 "src/syntax.y"
                {
			int line = yyvsp[-6]->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge(yyvsp[-6]);
			res->addEdge(yyvsp[-5]);
			res->addEdge(yyvsp[-4]);
			res->addEdge(yyvsp[-3]);
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval =res;		
		}
#line 1771 "syntax.tab.c"
    break;

  case 47: /* Stmt: WHILE LP Exp RP Stmt  */
#line 367 "src/syntax.y"
                {
			int line = yyvsp[-4]->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge(yyvsp[-4]);
			res->addEdge(yyvsp[-3]);
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval =res;		
		}
#line 1786 "syntax.tab.c"
    break;

  case 48: /* DefList: Def DefList  */
#line 383 "src/syntax.y"
                {
			int line = yyvsp[-1]->line;
			Node*res=new Node(line,false,"DefList");
			res->addEdge(yyvsp[-1]);
			if (yyvsp[0]->line !=0)res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1798 "syntax.tab.c"
    break;

  case 49: /* DefList: %empty  */
#line 391 "src/syntax.y"
                {
			int line=0;
			Node* res=new Node(line,false,"DefList");
			yyval=res;
		}
#line 1808 "syntax.tab.c"
    break;

  case 50: /* Def: Specifier DecList SEMI  */
#line 399 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node*res=new Node(line,false,"Def");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1821 "syntax.tab.c"
    break;

  case 51: /* Def: Specifier DecList error  */
#line 408 "src/syntax.y"
                {
			printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line); 
			printf("Missing SEMI\n");
		}
#line 1830 "syntax.tab.c"
    break;

  case 52: /* DecList: Dec  */
#line 415 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node*res=new Node(line,false,"DecList");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1841 "syntax.tab.c"
    break;

  case 53: /* DecList: Dec COMMA DecList  */
#line 422 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node*res=new Node(line,false,"DecList");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1854 "syntax.tab.c"
    break;

  case 54: /* Dec: VarDec  */
#line 433 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node*res=new Node(line,false,"Dec");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1865 "syntax.tab.c"
    break;

  case 55: /* Dec: VarDec ASSIGN Exp  */
#line 440 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node*res=new Node(line,false,"Dec");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1878 "syntax.tab.c"
    break;

  case 56: /* Exp: Exp ASSIGN Exp  */
#line 452 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1891 "syntax.tab.c"
    break;

  case 57: /* Exp: Exp AND Exp  */
#line 461 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1904 "syntax.tab.c"
    break;

  case 58: /* Exp: Exp OR Exp  */
#line 470 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1917 "syntax.tab.c"
    break;

  case 59: /* Exp: Exp LT Exp  */
#line 479 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1930 "syntax.tab.c"
    break;

  case 60: /* Exp: Exp LE Exp  */
#line 489 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1943 "syntax.tab.c"
    break;

  case 61: /* Exp: Exp GT Exp  */
#line 499 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1956 "syntax.tab.c"
    break;

  case 62: /* Exp: Exp GE Exp  */
#line 509 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1969 "syntax.tab.c"
    break;

  case 63: /* Exp: Exp NE Exp  */
#line 519 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1982 "syntax.tab.c"
    break;

  case 64: /* Exp: Exp EQ Exp  */
#line 529 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 1995 "syntax.tab.c"
    break;

  case 65: /* Exp: Exp PLUS Exp  */
#line 539 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2008 "syntax.tab.c"
    break;

  case 66: /* Exp: Exp MINUS Exp  */
#line 549 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2021 "syntax.tab.c"
    break;

  case 67: /* Exp: Exp MUL Exp  */
#line 559 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2034 "syntax.tab.c"
    break;

  case 68: /* Exp: Exp DIV Exp  */
#line 569 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2047 "syntax.tab.c"
    break;

  case 69: /* Exp: LP Exp RP  */
#line 579 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2060 "syntax.tab.c"
    break;

  case 70: /* Exp: LP Exp error  */
#line 588 "src/syntax.y"
                              {printf("Error type B at Line %d: syntax error, probably ",yyvsp[-1]->line);  printf("missing RP\n");}
#line 2066 "syntax.tab.c"
    break;

  case 71: /* Exp: MINUS Exp  */
#line 590 "src/syntax.y"
                {
			int line=yyvsp[-1]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2078 "syntax.tab.c"
    break;

  case 72: /* Exp: NOT Exp  */
#line 599 "src/syntax.y"
                {
			int line=yyvsp[-1]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2090 "syntax.tab.c"
    break;

  case 73: /* Exp: ID LP Args RP  */
#line 608 "src/syntax.y"
                {
			int line=yyvsp[-3]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-3]);
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2104 "syntax.tab.c"
    break;

  case 74: /* Exp: ID LP Args error  */
#line 617 "src/syntax.y"
                                 {printf("Error type B at Line %d: syntax error, probably ",yyvsp[-3]->line);  printf("missing RP\n");}
#line 2110 "syntax.tab.c"
    break;

  case 75: /* Exp: ID LP RP  */
#line 619 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2123 "syntax.tab.c"
    break;

  case 76: /* Exp: ID LP error  */
#line 627 "src/syntax.y"
                            { printf("Error type B at Line %d: syntax error, probably ",yyvsp[-2]->line); printf("missing RP\n");}
#line 2129 "syntax.tab.c"
    break;

  case 77: /* Exp: Exp LB Exp RB  */
#line 629 "src/syntax.y"
                {
			int line=yyvsp[-3]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-3]);
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			// res->addEdge(res);
			yyval=res;
		}
#line 2144 "syntax.tab.c"
    break;

  case 78: /* Exp: Exp LB Exp error  */
#line 639 "src/syntax.y"
                                 {printf("Error type B at Line %d: syntax error, probably ",yyvsp[-3]->line);  printf("missing RB\n");}
#line 2150 "syntax.tab.c"
    break;

  case 79: /* Exp: Exp DOT ID  */
#line 641 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2163 "syntax.tab.c"
    break;

  case 80: /* Exp: ID  */
#line 650 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2174 "syntax.tab.c"
    break;

  case 81: /* Exp: INT  */
#line 657 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2185 "syntax.tab.c"
    break;

  case 82: /* Exp: FLOAT  */
#line 664 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2196 "syntax.tab.c"
    break;

  case 83: /* Exp: CHAR  */
#line 671 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2207 "syntax.tab.c"
    break;

  case 84: /* Exp: HEXNUM  */
#line 678 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2218 "syntax.tab.c"
    break;

  case 85: /* Exp: HEXCHAR  */
#line 685 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge(yyvsp[0]);
			yyval=res;
		}
#line 2229 "syntax.tab.c"
    break;

  case 88: /* Args: Exp COMMA Args  */
#line 696 "src/syntax.y"
                {
			int line=yyvsp[-2]->line;
			Node* res=new Node(line,false,"Args");
			res->addEdge(yyvsp[-2]);
			res->addEdge(yyvsp[-1]);
			res->addEdge(yyvsp[0]);
			yyval = res;
		}
#line 2242 "syntax.tab.c"
    break;

  case 89: /* Args: Exp  */
#line 705 "src/syntax.y"
                {
			int line=yyvsp[0]->line;
			Node* res=new Node(line,false,"Args");
			res->addEdge(yyvsp[0]);
			yyval = res;	
		}
#line 2253 "syntax.tab.c"
    break;


#line 2257 "syntax.tab.c"

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

#line 712 "src/syntax.y"


void yyerror(char* s) {
	errorFlag = true;
}
int main(int argc, char **argv){
    char *file_path;
    if(argc < 2){
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAIL;
    } else if(argc == 2){
        file_path = argv[1];
        if(!(yyin = fopen(file_path, "r"))){
            perror(argv[1]);
            return EXIT_FAIL;
        }
        yyparse();
		if (!errorFlag) {
			printAST(root, 0);
		}
        return EXIT_OK;
    } else{
        fputs("Too many arguments! Expected: 2.\n", stderr);
        return EXIT_FAIL;
    }
}
