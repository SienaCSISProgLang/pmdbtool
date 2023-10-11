/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DOUBLE = 258,
     STRING = 259,
     INTEGER = 260,
     BOOLEAN = 261,
     LONG = 262,
     INDIR = 263,
     OUTDIR = 264,
     TRACE = 265,
     MODEL = 266,
     PART = 267,
     INERTIAL = 268,
     ORTHOGONAL = 269,
     READ_SMS = 270,
     WRITE_SMS = 271,
     READ_SPLIT_SMS = 272,
     DX = 273,
     COLOR = 274,
     BW = 275,
     SURFACE = 276,
     THREE_D = 277,
     TWO_D = 278,
     LOAD_BALANCE = 279,
     LB_SEL_METHOD = 280,
     LB_MAX_ITER = 281,
     LB_MAX_INTERNAL_ITER = 282,
     LB_DEBUG_LEVEL = 283,
     LB_TOLERANCE = 284,
     LB_INTERFACE_THRESH = 285,
     LB_SLICE = 286,
     LB_GEOM = 287,
     LB_INERTIAL = 288,
     LB_PROJECTION = 289,
     LB_GEOM_PRED = 290,
     LB_PROJECTION_PRED = 291,
     LB_PRINT_MIGSTATS = 292,
     LB_PRINT_ITBTIMES = 293,
     LB_PRINT_ZOLTANTIMES = 294,
     METRICS = 295,
     CLEAN = 296,
     REFINE = 297,
     COARSEN = 298,
     WEIGHT = 299,
     SPHERE = 300,
     BOX = 301,
     COMPRESS = 302,
     NONE = 303,
     GZIP = 304,
     GZIP9 = 305,
     CHECKLINKS = 306,
     REPARTITION = 307,
     PARMETIS = 308,
     ZOLTAN = 309,
     ECHO_STRING = 310,
     ALL = 311,
     MASTER = 312,
     LOADS = 313,
     MAX = 314,
     AVG = 315,
     LOCAL = 316,
     SI = 317,
     GLOBAL = 318,
     DISCONN = 319,
     REGION = 320,
     FACE = 321,
     EDGE = 322,
     VERTEX = 323,
     ADJACENCY = 324,
     COMM_MATRIX = 325,
     INT_MATRIX = 326,
     CHECKMESH = 327,
     MIGSTATS = 328,
     RESET = 329,
     PRINT = 330,
     OUTPUT = 331,
     DUPLICATES = 332,
     WRITE_SMS_ONLY = 333,
     WRITE_PMDB_ONLY = 334,
     PRINTNODECOUNTS = 335,
     PERCENTAGE = 336,
     MODELER = 337,
     PARASOLIDMODEL = 338,
     SHAPESMODEL = 339,
     SLEEP = 340,
     COMPUTECONN = 341,
     NULLMODEL = 342,
     SMDMODEL = 343,
     GATHER = 344,
     CENTROIDS = 345,
     BBOX = 346,
     SET_BOUND = 347,
     INIT_MESH = 348,
     HEAT_SOLVE = 349,
     HEAT_SOLVE_SERIAL = 350,
     HEAT_SOLVE_MPI = 351,
     CLEAR_HEAT = 352,
     HEAT_DX = 353,
     PRINT_BOUNDS = 354,
     HIER = 355,
     NUMLEVELS = 356,
     PARTITION = 357,
     LEVEL = 358,
     PROC = 359
   };
#endif
/* Tokens.  */
#define DOUBLE 258
#define STRING 259
#define INTEGER 260
#define BOOLEAN 261
#define LONG 262
#define INDIR 263
#define OUTDIR 264
#define TRACE 265
#define MODEL 266
#define PART 267
#define INERTIAL 268
#define ORTHOGONAL 269
#define READ_SMS 270
#define WRITE_SMS 271
#define READ_SPLIT_SMS 272
#define DX 273
#define COLOR 274
#define BW 275
#define SURFACE 276
#define THREE_D 277
#define TWO_D 278
#define LOAD_BALANCE 279
#define LB_SEL_METHOD 280
#define LB_MAX_ITER 281
#define LB_MAX_INTERNAL_ITER 282
#define LB_DEBUG_LEVEL 283
#define LB_TOLERANCE 284
#define LB_INTERFACE_THRESH 285
#define LB_SLICE 286
#define LB_GEOM 287
#define LB_INERTIAL 288
#define LB_PROJECTION 289
#define LB_GEOM_PRED 290
#define LB_PROJECTION_PRED 291
#define LB_PRINT_MIGSTATS 292
#define LB_PRINT_ITBTIMES 293
#define LB_PRINT_ZOLTANTIMES 294
#define METRICS 295
#define CLEAN 296
#define REFINE 297
#define COARSEN 298
#define WEIGHT 299
#define SPHERE 300
#define BOX 301
#define COMPRESS 302
#define NONE 303
#define GZIP 304
#define GZIP9 305
#define CHECKLINKS 306
#define REPARTITION 307
#define PARMETIS 308
#define ZOLTAN 309
#define ECHO_STRING 310
#define ALL 311
#define MASTER 312
#define LOADS 313
#define MAX 314
#define AVG 315
#define LOCAL 316
#define SI 317
#define GLOBAL 318
#define DISCONN 319
#define REGION 320
#define FACE 321
#define EDGE 322
#define VERTEX 323
#define ADJACENCY 324
#define COMM_MATRIX 325
#define INT_MATRIX 326
#define CHECKMESH 327
#define MIGSTATS 328
#define RESET 329
#define PRINT 330
#define OUTPUT 331
#define DUPLICATES 332
#define WRITE_SMS_ONLY 333
#define WRITE_PMDB_ONLY 334
#define PRINTNODECOUNTS 335
#define PERCENTAGE 336
#define MODELER 337
#define PARASOLIDMODEL 338
#define SHAPESMODEL 339
#define SLEEP 340
#define COMPUTECONN 341
#define NULLMODEL 342
#define SMDMODEL 343
#define GATHER 344
#define CENTROIDS 345
#define BBOX 346
#define SET_BOUND 347
#define INIT_MESH 348
#define HEAT_SOLVE 349
#define HEAT_SOLVE_SERIAL 350
#define HEAT_SOLVE_MPI 351
#define CLEAR_HEAT 352
#define HEAT_DX 353
#define PRINT_BOUNDS 354
#define HIER 355
#define NUMLEVELS 356
#define PARTITION 357
#define LEVEL 358
#define PROC 359




