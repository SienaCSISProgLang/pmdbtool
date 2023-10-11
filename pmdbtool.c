/* 
   pmdbtool.c

   PMDBtool
   A utility program to manipulate Parallel Mesh Database (PMDB) meshes

   Jim Teresco
   Rensselaer Polytechnic Institute
   Department of Computer Science
   Scientific Computation Research Center

   and

   Department of Computer Science
   Williams College

   Last change:
   Wed Oct 29 14:46:47 MST 2003

   $Id$
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <float.h>

#ifdef MPI
#include <mpi.h>
#endif

#ifndef FILENAME_MAX
#define FILENAME_MAX 256
#endif

#include "MSops.h"
#include "comm_lib.h"
#include "util_macros.h"
#include "pmshops.h"
#include "MeshTools.h"
#ifdef PARASOLID
#include "modelerParasolid.h"
#endif
#ifdef SHAPES
#include "modelerShapes.h"
#endif
#include "modelerNull.h"
#include "modelerSmd.h"

#ifndef PMDB_ONLY
#include "ref_deref_ops.h"
#include "partition_ops.h"
/*#include "parinc.h"*/
#include "zoltan.h"
#endif

#include "modeler.h" /* 03dcb 7/7/03*/
#include "dx_write.h"

#include "pmdbtool.h"

#include "autopack.h"

static void do_refinement(int (*should_refine)(), int);
static void get_centroid(pEntity, double *);
static int in_percentage(pEntity);
static int in_refine_sphere(pEntity);
static int in_refine_box(pEntity);
static void set_refine_percentage(double);
static void set_refine_box(double *, double *);
static void set_refine_sphere(double *, double);
static void do_set_weights(int (*should_refine)(), PMDB_ELT_WT);
static void setup_weights();
static PMDB_ELT_WT weight_func(pEntity, PMDB_ELT_WT);
static int modeler=-1; /* -1=none, 0=parasolid, 1=shapes, 2=null */
static char *conn_env="PMDB_SKIP_CONN=1";
static void get_bbox(double *,double *);

#define USE_REFDREF

#define MIN(x,y) ((x)<(y) ? (x) : (y))
#define MAX(x,y) ((x)<(y) ? (y) : (x))

#define TRACE (trace>1) || (trace && (COM_PID==0))

#ifndef HAVE_MPL
static void mpc_flush(int fd) { fflush(stdout); }
#endif

#define PRINT_IN_ORDER() \
  com_all_sync(); \
  for (msg_temp=0, mpc_flush(1); msg_temp<COM_NUMPROCS; msg_temp++, mpc_flush(1),fflush(stdout)) \
    if (COM_PID==msg_temp)

/* for PRINT_IN_ORDER macro */
static int msg_temp;

/* yacc/lex externs */
extern FILE *yyin;
extern int yyparse();

/* pmdbtool globals */
static pMesh      mesh=NULL;
static pGModel    model; 
static pMeshPB    pmeshpb=NULL; 
static char *indir=NULL;
static char *outdir=NULL;
static int trace=0;
static char *model_filename=NULL;
static double ref_sphere_center[3], ref_sphere_radius;
static double ref_box_corner1[3], ref_box_corner2[3];
static double ref_percentage;
static char *weight_tag="wght";
static char *heat_tag="heat";
#ifndef PMDB_ONLY
static struct Zoltan_Struct *lb = NULL;
#endif
/* for Heatsolver functions */
typedef struct Heat{ double h1, h2; }Heat;
#define MAX_NEIGHBORS 4 /* max # neighbors of a region*/
typedef struct HeatPack{ double heat; pFace face; }HeatPack;
static struct tagVals { int tag; double value; }**tagArray = NULL; 
static int tagCount=0;

static char *pt_make_input_file(char *name, char *ext) {
  char *path;

  /* do we need to prepend the indir path? */
  if (indir && !strchr(name,'/')) {
    SAFE_MALLOC(path,char *,strlen(indir)+strlen(name)+strlen(ext)+3);
    sprintf(path,"%s/%s%s",indir,name,ext);
    return path;
  }

  SAFE_MALLOC(path,char *,strlen(name)+strlen(ext)+3);
  sprintf(path,"%s%s",name,ext);
  return path;
}

static char *pt_make_output_file(char *name, char *ext) {
  char *path;

  /* do we need to prepend the outdir path? */
  if (outdir && !strchr(name,'/')) {
    SAFE_MALLOC(path,char *,strlen(outdir)+strlen(name)+strlen(ext)+3);
    sprintf(path,"%s/%s%s",outdir,name,ext);
    return path;
  }

  SAFE_MALLOC(path,char *,strlen(name)+strlen(ext)+3);
  sprintf(path,"%s%s",name,ext);
  return path;
}

static void pt_start_timer(double *start_time) {

  *start_time=com_wall_time();
}

static void pt_print_timer_max(double start_time, char *label) {
  double total_time, max_time;

  total_time=com_wall_time()-start_time;
  com_max_double(&total_time, &max_time, 1);
  if (COM_PID==0)
    printf("TIMING %s %15.9e\n", label, max_time);
}

int main(int argc, char *argv[]) {
  int worker();
  
  return worker(&argc,&argv);
}

int worker(int *argc,char **argv[]) {
  int rc;

#ifdef MPI
  rc=MPI_Init(argc, argv);
  if (rc!=MPI_SUCCESS) com_abort(NULL, NULL);
  rc=MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
  if (rc!=MPI_SUCCESS) com_abort(NULL, NULL);
  AP_init(argc,argv); /* Added 8/4/03 DB*/
#endif

  /* stop I/O buffering for more readable parallel output */
  setbuf(stdout, NULL);

  com_init();

  if ( *argc != 2 ) {
    
    fprintf(stderr, "Usage: %s <command script>\n",*argv[0]);
    fprintf(stderr, "Reads PMDB-related command from a file and performs\n");
    fprintf(stderr, "the desired actions\n");
    com_abort(NULL, NULL);
  }
  
  srand(0);
  if (COM_PID==0) printf("Starting %s\n",PMDBTOOL_VERSION);

  MD_init();                 /* initialize the mesh database       */
  /*model = GM_new(0);*/
  pmdb_set_output_compression(PMDB_GZIP9_OUTPUT);

  /* by default, turn off connectivity for PMDB metrics - it's too slow */
  putenv(conn_env);

  if ((yyin=fopen((*argv)[1],"r"))==NULL) {
    fprintf(stderr, "Could not open script file %s\n",(*argv)[1]);
    com_abort(NULL, NULL);
  }

  if (COM_PID==0) printf("%s: using script file %s\n",(*argv)[0],(*argv)[1]);

  yyparse();

  fclose(yyin);

  if (mesh) M_delete(mesh); 
  MD_exit(); 

#ifdef MPI
  MPI_Finalize();
  AP_finalize();
#endif
  return 0;
}

void pt_read_model(char *filename) {
  char *file;

  com_all_sync();

  if (TRACE) printf("(pt_read_model) using base filename %s\n",filename);

  switch (modeler) {
  case 0: /* parasolid */
    file=pt_make_input_file(filename,".xmt_txt");
#ifdef PARASOLID
    GM_setupParasolid();
    model=GM_createFromParasolidFile(file);
#else
    fprintf(stderr, "parasolid modeler not linked in\n");
    com_abort(NULL,NULL);
#endif    
    break;
  case 1: /* shapes */
    file=pt_make_input_file(filename,".geom");
#ifdef SHAPES
    GM_setupShapes();
    model=GM_createFromShapesFile(file);
#else
    fprintf(stderr, "shapes modeler not linked in\n");
    com_abort(NULL,NULL);
#endif    
    break;
  case 2: /* null model */
    file=pt_make_input_file(filename,".null");
    GM_setupNull();
    model=GM_createFromNothing(file);
    break;
  case 3: /* SMD model */
    file=pt_make_input_file(filename,".smd");
    GM_setupSmd();
    model=GM_createFromSmdFile(file);
    break;
  default:
    if (COM_PID==COM_MASTER)
      printf("No valid modeler option set, using NO MODEL\n");
    file=pt_make_input_file(filename,".fake");
    model=0;
    }
  
  if (model_filename) free(model_filename);
  model_filename=file;
  file=(char *)strrchr(model_filename,'.');
  if (file) *file='\0';

  if (model)
    pmdb_ge_tabl_new(model); /* initialize the (eType,tag) -> pGEntity table */
  
  mesh = M_new(1,model);    /* make a mesh object                 */
}  

void pt_set_input_dir(char *path) {

  com_all_sync();
  if (indir) free(indir);
  indir=(char *)strdup(path);
  if (TRACE) printf("(pt_set_input_dir) set to %s\n",indir);
}

void pt_set_output_dir(char *path) {

  com_all_sync();
  if (outdir) free(outdir);
  outdir=(char *)strdup(path);
  if (TRACE) printf("(pt_set_output_dir) set to %s\n",outdir);
}

void pt_trace_on(int flag) {

  com_all_sync();
  trace=flag;
  if (TRACE) printf("(pt_trace_on) trace turned on\n");
}

void pt_init_part(int type, char *filename) {
  char *file;
  double timeval;

  com_all_sync();
  if (!mesh) {
    fflush(stdout);
    fprintf(stderr,"PMDBtool %s: (pt_init_part) must load model first!\n",
	    PMDBTOOL_VERSION);
    com_abort(NULL, NULL);
  }

  file=pt_make_input_file(filename,"");
  
  if (TRACE) printf("(pt_init_part) using type %d on file %s\n",type,file);

  pt_start_timer(&timeval);

  switch (type) {
  case PT_PART_INERTIAL:
    pmdb_inertia_rb(file, mesh, &pmeshpb);
    break;
  case PT_PART_ORTHOGONAL: {
    int num_axes=3;
    int axes[3]={0, 1, 2};
    pmdb_ortho_rb(file, num_axes, axes, mesh, &pmeshpb);
    break;
  }
  default:
    fflush(stdout);
    fprintf(stderr,
	    "PMDBtool %s: (pt_init_part) invalid partitioning type %d\n",
	    PMDBTOOL_VERSION,type);
    com_abort(NULL, NULL);
    break;
  }

  pt_print_timer_max(timeval,"pt_init_part");
  free(file);
}

void pt_read_sms(char *filename) {
  char *file;
  double timeval;
 
  com_all_sync();
  if (!mesh) {
    fflush(stdout);
    fprintf(stderr,"PMDBtool %s: (pt_read_sms) must load model first!\n",
	    PMDBTOOL_VERSION);
    com_abort(NULL, NULL);
  }

  file=pt_make_input_file(filename,"");
  
  if (TRACE) printf("(pt_read_sms) using file %s\n",file);

  pt_start_timer(&timeval);
  pmdb_read_msh_par(file, mesh, &pmeshpb);
  pt_print_timer_max(timeval,"pt_read_sms");
  free(file);
}

