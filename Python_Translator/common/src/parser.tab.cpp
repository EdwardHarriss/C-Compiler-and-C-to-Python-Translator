/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "common/src/parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_COMMON_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_COMMON_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "common/src/parser.y" /* yacc.c:355  */

  #include "../inc/ast.hpp"
  #include <vector>

  #include <cassert>

//  extern const AndExpression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

  extern std::vector<const Node*> ast_roots;

  extern void yyset_in(FILE* inputfile);

#line 116 "common/src/parser.tab.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    C_IDENTIFIER = 258,
    INT_CONSTANT = 259,
    FLOAT_CONST = 260,
    CHAR_CONST = 261,
    SIZEOF = 262,
    PTR_OP = 263,
    INC_OP = 264,
    DEC_OP = 265,
    LEFT_OP = 266,
    RIGHT_OP = 267,
    LE_OP = 268,
    GE_OP = 269,
    EQ_OP = 270,
    NE_OP = 271,
    AND_OP = 272,
    OR_OP = 273,
    MUL_ASSIGN = 274,
    DIV_ASSIGN = 275,
    MOD_ASSIGN = 276,
    ADD_ASSIGN = 277,
    SUB_ASSIGN = 278,
    LEFT_ASSIGN = 279,
    RIGHT_ASSIGN = 280,
    AND_ASSIGN = 281,
    XOR_ASSIGN = 282,
    OR_ASSIGN = 283,
    TYPEDEF = 284,
    EXTERN = 285,
    STATIC = 286,
    AUTO = 287,
    REGISTER = 288,
    CHAR = 289,
    SHORT = 290,
    INT = 291,
    LONG = 292,
    SIGNED = 293,
    UNSIGNED = 294,
    FLOAT = 295,
    DOUBLE = 296,
    CONST = 297,
    VOLATILE = 298,
    VOID = 299,
    STRUCT = 300,
    UNION = 301,
    ENUM = 302,
    ELLIPSIS = 303,
    CASE = 304,
    DEFAULT = 305,
    IF = 306,
    ELSE = 307,
    SWITCH = 308,
    WHILE = 309,
    DO = 310,
    FOR = 311,
    GOTO = 312,
    CONTINUE = 313,
    BREAK = 314,
    RETURN = 315
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "common/src/parser.y" /* yacc.c:355  */

  int int_constant;
  float float_constant;
  char *char_constant;
  std::string *str;
  const Node* node;

#line 197 "common/src/parser.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_COMMON_SRC_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 214 "common/src/parser.tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   970

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  187
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  305

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,     2,     2,    81,    70,     2,
      68,    69,    71,    72,    62,    73,    79,    80,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    66,    61,
      82,    63,    83,    67,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    77,     2,    78,    84,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,    76,    65,    74,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    66,    66,    67,    71,    72,    79,    80,    81,    82,
      88,    89,    90,    94,    95,    96,    97,    98,    99,   103,
     104,   108,   109,   113,   122,   123,   124,   125,   126,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   146,   147,
     170,   171,   172,   173,   201,   205,   206,   210,   211,   215,
     216,   217,   218,   219,   220,   224,   225,   226,   227,   228,
     229,   233,   234,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   252,   253,   258,   259,   263,   264,
     268,   269,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   285,   286,   287,   288,   289,   293,   294,   298,   299,
     305,   306,   309,   310,   311,   312,   313,   314,   315,   319,
     320,   321,   322,   326,   327,   331,   332,   336,   337,   341,
     342,   346,   347,   348,   352,   353,   354,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   370,   371,   377,   378,
     379,   380,   381,   391,   392,   393,   394,   398,   399,   403,
     404,   408,   409,   413,   414,   415,   419,   420,   421,   422,
     426,   427,   428,   429,   430,   431,   436,   437,   438,   439,
     443,   444,   445,   449,   450,   451,   455,   456,   457,   458,
     459,   463,   464,   465,   469,   470,   474,   475
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "C_IDENTIFIER", "INT_CONSTANT",
  "FLOAT_CONST", "CHAR_CONST", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP",
  "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPEDEF", "EXTERN", "STATIC", "AUTO", "REGISTER", "CHAR",
  "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST",
  "VOLATILE", "VOID", "STRUCT", "UNION", "ENUM", "ELLIPSIS", "CASE",
  "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO",
  "CONTINUE", "BREAK", "RETURN", "';'", "','", "'='", "'{'", "'}'", "':'",
  "'?'", "'('", "')'", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'|'",
  "'['", "']'", "'.'", "'/'", "'%'", "'<'", "'>'", "'^'", "$accept",
  "translation_unit", "external_declaration", "function_definition",
  "declaration", "declaration_specifiers", "init_declarator_list",
  "init_declarator", "initializer", "storage_class_specifier",
  "type_specifier", "type_qualifier", "specifier_qualifier_list",
  "constant_expression", "conditional_expression", "expression",
  "unary_expression", "unary_operator", "cast_expression",
  "assignment_operator", "inclusive_or_expression",
  "logical_or_expression", "logical_and_expression", "type_name",
  "postfix_expression", "primary_expression", "argument_expression_list",
  "assignment_expression", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "abstract_declarator",
  "direct_abstract_declarator", "identifier_list", "statement",
  "compound_statement", "declaration_list", "statement_list",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,    59,    44,    61,   123,   125,    58,    63,    40,    41,
      38,    42,    43,    45,   126,    33,   124,    91,    93,    46,
      47,    37,    60,    62,    94
};
# endif

