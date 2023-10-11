%{
#include "pt_yacc.h"
/*
   pmdbtool

   Jim Teresco
   Department of Computer Science, Rensselaer Polytechnic Institute

   pt_lex.l:  Lex file to parse command scripts for pmdbtool

   Created:
   Sat May  6 10:46:13 EDT 1995

   Last change:
   Wed Jul  2 09:37:42 EDT 2003

   $Id: pt_lex.l,v 1.8 2003/10/29 21:48:41 terescoj Exp $

*/
%}

%p 5000
%e 1500
%n 750
ws              [ \t]+
comment         #.*

%%
{ws}            ;
{comment}       ;

"indir"         return(INDIR);
"outdir"        return(OUTDIR);
"trace"         return(TRACE);
"model"         return(MODEL);
"part"          return(PART);
"partition"     return(PART);
"inertial"      return(INERTIAL);
"orthogonal"    return(ORTHOGONAL);
"read_sms"      return(READ_SMS);
"write_sms"     return(WRITE_SMS);
"read_split_sms" return(READ_SPLIT_SMS);
"dx"            return(DX);
"color"         return(COLOR);
"bw"            return(BW);
"surface"       return(SURFACE);
"sur"           return(SURFACE);
"3d"            return(THREE_D);
"2d"            return(TWO_D);
"load_balance"  return(LOAD_BALANCE);
"refine"        return(REFINE);
"coarsen"       return(COARSEN);
"weight"        return(WEIGHT);
"sphere"        return(SPHERE);
"box"           return(BOX);
"PMDB_LB_SEL_METHOD"        return(LB_SEL_METHOD);
"PMDB_LB_MAX_ITER"          return(LB_MAX_ITER);
"PMDB_LB_MAX_INTERNAL_ITER" return(LB_MAX_INTERNAL_ITER);
"PMDB_LB_DEBUG_LEVEL"       return(LB_DEBUG_LEVEL);
"PMDB_LB_TOLERANCE"         return(LB_TOLERANCE);
"PMDB_LB_INTERFACE_THRESH"  return(LB_INTERFACE_THRESH);
"PMDB_LB_SLICE"             return(LB_SLICE);
"PMDB_LB_GEOM"              return(LB_GEOM);
"PMDB_LB_INERTIAL"          return(LB_INERTIAL);
"PMDB_LB_PROJECTION"        return(LB_PROJECTION);
"PMDB_LB_GEOM_PRED"         return(LB_GEOM_PRED);
"PMDB_LB_PROJECTION_PRED"   return(LB_PROJECTION_PRED);
"PMDB_LB_PRINT_MIGSTATS"    return(LB_PRINT_MIGSTATS);
"PMDB_LB_PRINT_ITBTIMES"    return(LB_PRINT_ITBTIMES);
"PMDB_LB_PRINT_ZOLTANTIMES" return(LB_PRINT_ZOLTANTIMES);
"printnodecounts"           return(PRINTNODECOUNTS);
"metrics"       return(METRICS);
"clean"         return(CLEAN);

"true"          { yylval.integer=1; return(BOOLEAN); }
"false"         { yylval.integer=0; return(BOOLEAN); }
"yes"           { yylval.integer=1; return(BOOLEAN); }
"no"            { yylval.integer=0; return(BOOLEAN); }
"compress"      return(COMPRESS);
"none"          return(NONE);
"gzip"          return(GZIP);
"gzip9"         return(GZIP9);
"checklinks"    return(CHECKLINKS);
"repartition"   return(REPARTITION);
"parmetis"      return(PARMETIS);
"zoltan"        return(ZOLTAN);
"echo"          return(ECHO_STRING);
"all"           return(ALL);
"master"        return(MASTER);
"loads"         return(LOADS);
"max"           return(MAX);
"avg"           return(AVG);
"average"       return(AVG);
"local"         return(LOCAL);
"surface_index" return(SI);
"si"            return(SI);
"global"        return(GLOBAL);
"disconn"       return(DISCONN);
"region"        return(REGION);
"face"          return(FACE);
"edge"          return(EDGE);
"vertex"        return(VERTEX);
"adjacency"     return(ADJACENCY);
"comm_matrix"   return(COMM_MATRIX);
"int_matrix"    return(INT_MATRIX);
"checkmesh"     return(CHECKMESH);
"migstats"      return(MIGSTATS);
"reset"         return(RESET);
"print"         return(PRINT);
"output"        return(OUTPUT);
"duplicates"    return(DUPLICATES);
"write_sms_only" return(WRITE_SMS_ONLY);
"write_pmdb_only" return(WRITE_PMDB_ONLY);
"percentage"    return(PERCENTAGE);
"modeler"       return(MODELER);
"shapes"        return(SHAPESMODEL);
"parasolid"     return(PARASOLIDMODEL);
"sleep"         return(SLEEP);
"computeconn"   return(COMPUTECONN);
"null"          return(NULLMODEL);
"smd"           return(SMDMODEL);
"gather"        return(GATHER);
"centroids"     return(CENTROIDS);
"bbox"          return(BBOX);
"set_bound"     return(SET_BOUND);
"init_mesh"     return(INIT_MESH);
"heat_solve"    return(HEAT_SOLVE);
"heat_solve_serial" return(HEAT_SOLVE_SERIAL);
"heat_solve_mpi" return(HEAT_SOLVE_MPI);
"clear_heat"    return(CLEAR_HEAT);
"heat_dx"       return(HEAT_DX);
"print_bounds"  return(PRINT_BOUNDS);
"hier"          return(HIER);
"numlevels"     return(NUMLEVELS);
"level"         return(LEVEL);
"proc"          return(PROC);
-?[0-9]+        { sscanf(yytext,"%d",&yylval.integer); return(INTEGER);}
-?(([0-9]+)|([0-9]*\.[0-9]+)([eE][+-]?[0-9]+)?) { sscanf(yytext,"%lf",&yylval.real); return(DOUBLE); }
[\t\n ]+   ;
\"[^\"\n]+\"    { int i;yylval.str =(char *) malloc(strlen(yytext)/*100*/);  
                  for(i=1;i<strlen(yytext)-1;i++)
                     yylval.str[i-1]=yytext[i]; 
                  yylval.str[strlen(yytext)-2]='\0';  return(STRING);
                }
.               return(yytext[0]);

%%