void pt_read_split_sms(char *filename) {
  char *file;
  double timeval;
  
  com_all_sync();
  if (!mesh) {
    fflush(stdout);
    fprintf(stderr,"PMDBtool %s: (pt_read_split_sms) must load model first!\n",
	    PMDBTOOL_VERSION);
    com_abort(NULL, NULL);
  }

  file=pt_make_input_file(filename,"");
  
  if (TRACE) printf("(pt_read_split_sms) using file %s\n",file);

  pt_start_timer(&timeval);
  pmdb_load_split_sms(file, mesh, &pmeshpb);
  pt_print_timer_max(timeval,"pt_read_split_sms");
  free(file);
}

void pt_write_sms(char *filename) {
  char *file;
  double timeval;
  
  com_all_sync();
  if (!mesh || !pmeshpb) {
    fflush(stdout);
    fprintf(stderr,"PMDBtool %s: (pt_write_sms) no data!\n",PMDBTOOL_VERSION);
    com_abort(NULL, NULL);
  }

  file=pt_make_output_file(filename,"");
  
  if (TRACE) printf("(pt_write_sms) using file %s\n",file);

  pt_start_timer(&timeval);
  pmdb_write_msh_par(file, pmeshpb);
  pt_print_timer_max(timeval,"pt_write_sms");
  free(file);
}

void pt_write_sms_only(char *filename) {
  char *file;
  double timeval;
  
  com_all_sync();
  if (!mesh || !pmeshpb) {
    fflush(stdout);
    fprintf(stderr,"PMDBtool %s: (pt_write_sms_only) no data!\n",
	    PMDBTOOL_VERSION);
    com_abort(NULL, NULL);
  }

  file=pt_make_output_file(filename,"");
  
  if (TRACE) printf("(pt_write_sms_only) using file %s\n",file);

  pt_start_timer(&timeval);
  pmdb_write_sms_only(file, pmeshpb);
  pt_print_timer_max(timeval,"pt_write_sms_only");
  free(file);
}

void pt_write_pmdb_only(char *filename) {
  char *file;
  double timeval;
  
  com_all_sync();
  if (!mesh || !pmeshpb) {
    fflush(stdout);
    fprintf(stderr,"PMDBtool %s: (pt_write_pmdb_only) no data!\n",PMDBTOOL_VERSION);
    com_abort(NULL, NULL);
  }

  file=pt_make_output_file(filename,"");
  
  if (TRACE) printf("(pt_write_pmdb_only) using file %s\n",file);

  pt_start_timer(&timeval);
  pmdb_write_pmdb_only(file, pmeshpb);
  pt_print_timer_max(timeval,"pt_write_pmdb_only");
  free(file);
}

/* DX output variables and routines */
static short dx_color;
static short dx_type;

#define DX_COLOR 0
#define DX_BW    1
#define DX_3D    0
#define DX_2D    1
#define DX_SUR   2

void pt_dx_opt_init() {

  dx_color=DX_COLOR;
  dx_type=DX_3D;
}

void pt_dx_opt_color() {

  dx_color=DX_COLOR;
}

void pt_dx_opt_bw() {

  dx_color=DX_BW;
}

void pt_dx_opt_3d() {

  dx_type=DX_3D;
}

void pt_dx_opt_2d() {

  dx_type=DX_2D;
}

void pt_dx_opt_sur() {

  dx_type=DX_SUR;
}

void pt_write_dx(char *filename) {
  char *file;
  double timeval;
  
  com_all_sync();
  if (!mesh || !pmeshpb) {
    fflush(stdout);
    fprintf(stderr,"PMDBtool %s: (pt_write_dx) no data!\n",PMDBTOOL_VERSION);
    com_abort(NULL, NULL);
  }

  file=pt_make_output_file(filename,"");
  
  if (TRACE) printf("(pt_write_dx) using file %s\n",file);

  pt_start_timer(&timeval);
  switch (dx_type) {
  case DX_3D:
    if (dx_color==DX_COLOR)
      pmdb_write_dx(file, mesh, pmeshpb);
    else
      pmdb_write_bw_dx(file, mesh, pmeshpb);
    break;
  case DX_2D:
    if (dx_color==DX_COLOR) 
      pmdb_write_2d_dx(file, mesh, pmeshpb);
    else
      pmdb_write_2d_bw_dx(file, mesh, pmeshpb);
    break;
  case DX_SUR:
    if (dx_color==DX_COLOR)
      pmdb_write_sur_dx(file, mesh, pmeshpb);
    else
      pmdb_write_bw_sur_dx(file, mesh, pmeshpb);
    break;
  }
  pt_print_timer_max(timeval,"pt_write_dx");

  free(file);
}

void pt_load_balance() {
  double timeval;

  com_all_sync();
  /*pmdb_set_load_balance_method(lbtype, pmeshpb);*/

  if (TRACE)
    printf("(pt_load_balance) load balance\n");

  pt_start_timer(&timeval);
  pmdb_load_balance(pmeshpb);
  pt_print_timer_max(timeval,"pt_load_balance");
}

void pt_set_lb_int_param(int param, int val) {

  if (TRACE)
    printf("(pt_set_lb_int_param) setting param %d to %d\n", param, val);

  pmdb_set_load_balance_params(pmeshpb, param, val, NULL);
  /* also need to shut off default refdref load bal call or else it will
     override this */
  refdref_set_rebal_func(pmdb_load_balance);
}

void pt_set_lb_long_param(int param, long val) {

  if (TRACE)
    printf("(pt_set_lb_int_param) setting param %d to %ld\n", param, val);

  pmdb_set_load_balance_params(pmeshpb, param, val, NULL);
}

void pt_metrics(char *prefix, char *infix) {
  char *file;

  com_all_sync();
  file=pt_make_output_file(prefix, "");

  if (TRACE)
    printf("(pt_metrics) writing metric files\n");

  pmdb_output_metrics(pmeshpb, model, file, infix);

  free(file);
}

void pt_clean() {

  com_all_sync();
  if (TRACE)
    printf("(pt_clean) cleaning mesh structure\n");

  pmdb_clean_pmeshpb(pmeshpb);
}

static void set_refine_sphere(double *center, double radius) {
  int i;

  for (i=0; i<3; i++) {
    ref_sphere_center[i]=center[i];
  }
  ref_sphere_radius=radius;
  if (TRACE) {
    printf("(set_refine_sphere) center: (%8.5f,%8.5f,%8.5f), radius %8.5f\n",
	   ref_sphere_center[0],ref_sphere_center[1],ref_sphere_center[2],
	   ref_sphere_radius);
  }
}

void pt_refine_sphere(double *center, double radius, int refine) {
  double timeval;

  set_refine_sphere(center, radius);

  pt_start_timer(&timeval);
  do_refinement(in_refine_sphere, refine);
  pt_print_timer_max(timeval,"pt_refine_sphere");
}

void pt_weight_sphere(double *center, double radius, PMDB_ELT_WT weight) {
  double timeval;

  setup_weights();

  set_refine_sphere(center, radius);

  pt_start_timer(&timeval);
  do_set_weights(in_refine_sphere, weight);
  pt_print_timer_max(timeval,"pt_weight_sphere");
}

static void set_refine_box(double *corner1, double *corner2) {
  int i;

  for (i=0; i<3; i++) {
    if (corner1[i] < corner2[i]) {
      ref_box_corner1[i]=corner1[i];
      ref_box_corner2[i]=corner2[i];
    }
    else {
      ref_box_corner1[i]=corner2[i];
      ref_box_corner2[i]=corner1[i];
    }
  }
  if (TRACE) {
    printf("(pt_refine_box) low: (%8.5f,%8.5f,%8.5f), high: (%8.5f,%8.5f,%8.5f)\n",
	   ref_box_corner1[0],ref_box_corner1[1],ref_box_corner1[2],
	   ref_box_corner2[0],ref_box_corner2[1],ref_box_corner2[2]);
  }
}

static void set_refine_percentage(double percent) {

  ref_percentage=percent;
  if (TRACE) {
    printf("(pt_refine_percent) percent of edges marked: %8.5f\n",
	   ref_percentage);
  }
}

static void setup_weights() {
  pRegion region;
  void *temp=0;
  static int first_time=1;
  PMDB_ELT_WT *weight;

  if (first_time) {
    if (!pmdb_ptag_register(pmeshpb, Tregion, weight_tag,
			    sizeof(PMDB_ELT_WT))) {
      fprintf(stderr,
	      "PMDBtool %s: (setup_weights) Weight tag already registered!\n",
	      PMDBTOOL_VERSION);
      com_abort(NULL, NULL);
    }
    pmdb_register_weight_func(pmeshpb, weight_func);
    first_time=0;
  }

  while ((region=M_nextRegion(mesh, &temp))) {
    if (!(EN_dataP(region, weight_tag))) {
      SAFE_MALLOC(weight,PMDB_ELT_WT *,sizeof(PMDB_ELT_WT));
      *weight=1;
      EN_attachDataP(region, weight_tag, weight);
    }
  }
}

static PMDB_ELT_WT weight_func(pEntity ent, PMDB_ELT_WT add) {
  PMDB_ELT_WT weight;

  weight=EN_dataI(ent, weight_tag);
  return weight;
}

void pt_refine_box(double *corner1, double *corner2, int refine) {
  double timeval;

  set_refine_box(corner1, corner2);

  pt_start_timer(&timeval);
  do_refinement(in_refine_box, refine);
  pt_print_timer_max(timeval,"pt_refine_box");
}

void pt_refine_percentage(double percent, int refine) {
  double timeval;

  set_refine_percentage(percent);

  pt_start_timer(&timeval);
  do_refinement(in_percentage, refine);
  pt_print_timer_max(timeval,"pt_refine_percentage");
}

void pt_weight_box(double *corner1, double *corner2, PMDB_ELT_WT weight) {
  double timeval;

  setup_weights();

  set_refine_box(corner1, corner2);

  pt_start_timer(&timeval);
  do_set_weights(in_refine_box, weight);
  pt_print_timer_max(timeval,"pt_weight_box");
}