#define YYPACT_NINF -165

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-165)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     773,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,    25,    -4,
     707,  -165,  -165,  -165,     8,    94,  -165,   926,   926,   926,
     889,   -41,    10,   -53,  -165,  -165,    -4,  -165,  -165,  -165,
     108,   889,  -165,    25,  -165,  -165,  -165,   686,   327,     9,
      11,  -165,  -165,   791,   171,   -41,  -165,  -165,  -165,  -165,
      11,  -165,  -165,   -37,  -165,  -165,  -165,  -165,   694,   686,
     686,   686,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
     232,   717,   -47,     1,    17,    35,  -165,  -165,    67,   -12,
     185,    33,   189,   -15,   -43,  -165,   -10,    15,    41,   571,
      90,   139,   105,   110,   591,  -165,  -165,   725,    -4,  -165,
       8,   146,  -165,  -165,  -165,   400,   473,  -165,  -165,  -165,
    -165,   278,   214,  -165,    22,  -165,   -28,   926,  -165,  -165,
    -165,    36,    74,  -165,   104,  -165,  -165,  -165,   644,  -165,
    -165,  -165,    82,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   686,   644,  -165,  -165,   686,   686,
     686,   686,   196,  -165,  -165,   270,   686,   213,   686,   686,
     686,   686,   686,   686,   686,   686,   686,   686,   686,   686,
     686,   686,   686,   686,   686,   686,   175,   599,   179,  -165,
    -165,  -165,   686,   149,  -165,   686,  -165,  -165,   498,  -165,
    -165,  -165,   167,   199,   201,  -165,   193,   -28,   848,   228,
    -165,  -165,   269,  -165,  -165,   475,   475,    91,   209,  -165,
    -165,   221,   -43,    17,    38,   -47,  -165,  -165,    98,   117,
    -165,    39,  -165,  -165,  -165,  -165,    67,    67,   -12,   -12,
     185,   185,   185,   185,    33,    33,   189,   -15,   121,   122,
     123,   215,   599,  -165,   131,  -165,  -165,  -165,  -165,   906,
    -165,  -165,  -165,   222,  -165,   216,  -165,  -165,  -165,   832,
     -14,  -165,  -165,   717,   686,  -165,   686,  -165,  -165,   571,
     571,   571,   686,   416,   236,  -165,  -165,  -165,  -165,  -165,
    -165,   241,  -165,  -165,   132,   571,   133,  -165,   571,   243,
    -165,   571,  -165,  -165,  -165
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   102,    24,    25,    26,    27,    28,    30,    31,    32,
      33,    36,    37,    34,    35,    38,    39,    29,     0,   109,
       0,     2,     4,     5,     0,     0,    19,    13,    15,    17,
      21,   101,     0,     0,   113,   111,   110,     1,     3,    10,
       0,    21,    12,     0,    14,    16,    18,     0,     0,   123,
       0,   119,     9,     0,     0,   100,   103,   114,   112,    11,
       0,     7,    20,    21,    91,    92,    93,    94,     0,     0,
       0,     0,    55,    56,    57,    58,    59,    60,    22,    98,
     166,     0,    78,    45,    76,    49,    82,    23,   170,   173,
     176,   181,   184,   186,    74,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   151,   143,     0,    56,   147,
       0,     0,    47,   149,   138,     0,     0,   139,   140,   141,
     142,     0,     0,   121,   124,   122,   125,     0,     8,   136,
     108,     0,     0,   105,     0,    44,   166,     6,     0,    53,
      50,    51,     0,    68,    69,    70,    66,    67,    65,    64,
      71,    72,    73,    63,     0,     0,    61,    52,     0,     0,
       0,     0,     0,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   161,
     162,   163,     0,     0,   152,     0,   145,   148,     0,   144,
     150,   132,     0,   117,     0,   128,     0,   126,     0,     0,
     120,   106,     0,   107,   104,    41,    43,    80,     0,    95,
      99,     0,    75,    77,     0,    79,    88,    84,     0,     0,
      47,     0,    87,   167,   168,   169,   171,   172,   174,   175,
     179,   180,   177,   178,   182,   183,   185,   187,     0,     0,
       0,     0,     0,   160,     0,   165,    48,   146,   133,     0,
     127,   129,   134,     0,   130,     0,   137,    40,    42,     0,
     124,    81,    54,     0,     0,    86,     0,    85,    83,     0,
       0,     0,     0,     0,    95,   118,   135,   131,    62,    46,
      97,   153,   155,   156,     0,     0,     0,   164,     0,     0,
     158,     0,   154,   157,   159
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,   285,  -165,   -33,    37,   -16,   280,  -165,  -165,
    -124,    -1,    -3,  -112,   -52,   -20,   -48,  -165,    51,  -165,
     164,  -165,   168,   173,  -165,  -165,  -165,   -46,    32,   -29,
     -19,  -165,   118,    18,  -118,   -44,  -120,  -165,   -92,    12,
    -165,   220,  -164,  -165,  -165,  -165,    56,    95,    89,    68,
     148,   166,   192
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    20,    21,    22,    23,    49,    25,    26,    78,    27,
      28,    29,   217,   134,    79,   111,    80,    81,   157,   154,
      82,    83,    84,   218,    85,    86,   229,   112,    63,    31,
      32,    36,   202,   203,    51,   204,   126,   132,   113,   114,
     115,   116,   117,   118,   119,   120,    88,    89,    90,    91,
      92,    93,    94
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      35,    87,   135,    55,   207,   125,   136,   186,    40,   210,
     206,     1,     1,     1,   215,   109,    56,    58,    34,   159,
     139,   140,   141,   252,   200,     1,    47,    53,     1,   158,
     124,   215,    30,   156,   161,    57,    54,    24,    15,    16,
     208,   182,    52,   162,   163,   164,   175,   176,    50,   209,
      33,   142,    30,    61,   269,   181,    41,    24,   183,    60,
     171,   172,   128,   122,    44,    45,    46,    19,   160,    39,
     135,   131,   137,   127,   136,    48,    18,   121,    18,    19,
      19,   123,   197,   184,   193,   110,   122,   142,   283,    35,
     121,   215,   215,    18,    40,    55,    19,   265,   127,   122,
     195,   195,   124,   165,   274,   211,   200,    34,   220,   185,
     136,   136,   166,   136,   167,   177,   178,   278,   142,   230,
     233,   234,   235,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   142,   212,   216,   168,    33,
     224,   210,   188,   213,   195,   228,   231,   169,   170,   256,
     207,   219,   110,    33,   216,    42,    43,   135,   187,   269,
     195,   136,    19,   248,   249,   250,   189,   275,   122,    59,
      43,   190,   254,   271,    64,    65,    66,    67,    68,   276,
      69,    70,   214,   195,   195,   195,   277,   291,   292,   293,
     279,   280,   281,   195,   195,   195,   173,   174,   270,   226,
     284,   299,   301,   300,   179,   180,   302,   194,   195,   304,
     255,   195,   267,   268,   216,   216,   232,    64,    65,    66,
      67,    68,   289,    69,    70,   156,   136,   236,   237,   251,
     290,    64,    65,    66,    67,    68,   258,    69,    70,    71,
     253,    72,    73,    74,    75,    76,    77,   244,   245,   133,
     270,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   259,   294,   296,   240,   241,   242,   243,   238,   239,
     260,   261,   266,    64,    65,    66,    67,    68,   272,    69,
      70,     1,    71,   282,    72,    73,    74,    75,    76,    77,
     273,   286,   205,   298,   287,   153,    71,   297,    72,    73,
      74,    75,    76,    77,   303,    38,   264,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    62,   288,   225,   263,   223,   221,   246,
      95,    65,    66,    67,    68,   198,    69,    70,    71,   227,
      72,    73,    74,    75,    76,    77,   121,   201,   247,    19,
     222,     0,     0,     0,     0,   122,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,     0,     0,     0,    96,     0,
      97,    98,    99,   100,   101,   102,   103,   104,   105,     0,
       0,    48,   106,     0,     0,   107,     0,    72,   108,    74,
      75,    76,    77,    95,    65,    66,    67,    68,     0,    69,
      70,     0,     0,     0,     0,     0,     0,     0,     0,    64,
      65,    66,    67,    68,     0,    69,    70,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,     0,     0,
       0,    96,     0,    97,    98,    99,   100,   101,   102,   103,
     104,   105,     0,     0,    48,   196,     0,     0,   107,     0,
      72,   108,    74,    75,    76,    77,    64,    65,    66,    67,
      68,     0,    69,    70,    71,   295,    72,    73,    74,    75,
      76,    77,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    65,    66,    67,    68,     0,    69,    70,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,     0,     0,    96,     0,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     0,     0,    48,   199,     0,
       0,    71,     0,    72,    73,    74,    75,    76,    77,    96,
       0,    97,    98,    99,   100,   101,   102,   103,   104,   105,
       0,     0,    48,   257,     0,     0,    71,     0,    72,    73,
      74,    75,    76,    77,    64,    65,    66,    67,    68,     0,
      69,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,    65,    66,    67,    68,     0,
      69,    70,    64,    65,    66,    67,    68,     0,    69,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,    97,    98,    99,   100,   101,   102,
     103,   104,   105,     0,     0,    48,     0,     0,     0,    71,
       0,    72,    73,    74,    75,    76,    77,    64,    65,    66,
      67,    68,   191,    69,    70,     0,     0,     0,     0,   192,
     105,    72,    73,    74,    75,    76,    77,    71,     0,    72,
      73,    74,    75,    76,    77,     0,     0,     0,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    64,
      65,    66,    67,    68,     0,    69,    70,    64,    65,    66,
      67,    68,     0,    69,    70,     0,     0,    37,     0,     0,
       1,     0,    71,     0,    72,    73,    74,    75,    76,    77,
      64,    65,    66,    67,    68,     0,    69,    70,    95,    65,
      66,    67,    68,     0,    69,    70,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,    71,     0,    72,    73,    74,    75,
      76,    77,   138,     0,    72,    73,    74,    75,    76,    77,
       0,     0,     0,     0,     0,    18,     1,     0,    19,     0,
       0,     0,     0,     0,     0,   155,     0,    72,    73,    74,
      75,    76,    77,   107,   129,    72,   108,    74,    75,    76,
      77,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,     0,     0,
       0,    18,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,     0,     0,     0,     0,     0,
     269,   201,     0,    19,     0,     0,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,   262,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     0,    47,    48,   285,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17
};

