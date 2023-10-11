%{
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
%}
%union {
   char *str;
   int integer;
   double real;
   double coords[3];
   long long_val;
 }

%token <real> DOUBLE
%token <str> STRING
%token <integer> INTEGER
%token <integer> BOOLEAN
%token <long_val> LONG
%token INDIR
%token OUTDIR
%token TRACE
%token MODEL
%token PART
%token INERTIAL
%token ORTHOGONAL
%token READ_SMS
%token WRITE_SMS
%token READ_SPLIT_SMS
%token DX
%token COLOR
%token BW
%token SURFACE
%token THREE_D
%token TWO_D
%token LOAD_BALANCE
%token LB_SEL_METHOD
%token LB_MAX_ITER
%token LB_MAX_INTERNAL_ITER
%token LB_DEBUG_LEVEL
%token LB_TOLERANCE
%token LB_INTERFACE_THRESH
%token LB_SLICE
%token LB_GEOM
%token LB_INERTIAL
%token LB_PROJECTION
%token LB_GEOM_PRED
%token LB_PROJECTION_PRED
%token LB_PRINT_MIGSTATS
%token LB_PRINT_ITBTIMES
%token LB_PRINT_ZOLTANTIMES
%token METRICS
%token CLEAN
%token REFINE
%token COARSEN
%token WEIGHT
%token SPHERE
%token BOX
%token COMPRESS
%token NONE
%token GZIP
%token GZIP9
%token CHECKLINKS
%token REPARTITION
%token PARMETIS
%token ZOLTAN
%token ECHO_STRING
%token ALL
%token MASTER
%token LOADS
%token MAX
%token AVG
%token LOCAL
%token SI
%token GLOBAL
%token DISCONN
%token REGION
%token FACE
%token EDGE
%token VERTEX
%token ADJACENCY
%token COMM_MATRIX
%token INT_MATRIX
%token CHECKMESH
%token MIGSTATS
%token RESET
%token PRINT
%token OUTPUT
%token DUPLICATES
%token WRITE_SMS_ONLY
%token WRITE_PMDB_ONLY
%token PRINTNODECOUNTS
%token PERCENTAGE
%token MODELER
%token PARASOLIDMODEL
%token SHAPESMODEL
%token SLEEP
%token COMPUTECONN
%token NULLMODEL
%token SMDMODEL
%token GATHER
%token CENTROIDS
%token BBOX
%token SET_BOUND
%token INIT_MESH
%token HEAT_SOLVE
%token HEAT_SOLVE_SERIAL
%token HEAT_SOLVE_MPI
%token CLEAR_HEAT
%token HEAT_DX
%token PRINT_BOUNDS
%token HIER
%token NUMLEVELS
%token PARTITION
%token LEVEL
%token PROC

%type <integer> bool
%type <integer> part_type
%type <integer> lb_type
%type <coords> point
%type <integer> compression
%type <integer> maxavglocal
%type <integer> maxavglocalglobal
%type <integer> entity_types
%type <integer> one_mal
%type <integer> more_mals
%type <integer> one_malg
%type <integer> more_malgs
%type <integer> one_type
%type <integer> more_types
%type <integer> modeler_type
%type <integer> procnum