static void do_refinement(int (*should_refine)(), int refine) {
  /* refine == 1 means to refinement, refine == 0 means do coarsening */
  void *temp;
  pEntity t;
  double *d;
  int nkeyv;
  double *thres;
  int ndof;
  double *dum_err;
  double *dum_sol;
  double mark_err, nomark_err;
  int fd;
  int ref_verts, no_ref_verts;

  com_all_sync();
  fd=open("refdref.inp",O_RDONLY);
  if (fd<0) {
    fprintf(stderr,"%s: fatal: refdref.inp not found\n",
	    PMDBTOOL_VERSION);
    com_abort(NULL, NULL);
  }
  close(fd);

  pmdb_tag_registerP(pmeshpb, Tvertex, "ert0", sizeof(double), PMDB_TAG_DEFAULT);
  pmdb_tag_registerP(pmeshpb, Tvertex, "solt", sizeof(double), PMDB_TAG_DEFAULT);

  SAFE_MALLOC(thres,double *,2*sizeof(double));

  if (refine == 0) { /* coarsen */
    mark_err=0.001;
    nomark_err=0.5;
    thres[0]=0.1;
    thres[1]=1.0;
  }
  else { /* refine */
    mark_err=0.5;
    nomark_err=0.001;
    thres[0]=0.00;
    thres[1]=0.01;
  }
 
  temp=NULL;
  while ((t=M_nextVertex(mesh, &temp))) {

    if ((d=EN_dataP(t, "ert0")) != NULL) {
      EN_removeData(t, "ert0");
      free(d);
    }

    if ((d=EN_dataP(t, "solt")) != NULL) {
      EN_removeData(t, "solt");
      free(d);
    }
  }

  ref_verts=0; no_ref_verts=0;
  temp=NULL ;
  while ((t=M_nextVertex(mesh,&temp))) {
    SAFE_MALLOC(dum_err,double *,sizeof(double));
    SAFE_MALLOC(dum_sol,double *,sizeof(double));
    
    if ((*should_refine)(t)) {
      ref_verts++;
      *dum_err=mark_err;
    }
    else {
      no_ref_verts++;
      *dum_err=nomark_err;
    }

    *dum_sol=1.0;
    EN_attachDataP(t,"ert0",dum_err);
    EN_attachDataP(t,"solt",dum_sol);
  }
  
  ndof=1;
  nkeyv=1;

  /*printf("model filename to ref_deref is: <%s>\n",model_filename);*/
  PRINT_IN_ORDER() {
    printf("%d verts marked, %d not marked\n",ref_verts,no_ref_verts);
  }

#ifndef PMDB_ONLY
  ref_deref("parasolid",mesh,pmeshpb,model,model_filename,nkeyv,thres,"ert0",ndof,"solt");
#else
  printf("WARNING - ref_deref not linked in!!!!!!!!!!!\n");
#endif
  free(thres);
  pmdb_tag_unregisterP(pmeshpb, Tvertex, "ert0");
  pmdb_tag_unregisterP(pmeshpb, Tvertex, "solt");
}

static void do_set_weights(int (*should_refine)(), PMDB_ELT_WT new_weight) {
  pRegion region;
  void *temp=0;
  PMDB_ELT_WT *weight;

  while ((region=M_nextRegion(mesh, &temp))) {
    if (((*should_refine)(region))) {
      weight=EN_dataP(region, weight_tag);
      *weight=new_weight;
    }
  }
}

static void get_centroid(pEntity entity, double *xyz) {
  pVertex vertex;
  pPoint point;
  pPList list;
  int i, num_verts;
  
  for (i=0; i<3; i++) xyz[i]=0.0;

  switch (EN_type(entity)) {
  case Tvertex:
    point=V_point(entity);
    xyz[0]=P_x(point); xyz[1]=P_y(point); xyz[2]=P_z(point);
    return;
  case Tedge:
    vertex=E_vertex(entity, 0);
    point=V_point(vertex);
    xyz[0]=P_x(point); xyz[1]=P_y(point); xyz[2]=P_z(point);
    vertex=E_vertex(entity, 1);
    point=V_point(vertex);
    xyz[0]+=P_x(point); xyz[1]+=P_y(point); xyz[2]+=P_z(point);
    for (i=0; i<3; i++) xyz[i]/=2;
    return;
  case Tface:
  case Tregion:
    if (EN_type(entity) == Tface) list=F_vertices(entity, 1);
    else list=R_vertices(entity);
    num_verts=PList_size(list);
    for (i=0; i<num_verts; i++) {
      vertex=PList_item(list, i);
      point=V_point(vertex);
      xyz[0]+=P_x(point); xyz[1]+=P_y(point); xyz[2]+=P_z(point);
    }
    for (i=0; i<3; i++) xyz[i]/=num_verts;
    return;
  }
}

static int in_refine_sphere(pEntity entity) {
  double xyz[3];
  double dist;

  get_centroid(entity, xyz);

  dist=sqrt((xyz[0]-ref_sphere_center[0])*(xyz[0]-ref_sphere_center[0])+
	    (xyz[1]-ref_sphere_center[1])*(xyz[1]-ref_sphere_center[1])+
	    (xyz[2]-ref_sphere_center[2])*(xyz[2]-ref_sphere_center[2]));
  return (dist <= ref_sphere_radius);
}

static int in_refine_box(pEntity entity) {
  double xyz[3];
  int ans;

  get_centroid(entity, xyz);

  ans=(((xyz[0]>=ref_box_corner1[0])&&(xyz[0]<=ref_box_corner2[0]))&&
       ((xyz[1]>=ref_box_corner1[1])&&(xyz[1]<=ref_box_corner2[1]))&&
       ((xyz[2]>=ref_box_corner1[2])&&(xyz[2]<=ref_box_corner2[2])));
  return ans;
}

static int in_percentage(pEntity entity) {
  int ans;

  ans=((pmdb_en_num_iplinks(entity)<0) && (((1.0*rand())/RAND_MAX) < ref_percentage));
  return ans;
}

void pt_set_compression(int level) {

  if (TRACE) {
    char *s;
    switch (level) {
    case PMDB_UNCOMPRESSED_OUTPUT:
      s="no output compression";
      break;
    case PMDB_GZIP_OUTPUT:
      s="gzip output";
      break;
    case PMDB_GZIP9_OUTPUT:
      s="gzip -9 output";
      break;
    case PMDB_COMPRESS_OUTPUT:
      s="compress output";
      break;
    default:
      s="unknown compression";
      break;
    }
    printf("(pt_set_compression) setting to %s\n",s);
  }

  pmdb_set_output_compression(level);
}

void pt_check_links() {

  com_all_sync();
  if (TRACE) printf("(pt_check_links) checking links\n");

  pmdb_check_links(pmeshpb);
}

void pt_repartition() {
  double timeval;

  com_all_sync();
  if (TRACE) printf("(pt_repartition) global repartition using IRB\n");

#ifndef PMDB_ONLY
  pt_start_timer(&timeval);
  partition(1, model_filename, mesh, &pmeshpb);
  pt_print_timer_max(timeval,"pt_repartition");
#else
  printf("(pt_repartition) region_part not linked in!!!\n");
#endif

}

void pt_parmetis(int type) {

  printf("(pt_parmetis) use Zoltan for access to Parmetis routines.\n");
  /*
  double timeval;
  idxtype options[5];
  double dummy1, dummy2, dummy3;
  options[1]=0;
  options[2]=2;
  options[3]=0;
  options[4]=1;
  
  com_all_sync();
  if (TRACE) printf("(pt_parmetis) repartition using parmetis, type %d\n",
		    type);

#ifndef PMDB_ONLY
  pt_start_timer(&timeval);
  parmetis_setup(mesh, pmeshpb, type, &dummy1, &dummy2, &dummy3);
  pt_print_timer_max(timeval,"pt_parmetis (setup)");
  pt_start_timer(&timeval);
  parmetis_balance(mesh, pmeshpb, options, type);
  pt_print_timer_max(timeval,"pt_parmetis (balance)");

#else
  printf("(pt_parmetis) parmetis not linked in!!!\n");
#endif
  */
}

#ifndef PMDB_ONLY
static void pt_zoltan_init() {

  float zoltan_version;
  int ierr;

  if (lb == NULL) {
    ierr = Zoltan_Initialize(0, NULL, &zoltan_version);
    if (ierr != ZOLTAN_OK) {
      fprintf(stderr,"(pt_zoltan_init) Zoltan_Initialize failed");
      com_abort(NULL,NULL);
    }
    if (TRACE)
      printf("(pt_zoltan_init) initialized Zoltan, version %f\n", 
	     zoltan_version);
    lb = Zoltan_Create(MPI_COMM_WORLD);
    pmdb_zoltan_setup(pmeshpb, lb);
  }
}

void pt_zoltan_setparam(char *param, char *value) {
  int ierr;

  /* make sure Zoltan has been initialized */
  pt_zoltan_init();

  /* go ahead and set the parameter */
  ierr = Zoltan_Set_Param(lb, param, value);
  if (ierr != ZOLTAN_OK) {
    fprintf(stderr,"(pt_zoltan_setparam) Zoltan_Set_Param failed to set param <%s> to <%s>\n", param, value);
    com_abort(NULL,NULL);
  }
  if (TRACE) 
    printf("(pt_zoltan_setparam) Zoltan_Set_Param <%s> to <%s>\n", param, value);
}

void pt_zoltan_read_paramfile(char *file) {

  /* make sure Zoltan is initialized */
  pt_zoltan_init();

  pmdb_read_zoltan_paramfile(pmeshpb, file);

  if (TRACE)
    printf("(pt_zoltan_read_paramfile) set params from file <%s>\n",file);
}
#endif
  
void pt_zoltan() {

#ifndef PMDB_ONLY
  double timeval;

  /* make sure Zoltan has been initialized */
  pt_zoltan_init();

  /* do the balancing based on the current parameters */ 
  if (TRACE) printf("(pt_zoltan) beginning load balancing\n");
  com_all_sync();
  pt_start_timer(&timeval);
  pmdb_zoltan_balance(pmeshpb);
  pt_print_timer_max(timeval, "pt_zoltan(totalbalancing)");
  if (TRACE) printf("(pt_zoltan) load balancing complete\n");

#if 0 /* this is the old way when using loadbal library Zoltan interface */
  if (!paramfile || strcmp(paramfile,file)) {
    /* there's either no param file or a new param file */
    paramfile = file;
    zoltan_init(pmeshpb, paramfile);
  }
  pt_start_timer(&timeval);
  zoltan_balance();
  pt_print_timer_max(timeval, "pt_zoltan(balance)");
  pt_start_timer(&timeval);
  zoltan_migrate();
  pt_print_timer_max(timeval, "pt_zoltan(migrate)");
#endif /* end of old way */

#else
  printf("(pt_zoltan) Zoltan not linked in!!!\n");
#endif
}

