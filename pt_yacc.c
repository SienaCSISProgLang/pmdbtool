#include <sys/cdefs.h>
#ifndef lint
#if 0
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#else
__IDSTRING(yyrcsid, "$NetBSD: skeleton.c,v 1.14 1997/10/20 03:41:16 lukem Exp $");
#endif
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "pt_yacc.y"
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

   $Id$
*/
#line 34 "pt_yacc.y"
typedef union {
   char *str;
   int integer;
   double real;
   double coords[3];
   long long_val;
 } YYSTYPE;
#line 60 "y.tab.c"
#define DOUBLE 257
#define STRING 258
#define INTEGER 259
#define BOOLEAN 260
#define LONG 261
#define INDIR 262
#define OUTDIR 263
#define TRACE 264
#define MODEL 265
#define PART 266
#define INERTIAL 267
#define ORTHOGONAL 268
#define READ_SMS 269
#define WRITE_SMS 270
#define READ_SPLIT_SMS 271
#define DX 272
#define COLOR 273
#define BW 274
#define SURFACE 275
#define THREE_D 276
#define TWO_D 277
#define LOAD_BALANCE 278
#define LB_SEL_METHOD 279
#define LB_MAX_ITER 280
#define LB_MAX_INTERNAL_ITER 281
#define LB_DEBUG_LEVEL 282
#define LB_TOLERANCE 283
#define LB_INTERFACE_THRESH 284
#define LB_SLICE 285
#define LB_GEOM 286
#define LB_INERTIAL 287
#define LB_PROJECTION 288
#define LB_GEOM_PRED 289
#define LB_PROJECTION_PRED 290
#define LB_PRINT_MIGSTATS 291
#define LB_PRINT_ITBTIMES 292
#define LB_PRINT_ZOLTANTIMES 293
#define METRICS 294
#define CLEAN 295
#define REFINE 296
#define COARSEN 297
#define WEIGHT 298
#define SPHERE 299
#define BOX 300
#define COMPRESS 301
#define NONE 302
#define GZIP 303
#define GZIP9 304
#define CHECKLINKS 305
#define REPARTITION 306
#define PARMETIS 307
#define ZOLTAN 308
#define ECHO_STRING 309
#define ALL 310
#define MASTER 311
#define LOADS 312
#define MAX 313
#define AVG 314
#define LOCAL 315
#define SI 316
#define GLOBAL 317
#define DISCONN 318
#define REGION 319
#define FACE 320
#define EDGE 321
#define VERTEX 322
#define ADJACENCY 323
#define COMM_MATRIX 324
#define INT_MATRIX 325
#define CHECKMESH 326
#define MIGSTATS 327
#define RESET 328
#define PRINT 329
#define OUTPUT 330
#define DUPLICATES 331
#define WRITE_SMS_ONLY 332
#define WRITE_PMDB_ONLY 333
#define PRINTNODECOUNTS 334
#define PERCENTAGE 335
#define MODELER 336
#define PARASOLIDMODEL 337
#define SHAPESMODEL 338
#define SLEEP 339
#define COMPUTECONN 340
#define NULLMODEL 341
#define SMDMODEL 342
#define GATHER 343
#define CENTROIDS 344
#define BBOX 345
#define SET_BOUND 346
#define INIT_MESH 347
#define HEAT_SOLVE 348
#define HEAT_SOLVE_SERIAL 349
#define HEAT_SOLVE_MPI 350
#define CLEAR_HEAT 351
#define HEAT_DX 352
#define PRINT_BOUNDS 353
#define HIER 354
#define NUMLEVELS 355
#define PARTITION 356
#define LEVEL 357
#define PROC 358
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,   17,   17,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   20,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,    6,    6,    9,    9,
    9,   10,   10,    7,    7,   11,   11,   11,   11,   12,
   12,    8,    8,   13,   13,   13,   13,   14,   14,    1,
    1,    2,    2,   19,   19,   19,   21,   21,   21,   21,
   21,    3,    3,    3,    3,    3,    3,    3,    3,    4,
    5,    5,    5,    5,   15,   15,   15,   15,   16,   16,
};
short yylen[] = {                                         2,
    1,    2,    1,    2,    2,    1,    2,    2,    3,    2,
    2,    2,    0,    4,    1,    3,    1,    3,    4,    4,
    3,    4,    4,    5,    5,    2,    1,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    1,    2,    1,    2,
    3,    3,    3,    2,    3,    2,    2,    3,    2,    1,
    1,    1,    2,    2,    3,    2,    2,    2,    1,    2,
    2,    1,    1,    2,    1,    3,    2,    3,    4,    3,
    1,    2,    1,    4,    8,    8,    2,    0,    1,    1,
    1,    2,    0,    2,    0,    1,    1,    1,    1,    2,
    0,    2,    0,    1,    1,    1,    1,    2,    0,    1,
    1,    1,    1,    2,    1,    0,    1,    1,    1,    1,
    1,    0,    1,    1,    1,    1,    1,    1,    1,    7,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,   13,   15,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   17,    0,    0,    0,    0,   27,   37,    0,    0,    0,
    0,    0,    0,    0,   50,   51,   52,    0,    0,    0,
    0,   59,    0,    0,   62,   63,    0,   65,    0,    0,
    0,    0,    0,   71,    0,   73,    0,    0,    3,    4,
    5,  101,  100,    7,    8,  102,  103,    0,   10,   12,
   11,    0,  119,  113,  114,  115,  116,  117,  118,   28,
   29,   30,   31,   32,   33,   34,   35,   36,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  122,  121,  123,
  124,   26,   38,    0,    0,   44,    0,    0,    0,   46,
    0,   47,    0,    0,   49,   53,   54,    0,   56,    0,
   57,   58,  126,  125,  127,  128,   60,   61,   64,    0,
   67,    0,    0,    0,   72,    2,    9,  107,  108,  111,
  109,  110,    0,  105,   16,    0,    0,    0,   18,    0,
    0,   21,    0,    0,   41,    0,    0,   45,   42,   43,
   86,   87,   88,   89,    0,   48,   79,   80,   81,    0,
   55,   97,   96,   95,   94,    0,   66,   68,    0,   70,
   14,  104,    0,   19,   20,   22,   23,    0,    0,   74,
    0,   69,    0,   24,   25,    0,    0,    0,  130,    0,
    0,    0,    0,    0,   75,   76,  120,
};
short yydgoto[] = {                                      57,
   64,   68,   80,  147,  102,  113,  110,  119,  170,  114,
  165,  111,  176,  120,  127,  200,   58,   59,  143,   72,
  144,
};
short yysindex[] = {                                   -245,
 -248, -242, -237, -217, -209, -213, -193, -190,    0,    0,
 -176, -246, -228, -189, -169, -167, -163, -142, -141, -116,
    0, -295, -292, -215, -227,    0,    0, -115, -258, -256,
    0,    0,    0,    0,    0,    0,    0, -201,    0, -113,
 -112,    0, -221, -111,    0,    0, -109,    0, -108, -114,
 -107, -106, -105,    0, -103,    0,    0, -245,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -102,    0,    0,
    0, -151,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -101,  107,
  107,  -99,  107,  107,  -98,  107,  107,    0,    0,    0,
    0,    0,    0,  -97, -313,    0,  -96,  -95,  -94,    0,
 -285,    0,    0, -174,    0,    0,    0,  -93,    0, -184,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -91,
    0,  -90,  -89,  -88,    0,    0,    0,    0,    0,    0,
    0,    0, -143,    0,    0,  -87,  -86,  107,    0,  -85,
  107,    0,  -84,  107,    0,  -83,  -81,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -79,    0,
    0,    0,  106,    0,    0,    0,    0,  -78,  -77,    0,
 -198,    0,  -80,    0,    0, -253,  130,  -76,    0,  -75,
  -73,  -72,  -70,  134,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,  645,    0,    0,    0,    0,    0,    0,    0,
  737,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  829,    0,
  185,  185,    1,  553,    0,    0,    0,    0,  277,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  180,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -69,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  921,    0,    0,    0,    0,    0,    0,
    0,    0,  277,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  369,    0,    0,    0,    0,   93,
    0,    0,    0,    0,    0,  461,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -109,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,    0,    0,  -82,    0,  152,  159,   79,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  135,    0,    0,
   51,
};
#define YYTABLESIZE 1274
short yytable[] = {                                     104,
   78,  106,  107,   90,   91,  198,   93,   94,  148,   60,
  150,  151,   81,  153,  154,   61,    1,    2,    3,    4,
    5,   62,   63,    6,    7,    8,    9,  161,  162,  163,
   82,  164,   10,   11,   12,   13,   14,   15,   16,   92,
   65,  156,   95,  157,   69,   17,   18,   19,   20,   21,
   22,   23,   24,  108,  109,   25,  199,   66,   67,   26,
   27,   28,   29,   30,   70,  185,   31,   71,  187,   83,
   32,  189,   33,   98,   99,  100,  101,   34,   35,   36,
   37,   38,   73,   96,   97,   39,   40,   41,   42,   84,
   43,   85,   77,   44,   45,  105,   86,   46,   47,   48,
   49,   50,   51,   52,   53,   54,   55,   56,   74,   75,
   76,   77,   78,   79,  181,  123,  124,   87,   88,  125,
  126,  138,  139,  140,  141,  142,  116,  117,  118,  138,
  139,  140,  141,  142,  172,  173,  174,  175,  167,  168,
  169,   89,  131,  103,  121,  122,  146,  128,  129,  193,
  130,  132,  133,  134,  135,  137,  145,  149,  152,  196,
  155,  158,  159,  160,  171,  177,  178,  179,  180,  183,
  184,  186,  188,  201,  207,  190,  197,  191,  192,    1,
  194,  195,  203,  204,   85,  115,  205,  206,  106,  202,
  112,  166,  136,  182,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   78,   78,   78,   78,   78,    0,    0,   78,
   78,   78,   78,    0,    0,    0,   93,    0,   78,   78,
   78,   78,   78,   78,   78,    0,    0,    0,    0,    0,
    0,   78,   78,   78,   78,   78,   78,   78,   78,    0,
    0,   78,    0,    0,    0,   78,   78,   78,   78,   78,
    0,    0,   78,   83,   83,   83,   78,    0,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,    0,    0,
    0,   78,   78,   78,   78,    0,   78,    0,    0,   78,
   78,    0,    0,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   77,   77,   77,   77,   77,    0,
    0,   77,   77,   77,   77,    0,    0,    0,   84,    0,
   77,   77,   77,   77,   77,   77,   77,    0,    0,    0,
    0,    0,    0,   77,   77,   77,   77,   77,   77,   77,
   77,    0,    0,   77,    0,    0,    0,   77,   77,   77,
   77,   77,    0,    0,   77,   82,   82,   82,   77,    0,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
    0,    0,    0,   77,   77,   77,   77,    0,   77,    0,
    0,   77,   77,    0,    0,   77,   77,   77,   77,   77,
   77,   77,   77,   77,   77,   77,   85,   85,   85,   85,
   85,    0,    0,   85,   85,   85,   85,    0,    0,    0,
   92,    0,   85,   85,   85,   85,   85,   85,   85,    0,
    0,    0,    0,    0,    0,   85,   85,   85,   85,   85,
   85,   85,   85,    0,    0,   85,    0,    0,    0,   85,
   85,   85,   85,   85,    0,    0,   85,   91,   91,   91,
   85,   91,   85,    0,    0,    0,    0,   85,   85,   85,
   85,   85,    0,    0,    0,   85,   85,   85,   85,    0,
   85,    0,    0,   85,   85,    0,    0,   85,   85,   85,
   85,   85,   85,   85,   85,   85,   85,   85,   93,   93,
   93,   93,   93,    0,    0,   93,   93,   93,   93,    0,
    0,    0,   78,    0,   93,   93,   93,   93,   93,   93,
   93,    0,    0,    0,    0,    0,    0,   93,   93,   93,
   93,   93,   93,   93,   93,    0,    0,   93,    0,    0,
    0,   93,   93,   93,   93,   93,    0,    0,   93,    0,
    0,    0,   93,    0,   93,   99,   99,   99,   99,   93,
   93,   93,   93,   93,    0,    0,    0,   93,   93,   93,
   93,    0,   93,    0,    0,   93,   93,    0,    0,   93,
   93,   93,   93,   93,   93,   93,   93,   93,   93,   93,
   84,   84,   84,   84,   84,    0,    0,   84,   84,   84,
   84,    0,    0,    0,    6,    0,   84,   84,   84,   84,
   84,   84,   84,    0,    0,    0,    0,    0,    0,   84,
   84,   84,   84,   84,   84,   84,   84,    0,    0,   84,
    0,    0,    0,   84,   84,   84,   84,   84,    0,    0,
   84,   90,   90,   90,   84,   90,   84,    0,    0,    0,
    0,   84,   84,   84,   84,   84,    0,    0,    0,   84,
   84,   84,   84,    0,   84,    0,    0,   84,   84,    0,
    0,   84,   84,   84,   84,   84,   84,   84,   84,   84,
   84,   84,   92,   92,   92,   92,   92,    0,    0,   92,
   92,   92,   92,    0,    0,    0,  112,    0,   92,   92,
   92,   92,   92,   92,   92,    0,    0,    0,    0,    0,
    0,   92,   92,   92,   92,   92,   92,   92,   92,    0,
    0,   92,    0,    0,    0,   92,   92,   92,   92,   92,
    0,    0,   92,    0,    0,    0,   92,    0,   92,   98,
   98,   98,   98,   92,   92,   92,   92,   92,    0,    0,
    0,   92,   92,   92,   92,    0,   92,    0,    0,   92,
   92,    0,    0,   92,   92,   92,   92,   92,   92,   92,
   92,   92,   92,   92,   78,   78,   78,   78,   78,    0,
    0,   78,   78,   78,   78,    0,    0,    0,   39,    0,
   78,   78,   78,   78,   78,   78,   78,    0,    0,    0,
    0,    0,    0,   78,   78,   78,   78,   78,   78,   78,
   78,    0,    0,   78,    0,    0,    0,   78,   78,   78,
   78,   78,    0,    0,   78,   83,   83,   83,   78,    0,
   78,    0,    0,    0,    0,   78,   78,   78,   78,   78,
    0,    0,    0,   78,   78,   78,   78,    0,   78,    0,
    0,   78,   78,    0,    0,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,    6,    6,    6,    6,
    6,    0,    0,    6,    6,    6,    6,    0,    0,    0,
   40,    0,    6,    6,    6,    6,    6,    6,    6,    0,
    0,    0,    0,    0,    0,    6,    6,    6,    6,    6,
    6,    6,    6,    0,    0,    6,    0,    0,    0,    6,
    6,    6,    6,    6,    0,    0,    6,    0,    0,    0,
    6,    0,    6,    0,    0,    0,    0,    6,    6,    6,
    6,    6,    0,    0,    0,    6,    6,    6,    6,    0,
    6,    0,    0,    6,    6,    0,    0,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,  112,  112,
  112,  112,  112,    0,    0,  112,  112,  112,  112,    0,
    0,    0,    0,    0,  112,  112,  112,  112,  112,  112,
  112,    0,    0,    0,    0,    0,    0,  112,  112,  112,
  112,  112,  112,  112,  112,    0,    0,  112,    0,    0,
    0,  112,  112,  112,  112,  112,    0,    0,  112,    0,
    0,    0,  112,    0,  112,    0,    0,    0,    0,  112,
  112,  112,  112,  112,    0,    0,    0,  112,  112,  112,
  112,    0,  112,    0,    0,  112,  112,    0,    0,  112,
  112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
   39,   39,   39,   39,   39,    0,    0,   39,   39,   39,
   39,    0,    0,    0,    0,    0,   39,   39,   39,   39,
   39,   39,   39,    0,    0,    0,    0,    0,    0,   39,
   39,   39,   39,   39,   39,   39,   39,    0,    0,   39,
    0,    0,    0,   39,   39,   39,   39,   39,    0,    0,
   39,    0,    0,    0,   39,    0,   39,    0,    0,    0,
    0,   39,   39,   39,   39,   39,    0,    0,    0,   39,
   39,   39,   39,    0,   39,    0,    0,   39,   39,    0,
    0,   39,   39,   39,   39,   39,   39,   39,   39,   39,
   39,   39,   40,   40,   40,   40,   40,    0,    0,   40,
   40,   40,   40,    0,    0,    0,    0,    0,   40,   40,
   40,   40,   40,   40,   40,    0,    0,    0,    0,    0,
    0,   40,   40,   40,   40,   40,   40,   40,   40,    0,
    0,   40,    0,    0,    0,   40,   40,   40,   40,   40,
    0,    0,   40,    0,    0,    0,   40,    0,   40,    0,
    0,    0,    0,   40,   40,   40,   40,   40,    0,    0,
    0,   40,   40,   40,   40,    0,   40,    0,    0,   40,
   40,    0,    0,   40,   40,   40,   40,   40,   40,   40,
   40,   40,   40,   40,
};
short yycheck[] = {                                     258,
    0,  258,  259,  299,  300,  259,  299,  300,   91,  258,
   93,   94,  259,   96,   97,  258,  262,  263,  264,  265,
  266,  259,  260,  269,  270,  271,  272,  313,  314,  315,
  259,  317,  278,  279,  280,  281,  282,  283,  284,  335,
  258,  355,  335,  357,  258,  291,  292,  293,  294,  295,
  296,  297,  298,  310,  311,  301,  310,  267,  268,  305,
  306,  307,  308,  309,  258,  148,  312,  258,  151,  259,
  316,  154,  318,  301,  302,  303,  304,  323,  324,  325,
  326,  327,  259,  299,  300,  331,  332,  333,  334,  259,
  336,  259,    0,  339,  340,  354,  260,  343,  344,  345,
  346,  347,  348,  349,  350,  351,  352,  353,  285,  286,
  287,  288,  289,  290,  258,  337,  338,  260,  260,  341,
  342,  273,  274,  275,  276,  277,  328,  329,  330,  273,
  274,  275,  276,  277,  319,  320,  321,  322,  313,  314,
  315,  258,  257,  259,  258,  258,   40,  259,  258,   44,
  259,  259,  259,  259,  258,  258,  258,  257,  257,  358,
  258,  258,  258,  258,  258,  257,  257,  257,  257,  257,
  257,  257,  257,   44,   41,  259,  257,  259,  258,    0,
  259,  259,  258,  257,    0,   34,  259,  258,  258,  266,
   32,  113,   58,  143,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  262,  263,  264,  265,  266,   -1,   -1,  269,
  270,  271,  272,   -1,   -1,   -1,    0,   -1,  278,  279,
  280,  281,  282,  283,  284,   -1,   -1,   -1,   -1,   -1,
   -1,  291,  292,  293,  294,  295,  296,  297,  298,   -1,
   -1,  301,   -1,   -1,   -1,  305,  306,  307,  308,  309,
   -1,   -1,  312,  313,  314,  315,  316,   -1,  318,  319,
  320,  321,  322,  323,  324,  325,  326,  327,   -1,   -1,
   -1,  331,  332,  333,  334,   -1,  336,   -1,   -1,  339,
  340,   -1,   -1,  343,  344,  345,  346,  347,  348,  349,
  350,  351,  352,  353,  262,  263,  264,  265,  266,   -1,
   -1,  269,  270,  271,  272,   -1,   -1,   -1,    0,   -1,
  278,  279,  280,  281,  282,  283,  284,   -1,   -1,   -1,
   -1,   -1,   -1,  291,  292,  293,  294,  295,  296,  297,
  298,   -1,   -1,  301,   -1,   -1,   -1,  305,  306,  307,
  308,  309,   -1,   -1,  312,  313,  314,  315,  316,   -1,
  318,  319,  320,  321,  322,  323,  324,  325,  326,  327,
   -1,   -1,   -1,  331,  332,  333,  334,   -1,  336,   -1,
   -1,  339,  340,   -1,   -1,  343,  344,  345,  346,  347,
  348,  349,  350,  351,  352,  353,  262,  263,  264,  265,
  266,   -1,   -1,  269,  270,  271,  272,   -1,   -1,   -1,
    0,   -1,  278,  279,  280,  281,  282,  283,  284,   -1,
   -1,   -1,   -1,   -1,   -1,  291,  292,  293,  294,  295,
  296,  297,  298,   -1,   -1,  301,   -1,   -1,   -1,  305,
  306,  307,  308,  309,   -1,   -1,  312,  313,  314,  315,
  316,  317,  318,   -1,   -1,   -1,   -1,  323,  324,  325,
  326,  327,   -1,   -1,   -1,  331,  332,  333,  334,   -1,
  336,   -1,   -1,  339,  340,   -1,   -1,  343,  344,  345,
  346,  347,  348,  349,  350,  351,  352,  353,  262,  263,
  264,  265,  266,   -1,   -1,  269,  270,  271,  272,   -1,
   -1,   -1,    0,   -1,  278,  279,  280,  281,  282,  283,
  284,   -1,   -1,   -1,   -1,   -1,   -1,  291,  292,  293,
  294,  295,  296,  297,  298,   -1,   -1,  301,   -1,   -1,
   -1,  305,  306,  307,  308,  309,   -1,   -1,  312,   -1,
   -1,   -1,  316,   -1,  318,  319,  320,  321,  322,  323,
  324,  325,  326,  327,   -1,   -1,   -1,  331,  332,  333,
  334,   -1,  336,   -1,   -1,  339,  340,   -1,   -1,  343,
  344,  345,  346,  347,  348,  349,  350,  351,  352,  353,
  262,  263,  264,  265,  266,   -1,   -1,  269,  270,  271,
  272,   -1,   -1,   -1,    0,   -1,  278,  279,  280,  281,
  282,  283,  284,   -1,   -1,   -1,   -1,   -1,   -1,  291,
  292,  293,  294,  295,  296,  297,  298,   -1,   -1,  301,
   -1,   -1,   -1,  305,  306,  307,  308,  309,   -1,   -1,
  312,  313,  314,  315,  316,  317,  318,   -1,   -1,   -1,
   -1,  323,  324,  325,  326,  327,   -1,   -1,   -1,  331,
  332,  333,  334,   -1,  336,   -1,   -1,  339,  340,   -1,
   -1,  343,  344,  345,  346,  347,  348,  349,  350,  351,
  352,  353,  262,  263,  264,  265,  266,   -1,   -1,  269,
  270,  271,  272,   -1,   -1,   -1,    0,   -1,  278,  279,
  280,  281,  282,  283,  284,   -1,   -1,   -1,   -1,   -1,
   -1,  291,  292,  293,  294,  295,  296,  297,  298,   -1,
   -1,  301,   -1,   -1,   -1,  305,  306,  307,  308,  309,
   -1,   -1,  312,   -1,   -1,   -1,  316,   -1,  318,  319,
  320,  321,  322,  323,  324,  325,  326,  327,   -1,   -1,
   -1,  331,  332,  333,  334,   -1,  336,   -1,   -1,  339,
  340,   -1,   -1,  343,  344,  345,  346,  347,  348,  349,
  350,  351,  352,  353,  262,  263,  264,  265,  266,   -1,
   -1,  269,  270,  271,  272,   -1,   -1,   -1,    0,   -1,
  278,  279,  280,  281,  282,  283,  284,   -1,   -1,   -1,
   -1,   -1,   -1,  291,  292,  293,  294,  295,  296,  297,
  298,   -1,   -1,  301,   -1,   -1,   -1,  305,  306,  307,
  308,  309,   -1,   -1,  312,  313,  314,  315,  316,   -1,
  318,   -1,   -1,   -1,   -1,  323,  324,  325,  326,  327,
   -1,   -1,   -1,  331,  332,  333,  334,   -1,  336,   -1,
   -1,  339,  340,   -1,   -1,  343,  344,  345,  346,  347,
  348,  349,  350,  351,  352,  353,  262,  263,  264,  265,
  266,   -1,   -1,  269,  270,  271,  272,   -1,   -1,   -1,
    0,   -1,  278,  279,  280,  281,  282,  283,  284,   -1,
   -1,   -1,   -1,   -1,   -1,  291,  292,  293,  294,  295,
  296,  297,  298,   -1,   -1,  301,   -1,   -1,   -1,  305,
  306,  307,  308,  309,   -1,   -1,  312,   -1,   -1,   -1,
  316,   -1,  318,   -1,   -1,   -1,   -1,  323,  324,  325,
  326,  327,   -1,   -1,   -1,  331,  332,  333,  334,   -1,
  336,   -1,   -1,  339,  340,   -1,   -1,  343,  344,  345,
  346,  347,  348,  349,  350,  351,  352,  353,  262,  263,
  264,  265,  266,   -1,   -1,  269,  270,  271,  272,   -1,
   -1,   -1,   -1,   -1,  278,  279,  280,  281,  282,  283,
  284,   -1,   -1,   -1,   -1,   -1,   -1,  291,  292,  293,
  294,  295,  296,  297,  298,   -1,   -1,  301,   -1,   -1,
   -1,  305,  306,  307,  308,  309,   -1,   -1,  312,   -1,
   -1,   -1,  316,   -1,  318,   -1,   -1,   -1,   -1,  323,
  324,  325,  326,  327,   -1,   -1,   -1,  331,  332,  333,
  334,   -1,  336,   -1,   -1,  339,  340,   -1,   -1,  343,
  344,  345,  346,  347,  348,  349,  350,  351,  352,  353,
  262,  263,  264,  265,  266,   -1,   -1,  269,  270,  271,
  272,   -1,   -1,   -1,   -1,   -1,  278,  279,  280,  281,
  282,  283,  284,   -1,   -1,   -1,   -1,   -1,   -1,  291,
  292,  293,  294,  295,  296,  297,  298,   -1,   -1,  301,
   -1,   -1,   -1,  305,  306,  307,  308,  309,   -1,   -1,
  312,   -1,   -1,   -1,  316,   -1,  318,   -1,   -1,   -1,
   -1,  323,  324,  325,  326,  327,   -1,   -1,   -1,  331,
  332,  333,  334,   -1,  336,   -1,   -1,  339,  340,   -1,
   -1,  343,  344,  345,  346,  347,  348,  349,  350,  351,
  352,  353,  262,  263,  264,  265,  266,   -1,   -1,  269,
  270,  271,  272,   -1,   -1,   -1,   -1,   -1,  278,  279,
  280,  281,  282,  283,  284,   -1,   -1,   -1,   -1,   -1,
   -1,  291,  292,  293,  294,  295,  296,  297,  298,   -1,
   -1,  301,   -1,   -1,   -1,  305,  306,  307,  308,  309,
   -1,   -1,  312,   -1,   -1,   -1,  316,   -1,  318,   -1,
   -1,   -1,   -1,  323,  324,  325,  326,  327,   -1,   -1,
   -1,  331,  332,  333,  334,   -1,  336,   -1,   -1,  339,
  340,   -1,   -1,  343,  344,  345,  346,  347,  348,  349,
  350,  351,  352,  353,
};
#define YYFINAL 57
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 358
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"DOUBLE","STRING",
"INTEGER","BOOLEAN","LONG","INDIR","OUTDIR","TRACE","MODEL","PART","INERTIAL",
"ORTHOGONAL","READ_SMS","WRITE_SMS","READ_SPLIT_SMS","DX","COLOR","BW",
"SURFACE","THREE_D","TWO_D","LOAD_BALANCE","LB_SEL_METHOD","LB_MAX_ITER",
"LB_MAX_INTERNAL_ITER","LB_DEBUG_LEVEL","LB_TOLERANCE","LB_INTERFACE_THRESH",
"LB_SLICE","LB_GEOM","LB_INERTIAL","LB_PROJECTION","LB_GEOM_PRED",
"LB_PROJECTION_PRED","LB_PRINT_MIGSTATS","LB_PRINT_ITBTIMES",
"LB_PRINT_ZOLTANTIMES","METRICS","CLEAN","REFINE","COARSEN","WEIGHT","SPHERE",
"BOX","COMPRESS","NONE","GZIP","GZIP9","CHECKLINKS","REPARTITION","PARMETIS",
"ZOLTAN","ECHO_STRING","ALL","MASTER","LOADS","MAX","AVG","LOCAL","SI","GLOBAL",
"DISCONN","REGION","FACE","EDGE","VERTEX","ADJACENCY","COMM_MATRIX",
"INT_MATRIX","CHECKMESH","MIGSTATS","RESET","PRINT","OUTPUT","DUPLICATES",
"WRITE_SMS_ONLY","WRITE_PMDB_ONLY","PRINTNODECOUNTS","PERCENTAGE","MODELER",
"PARASOLIDMODEL","SHAPESMODEL","SLEEP","COMPUTECONN","NULLMODEL","SMDMODEL",
"GATHER","CENTROIDS","BBOX","SET_BOUND","INIT_MESH","HEAT_SOLVE",
"HEAT_SOLVE_SERIAL","HEAT_SOLVE_MPI","CLEAR_HEAT","HEAT_DX","PRINT_BOUNDS",
"HIER","NUMLEVELS","PARTITION","LEVEL","PROC",
};
char *yyrule[] = {
"$accept : strt",
"strt : commands",
"commands : commands command",
"commands : command",
"command : INDIR STRING",
"command : OUTDIR STRING",
"command : TRACE",
"command : TRACE bool",
"command : MODEL STRING",
"command : PART part_type STRING",
"command : READ_SMS STRING",
"command : READ_SPLIT_SMS STRING",
"command : WRITE_SMS STRING",
"$$1 :",
"command : DX $$1 dx_opts STRING",
"command : LOAD_BALANCE",
"command : METRICS STRING STRING",
"command : CLEAN",
"command : REFINE PERCENTAGE DOUBLE",
"command : REFINE SPHERE point DOUBLE",
"command : REFINE BOX point point",
"command : COARSEN PERCENTAGE DOUBLE",
"command : COARSEN SPHERE point DOUBLE",
"command : COARSEN BOX point point",
"command : WEIGHT SPHERE point DOUBLE INTEGER",
"command : WEIGHT BOX point point INTEGER",
"command : COMPRESS compression",
"command : CHECKLINKS",
"command : LB_SEL_METHOD lb_type",
"command : LB_MAX_ITER INTEGER",
"command : LB_MAX_INTERNAL_ITER INTEGER",
"command : LB_DEBUG_LEVEL INTEGER",
"command : LB_TOLERANCE INTEGER",
"command : LB_INTERFACE_THRESH INTEGER",
"command : LB_PRINT_MIGSTATS BOOLEAN",
"command : LB_PRINT_ITBTIMES BOOLEAN",
"command : LB_PRINT_ZOLTANTIMES BOOLEAN",
"command : REPARTITION",
"command : PARMETIS INTEGER",
"command : ZOLTAN",
"command : ZOLTAN STRING",
"command : ZOLTAN STRING STRING",
"command : ECHO_STRING ALL STRING",
"command : ECHO_STRING MASTER STRING",
"command : ECHO_STRING STRING",
"command : ECHO_STRING INTEGER STRING",
"command : LOADS maxavglocalglobal",
"command : SI maxavglocalglobal",
"command : DISCONN maxavglocal entity_types",
"command : ADJACENCY maxavglocal",
"command : COMM_MATRIX",
"command : INT_MATRIX",
"command : CHECKMESH",
"command : MIGSTATS RESET",
"command : MIGSTATS PRINT",
"command : MIGSTATS OUTPUT STRING",
"command : DUPLICATES entity_types",
"command : WRITE_SMS_ONLY STRING",
"command : WRITE_PMDB_ONLY STRING",
"command : PRINTNODECOUNTS",
"command : MODELER modeler_type",
"command : SLEEP INTEGER",
"command : COMPUTECONN",
"command : GATHER",
"command : CENTROIDS STRING",
"command : BBOX",
"command : SET_BOUND INTEGER DOUBLE",
"command : INIT_MESH DOUBLE",
"command : HEAT_SOLVE INTEGER DOUBLE",
"command : HEAT_SOLVE_SERIAL INTEGER DOUBLE STRING",
"command : HEAT_SOLVE_MPI INTEGER DOUBLE",
"command : CLEAR_HEAT",
"command : HEAT_DX STRING",
"command : PRINT_BOUNDS",
"command : ZOLTAN HIER NUMLEVELS INTEGER",
"command : ZOLTAN HIER LEVEL INTEGER PROC INTEGER PART INTEGER",
"command : ZOLTAN HIER LEVEL INTEGER PROC procnum STRING STRING",
"maxavglocal : more_mals one_mal",
"maxavglocal :",
"one_mal : MAX",
"one_mal : AVG",
"one_mal : LOCAL",
"more_mals : more_mals one_mal",
"more_mals :",
"maxavglocalglobal : more_malgs one_malg",
"maxavglocalglobal :",
"one_malg : MAX",
"one_malg : AVG",
"one_malg : LOCAL",
"one_malg : GLOBAL",
"more_malgs : more_malgs one_malg",
"more_malgs :",
"entity_types : more_types one_type",
"entity_types :",
"one_type : VERTEX",
"one_type : EDGE",
"one_type : FACE",
"one_type : REGION",
"more_types : more_types one_type",
"more_types :",
"bool : BOOLEAN",
"bool : INTEGER",
"part_type : INERTIAL",
"part_type : ORTHOGONAL",
"dx_opts : dx_opts dx_opt",
"dx_opts : dx_opt",
"dx_opts :",
"dx_opt : COLOR",
"dx_opt : BW",
"dx_opt : THREE_D",
"dx_opt : TWO_D",
"dx_opt : SURFACE",
"lb_type :",
"lb_type : LB_SLICE",
"lb_type : LB_GEOM",
"lb_type : LB_INERTIAL",
"lb_type : LB_PROJECTION",
"lb_type : LB_GEOM_PRED",
"lb_type : LB_PROJECTION_PRED",
"lb_type : INTEGER",
"point : '(' DOUBLE ',' DOUBLE ',' DOUBLE ')'",
"compression : NONE",
"compression : COMPRESS",
"compression : GZIP",
"compression : GZIP9",
"modeler_type : SHAPESMODEL",
"modeler_type : PARASOLIDMODEL",
"modeler_type : NULLMODEL",
"modeler_type : SMDMODEL",
"procnum : INTEGER",
"procnum : ALL",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 345 "pt_yacc.y"

#line 725 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
int yyparse __P((void));
static int yygrowstack __P((void));
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    if ((newss = (short *)realloc(yyss, newsize * sizeof *newss)) == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    if ((newvs = (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs)) == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    int yym, yyn, yystate;
#if YYDEBUG
    char *yys;

    if ((yys = getenv("YYDEBUG")) != NULL)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
    goto yynewerror;
yynewerror:
    yyerror("syntax error");
    goto yyerrlab;
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 4:
#line 170 "pt_yacc.y"
{ pt_set_input_dir(yyvsp[0].str); }
break;
case 5:
#line 171 "pt_yacc.y"
{ pt_set_output_dir(yyvsp[0].str); }
break;
case 6:
#line 172 "pt_yacc.y"
{ pt_trace_on(1); }
break;
case 7:
#line 173 "pt_yacc.y"
{ pt_trace_on(yyvsp[0].integer); }
break;
case 8:
#line 174 "pt_yacc.y"
{ pt_read_model(yyvsp[0].str); }
break;
case 9:
#line 175 "pt_yacc.y"
{ pt_init_part(yyvsp[-1].integer, yyvsp[0].str); }
break;
case 10:
#line 176 "pt_yacc.y"
{ pt_read_sms(yyvsp[0].str); }
break;
case 11:
#line 177 "pt_yacc.y"
{ pt_read_split_sms(yyvsp[0].str); }
break;
case 12:
#line 178 "pt_yacc.y"
{ pt_write_sms(yyvsp[0].str); }
break;
case 13:
#line 179 "pt_yacc.y"
{ pt_dx_opt_init(); }
break;
case 14:
#line 179 "pt_yacc.y"
{ pt_write_dx(yyvsp[0].str); }
break;
case 15:
#line 180 "pt_yacc.y"
{ pt_load_balance(); }
break;
case 16:
#line 181 "pt_yacc.y"
{ pt_metrics(yyvsp[-1].str, yyvsp[0].str); }
break;
case 17:
#line 182 "pt_yacc.y"
{ pt_clean(); }
break;
case 18:
#line 183 "pt_yacc.y"
{ pt_refine_percentage(yyvsp[0].real, 1); }
break;
case 19:
#line 184 "pt_yacc.y"
{ pt_refine_sphere(yyvsp[-1].coords, yyvsp[0].real, 1); }
break;
case 20:
#line 185 "pt_yacc.y"
{ pt_refine_box(yyvsp[-1].coords, yyvsp[0].coords, 1); }
break;
case 21:
#line 186 "pt_yacc.y"
{ pt_refine_percentage(yyvsp[0].real, 0); }
break;
case 22:
#line 187 "pt_yacc.y"
{ pt_refine_sphere(yyvsp[-1].coords, yyvsp[0].real, 0); }
break;
case 23:
#line 188 "pt_yacc.y"
{ pt_refine_box(yyvsp[-1].coords, yyvsp[0].coords, 0); }
break;
case 24:
#line 189 "pt_yacc.y"
{ pt_weight_sphere(yyvsp[-2].coords, yyvsp[-1].real, yyvsp[0].integer); }
break;
case 25:
#line 190 "pt_yacc.y"
{ pt_weight_box(yyvsp[-2].coords, yyvsp[-1].coords, yyvsp[0].integer); }
break;
case 26:
#line 191 "pt_yacc.y"
{ pt_set_compression(yyvsp[0].integer); }
break;
case 27:
#line 192 "pt_yacc.y"
{ pt_check_links(); }
break;
case 28:
#line 193 "pt_yacc.y"
{ pt_set_lb_int_param(PMDB_LB_SEL_METHOD, yyvsp[0].integer); }
break;
case 29:
#line 194 "pt_yacc.y"
{ pt_set_lb_int_param(PMDB_LB_MAX_ITER, yyvsp[0].integer); }
break;
case 30:
#line 195 "pt_yacc.y"
{
     pt_set_lb_int_param(PMDB_LB_MAX_INTERNAL_ITER, yyvsp[0].integer); }
break;
case 31:
#line 197 "pt_yacc.y"
{ pt_set_lb_int_param(PMDB_LB_DEBUG_LEVEL, yyvsp[0].integer); }
break;
case 32:
#line 198 "pt_yacc.y"
{ 
     pt_set_lb_long_param(PMDB_LB_TOLERANCE, (long)yyvsp[0].integer); }
break;
case 33:
#line 200 "pt_yacc.y"
{ 
     pt_set_lb_int_param(PMDB_LB_INTERFACE_THRESH, yyvsp[0].integer); }
break;
case 34:
#line 202 "pt_yacc.y"
{
     pt_set_lb_int_param(PMDB_LB_PRINT_MIGSTATS, yyvsp[0].integer); }
break;
case 35:
#line 204 "pt_yacc.y"
{
     pt_set_lb_int_param(PMDB_LB_PRINT_ITBTIMES, yyvsp[0].integer); }
break;
case 36:
#line 206 "pt_yacc.y"
{
     pt_set_lb_int_param(PMDB_LB_PRINT_ZOLTANTIMES, yyvsp[0].integer); }
break;
case 37:
#line 208 "pt_yacc.y"
{ pt_repartition(); }
break;
case 38:
#line 209 "pt_yacc.y"
{ pt_parmetis(yyvsp[0].integer); }
break;
case 39:
#line 210 "pt_yacc.y"
{ pt_zoltan(); }
break;
case 40:
#line 211 "pt_yacc.y"
{ pt_zoltan_read_paramfile(yyvsp[0].str); }
break;
case 41:
#line 212 "pt_yacc.y"
{ pt_zoltan_setparam(yyvsp[-1].str,yyvsp[0].str); }
break;
case 42:
#line 213 "pt_yacc.y"
{ pt_printall(yyvsp[0].str); }
break;
case 43:
#line 214 "pt_yacc.y"
{ pt_printone(0,yyvsp[0].str); }
break;
case 44:
#line 215 "pt_yacc.y"
{ pt_printone(0,yyvsp[0].str); }
break;
case 45:
#line 216 "pt_yacc.y"
{ pt_printone(yyvsp[-1].integer,yyvsp[0].str); }
break;
case 46:
#line 217 "pt_yacc.y"
{ pt_print_loads(yyvsp[0].integer); }
break;
case 47:
#line 218 "pt_yacc.y"
{ pt_print_si(yyvsp[0].integer); }
break;
case 48:
#line 219 "pt_yacc.y"
{ pt_print_disconn(yyvsp[-1].integer, yyvsp[0].integer); }
break;
case 49:
#line 220 "pt_yacc.y"
{ pt_print_adj(yyvsp[0].integer); }
break;
case 50:
#line 221 "pt_yacc.y"
{ pt_print_comm_matrix(); }
break;
case 51:
#line 222 "pt_yacc.y"
{ pt_print_int_matrix(); }
break;
case 52:
#line 223 "pt_yacc.y"
{ pt_check_mesh(); }
break;
case 53:
#line 224 "pt_yacc.y"
{ pt_reset_migstats(); }
break;
case 54:
#line 225 "pt_yacc.y"
{ pt_print_migstats(); }
break;
case 55:
#line 226 "pt_yacc.y"
{ pt_output_migstats(yyvsp[0].str); }
break;
case 56:
#line 227 "pt_yacc.y"
{ pt_print_duplicate_overhead(yyvsp[0].integer); }
break;
case 57:
#line 228 "pt_yacc.y"
{ pt_write_sms_only(yyvsp[0].str); }
break;
case 58:
#line 229 "pt_yacc.y"
{ pt_write_pmdb_only(yyvsp[0].str); }
break;
case 59:
#line 230 "pt_yacc.y"
{ pt_print_nodecounts(); }
break;
case 60:
#line 231 "pt_yacc.y"
{ pt_set_modeler(yyvsp[0].integer); }
break;
case 61:
#line 232 "pt_yacc.y"
{ pt_sleep(yyvsp[0].integer); }
break;
case 62:
#line 233 "pt_yacc.y"
{ pt_set_compute_conn(); }
break;
case 63:
#line 234 "pt_yacc.y"
{ pt_gather_to_master(); }
break;
case 64:
#line 235 "pt_yacc.y"
{ pt_write_centroids(yyvsp[0].str); }
break;
case 65:
#line 236 "pt_yacc.y"
{ pt_print_bbox(); }
break;
case 66:
#line 237 "pt_yacc.y"
{ pt_set_bound(yyvsp[-1].integer,yyvsp[0].real); }
break;
case 67:
#line 238 "pt_yacc.y"
{ pt_initialize_mesh(yyvsp[0].real); }
break;
case 68:
#line 239 "pt_yacc.y"
{ pt_heat_solve(yyvsp[-1].integer,yyvsp[0].real); }
break;
case 69:
#line 240 "pt_yacc.y"
{ pt_heat_solve_serial(yyvsp[-2].integer,yyvsp[-1].real,yyvsp[0].str); }
break;
case 70:
#line 241 "pt_yacc.y"
{ pt_heat_solve_mpi(yyvsp[-1].integer,yyvsp[0].real); }
break;
case 71:
#line 242 "pt_yacc.y"
{ pt_clear_regions("heat"); }
break;
case 72:
#line 243 "pt_yacc.y"
{ pt_heat_write_dx(yyvsp[0].str,pt_get_pmeshpb(),0,0,com_wall_time()); }
break;
case 73:
#line 244 "pt_yacc.y"
{ pt_print_bounds(); }
break;
case 74:
#line 245 "pt_yacc.y"
{ pt_hier_set_num_levels(yyvsp[0].integer); }
break;
case 75:
#line 246 "pt_yacc.y"
{ 
     if (yyvsp[-2].integer == COM_PID || yyvsp[-2].integer == -1) pt_hier_set_partition(yyvsp[-4].integer, yyvsp[0].integer);
   }
break;
case 76:
#line 249 "pt_yacc.y"
{ 
     if (yyvsp[-2].integer == COM_PID || yyvsp[-2].integer == -1) pt_hier_set_param(yyvsp[-4].integer, yyvsp[-1].str, yyvsp[0].str); 
   }
break;
case 77:
#line 254 "pt_yacc.y"
{ yyval.integer=yyvsp[-1].integer|yyvsp[0].integer; }
break;
case 78:
#line 255 "pt_yacc.y"
{ yyval.integer=0; }
break;
case 79:
#line 258 "pt_yacc.y"
{ yyval.integer=PT_MAX; }
break;
case 80:
#line 259 "pt_yacc.y"
{ yyval.integer=PT_AVG; }
break;
case 81:
#line 260 "pt_yacc.y"
{ yyval.integer=PT_LOCAL; }
break;
case 82:
#line 263 "pt_yacc.y"
{ yyval.integer=yyvsp[-1].integer|yyvsp[0].integer; }
break;
case 83:
#line 264 "pt_yacc.y"
{ yyval.integer=0; }
break;
case 84:
#line 267 "pt_yacc.y"
{ yyval.integer=yyvsp[-1].integer|yyvsp[0].integer; }
break;
case 85:
#line 268 "pt_yacc.y"
{ yyval.integer=0; }
break;
case 86:
#line 271 "pt_yacc.y"
{ yyval.integer=PT_MAX; }
break;
case 87:
#line 272 "pt_yacc.y"
{ yyval.integer=PT_AVG; }
break;
case 88:
#line 273 "pt_yacc.y"
{ yyval.integer=PT_LOCAL; }
break;
case 89:
#line 274 "pt_yacc.y"
{ yyval.integer=PT_GLOBAL; }
break;
case 90:
#line 277 "pt_yacc.y"
{ yyval.integer=yyvsp[-1].integer|yyvsp[0].integer; }
break;
case 91:
#line 278 "pt_yacc.y"
{ yyval.integer=0; }
break;
case 92:
#line 281 "pt_yacc.y"
{ yyval.integer=yyvsp[-1].integer|yyvsp[0].integer; }
break;
case 93:
#line 282 "pt_yacc.y"
{ yyval.integer=0; }
break;
case 94:
#line 285 "pt_yacc.y"
{ yyval.integer=PT_VERTEX; }
break;
case 95:
#line 286 "pt_yacc.y"
{ yyval.integer=PT_EDGE; }
break;
case 96:
#line 287 "pt_yacc.y"
{ yyval.integer=PT_FACE; }
break;
case 97:
#line 288 "pt_yacc.y"
{ yyval.integer=PT_REGION; }
break;
case 98:
#line 291 "pt_yacc.y"
{ yyval.integer=yyvsp[-1].integer|yyvsp[0].integer; }
break;
case 99:
#line 292 "pt_yacc.y"
{ yyval.integer=0; }
break;
case 100:
#line 295 "pt_yacc.y"
{ yyval.integer=yyvsp[0].integer; }
break;
case 101:
#line 296 "pt_yacc.y"
{ if (yyvsp[0].integer) {yyval.integer=1;} else {yyval.integer=0;} }
break;
case 102:
#line 299 "pt_yacc.y"
{ yyval.integer=PT_PART_INERTIAL; }
break;
case 103:
#line 300 "pt_yacc.y"
{ yyval.integer=PT_PART_ORTHOGONAL; }
break;
case 107:
#line 308 "pt_yacc.y"
{ pt_dx_opt_color(); }
break;
case 108:
#line 309 "pt_yacc.y"
{ pt_dx_opt_bw(); }
break;
case 109:
#line 310 "pt_yacc.y"
{ pt_dx_opt_3d(); }
break;
case 110:
#line 311 "pt_yacc.y"
{ pt_dx_opt_2d(); }
break;
case 111:
#line 312 "pt_yacc.y"
{ pt_dx_opt_sur(); }
break;
case 112:
#line 315 "pt_yacc.y"
{ yyval.integer=PMDB_LB_SLICE; }
break;
case 113:
#line 316 "pt_yacc.y"
{ yyval.integer=PMDB_LB_SLICE; }
break;
case 114:
#line 317 "pt_yacc.y"
{ yyval.integer=PMDB_LB_GEOM; }
break;
case 115:
#line 318 "pt_yacc.y"
{ yyval.integer=PMDB_LB_INERTIAL; }
break;
case 116:
#line 319 "pt_yacc.y"
{ yyval.integer=PMDB_LB_PROJECTION; }
break;
case 117:
#line 320 "pt_yacc.y"
{ yyval.integer=PMDB_LB_GEOM_PRED; }
break;
case 118:
#line 321 "pt_yacc.y"
{ yyval.integer=PMDB_LB_PROJECTION_PRED; }
break;
case 119:
#line 322 "pt_yacc.y"
{ yyval.integer=yyvsp[0].integer; }
break;
case 120:
#line 325 "pt_yacc.y"
{
   yyval.coords[0]=yyvsp[-5].real; yyval.coords[1]=yyvsp[-3].real; yyval.coords[2]=yyvsp[-1].real; }
break;
case 121:
#line 329 "pt_yacc.y"
{ yyval.integer=PMDB_UNCOMPRESSED_OUTPUT; }
break;
case 122:
#line 330 "pt_yacc.y"
{ yyval.integer=PMDB_COMPRESS_OUTPUT; }
break;
case 123:
#line 331 "pt_yacc.y"
{ yyval.integer=PMDB_GZIP_OUTPUT; }
break;
case 124:
#line 332 "pt_yacc.y"
{ yyval.integer=PMDB_GZIP9_OUTPUT; }
break;
case 125:
#line 335 "pt_yacc.y"
{ yyval.integer=1; }
break;
case 126:
#line 336 "pt_yacc.y"
{ yyval.integer=0; }
break;
case 127:
#line 337 "pt_yacc.y"
{ yyval.integer=2; }
break;
case 128:
#line 338 "pt_yacc.y"
{ yyval.integer=3; }
break;
case 129:
#line 341 "pt_yacc.y"
{ yyval.integer=yyvsp[0].integer; }
break;
case 130:
#line 342 "pt_yacc.y"
{ yyval.integer=-1; }
break;
#line 1398 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