%%
 strt: commands
   ;

 commands: commands command
   | command
   ;

 command: INDIR STRING { pt_set_input_dir($2); }
   | OUTDIR STRING { pt_set_output_dir($2); }
   | TRACE { pt_trace_on(1); }
   | TRACE bool { pt_trace_on($2); }
   | MODEL STRING { pt_read_model($2); }
   | PART part_type STRING { pt_init_part($2, $3); }
   | READ_SMS STRING { pt_read_sms($2); }
   | READ_SPLIT_SMS STRING { pt_read_split_sms($2); }
   | WRITE_SMS STRING { pt_write_sms($2); }
   | DX { pt_dx_opt_init(); } dx_opts STRING { pt_write_dx($4); }
   | LOAD_BALANCE { pt_load_balance(); }
   | METRICS STRING STRING { pt_metrics($2, $3); }
   | CLEAN { pt_clean(); }
   | REFINE PERCENTAGE DOUBLE { pt_refine_percentage($3, 1); }
   | REFINE SPHERE point DOUBLE { pt_refine_sphere($3, $4, 1); }
   | REFINE BOX point point { pt_refine_box($3, $4, 1); }
   | COARSEN PERCENTAGE DOUBLE { pt_refine_percentage($3, 0); }
   | COARSEN SPHERE point DOUBLE { pt_refine_sphere($3, $4, 0); }
   | COARSEN BOX point point { pt_refine_box($3, $4, 0); }
   | WEIGHT SPHERE point DOUBLE INTEGER { pt_weight_sphere($3, $4, $5); }
   | WEIGHT BOX point point INTEGER { pt_weight_box($3, $4, $5); }
   | COMPRESS compression { pt_set_compression($2); }
   | CHECKLINKS { pt_check_links(); }
   | LB_SEL_METHOD lb_type { pt_set_lb_int_param(PMDB_LB_SEL_METHOD, $2); }
   | LB_MAX_ITER INTEGER { pt_set_lb_int_param(PMDB_LB_MAX_ITER, $2); }
   | LB_MAX_INTERNAL_ITER INTEGER {
     pt_set_lb_int_param(PMDB_LB_MAX_INTERNAL_ITER, $2); }
   | LB_DEBUG_LEVEL INTEGER { pt_set_lb_int_param(PMDB_LB_DEBUG_LEVEL, $2); }
   | LB_TOLERANCE INTEGER { 
     pt_set_lb_long_param(PMDB_LB_TOLERANCE, (long)$2); }
   | LB_INTERFACE_THRESH INTEGER { 
     pt_set_lb_int_param(PMDB_LB_INTERFACE_THRESH, $2); }
   | LB_PRINT_MIGSTATS BOOLEAN {
     pt_set_lb_int_param(PMDB_LB_PRINT_MIGSTATS, $2); }
   | LB_PRINT_ITBTIMES BOOLEAN {
     pt_set_lb_int_param(PMDB_LB_PRINT_ITBTIMES, $2); }
   | LB_PRINT_ZOLTANTIMES BOOLEAN {
     pt_set_lb_int_param(PMDB_LB_PRINT_ZOLTANTIMES, $2); }
   | REPARTITION { pt_repartition(); }
   | PARMETIS INTEGER { pt_parmetis($2); }
   | ZOLTAN { pt_zoltan(); }
   | ZOLTAN STRING { pt_zoltan_read_paramfile($2); }
   | ZOLTAN STRING STRING { pt_zoltan_setparam($2,$3); }
   | ECHO_STRING ALL STRING { pt_printall($3); }
   | ECHO_STRING MASTER STRING { pt_printone(0,$3); }
   | ECHO_STRING STRING { pt_printone(0,$2); }
   | ECHO_STRING INTEGER STRING { pt_printone($2,$3); }
   | LOADS maxavglocalglobal { pt_print_loads($2); }
   | SI maxavglocalglobal { pt_print_si($2); }
   | DISCONN maxavglocal entity_types { pt_print_disconn($2, $3); }
   | ADJACENCY maxavglocal { pt_print_adj($2); }
   | COMM_MATRIX { pt_print_comm_matrix(); }
   | INT_MATRIX { pt_print_int_matrix(); }
   | CHECKMESH { pt_check_mesh(); }
   | MIGSTATS RESET { pt_reset_migstats(); }
   | MIGSTATS PRINT { pt_print_migstats(); }
   | MIGSTATS OUTPUT STRING { pt_output_migstats($3); }
   | DUPLICATES entity_types { pt_print_duplicate_overhead($2); }
   | WRITE_SMS_ONLY STRING { pt_write_sms_only($2); }
   | WRITE_PMDB_ONLY STRING { pt_write_pmdb_only($2); }
   | PRINTNODECOUNTS { pt_print_nodecounts(); }
   | MODELER modeler_type { pt_set_modeler($2); }
   | SLEEP INTEGER { pt_sleep($2); }
   | COMPUTECONN { pt_set_compute_conn(); }
   | GATHER { pt_gather_to_master(); }
   | CENTROIDS STRING { pt_write_centroids($2); }
   | BBOX { pt_print_bbox(); }
   | SET_BOUND INTEGER DOUBLE { pt_set_bound($2,$3); }
   | INIT_MESH DOUBLE { pt_initialize_mesh($2); }
   | HEAT_SOLVE INTEGER DOUBLE { pt_heat_solve($2,$3); }
   | HEAT_SOLVE_SERIAL INTEGER DOUBLE STRING { pt_heat_solve_serial($2,$3,$4); }
   | HEAT_SOLVE_MPI INTEGER DOUBLE { pt_heat_solve_mpi($2,$3); }
   | CLEAR_HEAT { pt_clear_regions("heat"); }
   | HEAT_DX STRING { pt_heat_write_dx($2,pt_get_pmeshpb(),0,0,com_wall_time()); }
   | PRINT_BOUNDS { pt_print_bounds(); }
   | ZOLTAN HIER NUMLEVELS INTEGER { pt_hier_set_num_levels($4); }
   | ZOLTAN HIER LEVEL INTEGER PROC INTEGER PART INTEGER { 
     if ($6 == COM_PID || $6 == -1) pt_hier_set_partition($4, $8);
   }
   | ZOLTAN HIER LEVEL INTEGER PROC procnum STRING STRING { 
     if ($6 == COM_PID || $6 == -1) pt_hier_set_param($4, $7, $8); 
   }
   ;

 maxavglocal: more_mals one_mal { $$=$1|$2; }
   | { $$=0; }
  ;

 one_mal: MAX { $$=PT_MAX; }
   | AVG { $$=PT_AVG; }
   | LOCAL { $$=PT_LOCAL; }
  ;

 more_mals: more_mals one_mal { $$=$1|$2; }
   | { $$=0; }
  ;

 maxavglocalglobal: more_malgs one_malg { $$=$1|$2; }
   | { $$=0; }
  ;

 one_malg: MAX { $$=PT_MAX; }
   | AVG { $$=PT_AVG; }
   | LOCAL { $$=PT_LOCAL; }
   | GLOBAL { $$=PT_GLOBAL; }
  ;

 more_malgs: more_malgs one_malg { $$=$1|$2; }
   | { $$=0; }
  ;

 entity_types: more_types one_type { $$=$1|$2; }
   | { $$=0; }
  ;

 one_type: VERTEX { $$=PT_VERTEX; }
   | EDGE { $$=PT_EDGE; }
   | FACE { $$=PT_FACE; }
   | REGION { $$=PT_REGION; }
  ;

 more_types: more_types one_type { $$=$1|$2; }
   | { $$=0; }
  ;

 bool: BOOLEAN { $$=$1; }
   | INTEGER { if ($1) {$$=1;} else {$$=0;} }
  ;

 part_type: INERTIAL { $$=PT_PART_INERTIAL; }
   | ORTHOGONAL { $$=PT_PART_ORTHOGONAL; }
  ;

 dx_opts: dx_opts dx_opt
   | dx_opt
   | 
  ;

 dx_opt: COLOR { pt_dx_opt_color(); }
   | BW { pt_dx_opt_bw(); }
   | THREE_D { pt_dx_opt_3d(); }
   | TWO_D { pt_dx_opt_2d(); }
   | SURFACE { pt_dx_opt_sur(); }
  ;

 lb_type: { $$=PMDB_LB_SLICE; }
   | LB_SLICE { $$=PMDB_LB_SLICE; }
   | LB_GEOM { $$=PMDB_LB_GEOM; }
   | LB_INERTIAL { $$=PMDB_LB_INERTIAL; }
   | LB_PROJECTION { $$=PMDB_LB_PROJECTION; }
   | LB_GEOM_PRED { $$=PMDB_LB_GEOM_PRED; }
   | LB_PROJECTION_PRED { $$=PMDB_LB_PROJECTION_PRED; }
   | INTEGER { $$=$1; }
  ;

 point: '(' DOUBLE ',' DOUBLE ',' DOUBLE ')' {
   $$[0]=$2; $$[1]=$4; $$[2]=$6; }
  ;

 compression: NONE { $$=PMDB_UNCOMPRESSED_OUTPUT; }
   | COMPRESS { $$=PMDB_COMPRESS_OUTPUT; }
   | GZIP { $$=PMDB_GZIP_OUTPUT; }
   | GZIP9 { $$=PMDB_GZIP9_OUTPUT; }
  ;

  modeler_type: SHAPESMODEL { $$=1; }
   | PARASOLIDMODEL { $$=0; }
   | NULLMODEL { $$=2; }
   | SMDMODEL { $$=3; }
  ;

  procnum: INTEGER { $$=$1; }
   | ALL { $$=-1; }
  ;
%%