/**********************************************************************/
/* functions and more related to Zoltan hierarchical balancing */
/**********************************************************************/

void pt_hier_set_num_levels(int levels) {
  int i;

  if (TRACE) {
    printf("(pt_hier_set_num_levels) setting to %d\n", levels);  
    fflush(stdout);
  }

  pmdb_zoltan_hier_setup(pmeshpb);
  pmdb_hier_set_num_levels(levels);
}

void pt_hier_set_partition(int level, int partition) {

  if (trace) {
    printf("[%d] will compute partition %d at level %d\n", 
	   COM_PID, partition, level); fflush(stdout);
  }

  pmdb_hier_set_partition(level, partition);
}

void pt_hier_set_param(int level, char *param, char *value) {

  if (trace) {
    printf("[%d] will set param <%s> to <%s> at level %d\n", 
	   COM_PID, param, value, level); fflush(stdout);
  }

  pmdb_hier_set_param(level, param, value);
}

void pt_printall(char *message) {

  com_all_sync();
  PRINT_IN_ORDER() {
    printf("%s\n", message);
  }
}

void pt_printone(int where, char *message) {

  com_all_sync();
  if (COM_PID == where) {
    printf("%s\n", message);
  }
}

void pt_print_loads(int which) {
  long max_regions, avg_regions, my_regions, total_regions;
  double max_load, avg_load, my_load, total_load;
  int i;

  com_all_sync();
  if (TRACE) printf("(pt_print_loads) on %d\n",which);

  pmdb_metrics(pmeshpb,
	       PMDB_MAX_LOAD, (which&PT_MAX ? &max_load : NULL),
	       PMDB_AVG_LOAD, (which&PT_AVG ? &avg_load : NULL),
	       PMDB_LOCAL_LOAD, (which&PT_LOCAL ? &my_load : NULL),
	       PMDB_TOTAL_LOAD, (which&PT_GLOBAL ? &total_load : NULL),
	       PMDB_MAX_REGIONS, (which&PT_MAX ? &max_regions : NULL),
	       PMDB_AVG_REGIONS, (which&PT_AVG ? &avg_regions : NULL),
	       PMDB_LOCAL_REGIONS, (which&PT_LOCAL ? &my_regions : NULL),
	       PMDB_TOTAL_REGIONS, (which&PT_GLOBAL ? &total_regions : NULL),
	       NULL);

  com_sync_io();

  if (which&PT_LOCAL) {
    if (COM_PID==0) printf("Processor loads:\n");
    com_sync_io();
    for (i=0; i<COM_NUMPROCS; i++) {
      if (i==COM_PID) printf("Proc %-3d: %-7d reg, %15.5f load\n",COM_PID,my_regions,my_load);
      com_sync_io();
    }
  }

  if (which&PT_MAX) {
    if (COM_PID==0) printf("Max Load: %-7d reg, %15.5f load\n",max_regions,max_load);
  }

  if (which&PT_AVG) {
    if (COM_PID==0) printf("Avg Load: %-7d reg, %15.5f load\n",avg_regions,avg_load);
  }

  if (which&PT_GLOBAL) {
    if (COM_PID==0) printf("Total Load: %-7d reg, %15.5f load\n",total_regions,total_load);
  }
}

void pt_print_si(int which) {
  double max_si, avg_si, local_si, global_si;

  com_all_sync();
  if (TRACE) printf("(pt_print_si) on %d\n",which);

  pmdb_metrics(pmeshpb,
	       PMDB_MAX_LOCAL_SI, (which&PT_MAX ? &max_si : NULL),
	       PMDB_AVG_LOCAL_SI, (which&PT_AVG ? &avg_si : NULL),
	       PMDB_LOCAL_SI, (which&PT_LOCAL ? &local_si : NULL),
	       PMDB_GLOBAL_SI, (which&PT_GLOBAL ? &global_si : NULL),
	       NULL);

  com_sync_io();
  if (which&PT_LOCAL) {
    if (COM_PID==0) printf("Processor surface indices:\n");
    PRINT_IN_ORDER() {
      printf("Proc %-3d: %12.5f\n",COM_PID,local_si);
    }
  }
  com_sync_io();
  if (which&PT_MAX) {
    if (COM_PID==0) printf("Max Surface Index:    %12.5f\n",max_si);
  }

  if (which&PT_AVG) {
    if (COM_PID==0) printf("Avg Surface Index:    %12.5f\n",avg_si);
  }

  if (which&PT_GLOBAL) {
    if (COM_PID==0) printf("Global Surface Index: %12.5f\n",global_si);
  }  
}

void pt_print_disconn(int which_types, int entities) {
  double avg_disc[3];
  int max_disc[3], local_disc[3];
  int i;

  com_all_sync();
  if (TRACE)
    printf("(pt_print_disconn) on %d, types %d\n",which_types,entities);

  pmdb_metrics(pmeshpb,
	       PMDB_AVG_VERTEX_DISCONN, 
	       (which_types&PT_AVG && entities&PT_VERTEX) ? &avg_disc[0]: NULL,
	       PMDB_AVG_EDGE_DISCONN, 
	       (which_types&PT_AVG && entities&PT_EDGE) ? &avg_disc[1]: NULL,
	       PMDB_AVG_FACE_DISCONN, 
	       (which_types&PT_AVG && entities&PT_FACE) ? &avg_disc[2]: NULL,
	       PMDB_MAX_VERTEX_DISCONN, 
	       (which_types&PT_MAX && entities&PT_VERTEX) ? &max_disc[0]: NULL,
	       PMDB_MAX_EDGE_DISCONN, 
	       (which_types&PT_MAX && entities&PT_EDGE) ? &max_disc[1]: NULL,
	       PMDB_MAX_FACE_DISCONN, 
	       (which_types&PT_MAX && entities&PT_FACE) ? &max_disc[2]: NULL,
	       PMDB_VERTEX_DISCONN, 
	       (which_types&PT_LOCAL &&entities&PT_VERTEX)?&local_disc[0]:NULL,
	       PMDB_EDGE_DISCONN, 
	       (which_types&PT_LOCAL && entities&PT_EDGE) ?&local_disc[1]:NULL,
	       PMDB_FACE_DISCONN, 
	       (which_types&PT_LOCAL && entities&PT_FACE) ?&local_disc[2]:NULL,
	       NULL);

  com_sync_io();

  if (COM_PID==0) printf("Intraprocessor Connectivity\n");

  if (COM_PID==0) {
    if (which_types&PT_LOCAL) printf("PID    ");
    else printf("        ");
    if (entities&PT_FACE) printf("Face      ");
    if (entities&PT_EDGE) printf("Edge      ");
    if (entities&PT_VERTEX) printf("Vertex ");
    printf("\n");

    printf("-------");
    if (entities&PT_FACE) printf("----------");
    if (entities&PT_EDGE) printf("----------");
    if (entities&PT_VERTEX) printf("----------");
    printf("\n");
  }

  if (which_types&PT_LOCAL) {
    for (i=0;i<COM_NUMPROCS;i++) {
      if (i==COM_PID) {
	printf("%3d    ",i);
	if (entities&PT_FACE) printf("%5d     ",local_disc[2]);
	if (entities&PT_EDGE) printf("%5d     ",local_disc[1]);
	if (entities&PT_VERTEX) printf("%5d     ",local_disc[0]);
	printf("\n");
      }
      com_sync_io();
    }
  }
  
  if (which_types&PT_MAX) {
    if (COM_PID==0) {
      printf("Max    ");
      if (entities&PT_FACE) printf("%5d     ",max_disc[2]);
      if (entities&PT_EDGE) printf("%5d     ",max_disc[1]);
      if (entities&PT_VERTEX) printf("%5d     ",max_disc[0]);
      printf("\n");
    }
  }
  
  if (which_types&PT_AVG) {
    if (COM_PID==0) {
      printf("Avg    ");
      if (entities&PT_FACE) printf("%9.5f ",avg_disc[2]);
      if (entities&PT_EDGE) printf("%9.5f ",avg_disc[1]);
      if (entities&PT_VERTEX) printf("%9.5f ",avg_disc[0]);
      printf("\n");
    }
  }
}

void pt_print_adj(int which) {
  double max_adj, avg_adj, local_adj;
  int i;

  com_all_sync();
  if (TRACE) printf("(pt_print_adj) on %d\n",which);

  pmdb_metrics(pmeshpb,
	       PMDB_MAX_ADJACENCY, (which&PT_MAX ? &max_adj : NULL),
	       PMDB_AVG_ADJACENCY, (which&PT_AVG ? &avg_adj : NULL),
	       PMDB_LOCAL_ADJACENCY, (which&PT_LOCAL ? &local_adj : NULL),
	       NULL);

  com_sync_io();

  if (which&PT_LOCAL) {
    if (COM_PID==0) printf("Local interprocessor adjacencies:\n");
    com_sync_io();
    for (i=0; i<COM_NUMPROCS; i++) {
      if (i==COM_PID) printf("Proc %-3d: %12.5f\n",COM_PID,local_adj);
      com_sync_io();
    }
  }

  if (which&PT_MAX) {
    if (COM_PID==0) printf("Max Adjacency:    %12.5f\n",max_adj);
  }

  if (which&PT_AVG) {
    if (COM_PID==0) printf("Avg Adjacency:    %12.5f\n",avg_adj);
  }
}

void pt_print_comm_matrix() {
  char *matrix;
  int i, j;

  com_all_sync();
  if (TRACE) printf("(pt_print_comm_matrix)\n");

  SAFE_MALLOC(matrix,char *,sizeof(char)*COM_NUMPROCS*COM_NUMPROCS);

  pmdb_metrics(pmeshpb,
	       PMDB_COMM_MATRIX, &matrix,
	       NULL);

  if (COM_PID == 0) {
    printf("   ");
    for (i=0; i < COM_NUMPROCS; i++) 
      printf("%3d", i);
    printf("\n");

    for (i=0; i < COM_NUMPROCS; i++) {
      printf("%3d", i); 
      for (j=0; j < COM_NUMPROCS; j++) {

	if ( *(matrix + i*COM_NUMPROCS*sizeof(char) + j*sizeof(char)) == 1 )
	  printf("%3s", "X");
	else
	  printf("%3s", " ");
      }
      printf("\n");
    }  
  }
  free(matrix);
}