static const yytype_int16 yycheck[] =
{
      19,    47,    54,    32,   124,    49,    54,    99,    24,   127,
     122,     3,     3,     3,   138,    48,    69,    36,    19,    18,
      68,    69,    70,   187,   116,     3,    63,    68,     3,    76,
      49,   155,     0,    81,    17,    36,    77,     0,    42,    43,
      68,    84,    30,     8,     9,    10,    13,    14,    30,    77,
      18,    71,    20,    41,    68,    70,    24,    20,    68,    41,
      72,    73,    50,    77,    27,    28,    29,    71,    67,    61,
     122,    53,    60,    62,   122,    64,    68,    68,    68,    71,
      71,    49,   115,    68,   104,    48,    77,   107,   252,   108,
      68,   215,   216,    68,   110,   124,    71,   209,    62,    77,
      62,    62,   121,    68,    66,    69,   198,   108,   154,    68,
     158,   159,    77,   161,    79,    82,    83,    78,   138,   165,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   155,    62,   138,    71,   107,
     160,   259,     3,    69,    62,   165,   166,    80,    81,   195,
     270,    69,   115,   121,   155,    61,    62,   209,    68,    68,
      62,   209,    71,   183,   184,   185,    61,    69,    77,    61,
      62,    61,   192,   217,     3,     4,     5,     6,     7,    62,
       9,    10,    78,    62,    62,    62,    69,   279,   280,   281,
      69,    69,    69,    62,    62,    62,    11,    12,   217,     3,
      69,    69,    69,   295,    15,    16,   298,    61,    62,   301,
      61,    62,   215,   216,   215,   216,     3,     3,     4,     5,
       6,     7,   274,     9,    10,   273,   274,   171,   172,    54,
     276,     3,     4,     5,     6,     7,    69,     9,    10,    68,
      61,    70,    71,    72,    73,    74,    75,   179,   180,    78,
     269,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    62,   282,   283,   175,   176,   177,   178,   173,   174,
      69,    78,     3,     3,     4,     5,     6,     7,    69,     9,
      10,     3,    68,    68,    70,    71,    72,    73,    74,    75,
      69,    69,    78,    52,    78,    63,    68,    61,    70,    71,
      72,    73,    74,    75,    61,    20,    78,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    43,   273,   161,   208,   159,   155,   181,
       3,     4,     5,     6,     7,   115,     9,    10,    68,    69,
      70,    71,    72,    73,    74,    75,    68,    69,   182,    71,
     158,    -1,    -1,    -1,    -1,    77,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    64,    65,    -1,    -1,    68,    -1,    70,    71,    72,
      73,    74,    75,     3,     4,     5,     6,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    64,    65,    -1,    -1,    68,    -1,
      70,    71,    72,    73,    74,    75,     3,     4,     5,     6,
       7,    -1,     9,    10,    68,    69,    70,    71,    72,    73,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    64,    65,    -1,
      -1,    68,    -1,    70,    71,    72,    73,    74,    75,    51,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    64,    65,    -1,    -1,    68,    -1,    70,    71,
      72,    73,    74,    75,     3,     4,     5,     6,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,     3,     4,     5,     6,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    -1,    68,
      -1,    70,    71,    72,    73,    74,    75,     3,     4,     5,
       6,     7,    61,     9,    10,    -1,    -1,    -1,    -1,    68,
      61,    70,    71,    72,    73,    74,    75,    68,    -1,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,     3,
       4,     5,     6,     7,    -1,     9,    10,     3,     4,     5,
       6,     7,    -1,     9,    10,    -1,    -1,     0,    -1,    -1,
       3,    -1,    68,    -1,    70,    71,    72,    73,    74,    75,
       3,     4,     5,     6,     7,    -1,     9,    10,     3,     4,
       5,     6,     7,    -1,     9,    10,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    68,    -1,    70,    71,    72,    73,
      74,    75,    68,    -1,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    68,     3,    -1,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,
      73,    74,    75,    68,     3,    70,    71,    72,    73,    74,
      75,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    63,    64,    48,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    68,    71,
      86,    87,    88,    89,    90,    91,    92,    94,    95,    96,
     113,   114,   115,   113,    96,   115,   116,     0,    87,    61,
      91,   113,    61,    62,    90,    90,    90,    63,    64,    90,
     118,   119,   124,    68,    77,   114,    69,    96,   115,    61,
     118,   124,    92,   113,     3,     4,     5,     6,     7,     9,
      10,    68,    70,    71,    72,    73,    74,    75,    93,    99,
     101,   102,   105,   106,   107,   109,   110,   112,   131,   132,
     133,   134,   135,   136,   137,     3,    51,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    65,    68,    71,    89,
      90,   100,   112,   123,   124,   125,   126,   127,   128,   129,
     130,    68,    77,   113,   115,   120,   121,    62,   124,     3,
      69,   118,   122,    78,    98,    99,   101,   124,    68,   101,
     101,   101,   100,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    63,   104,    68,   101,   103,    76,    18,
      67,    17,     8,     9,    10,    68,    77,    79,    71,    80,
      81,    72,    73,    11,    12,    13,    14,    82,    83,    15,
      16,    70,    84,    68,    68,    68,   123,    68,     3,    61,
      61,    61,    68,   100,    61,    62,    65,    89,   126,    65,
     123,    69,   117,   118,   120,    78,    98,   121,    68,    77,
     119,    69,    62,    69,    78,    95,    96,    97,   108,    69,
     112,   108,   137,   107,   100,   105,     3,    69,   100,   111,
     112,   100,     3,   101,   101,   101,   131,   131,   132,   132,
     133,   133,   133,   133,   134,   134,   135,   136,   100,   100,
     100,    54,   127,    61,   100,    61,   112,    65,    69,    62,
      69,    78,    69,   117,    78,    98,     3,    97,    97,    68,
     115,   120,    69,    69,    66,    69,    62,    69,    78,    69,
      69,    69,    68,   127,    69,    48,    69,    78,   103,    99,
     112,   123,   123,   123,   100,    69,   100,    61,    52,    69,
     123,    69,   123,    61,   123
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    86,    87,    87,    88,    88,    88,    88,
      89,    89,    89,    90,    90,    90,    90,    90,    90,    91,
      91,    92,    92,    93,    94,    94,    94,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      97,    97,    97,    97,    98,    99,    99,   100,   100,   101,
     101,   101,   101,   101,   101,   102,   102,   102,   102,   102,
     102,   103,   103,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   110,   110,   110,   110,   111,   111,   112,   112,
     113,   113,   114,   114,   114,   114,   114,   114,   114,   115,
     115,   115,   115,   116,   116,    96,    96,   117,   117,   118,
     118,   119,   119,   119,   120,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   122,   122,   123,   123,
     123,   123,   123,   124,   124,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   128,   129,   129,   129,   129,
     130,   130,   130,   130,   130,   130,   131,   131,   131,   131,
     132,   132,   132,   133,   133,   133,   134,   134,   134,   134,
     134,   135,   135,   135,   136,   136,   137,   137
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     4,     3,     3,     2,
       2,     3,     2,     1,     2,     1,     2,     1,     2,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     5,     1,     3,     1,
       2,     2,     2,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     2,     1,     4,     3,     4,     4,     3,     3,     2,
       2,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       2,     1,     1,     3,     4,     3,     4,     4,     3,     1,
       2,     2,     3,     1,     2,     1,     1,     1,     3,     1,
       3,     2,     2,     1,     1,     1,     2,     3,     2,     3,
       3,     4,     2,     3,     3,     4,     1,     3,     1,     1,
       1,     1,     1,     2,     3,     3,     4,     1,     2,     1,
       2,     1,     2,     5,     7,     5,     5,     7,     6,     7,
       3,     2,     2,     2,     5,     3,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 66 "common/src/parser.y" /* yacc.c:1646  */
    { ast_roots.push_back((yyvsp[0].node)); }
#line 1669 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 67 "common/src/parser.y" /* yacc.c:1646  */
    { ast_roots.push_back((yyvsp[0].node)); }
#line 1675 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 71 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1681 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 72 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1687 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 79 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new FunctionDefinition((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1693 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 80 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new FunctionDefinition((yyvsp[-2].node), (yyvsp[-1].node), nullptr, (yyvsp[0].node)); }
#line 1699 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 81 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new FunctionDefinition(NULL,(yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1705 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 82 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new FunctionDefinition(NULL, (yyvsp[-1].node),nullptr, (yyvsp[0].node)); }
#line 1711 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 88 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Declaration((yyvsp[-1].node), NULL); }
#line 1717 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 89 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Declaration((yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1723 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 90 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Declaration(nullptr, (yyvsp[-1].node)); }
#line 1729 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 94 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1735 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 95 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new DeclarationSpecifier((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1741 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 96 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1747 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 97 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new DeclarationSpecifier((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1753 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 98 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1759 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 99 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new DeclarationSpecifier((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1765 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 103 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new InitDeclaratorList(nullptr, (yyvsp[0].node));}
#line 1771 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 104 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new InitDeclaratorList((yyvsp[-2].node), (yyvsp[0].node));}
#line 1777 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 108 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new InitDeclarator((yyvsp[0].node), nullptr);}
#line 1783 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 109 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new InitDeclarator((yyvsp[-2].node), (yyvsp[0].node));}
#line 1789 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 113 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1795 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 122 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("typedef"); }
#line 1801 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 123 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("extern"); }
#line 1807 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 124 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("static"); }
#line 1813 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 125 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("auto"); }
#line 1819 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 126 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("register"); }
#line 1825 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 130 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("void"); }
#line 1831 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 131 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("char"); }
#line 1837 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 132 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("short"); }
#line 1843 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 133 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("int"); }
#line 1849 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 134 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("long"); }
#line 1855 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 135 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("float"); }
#line 1861 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 136 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("double"); }
#line 1867 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 137 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("signed"); }
#line 1873 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 138 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("unsigned"); }
#line 1879 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 146 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("const"); }
#line 1885 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 147 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Specifier("volatile"); }
#line 1891 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 170 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1897 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 171 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1903 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 172 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1909 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 173 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1915 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 201 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1921 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 205 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1927 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 206 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ConditionalExpression((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1933 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 210 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Expression(nullptr, (yyvsp[0].node)); }
#line 1939 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 211 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Expression((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1945 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 215 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1951 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 216 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryExpression("++", (yyvsp[0].node)); }
#line 1957 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 217 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryExpression("--", (yyvsp[0].node)); }
#line 1963 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 218 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryExpression((yyvsp[-1].str), (yyvsp[0].node)); }
#line 1969 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 219 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryExpression("sizeof", (yyvsp[0].node)); }
#line 1975 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 220 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new UnaryExpression("sizeof", (yyvsp[-1].node)); }
#line 1981 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 224 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("&"); }
#line 1987 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 225 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("*"); }
#line 1993 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 226 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("+"); }
#line 1999 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 227 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("-"); }
#line 2005 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 228 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("~"); }
#line 2011 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 229 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("!"); }
#line 2017 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 233 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2023 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 234 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node); }
#line 2029 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 238 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("="); }
#line 2035 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 239 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string(">>="); }
#line 2041 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 240 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("<<="); }
#line 2047 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 241 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("+="); }
#line 2053 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 242 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("-="); }
#line 2059 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 243 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("*="); }
#line 2065 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 244 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("/="); }
#line 2071 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 245 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("%="); }
#line 2077 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 246 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("&="); }
#line 2083 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 247 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("^="); }
#line 2089 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 248 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.str) = new std::string("|="); }
#line 2095 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 252 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2101 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 253 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new InclusiveOrExpression((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2107 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 258 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2113 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 259 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new LogicalOrExpression((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2119 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 263 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2125 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 264 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new LogicalAndExpression((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2131 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 268 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2137 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 269 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2143 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 273 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2149 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 274 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixExpression((yyvsp[-3].node), "0",(yyvsp[-1].node)); }
#line 2155 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 275 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixExpression((yyvsp[-2].node), "function", nullptr); }
#line 2161 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 276 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixExpression((yyvsp[-3].node), "function", (yyvsp[-1].node)); }
#line 2167 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 277 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixExpression((yyvsp[-3].node), "function", (yyvsp[-1].node)); }
#line 2173 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 278 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixExpressionStr((yyvsp[-2].node), ".", (yyvsp[0].str)); }
#line 2179 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 279 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixExpressionStr((yyvsp[-2].node), "->", (yyvsp[0].str)); }
#line 2185 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 280 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixExpression((yyvsp[-1].node), "++", nullptr); }
#line 2191 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 281 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PostfixExpression((yyvsp[-1].node), "--", nullptr); }
#line 2197 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 285 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new identifierC((yyvsp[0].str)); }
#line 2203 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 286 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new IntConstant((yyvsp[0].int_constant));}
#line 2209 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 287 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new FloatConstant((yyvsp[0].float_constant));}
#line 2215 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 288 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new CharConstant((yyvsp[0].char_constant));}
#line 2221 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 289 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node);}
#line 2227 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 293 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 2233 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 294 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node);}
#line 2239 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 298 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node);}
#line 2245 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 299 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AssignmentExpression((yyvsp[-2].node), (yyvsp[-1].str), (yyvsp[0].node)); }
#line 2251 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 305 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Variable( (yyvsp[0].node), "pointer", nullptr); }
#line 2257 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 306 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2263 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 309 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new identifierC((yyvsp[0].str)); }
#line 2269 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 310 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2275 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 311 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Variable( (yyvsp[-3].node), "array", (yyvsp[-1].node)); }
#line 2281 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 312 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Variable( (yyvsp[-2].node), "array", nullptr); }
#line 2287 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 313 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Variable( (yyvsp[-3].node), "function", (yyvsp[-1].node)); }
#line 2293 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 314 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Variable( (yyvsp[-3].node), "function", (yyvsp[-1].node)); }
#line 2299 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 315 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Variable( (yyvsp[-2].node), "function", nullptr); }
#line 2305 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 319 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Pointer(nullptr); }
#line 2311 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 320 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Pointer((yyvsp[0].node)); }
#line 2317 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 321 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Pointer(nullptr); }
#line 2323 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 322 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new Pointer((yyvsp[-1].node)); }
#line 2329 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 326 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2335 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 327 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2341 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 331 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new TypeQualifier("const"); }
#line 2347 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 332 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new TypeQualifier("volatile"); }
#line 2353 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 336 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2359 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 337 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node); }
#line 2365 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 341 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ParameterList(nullptr, (yyvsp[0].node)); }
#line 2371 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 342 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ParameterList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2377 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 346 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ParametersListNode((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2383 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 347 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ParametersListNode((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2389 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 348 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ParametersListNode((yyvsp[0].node), nullptr); }
#line 2395 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 352 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2401 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 353 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2407 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 354 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new PointerAbstractDeclarator((yyvsp[0].node)); }
#line 2413 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 358 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AbstractDeclarator((yyvsp[-1].node)); }
#line 2419 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 359 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AbstractDeclarator(nullptr); }
#line 2425 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 360 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AbstractDeclarator((yyvsp[-1].node)); }
#line 2431 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 361 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node); }
#line 2437 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 362 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AbstractDeclarator((yyvsp[-1].node)); }
#line 2443 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 363 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AbstractDeclarator(nullptr); }
#line 2449 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 364 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AbstractDeclarator((yyvsp[-1].node)); }
#line 2455 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 365 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node); }
#line 2461 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 366 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AbstractDeclarator((yyvsp[-1].node)); }
#line 2467 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 370 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new VariableNorm((yyvsp[0].str)); }
#line 2473 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 371 "common/src/parser.y" /* yacc.c:1646  */
    {(yyval.node) = new VariableNormNode((yyvsp[-2].node), (yyvsp[0].str));}
#line 2479 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 377 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2485 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 378 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2491 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 379 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2497 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 380 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2503 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 381 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2509 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 391 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new CompoundStatement(nullptr, nullptr); }
#line 2515 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 392 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new CompoundStatement(nullptr, (yyvsp[-1].node)); }
#line 2521 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 393 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new CompoundStatement((yyvsp[-1].node), nullptr); }
#line 2527 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 394 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new CompoundStatement((yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2533 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 398 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new DeclarationList(nullptr, (yyvsp[0].node)); }
#line 2539 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 399 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new DeclarationList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2545 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 403 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new StatementListNode(nullptr, (yyvsp[0].node)); }
#line 2551 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 404 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new StatementListNode((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2557 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 408 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new EmptyExpression(); }
#line 2563 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 409 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2569 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 413 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new IfStatement((yyvsp[-2].node), (yyvsp[0].node), nullptr); }
#line 2575 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 414 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new IfStatement((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2581 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 415 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new SwitchStatement((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2587 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 419 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new WhileStatement((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2593 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 420 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new DoStatement((yyvsp[-5].node), (yyvsp[-2].node)); }
#line 2599 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 421 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForStatement((yyvsp[-3].node), (yyvsp[-2].node), nullptr, (yyvsp[0].node)); }
#line 2605 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 422 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ForStatement((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2611 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 426 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new GoToStatement((yyvsp[-1].str)); }
#line 2617 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 427 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ContinueStatement(); }
#line 2623 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 428 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new BreakStatement(); }
#line 2629 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 429 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnStatement(nullptr); }
#line 2635 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 430 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnStatement((yyvsp[-2].node)); }
#line 2641 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 431 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ReturnStatement((yyvsp[-1].node)); }
#line 2647 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 436 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2653 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 437 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeExpression((yyvsp[-2].node), "*", (yyvsp[0].node)); }
#line 2659 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 438 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeExpression((yyvsp[-2].node), "/", (yyvsp[0].node)); }
#line 2665 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 439 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new MultiplicativeExpression((yyvsp[-2].node), "%", (yyvsp[0].node)); }
#line 2671 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 443 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2677 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 444 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AdditiveExpression((yyvsp[-2].node), "+", (yyvsp[0].node)); }
#line 2683 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 445 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AdditiveExpression((yyvsp[-2].node), "-", (yyvsp[0].node)); }
#line 2689 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 449 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2695 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 450 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ShiftExpression((yyvsp[-2].node), "<<", (yyvsp[0].node)); }
#line 2701 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 451 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ShiftExpression((yyvsp[-2].node), ">>", (yyvsp[0].node)); }
#line 2707 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 455 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2713 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 456 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalExpression((yyvsp[-2].node), "<", (yyvsp[0].node)); }
#line 2719 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 457 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalExpression((yyvsp[-2].node), ">", (yyvsp[0].node)); }
#line 2725 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 458 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalExpression((yyvsp[-2].node), "<=", (yyvsp[0].node)); }
#line 2731 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 459 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new RelationalExpression((yyvsp[-2].node), ">=", (yyvsp[0].node)); }
#line 2737 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 463 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2743 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 464 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new EqualityExpression((yyvsp[-2].node), "==", (yyvsp[0].node)); }
#line 2749 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 465 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new EqualityExpression((yyvsp[-2].node), "!=", (yyvsp[0].node)); }
#line 2755 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 469 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2761 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 470 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new AndExpression((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2767 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 474 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2773 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 475 "common/src/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new ExclusiveOrExpression((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2779 "common/src/parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 2783 "common/src/parser.tab.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 477 "common/src/parser.y" /* yacc.c:1906  */


std::vector<const Node*> ast_roots;

std::vector<const Node*> parseAST() {
  yyparse();
  return ast_roots;
}
