#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
/*#include <values.h>*/

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

/*#include "pmdbtool.h"*/

#define MAXLABELS  (100)
#define FPRINTF  if (!ret) return(0); else ret= EOF!=fprintf

typedef struct Heat{ double h1, h2; }Heat;

static int solfile_dump_cells_writedata(FILE *outfile,
					pMesh mesh,
					char ***labels_ret,
					int *nlabels_ret)
{
  int ret=1;
  void *temp;
  pRegion region;
  struct Heat *heatdata; /* find way to make this heat data structure */

  int nlabels=0;
  static char *labels[MAXLABELS];

  int DUMP_CELL_HEAT     = 1; /*bc_getparam("DUMP_CELL_HEAT");*/

                          /* make sure that MAXLABELS is large enough */
  if (DUMP_CELL_HEAT)     labels[nlabels++]="heat value";

  if (labels_ret)         *labels_ret=labels;
  if (nlabels_ret)        *nlabels_ret=nlabels;

  if (!nlabels)
    return(1);

  temp=NULL;
  while ((region=M_nextRegion(mesh,&temp)))
    {
      if (EN_dataP((region),"heat"))
	heatdata=EN_dataP((region),"heat"); 
      
      /* This could possibly be prev value (off by 1 round) */
      if (DUMP_CELL_HEAT) {
	FPRINTF(outfile,"%.8e ", ( heatdata->h1 ));
      }
      
      FPRINTF(outfile,"\n");
    }

  return(ret);
}






static int solfile_dump_cells(char *filename,
		       pMesh mesh,
		       int compress,
		       char **filename_ret,
		       char ***labels_ret,
		       int *nlabels_ret)

{
  static char fname[128];
  FILE *outfile;
  char command[128];
  int status;

  sprintf(fname,"%s.%d.cell",filename,COM_PID);
  outfile=fopen(fname,"w");

  if (!outfile)
    {
      perror("solfile_dump_cells: File open error");
      return(0);
    }

  if (!solfile_dump_cells_writedata(outfile,mesh,labels_ret,nlabels_ret))
    {
      fprintf(stderr,"solfile_dump_cells: error writing to file %s\n",fname);
      perror(" fprintf");
      fclose(outfile);
      return(0);
    }
      
  if (fclose(outfile))
    {
      fprintf(stderr,"solfile_dump_cells: error closing file %s\n",fname);
      perror(" fclose");
      return(0);
    }

  if (filename_ret) 
    {
      if (*nlabels_ret)
	*filename_ret=fname;
      else
	*filename_ret=NULL;
    }

  if (! *nlabels_ret)
    {
      unlink(fname); /* ? */
      return(1);
    }

  if (compress)
    {
      sprintf(command,"gzip -f %s",fname);
      if ((status=system(command)))
	fprintf(stderr,"solfile_dump_cells:"
		" warning, command %s returned status %d\n",
		command,status);
    }

  return(1);
}

void pt_heat_write_dx(char *name,
	      pMeshPB pmeshpb,
	      int checknum,
	      int iter,
	      double time)
{
  char dxname[128];
  char *cfname,*nfname;       /* File names for cell and node data */
  pMesh mesh;
  char **cell_labels, **node_labels;
  int cell_nlabels, node_nlabels;
  static int lastchecknum= -1;
  static int seq;

  sprintf(dxname,"DX_%s",name);

  if (checknum!=lastchecknum)
    seq=0;
  else
    seq++;
  lastchecknum=checknum;


  mesh=pmdb_get_pmesh(pmeshpb);

  sprintf(dxname,"%03d.%d.%s",checknum,seq,name);
  cfname=NULL;
  nfname=NULL;

  if (COM_PID==1) printf("Writing dx file %s at iter %d time %e\n",dxname,
			 iter,time);

  if (! solfile_dump_cells(dxname,mesh,TRUE,
			   &cfname,&cell_labels,&cell_nlabels) )
    abort();

  if (! pmdb_write_ext_dx(dxname,pmeshpb,
			  cfname,cell_labels,cell_nlabels,
			  NULL,NULL,0,
			  PMDB_DX_DEFAULT))
    abort();
}