void pt_print_int_matrix() {
  long *matrix;
  int i, j;

  com_all_sync();
  if (TRACE) printf("(pt_print_int_matrix)\n");

  SAFE_MALLOC(matrix,long *,sizeof(long)*COM_NUMPROCS*COM_NUMPROCS);

  pmdb_metrics(pmeshpb,
	       PMDB_INTERFACE_MATRIX, &matrix,
	       NULL);

  if (COM_PID == 0) {
    printf("   |");
    for (i=0; i < COM_NUMPROCS; i++) 
      printf("%4d ", i);
    printf("\n");
    printf("---+");
    for (i=0; i<COM_NUMPROCS; i++)
      printf("-----");
    printf("\n");

    for (i=0; i < COM_NUMPROCS; i++) {
      printf("%3d|", i); 
      for (j=0; j < COM_NUMPROCS; j++) {

	printf("%4ld ",matrix[i*COM_NUMPROCS+j]);
      }
      printf("\n");
    }  
  }
  free(matrix);
}

void pt_print_duplicate_overhead(int entities) {
  long entity_overhead[4];
  double pct_overhead[4];

  com_all_sync();
  if (TRACE)
    printf("(pt_print_duplicate_overhead) types %d\n",entities);

  pmdb_metrics(pmeshpb,
	       PMDB_VERTEX_DUPLICATES, 
	       (entities&PT_VERTEX) ? &pct_overhead[0]: NULL,
	       PMDB_EDGE_DUPLICATES, 
	       (entities&PT_EDGE) ? &pct_overhead[1]: NULL,
	       PMDB_FACE_DUPLICATES, 
	       (entities&PT_FACE) ? &pct_overhead[2]: NULL,
	       PMDB_REGION_DUPLICATES, 
	       (entities&PT_REGION) ? &pct_overhead[3]: NULL,
	       PMDB_VERTEX_OVERHEAD, 
	       (entities&PT_VERTEX) ? &entity_overhead[0]: NULL,
	       PMDB_EDGE_OVERHEAD, 
	       (entities&PT_EDGE) ? &entity_overhead[1]: NULL,
	       PMDB_FACE_OVERHEAD, 
	       (entities&PT_FACE) ? &entity_overhead[2]: NULL,
	       PMDB_REGION_OVERHEAD, 
	       (entities&PT_REGION) ? &entity_overhead[3]: NULL,
	       NULL);

  com_sync_io();
  
  if (COM_PID == COM_MASTER) {
    printf("Overhead from duplicate processor boundary entities:\n");

    if (entities&PT_REGION)
      printf("Regions:  %6ld duplicate regions,  %8.3f%% overhead\n",
	     entity_overhead[3], pct_overhead[3]);
    if (entities&PT_FACE)
      printf("Faces:    %6ld duplicate faces,    %8.3f%% overhead\n",
	     entity_overhead[2], pct_overhead[2]);
    if (entities&PT_EDGE)
      printf("Edges:    %6ld duplicate edges,    %8.3f%% overhead\n",
	     entity_overhead[1], pct_overhead[1]);
    if (entities&PT_VERTEX)
      printf("Vertices: %6ld duplicate vertices, %8.3f%% overhead\n",
	     entity_overhead[0], pct_overhead[0]);

  }
}

void pt_check_mesh() {

  com_all_sync();
  if (TRACE) printf("(pt_check_mesh)\n");
#if 0
  M_checkAdj(mesh);
#else
  printf("(pt_check_mesh) M_checkAdj not linked in!\n");
#endif
}

void pt_reset_migstats() {

  if (TRACE) printf("(pt_reset_migstats)\n");

  pmdb_reset_migration_stats(pmeshpb);
}

void pt_print_migstats() {

  if (TRACE) printf("(pt_print_migstats)\n");

  pmdb_print_migration_stats(pmeshpb);
}

void pt_output_migstats(char *filename) {

  if (TRACE) printf("(pt_output_migstats)\n");

  pmdb_output_migration_stats(pmeshpb, filename);
}

void pt_print_nodecounts() {
#if 0
  pRegion region;
  pFace face;
  pEdge edge;
  pVertex vertex;
  void *temp;
  int nodecount;
#endif

  printf("(pt_print_nodecounts) - OBSOLETE since nodes are gone\n");

#if 0
  nodecount=0;
  temp=0;
  while (region=M_nextRegion(mesh,&temp)) {
    if (EN_node(region,0)) nodecount++;
  }
  if (COM_PID==0) printf("Region EN_node(0)'s by processor:\n");
  PRINT_IN_ORDER() {
    printf("%d: %d region nodes\n",COM_PID,nodecount);
  }

  nodecount=0;
  temp=0;
  while (face=M_nextFace(mesh,&temp)) {
    if (EN_node(face,0)) nodecount++;
  }
  if (COM_PID==0) printf("Face EN_node(0)'s by processor:\n");
  PRINT_IN_ORDER() {
    printf("%d: %d face nodes\n",COM_PID,nodecount);
  }


  nodecount=0;
  temp=0;
  while (edge=M_nextEdge(mesh,&temp)) {
    if (EN_node(edge,0)) nodecount++;
  }
  if (COM_PID==0) printf("Edge EN_node(0)'s by processor:\n");
  PRINT_IN_ORDER() {
    printf("%d: %d edge nodes\n",COM_PID,nodecount);
  }

  nodecount=0;
  temp=0;
  while (vertex=M_nextVertex(mesh,&temp)) {
    if (EN_node(vertex,0)) nodecount++;
  }
  if (COM_PID==0) printf("Vertex EN_node(0)'s by processor:\n");
  PRINT_IN_ORDER() {
    printf("%d: %d vertex nodes\n",COM_PID,nodecount);
  }
#endif
}

void pt_set_modeler(int new_model) {

  if (TRACE) {
    printf("(pt_set_modeler) to %d\n",new_model);
  }

  modeler=new_model;
}

void pt_sleep(int seconds) {

  if (TRACE) printf("(pt_sleep) going to sleep for %d seconds\n", seconds);

  sleep(seconds);
}

void pt_set_compute_conn() {

  sprintf(conn_env,"PMDB_SKIP_CONN=");
  putenv(conn_env);
}

/* gather everything to the master process */
void pt_gather_to_master() {

  int num_sends;
  long *num_send_regions;
  pEntity **send_regions;
  int *dest_pids;
  int num_recvs;
  long *num_recv_regions;
  pEntity **recv_regions;
  int *src_pids;
  pRegion insert_reg;
  void *iter;
  int i;

  if (TRACE) printf("(pt_gather_to_master)\n");

  num_sends=0;

  if (COM_PID != 0) {
    iter=0;
    while ((insert_reg=M_nextRegion(mesh, &iter))) {
      pmdb_insert_reg_for_mig((pEntity)insert_reg, 0,
	   		      &num_sends,&dest_pids,
			      &num_send_regions,&send_regions);
    }
  }

  pmdb_migrate_regions(pmeshpb, num_sends, num_send_regions, send_regions,
		       dest_pids, &num_recvs, &num_recv_regions, &recv_regions,
		       &src_pids);

  /* free memory returned by the insert and migrate calls */
  for(i=0; i<num_sends; i++) {
    free(send_regions[i]);
  }

  if (num_sends>0) {
    free(dest_pids);
    free(num_send_regions); 
    free(send_regions); 
  }
  
  for(i=0; i<num_recvs; i++) {
    free(recv_regions[i]); 
  }
  
  if (num_recvs>0) {
    free(src_pids);
    free(num_recv_regions); 
    free(recv_regions); 
  }
}

/* write out element centroids on each processor in files named
   file.proc.cent, where file is a parameter, proc is the process rank */
void pt_write_centroids(char *file) {
  FILE *fp;
  char filename[FILENAME_MAX];
  void *iter;
  pRegion region;
  double cent[3];

  if (TRACE) printf("(pt_write_centroids) to files %s.n.cent\n", file);

  sprintf(filename, "%s.%d.cent", file, COM_PID);
  if ((fp=fopen(filename,"w"))==NULL) {
    fprintf(stderr,"(pt_write_centroids) could not open file %s for writing\n",
	    filename);
    com_abort(NULL,NULL);
  }

  iter = NULL;
  while ((region = M_nextRegion(mesh, &iter))) {
    get_centroid(region, cent);
    fprintf(fp, "%15.15f %15.15f %15.15f\n", cent[0], cent[1], cent[2]);
  }

  fclose(fp);

}

/* print out the bounding box of the current mesh in memory */
void pt_print_bbox() {
  void *iter;
  pVertex vertex;
  pPoint point;
  double xyz[3];
  double min_xyz[3], max_xyz[3];
  double global_min_xyz[3], global_max_xyz[3];
  int i;

  if (TRACE) printf("(pt_print_bbox) called\n");

  min_xyz[0] = min_xyz[1] = min_xyz[2] = DBL_MAX;
  max_xyz[0] = max_xyz[1] = max_xyz[2] = -DBL_MAX;

  iter = NULL;
  while ((vertex = M_nextVertex(mesh, &iter))) {
    point=V_point(vertex);
    xyz[0]=P_x(point); xyz[1]=P_y(point); xyz[2]=P_z(point);
    for (i=0; i<3; i++) {
      if (xyz[i] < min_xyz[i]) min_xyz[i] = xyz[i];
      if (xyz[i] > max_xyz[i]) max_xyz[i] = xyz[i];
    }
  }

  com_max_double(max_xyz, global_max_xyz, 3);
  com_min_double(min_xyz, global_min_xyz, 3);

  if (COM_PID == 0) 
    printf("Bbox: min (%f,%f,%f), max (%f,%f,%f)\n", 
	   global_min_xyz[0], global_min_xyz[1], global_min_xyz[2],
	   global_max_xyz[0], global_max_xyz[1], global_max_xyz[2]);
}

/* Get the bounding box and put its coords in the variables passed as params */
static void get_bbox(double *global_min_xyz, double *global_max_xyz){
  void *iter;
  pVertex vertex;
  pPoint point;
  double xyz[3], min_xyz[3], max_xyz[3];
  int i;

  min_xyz[0] = min_xyz[1] = min_xyz[2] = DBL_MAX;
  max_xyz[0] = max_xyz[1] = max_xyz[2] = -DBL_MAX;

  iter = NULL;
  while ((vertex = M_nextVertex(mesh, &iter))) {
    point=V_point(vertex);
    xyz[0]=P_x(point); xyz[1]=P_y(point); xyz[2]=P_z(point);
    for (i=0; i<3; i++) {
      if (xyz[i] < min_xyz[i]) min_xyz[i] = xyz[i];
      if (xyz[i] > max_xyz[i]) max_xyz[i] = xyz[i];
    }
  }

  com_max_double(max_xyz, global_max_xyz, 3);
  com_min_double(min_xyz, global_min_xyz, 3);
}