/* Copy the first part of user declarations.  */
#line 1 "pt_yacc.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MSops.h"
#include "pmshops.h"
#include "pmdbtool.h"
#include "dx_write.h"
#include "comm_lib.h"
/*
   pmdbtool

   Jim Teresco
   Department of Computer Science
   Rensselaer Polytechnic Institute

   and

   Department of Computer Science
   Williams College

   pt_yacc.y:  Yacc file to parse script files for pmdbtool

   Created:
   Sat May  6 10:37:04 EDT 1995

   Last change:
   Tue Jul  1 15:48:52 EDT 2003

   $Id: pt_yacc.y,v 1.8 2003/10/29 21:48:41 terescoj Exp $
*/


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 34 "pt_yacc.y"
{
   char *str;
   int integer;
   double real;
   double coords[3];
   long long_val;
 }
/* Line 193 of yacc.c.  */
#line 346 "pt_yacc.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 359 "pt_yacc.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  136
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNRULES -- Number of states.  */
#define YYNSTATES  209

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   359

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     105,   107,     2,     2,   106,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    16,    18,    21,
      24,    28,    31,    34,    37,    38,    43,    45,    49,    51,
      55,    60,    65,    69,    74,    79,    85,    91,    94,    96,
      99,   102,   105,   108,   111,   114,   117,   120,   123,   125,
     128,   130,   133,   137,   141,   145,   148,   152,   155,   158,
     162,   165,   167,   169,   171,   174,   177,   181,   184,   187,
     190,   192,   195,   198,   200,   202,   205,   207,   211,   214,
     218,   223,   227,   229,   232,   234,   239,   248,   257,   260,
     261,   263,   265,   267,   270,   271,   274,   275,   277,   279,
     281,   283,   286,   287,   290,   291,   293,   295,   297,   299,
     302,   303,   305,   307,   309,   311,   314,   316,   317,   319,
     321,   323,   325,   327,   328,   330,   332,   334,   336,   338,
     340,   342,   350,   352,   354,   356,   358,   360,   362,   364,
     366,   368
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     109,     0,    -1,   110,    -1,   110,   111,    -1,   111,    -1,
       8,     4,    -1,     9,     4,    -1,    10,    -1,    10,   122,
      -1,    11,     4,    -1,    12,   123,     4,    -1,    15,     4,
      -1,    17,     4,    -1,    16,     4,    -1,    -1,    18,   112,
     124,     4,    -1,    24,    -1,    40,     4,     4,    -1,    41,
      -1,    42,    81,     3,    -1,    42,    45,   127,     3,    -1,
      42,    46,   127,   127,    -1,    43,    81,     3,    -1,    43,
      45,   127,     3,    -1,    43,    46,   127,   127,    -1,    44,
      45,   127,     3,     5,    -1,    44,    46,   127,   127,     5,
      -1,    47,   128,    -1,    51,    -1,    25,   126,    -1,    26,
       5,    -1,    27,     5,    -1,    28,     5,    -1,    29,     5,
      -1,    30,     5,    -1,    37,     6,    -1,    38,     6,    -1,
      39,     6,    -1,    52,    -1,    53,     5,    -1,    54,    -1,
      54,     4,    -1,    54,     4,     4,    -1,    55,    56,     4,
      -1,    55,    57,     4,    -1,    55,     4,    -1,    55,     5,
       4,    -1,    58,   116,    -1,    62,   116,    -1,    64,   113,
     119,    -1,    69,   113,    -1,    70,    -1,    71,    -1,    72,
      -1,    73,    74,    -1,    73,    75,    -1,    73,    76,     4,
      -1,    77,   119,    -1,    78,     4,    -1,    79,     4,    -1,
      80,    -1,    82,   129,    -1,    85,     5,    -1,    86,    -1,
      89,    -1,    90,     4,    -1,    91,    -1,    92,     5,     3,
      -1,    93,     3,    -1,    94,     5,     3,    -1,    95,     5,
       3,     4,    -1,    96,     5,     3,    -1,    97,    -1,    98,
       4,    -1,    99,    -1,    54,   100,   101,     5,    -1,    54,
     100,   103,     5,   104,     5,    12,     5,    -1,    54,   100,
     103,     5,   104,   130,     4,     4,    -1,   115,   114,    -1,
      -1,    59,    -1,    60,    -1,    61,    -1,   115,   114,    -1,
      -1,   118,   117,    -1,    -1,    59,    -1,    60,    -1,    61,
      -1,    63,    -1,   118,   117,    -1,    -1,   121,   120,    -1,
      -1,    68,    -1,    67,    -1,    66,    -1,    65,    -1,   121,
     120,    -1,    -1,     6,    -1,     5,    -1,    13,    -1,    14,
      -1,   124,   125,    -1,   125,    -1,    -1,    19,    -1,    20,
      -1,    22,    -1,    23,    -1,    21,    -1,    -1,    31,    -1,
      32,    -1,    33,    -1,    34,    -1,    35,    -1,    36,    -1,
       5,    -1,   105,     3,   106,     3,   106,     3,   107,    -1,
      48,    -1,    47,    -1,    49,    -1,    50,    -1,    84,    -1,
      83,    -1,    87,    -1,    88,    -1,     5,    -1,    56,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   163,   163,   166,   167,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   197,   198,   200,   202,   204,   206,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   249,   254,   255,
     258,   259,   260,   263,   264,   267,   268,   271,   272,   273,
     274,   277,   278,   281,   282,   285,   286,   287,   288,   291,
     292,   295,   296,   299,   300,   303,   304,   305,   308,   309,
     310,   311,   312,   315,   316,   317,   318,   319,   320,   321,
     322,   325,   329,   330,   331,   332,   335,   336,   337,   338,
     341,   342
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DOUBLE", "STRING", "INTEGER", "BOOLEAN",
  "LONG", "INDIR", "OUTDIR", "TRACE", "MODEL", "PART", "INERTIAL",
  "ORTHOGONAL", "READ_SMS", "WRITE_SMS", "READ_SPLIT_SMS", "DX", "COLOR",
  "BW", "SURFACE", "THREE_D", "TWO_D", "LOAD_BALANCE", "LB_SEL_METHOD",
  "LB_MAX_ITER", "LB_MAX_INTERNAL_ITER", "LB_DEBUG_LEVEL", "LB_TOLERANCE",
  "LB_INTERFACE_THRESH", "LB_SLICE", "LB_GEOM", "LB_INERTIAL",
  "LB_PROJECTION", "LB_GEOM_PRED", "LB_PROJECTION_PRED",
  "LB_PRINT_MIGSTATS", "LB_PRINT_ITBTIMES", "LB_PRINT_ZOLTANTIMES",
  "METRICS", "CLEAN", "REFINE", "COARSEN", "WEIGHT", "SPHERE", "BOX",
  "COMPRESS", "NONE", "GZIP", "GZIP9", "CHECKLINKS", "REPARTITION",
  "PARMETIS", "ZOLTAN", "ECHO_STRING", "ALL", "MASTER", "LOADS", "MAX",
  "AVG", "LOCAL", "SI", "GLOBAL", "DISCONN", "REGION", "FACE", "EDGE",
  "VERTEX", "ADJACENCY", "COMM_MATRIX", "INT_MATRIX", "CHECKMESH",
  "MIGSTATS", "RESET", "PRINT", "OUTPUT", "DUPLICATES", "WRITE_SMS_ONLY",
  "WRITE_PMDB_ONLY", "PRINTNODECOUNTS", "PERCENTAGE", "MODELER",
  "PARASOLIDMODEL", "SHAPESMODEL", "SLEEP", "COMPUTECONN", "NULLMODEL",
  "SMDMODEL", "GATHER", "CENTROIDS", "BBOX", "SET_BOUND", "INIT_MESH",
  "HEAT_SOLVE", "HEAT_SOLVE_SERIAL", "HEAT_SOLVE_MPI", "CLEAR_HEAT",
  "HEAT_DX", "PRINT_BOUNDS", "HIER", "NUMLEVELS", "PARTITION", "LEVEL",
  "PROC", "'('", "','", "')'", "$accept", "strt", "commands", "command",
  "@1", "maxavglocal", "one_mal", "more_mals", "maxavglocalglobal",
  "one_malg", "more_malgs", "entity_types", "one_type", "more_types",
  "bool", "part_type", "dx_opts", "dx_opt", "lb_type", "point",
  "compression", "modeler_type", "procnum", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,    40,    44,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   108,   109,   110,   110,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   112,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   113,   113,
     114,   114,   114,   115,   115,   116,   116,   117,   117,   117,
     117,   118,   118,   119,   119,   120,   120,   120,   120,   121,
     121,   122,   122,   123,   123,   124,   124,   124,   125,   125,
     125,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   128,   128,   128,   128,   129,   129,   129,   129,
     130,   130
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     1,     2,     2,
       3,     2,     2,     2,     0,     4,     1,     3,     1,     3,
       4,     4,     3,     4,     4,     5,     5,     2,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     2,
       1,     2,     3,     3,     3,     2,     3,     2,     2,     3,
       2,     1,     1,     1,     2,     2,     3,     2,     2,     2,
       1,     2,     2,     1,     1,     2,     1,     3,     2,     3,
       4,     3,     1,     2,     1,     4,     8,     8,     2,     0,
       1,     1,     1,     2,     0,     2,     0,     1,     1,     1,
       1,     2,     0,     2,     0,     1,     1,     1,     1,     2,
       0,     1,     1,     1,     1,     2,     1,     0,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     7,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     0,     0,     0,     0,    14,
      16,   113,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    28,    38,     0,    40,
       0,    86,    86,    79,    79,    51,    52,    53,     0,    94,
       0,     0,    60,     0,     0,    63,    64,     0,    66,     0,
       0,     0,     0,     0,    72,     0,    74,     0,     2,     4,
       5,     6,   102,   101,     8,     9,   103,   104,     0,    11,
      13,    12,   107,   120,   114,   115,   116,   117,   118,   119,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   122,
     124,   125,    27,    39,    41,     0,    45,     0,     0,     0,
      47,     0,    48,    94,     0,    50,    54,    55,     0,    57,
       0,    58,    59,   127,   126,   128,   129,    61,    62,    65,
       0,    68,     0,     0,     0,    73,     1,     3,    10,   108,
     109,   112,   110,   111,     0,   106,    17,     0,     0,     0,
      19,     0,     0,    22,     0,     0,    42,     0,     0,    46,
      43,    44,    87,    88,    89,    90,    85,    49,    80,    81,
      82,    78,    56,    98,    97,    96,    95,    93,    67,    69,
       0,    71,    15,   105,     0,    20,    21,    23,    24,     0,
       0,    75,     0,    70,     0,    25,    26,     0,     0,   130,
     131,     0,     0,     0,     0,     0,    76,    77,   121
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    57,    58,    59,    72,   113,   171,   114,   110,   166,
     111,   119,   177,   120,    64,    68,   144,   145,    80,   148,
     102,   127,   201
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -46
static const yytype_int16 yypact[] =
{
      -7,     8,    37,    63,    46,    67,    52,    57,    70,   -46,
     -46,    71,    10,   116,   121,   126,   140,    88,    93,   149,
      73,   -46,   -32,   -21,   112,    86,   -46,   -46,   158,    -4,
       2,    59,    59,    87,    87,   -46,   -46,   -46,   -22,   -39,
     160,   161,   -46,   -45,   162,   -46,   -46,   164,   -46,   165,
     163,   166,   167,   168,   -46,   170,   -46,   169,    -7,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   171,   -46,
     -46,   -46,    94,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   172,
      74,    74,   174,    74,    74,   175,    74,    74,   -46,   -46,
     -46,   -46,   -46,   -46,   176,    51,   -46,   177,   178,   179,
     -46,    64,   -46,   -39,    90,   -46,   -46,   -46,   180,   -46,
      72,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     182,   -46,   183,   184,   185,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,    89,   -46,   -46,   186,   187,    74,
     -46,   188,    74,   -46,   189,    74,   -46,   190,   191,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,    69,   -46,   -46,   -46,
     -46,   101,   -46,   -46,   -46,   -46,   -46,    76,   -46,   -46,
     193,   -46,   -46,   -46,    92,   -46,   -46,   -46,   -46,   194,
     195,   -46,    97,   -46,   199,   -46,   -46,    11,    98,   181,
     -46,   201,   200,   202,   204,    99,   -46,   -46,   -46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   -46,   -46,   136,   -46,   192,   -46,   -46,   196,   -46,
     -46,    96,   -46,   -46,   -46,   -46,   -46,    66,   -46,     4,
     -46,   -46,   -46
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -101
static const yytype_int16 yytable[] =
{
     104,     1,     2,     3,     4,     5,   106,   107,     6,     7,
       8,     9,    60,    90,    91,    81,   199,    10,    11,    12,
      13,    14,    15,    16,    93,    94,  -100,  -100,  -100,  -100,
      17,    18,    19,    20,    21,    22,    23,    24,   123,   124,
      25,    61,   125,   126,    26,    27,    28,    29,    30,    92,
      65,    31,   116,   117,   118,    32,    69,    33,   108,   109,
      95,    70,    34,    35,    36,    37,    38,   200,    62,    63,
      39,    40,    41,    42,    71,    43,    73,    89,    44,    45,
      66,    67,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,   182,    86,   149,   105,   151,   152,    87,
     154,   155,    74,    75,    76,    77,    78,    79,   139,   140,
     141,   142,   143,   139,   140,   141,   142,   143,   -92,   -92,
     -92,    82,   -92,   162,   163,   164,    83,   165,   -91,   -91,
     -91,    84,   -91,    98,    99,   100,   101,   173,   174,   175,
     176,   -99,   -99,   -99,   -99,    85,   -84,   -84,   -84,   168,
     169,   170,   157,   186,   158,    88,   188,    96,    97,   190,
     -83,   -83,   -83,   103,   121,   122,   131,   128,   129,   136,
     130,   132,   133,   134,   135,   138,   146,   150,   153,   147,
     156,   159,   160,   161,   172,   178,   179,   180,   181,   184,
     185,   187,   189,   203,   137,   191,   192,   193,   194,   195,
     196,   197,   198,   205,   202,   204,   208,   206,   207,   167,
     183,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,     0,   112
};

static const yytype_int16 yycheck[] =
{
       4,     8,     9,    10,    11,    12,     4,     5,    15,    16,
      17,    18,     4,    45,    46,     5,     5,    24,    25,    26,
      27,    28,    29,    30,    45,    46,    65,    66,    67,    68,
      37,    38,    39,    40,    41,    42,    43,    44,    83,    84,
      47,     4,    87,    88,    51,    52,    53,    54,    55,    81,
       4,    58,    74,    75,    76,    62,     4,    64,    56,    57,
      81,     4,    69,    70,    71,    72,    73,    56,     5,     6,
      77,    78,    79,    80,     4,    82,     5,     4,    85,    86,
      13,    14,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,     4,     6,    91,   100,    93,    94,     6,
      96,    97,    31,    32,    33,    34,    35,    36,    19,    20,
      21,    22,    23,    19,    20,    21,    22,    23,    59,    60,
      61,     5,    63,    59,    60,    61,     5,    63,    59,    60,
      61,     5,    63,    47,    48,    49,    50,    65,    66,    67,
      68,    65,    66,    67,    68,     5,    59,    60,    61,    59,
      60,    61,   101,   149,   103,     6,   152,    45,    46,   155,
      59,    60,    61,     5,     4,     4,     3,     5,     4,     0,
       5,     5,     5,     5,     4,     4,     4,     3,     3,   105,
       4,     4,     4,     4,     4,     3,     3,     3,     3,     3,
       3,     3,     3,    12,    58,     5,     5,     4,   106,     5,
       5,   104,     3,     3,   106,     4,   107,     5,     4,   113,
     144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,     9,    10,    11,    12,    15,    16,    17,    18,
      24,    25,    26,    27,    28,    29,    30,    37,    38,    39,
      40,    41,    42,    43,    44,    47,    51,    52,    53,    54,
      55,    58,    62,    64,    69,    70,    71,    72,    73,    77,
      78,    79,    80,    82,    85,    86,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   109,   110,   111,
       4,     4,     5,     6,   122,     4,    13,    14,   123,     4,
       4,     4,   112,     5,    31,    32,    33,    34,    35,    36,
     126,     5,     5,     5,     5,     5,     6,     6,     6,     4,
      45,    46,    81,    45,    46,    81,    45,    46,    47,    48,
      49,    50,   128,     5,     4,   100,     4,     5,    56,    57,
     116,   118,   116,   113,   115,   113,    74,    75,    76,   119,
     121,     4,     4,    83,    84,    87,    88,   129,     5,     4,
       5,     3,     5,     5,     5,     4,     0,   111,     4,    19,
      20,    21,    22,    23,   124,   125,     4,   105,   127,   127,
       3,   127,   127,     3,   127,   127,     4,   101,   103,     4,
       4,     4,    59,    60,    61,    63,   117,   119,    59,    60,
      61,   114,     4,    65,    66,    67,    68,   120,     3,     3,
       3,     3,     4,   125,     3,     3,   127,     3,   127,     3,
     127,     5,     5,     4,   106,     5,     5,   104,     3,     5,
      56,   130,   106,    12,     4,     3,     5,     4,   107
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 170 "pt_yacc.y"
    { pt_set_input_dir((yyvsp[(2) - (2)].str)); ;}
    break;

  case 6:
#line 171 "pt_yacc.y"
    { pt_set_output_dir((yyvsp[(2) - (2)].str)); ;}
    break;

  case 7:
#line 172 "pt_yacc.y"
    { pt_trace_on(1); ;}
    break;

  case 8:
#line 173 "pt_yacc.y"
    { pt_trace_on((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 9:
#line 174 "pt_yacc.y"
    { pt_read_model((yyvsp[(2) - (2)].str)); ;}
    break;

  case 10:
#line 175 "pt_yacc.y"
    { pt_init_part((yyvsp[(2) - (3)].integer), (yyvsp[(3) - (3)].str)); ;}
    break;

  case 11:
#line 176 "pt_yacc.y"
    { pt_read_sms((yyvsp[(2) - (2)].str)); ;}
    break;

  case 12:
#line 177 "pt_yacc.y"
    { pt_read_split_sms((yyvsp[(2) - (2)].str)); ;}
    break;

  case 13:
#line 178 "pt_yacc.y"
    { pt_write_sms((yyvsp[(2) - (2)].str)); ;}
    break;

  case 14:
#line 179 "pt_yacc.y"
    { pt_dx_opt_init(); ;}
    break;

  case 15:
#line 179 "pt_yacc.y"
    { pt_write_dx((yyvsp[(4) - (4)].str)); ;}
    break;

  case 16:
#line 180 "pt_yacc.y"
    { pt_load_balance(); ;}
    break;

  case 17:
#line 181 "pt_yacc.y"
    { pt_metrics((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str)); ;}
    break;

  case 18:
#line 182 "pt_yacc.y"
    { pt_clean(); ;}
    break;

  case 19:
#line 183 "pt_yacc.y"
    { pt_refine_percentage((yyvsp[(3) - (3)].real), 1); ;}
    break;

  case 20:
#line 184 "pt_yacc.y"
    { pt_refine_sphere((yyvsp[(3) - (4)].coords), (yyvsp[(4) - (4)].real), 1); ;}
    break;

  case 21:
#line 185 "pt_yacc.y"
    { pt_refine_box((yyvsp[(3) - (4)].coords), (yyvsp[(4) - (4)].coords), 1); ;}
    break;

  case 22:
#line 186 "pt_yacc.y"
    { pt_refine_percentage((yyvsp[(3) - (3)].real), 0); ;}
    break;

  case 23:
#line 187 "pt_yacc.y"
    { pt_refine_sphere((yyvsp[(3) - (4)].coords), (yyvsp[(4) - (4)].real), 0); ;}
    break;

  case 24:
#line 188 "pt_yacc.y"
    { pt_refine_box((yyvsp[(3) - (4)].coords), (yyvsp[(4) - (4)].coords), 0); ;}
    break;

  case 25:
#line 189 "pt_yacc.y"
    { pt_weight_sphere((yyvsp[(3) - (5)].coords), (yyvsp[(4) - (5)].real), (yyvsp[(5) - (5)].integer)); ;}
    break;

  case 26:
#line 190 "pt_yacc.y"
    { pt_weight_box((yyvsp[(3) - (5)].coords), (yyvsp[(4) - (5)].coords), (yyvsp[(5) - (5)].integer)); ;}
    break;

  case 27:
#line 191 "pt_yacc.y"
    { pt_set_compression((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 28:
#line 192 "pt_yacc.y"
    { pt_check_links(); ;}
    break;

  case 29:
#line 193 "pt_yacc.y"
    { pt_set_lb_int_param(PMDB_LB_SEL_METHOD, (yyvsp[(2) - (2)].integer)); ;}
    break;

  case 30:
#line 194 "pt_yacc.y"
    { pt_set_lb_int_param(PMDB_LB_MAX_ITER, (yyvsp[(2) - (2)].integer)); ;}
    break;

  case 31:
#line 195 "pt_yacc.y"
    {
     pt_set_lb_int_param(PMDB_LB_MAX_INTERNAL_ITER, (yyvsp[(2) - (2)].integer)); ;}
    break;

  case 32:
#line 197 "pt_yacc.y"
    { pt_set_lb_int_param(PMDB_LB_DEBUG_LEVEL, (yyvsp[(2) - (2)].integer)); ;}
    break;

  case 33:
#line 198 "pt_yacc.y"
    { 
     pt_set_lb_long_param(PMDB_LB_TOLERANCE, (long)(yyvsp[(2) - (2)].integer)); ;}
    break;

  case 34:
#line 200 "pt_yacc.y"
    { 
     pt_set_lb_int_param(PMDB_LB_INTERFACE_THRESH, (yyvsp[(2) - (2)].integer)); ;}
    break;

  case 35:
#line 202 "pt_yacc.y"
    {
     pt_set_lb_int_param(PMDB_LB_PRINT_MIGSTATS, (yyvsp[(2) - (2)].integer)); ;}
    break;

  case 36:
#line 204 "pt_yacc.y"
    {
     pt_set_lb_int_param(PMDB_LB_PRINT_ITBTIMES, (yyvsp[(2) - (2)].integer)); ;}
    break;

  case 37:
#line 206 "pt_yacc.y"
    {
     pt_set_lb_int_param(PMDB_LB_PRINT_ZOLTANTIMES, (yyvsp[(2) - (2)].integer)); ;}
    break;

  case 38:
#line 208 "pt_yacc.y"
    { pt_repartition(); ;}
    break;

  case 39:
#line 209 "pt_yacc.y"
    { pt_parmetis((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 40:
#line 210 "pt_yacc.y"
    { pt_zoltan(); ;}
    break;

  case 41:
#line 211 "pt_yacc.y"
    { pt_zoltan_read_paramfile((yyvsp[(2) - (2)].str)); ;}
    break;

  case 42:
#line 212 "pt_yacc.y"
    { pt_zoltan_setparam((yyvsp[(2) - (3)].str),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 43:
#line 213 "pt_yacc.y"
    { pt_printall((yyvsp[(3) - (3)].str)); ;}
    break;

  case 44:
#line 214 "pt_yacc.y"
    { pt_printone(0,(yyvsp[(3) - (3)].str)); ;}
    break;

  case 45:
#line 215 "pt_yacc.y"
    { pt_printone(0,(yyvsp[(2) - (2)].str)); ;}
    break;

  case 46:
#line 216 "pt_yacc.y"
    { pt_printone((yyvsp[(2) - (3)].integer),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 47:
#line 217 "pt_yacc.y"
    { pt_print_loads((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 48:
#line 218 "pt_yacc.y"
    { pt_print_si((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 49:
#line 219 "pt_yacc.y"
    { pt_print_disconn((yyvsp[(2) - (3)].integer), (yyvsp[(3) - (3)].integer)); ;}
    break;

  case 50:
#line 220 "pt_yacc.y"
    { pt_print_adj((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 51:
#line 221 "pt_yacc.y"
    { pt_print_comm_matrix(); ;}
    break;

  case 52:
#line 222 "pt_yacc.y"
    { pt_print_int_matrix(); ;}
    break;

  case 53:
#line 223 "pt_yacc.y"
    { pt_check_mesh(); ;}
    break;

  case 54:
#line 224 "pt_yacc.y"
    { pt_reset_migstats(); ;}
    break;

  case 55:
#line 225 "pt_yacc.y"
    { pt_print_migstats(); ;}
    break;

  case 56:
#line 226 "pt_yacc.y"
    { pt_output_migstats((yyvsp[(3) - (3)].str)); ;}
    break;

  case 57:
#line 227 "pt_yacc.y"
    { pt_print_duplicate_overhead((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 58:
#line 228 "pt_yacc.y"
    { pt_write_sms_only((yyvsp[(2) - (2)].str)); ;}
    break;

  case 59:
#line 229 "pt_yacc.y"
    { pt_write_pmdb_only((yyvsp[(2) - (2)].str)); ;}
    break;

  case 60:
#line 230 "pt_yacc.y"
    { pt_print_nodecounts(); ;}
    break;

  case 61:
#line 231 "pt_yacc.y"
    { pt_set_modeler((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 62:
#line 232 "pt_yacc.y"
    { pt_sleep((yyvsp[(2) - (2)].integer)); ;}
    break;

  case 63:
#line 233 "pt_yacc.y"
    { pt_set_compute_conn(); ;}
    break;

  case 64:
#line 234 "pt_yacc.y"
    { pt_gather_to_master(); ;}
    break;

  case 65:
#line 235 "pt_yacc.y"
    { pt_write_centroids((yyvsp[(2) - (2)].str)); ;}
    break;

  case 66:
#line 236 "pt_yacc.y"
    { pt_print_bbox(); ;}
    break;

  case 67:
#line 237 "pt_yacc.y"
    { pt_set_bound((yyvsp[(2) - (3)].integer),(yyvsp[(3) - (3)].real)); ;}
    break;

  case 68:
#line 238 "pt_yacc.y"
    { pt_initialize_mesh((yyvsp[(2) - (2)].real)); ;}
    break;

  case 69:
#line 239 "pt_yacc.y"
    { pt_heat_solve((yyvsp[(2) - (3)].integer),(yyvsp[(3) - (3)].real)); ;}
    break;

  case 70:
#line 240 "pt_yacc.y"
    { pt_heat_solve_serial((yyvsp[(2) - (4)].integer),(yyvsp[(3) - (4)].real),(yyvsp[(4) - (4)].str)); ;}
    break;

  case 71:
#line 241 "pt_yacc.y"
    { pt_heat_solve_mpi((yyvsp[(2) - (3)].integer),(yyvsp[(3) - (3)].real)); ;}
    break;

  case 72:
#line 242 "pt_yacc.y"
    { pt_clear_regions("heat"); ;}
    break;

  case 73:
#line 243 "pt_yacc.y"
    { pt_heat_write_dx((yyvsp[(2) - (2)].str),pt_get_pmeshpb(),0,0,com_wall_time()); ;}
    break;

  case 74:
#line 244 "pt_yacc.y"
    { pt_print_bounds(); ;}
    break;

  case 75:
#line 245 "pt_yacc.y"
    { pt_hier_set_num_levels((yyvsp[(4) - (4)].integer)); ;}
    break;

  case 76:
#line 246 "pt_yacc.y"
    { 
     if ((yyvsp[(6) - (8)].integer) == COM_PID || (yyvsp[(6) - (8)].integer) == -1) pt_hier_set_partition((yyvsp[(4) - (8)].integer), (yyvsp[(8) - (8)].integer));
   ;}
    break;

  case 77:
#line 249 "pt_yacc.y"
    { 
     if ((yyvsp[(6) - (8)].integer) == COM_PID || (yyvsp[(6) - (8)].integer) == -1) pt_hier_set_param((yyvsp[(4) - (8)].integer), (yyvsp[(7) - (8)].str), (yyvsp[(8) - (8)].str)); 
   ;}
    break;

  case 78:
#line 254 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (2)].integer)|(yyvsp[(2) - (2)].integer); ;}
    break;

  case 79:
#line 255 "pt_yacc.y"
    { (yyval.integer)=0; ;}
    break;

  case 80:
#line 258 "pt_yacc.y"
    { (yyval.integer)=PT_MAX; ;}
    break;

  case 81:
#line 259 "pt_yacc.y"
    { (yyval.integer)=PT_AVG; ;}
    break;

  case 82:
#line 260 "pt_yacc.y"
    { (yyval.integer)=PT_LOCAL; ;}
    break;

  case 83:
#line 263 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (2)].integer)|(yyvsp[(2) - (2)].integer); ;}
    break;

  case 84:
#line 264 "pt_yacc.y"
    { (yyval.integer)=0; ;}
    break;

  case 85:
#line 267 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (2)].integer)|(yyvsp[(2) - (2)].integer); ;}
    break;

  case 86:
#line 268 "pt_yacc.y"
    { (yyval.integer)=0; ;}
    break;

  case 87:
#line 271 "pt_yacc.y"
    { (yyval.integer)=PT_MAX; ;}
    break;

  case 88:
#line 272 "pt_yacc.y"
    { (yyval.integer)=PT_AVG; ;}
    break;

  case 89:
#line 273 "pt_yacc.y"
    { (yyval.integer)=PT_LOCAL; ;}
    break;

  case 90:
#line 274 "pt_yacc.y"
    { (yyval.integer)=PT_GLOBAL; ;}
    break;

  case 91:
#line 277 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (2)].integer)|(yyvsp[(2) - (2)].integer); ;}
    break;

  case 92:
#line 278 "pt_yacc.y"
    { (yyval.integer)=0; ;}
    break;

  case 93:
#line 281 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (2)].integer)|(yyvsp[(2) - (2)].integer); ;}
    break;

  case 94:
#line 282 "pt_yacc.y"
    { (yyval.integer)=0; ;}
    break;

  case 95:
#line 285 "pt_yacc.y"
    { (yyval.integer)=PT_VERTEX; ;}
    break;

  case 96:
#line 286 "pt_yacc.y"
    { (yyval.integer)=PT_EDGE; ;}
    break;

  case 97:
#line 287 "pt_yacc.y"
    { (yyval.integer)=PT_FACE; ;}
    break;

  case 98:
#line 288 "pt_yacc.y"
    { (yyval.integer)=PT_REGION; ;}
    break;

  case 99:
#line 291 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (2)].integer)|(yyvsp[(2) - (2)].integer); ;}
    break;

  case 100:
#line 292 "pt_yacc.y"
    { (yyval.integer)=0; ;}
    break;

  case 101:
#line 295 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (1)].integer); ;}
    break;

  case 102:
#line 296 "pt_yacc.y"
    { if ((yyvsp[(1) - (1)].integer)) {(yyval.integer)=1;} else {(yyval.integer)=0;} ;}
    break;

  case 103:
#line 299 "pt_yacc.y"
    { (yyval.integer)=PT_PART_INERTIAL; ;}
    break;

  case 104:
#line 300 "pt_yacc.y"
    { (yyval.integer)=PT_PART_ORTHOGONAL; ;}
    break;

  case 108:
#line 308 "pt_yacc.y"
    { pt_dx_opt_color(); ;}
    break;

  case 109:
#line 309 "pt_yacc.y"
    { pt_dx_opt_bw(); ;}
    break;

  case 110:
#line 310 "pt_yacc.y"
    { pt_dx_opt_3d(); ;}
    break;

  case 111:
#line 311 "pt_yacc.y"
    { pt_dx_opt_2d(); ;}
    break;

  case 112:
#line 312 "pt_yacc.y"
    { pt_dx_opt_sur(); ;}
    break;

  case 113:
#line 315 "pt_yacc.y"
    { (yyval.integer)=PMDB_LB_SLICE; ;}
    break;

  case 114:
#line 316 "pt_yacc.y"
    { (yyval.integer)=PMDB_LB_SLICE; ;}
    break;

  case 115:
#line 317 "pt_yacc.y"
    { (yyval.integer)=PMDB_LB_GEOM; ;}
    break;

  case 116:
#line 318 "pt_yacc.y"
    { (yyval.integer)=PMDB_LB_INERTIAL; ;}
    break;

  case 117:
#line 319 "pt_yacc.y"
    { (yyval.integer)=PMDB_LB_PROJECTION; ;}
    break;

  case 118:
#line 320 "pt_yacc.y"
    { (yyval.integer)=PMDB_LB_GEOM_PRED; ;}
    break;

  case 119:
#line 321 "pt_yacc.y"
    { (yyval.integer)=PMDB_LB_PROJECTION_PRED; ;}
    break;

  case 120:
#line 322 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (1)].integer); ;}
    break;

  case 121:
#line 325 "pt_yacc.y"
    {
   (yyval.coords)[0]=(yyvsp[(2) - (7)].real); (yyval.coords)[1]=(yyvsp[(4) - (7)].real); (yyval.coords)[2]=(yyvsp[(6) - (7)].real); ;}
    break;

  case 122:
#line 329 "pt_yacc.y"
    { (yyval.integer)=PMDB_UNCOMPRESSED_OUTPUT; ;}
    break;

  case 123:
#line 330 "pt_yacc.y"
    { (yyval.integer)=PMDB_COMPRESS_OUTPUT; ;}
    break;

  case 124:
#line 331 "pt_yacc.y"
    { (yyval.integer)=PMDB_GZIP_OUTPUT; ;}
    break;

  case 125:
#line 332 "pt_yacc.y"
    { (yyval.integer)=PMDB_GZIP9_OUTPUT; ;}
    break;

  case 126:
#line 335 "pt_yacc.y"
    { (yyval.integer)=1; ;}
    break;

  case 127:
#line 336 "pt_yacc.y"
    { (yyval.integer)=0; ;}
    break;

  case 128:
#line 337 "pt_yacc.y"
    { (yyval.integer)=2; ;}
    break;

  case 129:
#line 338 "pt_yacc.y"
    { (yyval.integer)=3; ;}
    break;

  case 130:
#line 341 "pt_yacc.y"
    { (yyval.integer)=(yyvsp[(1) - (1)].integer); ;}
    break;

  case 131:
#line 342 "pt_yacc.y"
    { (yyval.integer)=-1; ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2407 "pt_yacc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 344 "pt_yacc.y"