/* For a given mesh, identify all edges and the tags associated with them 
   print these values to file, then print min and max coords for each tag */
void pt_print_bounds(){
  FILE *fp;
  char filename[FILENAME_MAX];
  int numfaces=GM_numFaces(model), i, j, tagcount=0, tag, found;
  double xyz[3],min_xyz[3],max_xyz[3], g_max_xyz[3], g_min_xyz[3];
  pFace face;
  pPList verts;
  pGFace gface;
  void *iterator;
  struct coords { int tag; double min_xyz[3],max_xyz[3]; };
  struct coords **clist; /* local array of all tags & min, max vals*/
  struct coords *hugebox; /* DBL_MAX,DBL_MIN coords to start out */
  struct coords *value; /* reduction of all min & maxes for a given tag */
  GFIter f_iter;

  if (COM_PID == 0) printf("(pt_print_bounds) called\n");

  sprintf(filename, "boundaries-%d.heat",COM_PID);
  if ((fp=fopen(filename,"w"))==NULL) {
    fprintf(stderr,"(pt_print_bounds) could not open file %s for writing\n",
	    filename);
    com_abort(NULL,NULL);
  }

  fprintf(fp,"Boundary coordinates and associated tags\n\n");

  SAFE_MALLOC(clist,struct coords **,sizeof(struct coords *)*numfaces);

  g_min_xyz[0] = g_min_xyz[1] = g_min_xyz[2] = DBL_MAX;
  g_max_xyz[0] = g_max_xyz[1] = g_max_xyz[2] = -DBL_MAX; 
  
  for (i=0; i<numfaces; i++) {
    SAFE_MALLOC(clist[i],struct coords*,sizeof(struct coords));
    clist[i]->tag = -1;
    clist[i]->min_xyz[0] = clist[i]->min_xyz[1] = clist[i]->min_xyz[2]=DBL_MAX;
    clist[i]->max_xyz[0] = clist[i]->max_xyz[1] = 
      clist[i]->max_xyz[2] = -DBL_MAX;
  }
  
  /* For each face on a boundary, print to file its coords and tag */
  iterator = NULL;
  while ((face = M_nextFace(mesh,&iterator))){

    /* Only continue if face is on boundary */
    if (F_whatInType(face) == Gface) {
      double coords[3], c_min[3], c_max[3];

      get_centroid(face,xyz);
      tag = GEN_tag(F_whatIn(face));
      fprintf(fp,"x: %f\ty: %f\tx: %f\ttag: %d\n",xyz[0],xyz[1],xyz[2],tag);

      verts = F_vertices(face,0);
      V_coord(PList_item(verts,0), c_min);

      for (i=0; i<3; i++) { c_max[i] = c_min[i]; }

      for (i=1; i<PList_size(verts); i++) {
	V_coord(PList_item(verts,i), coords);
	for (j=0; j<3; j++) {	
	  if (coords[j] < c_min[j]) c_min[j] = coords[j];
	  if (coords[j] > c_max[j]) c_max[j] = coords[j];
	}
      }
      PList_delete(verts);

      found=0;
      for (i=0; i < tagcount && !found; i++) {
	if (clist[i]->tag == tag) {
	  found=1;
	  for (j=0; j<3; j++) {
	    if (c_min[j] < clist[i]->min_xyz[j]) clist[i]->min_xyz[j]=c_min[j];
	    if (c_max[j] > clist[i]->max_xyz[j]) clist[i]->max_xyz[j]=c_max[j];
	  }
	}
      }

      if (!found) {
	clist[tagcount]->tag = tag;
	for (i=0; i<3; i++) {
	  clist[tagcount]->min_xyz[i] = c_min[i];
	  clist[tagcount]->max_xyz[i] = c_max[i];
	}
	tagcount++;
      }
    }
  }
  fclose(fp);
  
  SAFE_MALLOC(hugebox,struct coords*,sizeof(struct coords));

  f_iter = GM_faceIter(model);
  while ((gface = GFIter_next(f_iter))) {
    tag=GEN_tag((pGEntity)gface);

    hugebox->min_xyz[0] = hugebox->min_xyz[1] = hugebox->min_xyz[2] = DBL_MAX; 
    hugebox->max_xyz[0] = hugebox->max_xyz[1] = hugebox->max_xyz[2] = -DBL_MAX; 

    value = hugebox;
    found=0;
    for (i=0; i<tagcount && !found;i++) {
      if (tag == clist[i]->tag) { value = clist[i]; found=1; }
    }

    com_max_double(value->max_xyz, max_xyz, 3);
    com_min_double(value->min_xyz, min_xyz, 3);
    
    if (COM_PID==0)
      printf("tag %d min (%f,%f,%f) max (%f,%f,%f)\n",
	     tag,min_xyz[0],min_xyz[1],min_xyz[2],
	     max_xyz[0],max_xyz[1],max_xyz[2]);

    for (i=0; i<3; i++) {
      if (min_xyz[i] < g_min_xyz[i]) g_min_xyz[i]=min_xyz[i];
      if (max_xyz[i] > g_max_xyz[i]) g_max_xyz[i]=max_xyz[i];
    }
    
  }
  GFIter_delete(f_iter);

  if (COM_PID==0)
    printf("global min (%f,%f,%f) max (%f,%f,%f)\n",
	   g_min_xyz[0],g_min_xyz[1],g_min_xyz[2],
	   g_max_xyz[0],g_max_xyz[1],g_max_xyz[2]);

  /* Free memory previously allocated */
  for (i=0; i<numfaces; i++) { 
    free(clist[i]); 
  }
  free(clist);
  free(hugebox);

  printf("(pt_print_bounds) %s successfully written\n",filename);
}

/* Set boundary conditions for a given mesh tag - initialize mesh MUST be
   called before calling this function */
void pt_set_bound(int tag, double init_val) {

  if (TRACE) printf("(pt_set_bound) setting tag %d to %f\n",tag,init_val);

  tagArray[tagCount]->tag = tag;
  tagArray[tagCount]->value = init_val;
  tagCount++;
}

/* Give all of the elements in a mesh an initial value. */
void pt_initialize_mesh(double init_val){
  pRegion region;
  void *iter;
  struct Heat *heat;
  static int first_time=1, i;
  struct tagVals *curTag;

  if (TRACE) printf("(pt_initialize_mesh) called\n");

  /* Allocate memory for all boundary tag values (these should be set later
     by the user) */
  SAFE_MALLOC(tagArray,struct tagVals*,
	      sizeof(struct tagVals)*GM_numFaces(model));
  for (i=0; i<GM_numFaces(model); i++){
    SAFE_MALLOC(curTag,struct tagVals*,sizeof(struct tagVals));
    curTag->tag = -1;
    tagArray[i] = curTag;
  }

  /* Register all heat structures before attaching them (prepare for
      migration) */
  if (first_time) {
    if (!pmdb_ptag_register(pmeshpb, Tregion, heat_tag,
			    sizeof(struct Heat))) {
      fprintf(stderr,
	      "PMDBtool %s: (pt_initialize_mesh) Heat tag already registered!\n",
	      PMDBTOOL_VERSION);
      com_abort(NULL, NULL);
    }
    first_time=0;
  }

  iter = NULL;
  /*  For each region in the mesh, associate an initial value for Heatsolver */
  while ((region = M_nextRegion(mesh,&iter))){
    if (!(EN_dataP(region, heat_tag))) {
      SAFE_MALLOC(heat, struct Heat*, sizeof(struct Heat));
      heat->h1=init_val;
      heat->h2=init_val;
      EN_attachDataP(region, heat_tag, heat);
    }
  }

  if (TRACE){
    printf("(initialize_mesh) All mesh regions set to %f\n", heat->h1);
  }
}

void pt_clear_regions(char *tag){
  void *iter;
  pRegion region;
  struct Heat *heat;
  int i;

  if (TRACE) printf("(pt_clear_regions) called\n");

  /* Clear the boundary tags and associated values */
  for (i=0; i<GM_numFaces(model); i++){
    free(tagArray[i]);
  }
  free(tagArray);
  tagCount=0;

  iter = NULL;
  /* For each region in the mesh, remove the value associated with tag */
  while ((region = M_nextRegion(mesh,&iter))) {
    if ((heat = EN_dataP(region, tag))) {
      free(EN_dataP(region,tag));
      EN_removeData(region, tag);
    }
    else printf("No tag here!!!\n");
  }
}


/* Solve LaPlace's heat equation on the mesh (optimized serial version) */
void pt_heat_solve_serial(int numturns, double epsilon, char *file){
  FILE *fp;
  char filename[FILENAME_MAX];
  pRegion region, adjReg;
  pFace face;
  pPList faces, regions;
  void *iter;
  int num_faces, i, odd=0;
  double error=0, xyz[3], timeval;
  int turn=0, keepGoing=1; /* how many times calculation has been done, 
                            whether or not epsilon is below error value */
  double neighbor_sols[MAX_NEIGHBORS]; /* Array of neighboring solution values */
  struct Heat *neighbor_data; /*  cur and prev values for each neighbor */
  struct Heat *heat; /* own cur and prev values */

  if (TRACE) printf("(heat_solve) data output to file %s.heat\n",file);

  pt_start_timer(&timeval);

  while (turn < numturns && keepGoing) {
    error = 0;
    keepGoing = 0;
    /* Every iteration, flip h1 and h2 values */
    if (odd) odd=0;
    else odd=1;

    iter = NULL;
    /* Update all regions */
    while ((region = M_nextRegion(mesh,&iter))){
      faces = R_faces(region);
      num_faces = PList_size(faces);
      /* for each bounding face of the region, either get neighboring value
         or apply a boundary condition */
      for (i=0; i < num_faces; i++) {
	face = PList_item(faces, i);
	
	/* Get the region adjacent to this face */
	regions = F_regions(face);
	if (PList_size(regions) == 2){
	  /* Store the region that is not the current one */
	  if (region != PList_item(regions, 0))
	    adjReg = PList_item(regions, 0);
	  else
	    adjReg = PList_item(regions, 1);

	  /* Get the value held in the region */
	  if (EN_dataP(adjReg, heat_tag))
	    neighbor_data = (struct Heat*)EN_dataP(adjReg, heat_tag);
	  else
	    printf("neighboring region has no heat associated with it!!!\n");
	  if (odd) neighbor_sols[i] = neighbor_data->h2;
	  else neighbor_sols[i] = neighbor_data->h1;
	}
	else { /* This is an edge, no adjacent region	  */
	  int found, j;
	  found=0;
	  for (j=0; j<GM_numFaces(model) && !found; j++) {
	    if (tagArray[j]->tag == GEN_tag(F_whatIn(face))){
	      found=1;
	    }		
	  }
	  if (found) neighbor_sols[i] = tagArray[j-1]->value;
	  else { /* tag not set, use "reflected" value from current region */
	    if (EN_dataP(region, heat_tag))
	      neighbor_data = (struct Heat*)EN_dataP(region, heat_tag);
	    else
	      printf("region has no heat associated with it!!!\n");
	    if (odd) neighbor_sols[i] = neighbor_data->h2;
	    else neighbor_sols[i] = neighbor_data->h1;
	  }
	}
	PList_delete(regions);
      }
      PList_delete(faces);
      if (EN_dataP(region, heat_tag))
	heat = (struct Heat*)EN_dataP(region, heat_tag);
      else
	printf("The current region has no heat associated with it!!!\n");

      /* Now have array of neighbor_sols (doubles) */
      if (odd){
	heat->h1=0;	
	/* Calculate new solution and store it in heat->h1 (h2 unchanged) */
	for (i=0; i < num_faces; i++){
	  heat->h1 += neighbor_sols[i];
	}
	heat->h1 = (heat->h1)*0.25;
      }
      else {
	heat->h2=0;
	/* Calculate new solution and store it in heat->h2 (h1 unchanged) */
	for (i=0; i < num_faces; i++){
	  heat->h2 += neighbor_sols[i];
	}
	heat->h2 = (heat->h2)*0.25;
      }
      if (fabs(heat->h2 - heat->h1) > error) error = fabs(heat->h2 - heat->h1);
      if (keepGoing == 0) /* only check if not already set */
	if (fabs(heat->h2 - heat->h1) > epsilon) keepGoing=1;
    }
    turn++;
  }

  if (TRACE) printf("(heat_solve) numturns = %d, error = %f\n",turn,error);
  pt_print_timer_max(timeval, "heat_solve(serial)");

  /* Print out final solution values in a format readable by gnuplot */
  sprintf(filename, "%s.heat", file);
  if ((fp=fopen(filename,"w"))==NULL) {
    fprintf(stderr,"(heat_solve) could not open file %s for writing\n",
	    filename);
    com_abort(NULL,NULL);
  }

  fprintf(fp,"# X coord \t Solution\n");

  iter=NULL;
  while ((region = M_nextRegion(mesh,&iter))) {
    get_centroid(region,xyz);
    fprintf(fp,"%f\t",xyz[0]);
    heat = (struct Heat*)EN_dataP(region, heat_tag);
    if (odd) fprintf(fp,"%f\n",heat->h1);
    else fprintf(fp,"%f\n",heat->h2);
  }

  fclose(fp);

}


/* Solve LaPlace's heat equation on the mesh - MPI version*/
void pt_heat_solve_mpi(int numturns, double epsilon){
  pRegion region, adjReg;
  pFace face, fac, recvface, remPtr;
  pPList faces, regions;
  void *iter;
  int num_faces, i, odd=0;
  double error=0, allerror, timeval;
  int turn=0,keepGoing=1,going; /* how many times calculation has been done, 
                                 whether or not epsilon is below error value */
  double neighbor_sols[MAX_NEIGHBORS]; /* Array of neighboring solution values */
  struct Heat *neighbor_data; /* cur and prev values for each neighbor */
  struct Heat *heat; /* own cur and prev values */
  void *reset=NULL, *res=NULL;
  int remProcId;  /* ID and pointer to region on remote process */
  double edge_heat, other_heat, *heatp;
  MPI_Request *req;
  MPI_Status *stat;
  int rc, done=0, found, numfaces=0;
  char *n_heat_tag="nhet"; /* neighboring proc heat value tag */
  struct HeatPack *send_pack, *recv_pack;

  /* MPI datatype declarations */
  int blocklens[2];
  MPI_Aint displacements[2];
  MPI_Datatype types[2], datatype;
  blocklens[0]=1;
  displacements[0]=0;
  types[0]=MPI_DOUBLE;
  blocklens[1]=sizeof(pFace);
  displacements[1]=sizeof(double);
  types[1]=MPI_BYTE;

  if (TRACE) printf("(heat_solve) beginning\n");
  com_all_sync();
  pt_start_timer(&timeval);

  if (TRACE) printf("(heat_solve) max num turns: %d, epsilon: %f\n", 
		    numturns, epsilon);

  numfaces = pmdb_num_all_pb_en(pmeshpb,Tface);

  /* Create a new datatype to pass heat & face ptr using MPI */
  rc=MPI_Type_struct(2,blocklens,displacements,types,&datatype);
  if (rc != MPI_SUCCESS) {
    fprintf(stderr, "MPI_Type_struct for proc %d failed\n",COM_PID);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  rc=MPI_Type_commit(&datatype);
  if (rc != MPI_SUCCESS) {
    fprintf(stderr, "MPI_Type_commit for proc %d failed\n",COM_PID);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  numfaces = pmdb_num_all_pb_en(pmeshpb,Tface);

  /* Allocate space for the HeatPack buffers */
  SAFE_MALLOC(send_pack,struct HeatPack*,(sizeof(struct HeatPack))*numfaces);
  SAFE_MALLOC(recv_pack,struct HeatPack*,(sizeof(struct HeatPack))*numfaces);

  /* Allocate space for send and receive buffers */
  SAFE_MALLOC(req,MPI_Request*,(sizeof(MPI_Request))*numfaces*2);
  SAFE_MALLOC(stat,MPI_Status*,(sizeof(MPI_Status))*numfaces*2);

  while (turn < numturns && keepGoing) {
    error = 0;
    going = 0;
    /* Every iteration, flip h1 and h2 values */
    if (odd) odd=0;
    else odd=1;

    i=0;
    reset=NULL;
    /* Send info about regions adjacent to all faces on a proc boundary */
    while ((face = pmdb_all_next_en(pmeshpb,Tface,&reset))) {

      regions = F_regions(face);       
      region = PList_item(regions,0);
      PList_delete(regions);

      if (EN_dataP(region, heat_tag)) {
	if (odd) edge_heat = ((struct Heat*)EN_dataP(region, heat_tag))->h2;
	else edge_heat = ((struct Heat*)EN_dataP(region, heat_tag))->h1;
      }
      else printf("Region contains no heat data!\n");
    
      /* Ask face who it is adjacent to */
      pbop_min_link((pEntity)face,0,&remProcId,(pEntity *)&remPtr);

      send_pack[i].heat = edge_heat;
      send_pack[i].face = remPtr;

      /* Send heat data to that region */
      rc = MPI_Isend(&send_pack[i],1,datatype,remProcId,0,
		     MPI_COMM_WORLD,&req[i]);
      if (rc != MPI_SUCCESS) {
	fprintf(stderr, "MPI_Isend from %d to %d failed\n",
		COM_PID,remProcId);
	MPI_Abort(MPI_COMM_WORLD, 1);
      }

      /* Receive data from that region */
      rc = MPI_Irecv(&recv_pack[i],1,datatype,remProcId,0,
		      MPI_COMM_WORLD,&req[i+numfaces]);
      if (rc != MPI_SUCCESS) {
	fprintf(stderr, "MPI_Irecv from %d to %d failed\n",
		COM_PID,remProcId);
	MPI_Abort(MPI_COMM_WORLD, 1);
      }

      i++;
    }

    /* Do requests with one big array, count through */
    MPI_Waitall(2*numfaces,req,stat);

    /* Process received values */
    for (i=0; i < numfaces; i++) {
      recvface = recv_pack[i].face;
      other_heat = recv_pack[i].heat;

#ifdef DEBUG
      /* Check to ensure faces being attached are on process boundaries. */
	found=0;
	res=NULL;
	while ((fac = pmdb_all_next_en(pmeshpb,Tface,&res))){
	  if (recvface == fac) found=1;
	}
	if (!found) printf("face not on proc boundary!\n");

	/* pmdb_is_en_on_pb((pEntity)face,COM_PID,(pEntity *)&offptr);
	   if (!pmdb_is_en_on_pb(face,COM_PID,&offptr))
	   printf("face not on proc boundary! (2)\n"); */
#endif
	 
	if (!EN_dataP(recvface,n_heat_tag)){ /* first time through */
	  SAFE_MALLOC(heatp,double *,sizeof(double));

	  /*Have heat value for region attached to this face, store the 
	    value before moving on to the next face. */
	  *heatp = other_heat;

	  /* Attach the double (value of neighbor heat) to this face
	     Value of face should now be face about which data was received */
	  EN_attachDataP(recvface, n_heat_tag, heatp);
	}
	else {  /* Data allocated, retrieve and update */
	  heatp = EN_dataP(recvface,n_heat_tag);
	  *heatp = other_heat;
	}
    }

    iter=NULL;
    /* Update all regions */
    while ((region = M_nextRegion(mesh,&iter))){
      faces = R_faces(region);
      num_faces = PList_size(faces);
      /* for each bounding face of the region, either get neighboring value
         or apply a boundary condition */
      for (i=0; i < num_faces; i++) {
	face = PList_item(faces, i);
	
	/* Get the region adjacent to this face */
	regions = F_regions(face);
	if (PList_size(regions) == 2){
	  /* Store the region that is not the current one */
	  if (region != PList_item(regions, 0))
	    adjReg = PList_item(regions, 0);
	  else
	    adjReg = PList_item(regions, 1);

	  /* Get the value held in the region */
	  if (EN_dataP(adjReg, heat_tag))
	    neighbor_data = (struct Heat*)EN_dataP(adjReg, heat_tag);
	  else
	    printf("neighboring region has no heat associated with it!!!\n");
	  if (odd) neighbor_sols[i] = neighbor_data->h2;
	  else neighbor_sols[i] = neighbor_data->h1;
	}
	else { /*  This could be actual boundary or process boundary */
	  if (F_whatInType(face) == Gface) { /* Face is on mesh boundary */
	    int j;
	    found=0;
	    for (j=0; j<GM_numFaces(model) && !found; j++) {
	      if (tagArray[j]->tag == GEN_tag(F_whatIn(face))){
		found=1;
	      }		
	    }
	    if (found) neighbor_sols[i] = tagArray[j-1]->value;
	    else { /* tag not set, use "reflected" value from current region*/
	      if (EN_dataP(region, heat_tag))
		neighbor_data = (struct Heat*)EN_dataP(region, heat_tag);
	      else
		printf("region has no heat associated with it!!!\n");
	      if (odd) neighbor_sols[i] = neighbor_data->h2;
	      else neighbor_sols[i] = neighbor_data->h1;
	    }
	  }
	  else { /* Face is on process boundary */
	    if (EN_dataP(face, n_heat_tag)) {
	      neighbor_sols[i] = *((double*)EN_dataP(face, n_heat_tag));
	    }
	    else printf("PID %d did not receive heat value from neighboring process!!!\n",COM_PID);
	  }
	}
	PList_delete(regions);
      }
      if (EN_dataP(region, heat_tag))
	heat = (struct Heat*)EN_dataP(region, heat_tag);
      else
	printf("The current region has no heat associated with it!!!\n");

      /* Now have array of neighbor_sols (doubles) */
      if (odd){
	heat->h1=0;	
	/* Calculate new solution and store it in heat->h1 (h2 unchanged) */
	for (i=0; i < num_faces; i++){
	  heat->h1 += neighbor_sols[i];
	}
	heat->h1 = (heat->h1)*0.25;
      }
      else {
	heat->h2=0;
	/* Calculate new solution and store it in heat->h2 (h1 unchanged) */
	for (i=0; i < num_faces; i++){
	  heat->h2 += neighbor_sols[i];
	}
	heat->h2 = (heat->h2)*0.25;
      }
      if (fabs(heat->h2 - heat->h1) > error) error = fabs(heat->h2-heat->h1);
      if (going == 0) /* only check if not already set */
	if (fabs(heat->h2 - heat->h1) > epsilon) going=1;

      PList_delete(faces);
    }

    turn++;
    done=0;

    MPI_Allreduce(&going,&keepGoing,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
  }

  MPI_Reduce(&error,&allerror,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);

  if (TRACE) 
    printf("(heat_solve) numturns = %d, error = %f\n",turn,allerror); 

  free(send_pack);
  free(recv_pack);
  free(stat);
  free(req);

  /* Free memory associated with tags on proc boundary faces */
  reset=NULL;
  while ((face = pmdb_all_next_en(pmeshpb,Tface,&reset))){
    if (EN_dataP(face,n_heat_tag))
      free(EN_dataP(face,n_heat_tag));
    else
      printf("Face has no data attached (attempt to free failed)\n");
  }

  pt_print_timer_max(timeval, "heat_solve(mpi)");
  if (TRACE) printf("(heat_solve) completed\n");
}

/* Solve LaPlace's heat equation on the mesh - autopack version*/
void pt_heat_solve(int numturns, double epsilon){
  pRegion region, adjReg;
  pFace face, fac, recvface, remPtr;
  pPList faces, regions;
  void *iter;
  int num_faces, i, odd=0;
  double error=0, allerror, timeval;
  int turn=0, keepGoing=1, going; /* how many times calculation has been done, 
				     whether or not epsilon is below 
				     error value */
  double neighbor_sols[MAX_NEIGHBORS]; /* Array of nbring solution values */
  struct Heat *neighbor_data; /* cur and prev values for each neighbor */
  struct Heat *heat; /* own cur and prev values */
  void *reset=NULL, *res=NULL;
  int remProcId;  /* ID and pointer to region on remote process */
  double edge_heat, other_heat, *heatp;
  int rc, done=0, found, numfaces=0;
  char *n_heat_tag="nhet"; /* neighboring proc heat value tag */
  struct HeatPack *bufptr;
  void *sendbuf, *msg;
  int size, from, tag, r_count, received;

  if (TRACE) printf("(pt_heat_solve) beginning\n");
  com_all_sync();
  pt_start_timer(&timeval);

  if (TRACE) printf("(pt_heat_solve) max iterations: %d, epsilon: %f\n", 
		    numturns, epsilon);

  numfaces = pmdb_num_all_pb_en(pmeshpb,Tface);

  while (turn < numturns && keepGoing) {
    if (TRACE) printf("(pt_heat_solve) iteration %d\n", turn);
    error = 0;
    going = 0;
    /* Every iteration, flip h1 and h2 values */
    if (odd) odd=0;
    else odd=1;

    AP_send_begin();

    reset=NULL;
    /* Send info about regions adjacent to all faces on a proc boundary */
    while ((face = pmdb_all_next_en(pmeshpb,Tface,&reset))) {

      regions = F_regions(face);       
      region = PList_item(regions,0);
      PList_delete(regions);

      if (EN_dataP(region, heat_tag)) {
	if (odd) edge_heat = ((struct Heat*)EN_dataP(region, heat_tag))->h2;
	else edge_heat = ((struct Heat*)EN_dataP(region, heat_tag))->h1;
      }
      else printf("Region contains no heat data!\n");
    
      /* Ask face who it is adjacent to */
      pbop_min_link((pEntity)face,0,&remProcId,(pEntity *)&remPtr);

      /* Allocate a buffer the size of a HeatPack for sending data */
      sendbuf = AP_alloc(remProcId,0,sizeof(struct HeatPack));

      /* Treat sendbuf like a HeatPack, set data before sending */
      bufptr=(struct HeatPack*)sendbuf;
      bufptr->heat = edge_heat;
      bufptr->face = remPtr;
      
      AP_send(sendbuf);
    }
    /* All sending should be completed here */
    AP_send_end();

    received=0;
    while (!AP_recv_count(&r_count) || received<r_count) {
      rc=AP_recv(MPI_ANY_SOURCE,0,AP_BLOCKING|AP_DROPOUT,
		 &msg,&size,&from,&tag);
      if (rc) {
	bufptr=(struct HeatPack *)msg;
	received++;

	recvface = bufptr->face;
	other_heat = bufptr->heat;

#ifdef DEBUG
	/* Check to ensure faces being attached are on process boundaries. */
	found=0;
	res=NULL;
	while ((fac = pmdb_all_next_en(pmeshpb,Tface,&res))){
	  if (recvface == fac) found=1;
	}
	if (!found) printf("face not on proc boundary!\n");
#endif

	if (!EN_dataP(recvface,n_heat_tag)){ /* first time through */
	  SAFE_MALLOC(heatp,double *,sizeof(double));

	  /* Have heat value for region attached to this face, store the 
	     value before moving on to the next face. */
	  *heatp = other_heat;

	  /* Attach the double (value of neighbor heat) to this face
	     Value of face should now be face about which data was received */
	  EN_attachDataP(recvface, n_heat_tag, heatp);
	}
	else {  /* Data allocated, retrieve and update */
	  heatp = EN_dataP(recvface,n_heat_tag);
	  *heatp = other_heat;
	}
      }
    }

    if (COM_NUMPROCS > 1) AP_free(msg);

    if (numfaces != received) 
      printf("Proc %d expected %d messages but received %d.\n",COM_PID,
	     numturns,received);

    iter=NULL;
    /* Update all regions */
    while ((region = M_nextRegion(mesh,&iter))){
      faces = R_faces(region);
      num_faces = PList_size(faces);
      /* for each bounding face of the region, either get neighboring value
	 or apply a boundary condition */
      for (i=0; i < num_faces; i++) {
	face = PList_item(faces, i);
	
	/* Get the region adjacent to this face */
	regions = F_regions(face);
	if (PList_size(regions) == 2){
	  /*  Store the region that is not the current one */
	  if (region != PList_item(regions, 0))
	    adjReg = PList_item(regions, 0);
	  else
	    adjReg = PList_item(regions, 1);

	  /* Get the value held in the region */
	  if (EN_dataP(adjReg, heat_tag))
	    neighbor_data = (struct Heat*)EN_dataP(adjReg, heat_tag);
	  else
	    printf("neighboring region has no heat associated with it!!!\n");
	  if (odd) neighbor_sols[i] = neighbor_data->h2;
	  else neighbor_sols[i] = neighbor_data->h1;
	}
	else { /* This could be actual boundary or process boundary */
	  if (F_whatInType(face) == Gface) { /* Face is on mesh boundary */
	    int j;
	    found=0;
	    for (j=0; j<GM_numFaces(model) && !found; j++) {
	      if (tagArray[j]->tag == GEN_tag(F_whatIn(face))){
		found=1;
	      }		
	    }
     	    if (found) neighbor_sols[i] = tagArray[j-1]->value;
	    else { /* tag not set, use "reflected" value from current region */
	      if (EN_dataP(region, heat_tag))
		neighbor_data = (struct Heat*)EN_dataP(region, heat_tag);
	      else
		printf("region has no heat associated with it!!!\n");
	      if (odd) neighbor_sols[i] = neighbor_data->h2;
	      else neighbor_sols[i] = neighbor_data->h1;
	    }
	  }
	  else { /* Face is on process boundary */
	    if (EN_dataP(face, n_heat_tag)) {
	      neighbor_sols[i] = *((double*)EN_dataP(face, n_heat_tag));
	    }
	    else printf("PID %d did not receive heat value from neighboring process!!!\n",COM_PID);
	  }
	}
	PList_delete(regions);
      }
      if (EN_dataP(region, heat_tag))
	heat = (struct Heat*)EN_dataP(region, heat_tag);
      else
	printf("The current region has no heat associated with it!!!\n");

      /* Now have array of neighbor_sols (doubles) */
      if (odd){
	heat->h1=0;	
	/* Calculate new solution and store it in heat->h1 (h2 unchanged) */
	for (i=0; i < num_faces; i++){
	  heat->h1 += neighbor_sols[i];
	}
	heat->h1 = (heat->h1)*0.25;
      }
      else {
	heat->h2=0;
	/* Calculate new solution and store it in heat->h2 (h1 unchanged) */
	for (i=0; i < num_faces; i++){
	  heat->h2 += neighbor_sols[i];
	}
	heat->h2 = (heat->h2)*0.25;
      }
      if (fabs(heat->h2 - heat->h1) > error) error = fabs(heat->h2-heat->h1);
      if (going == 0) /* only check if not already set */
	if (fabs(heat->h2 - heat->h1) > epsilon) going=1;

      PList_delete(faces);
    }

    turn++;
    done=0;

    MPI_Allreduce(&going,&keepGoing,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
  }

  MPI_Reduce(&error,&allerror,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);

  if (TRACE) 
    printf("(pt_heat_solve) numturns = %d, error = %f\n",turn,allerror); 

  /* Free memory associated with tags on proc boundary faces */
  reset=NULL;
  while ((face = pmdb_all_next_en(pmeshpb,Tface,&reset))){
    if (EN_dataP(face,n_heat_tag))
      free(EN_dataP(face,n_heat_tag));
    else
      printf("Face has no data attached (attempt to free failed)\n");
  }

  pt_print_timer_max(timeval, "pt_heat_solve(autopack)");
  if (TRACE) printf("(pt_heat_solve) completed\n");
}

pMeshPB pt_get_pmeshpb() {
  return pmeshpb;
}
