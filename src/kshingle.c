#include <python2.7/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>

#include "loadgraph.h"
#include "vidmap.h"
#include "lib.h"
#include "elib.h"

#define MAX_NAME_LEN 200

char gAdjFile[MAX_NAME_LEN];
char **n2gidHash; /* i -> gid */

int gN; /* #valid vertices, it changes */
int gNN; /* number of original lines, it is fixed */
int gC;
int gS;
ulong *gA;
ulong *gB;
ulong gLgPrime;

SGL *gFSgl;
SGL *gSSgl;

/* these global vars should not be shared */
int mfSglCnt;
int fSglCnt;
int sSglCnt;  /* #(second level shingles) */
long int msSglCnt; /* upper bound */
struct ufind *uSet;
int *vidmap; /* track position of vertices index in heap (array) */
int main(int argc, char *argv[])
{
    int i,temp=0;
    int singleton;
    SGL *res;
    long double x=0;
    void init_vars(void);
    void free_vars(void);
    void loadGUI1(int argc, char *argv[]);
    void loadOP1(int argc, char *argv[]);
    void loadOP3(int argc, char *argv[]);
    ///////////////////
    loadGUI1(1,argv);
    FILE *fp=NULL;
  	char str1[5],str2[5],str3[5],str4[10];
  	fp=fopen("src/input.txt","r");
  	fscanf(fp,"%s\n",str1);
  	fscanf(fp,"%s\n",str2);
  	fscanf(fp,"%s\n",str3);
  	fscanf(fp,"%s\n",str4);
    fclose(fp);
    strcpy(gAdjFile,str4);
    gS=atoi(str1);
    gC=atoi(str2);
    gN=atoi(str3);
    if(gN==0 || gS==0 || gC==0)
    {
        printf("Invalid Inputs..\n");
        exit(1);
    }
    printf("Inputs Accepted\n");
    double t1=omp_get_wtime();
    gNN = gN;
    init_vars();
    init_vidmap(vidmap, gN);
    gLgPrime = large_prime();
    fetch_rands(gA, gB, gC, gLgPrime);
    printf("Initialization succeed...\n");

    load_graph(gAdjFile, gN, vidmap);
    printf("%d\n",gN ); /* gN might be changed, becz of pruning */
    fSglCnt = gN*gC; /* real #sgls */
    printf("#vertices:%d => %d\n",gNN, gN);
    printf("First level shingling succeed...\n");

    /* at most gN*gC*gC/gS */
    msSglCnt = fSglCnt*gC/gS; /* second sgl depends on first sgl */
    gSSgl = ecalloc(msSglCnt,sizeof(*gSSgl));
    /* sSglCnt: #sgls */
    double d1=omp_get_wtime();
    sSglCnt = re_shingle(gFSgl, fSglCnt, gSSgl, msSglCnt);
    printf("Second level shingling succeed...\n");
    double d2=omp_get_wtime();
    printf("Shingling time =%lf\n",d2-d1 );
    /* gFSgl is sorted in re_shingle() */
    //#pragma omp parallel for schedule(dynamic,500) num_threads(2) ////////////////////////********************//////////////////////
    for(i=0; i<sSglCnt; i++)
    {
        //printf("threads = %d\n",omp_get_num_procs());
        res = bsearch(&gSSgl[i], gFSgl, fSglCnt, sizeof *gFSgl, node_val_cmp);
        //#pragma omp critical
          list_union(uSet, res->vids, gS, gSSgl[i].vids, gS);
    }
    /* dump clusters */
    singleton = gS;
    disp_all_clusters(uSet, gNN, &singleton, ".");
    printf("Dumping clusters succeed...\n");
    double t2=omp_get_wtime();
    printf("\nTime taken for program Execution = %lf\n",(t2-t1));
    free_vars();
    temp=remove("input.txt");
    printf("\nGraphs Loaded..\n");
    //loadOP2(1,argv);
    loadOP3(1,argv);
    /*LOOP:printf("\n1. Load/Save ClusterNumber v/s ClusterSize Graph\n2. Load/Save Cluster Density Graph\n3. Upload output files to cloud\n4. Exit\n" );
    scanf("%d",&temp);
    if(temp==1)
    {
        loadOP1(1,argv);
    }
    else if(temp==2)
    {
        loadOP2(1,argv);
    }
    //loadOP2(1,argv);
    //loadOP1(1,argv);
    goto LOOP;*/
    temp=remove("vertexCustomClustSize");
    temp=remove("vertexDensity.SGL");
    return EXIT_SUCCESS;
}

void init_vars(void)
{
  uSet = init_union(gN);
  #pragma omp parallel
  {
      #pragma omp sections
      {
          #pragma omp section
          {
              vidmap = emalloc(gN*(sizeof *vidmap));
              gA = emalloc(gC*(sizeof *gA));
              gB = emalloc(gC*(sizeof *gB));
              //printf("Thread num %d\n",omp_get_thread_num() );
          }
          #pragma omp section
          {
              mfSglCnt = gN*gC;
              gFSgl = ecalloc(mfSglCnt, sizeof *gFSgl);
              n2gidHash = ecalloc(gN, sizeof(*n2gidHash));
              //printf("Thread num %d\n",omp_get_thread_num() );
          }
      }
    }
    /*
    uSet = init_union(gN);
    vidmap = emalloc(gN*(sizeof *vidmap));
    gA = emalloc(gC*(sizeof *gA));
    gB = emalloc(gC*(sizeof *gB));
    mfSglCnt = gN*gC;
    gFSgl = ecalloc(mfSglCnt, sizeof *gFSgl);
    n2gidHash = ecalloc(gN, sizeof(*n2gidHash));*/
}

void free_vars(void)
{
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                free(vidmap);
                free(gA);
                free(gB);
                free_union(uSet);
            }
            #pragma omp section
            {
                free_sgl(gFSgl, fSglCnt);
                free_sgl(gSSgl, msSglCnt);
                free_hash();
                free_gid_hash(n2gidHash, gNN);
            }
        }
    }
    /* free resource
    free(vidmap);
    free(gA);
    free(gB);
    free_union(uSet);
    free_sgl(gFSgl, fSglCnt);
    free_sgl(gSSgl, msSglCnt);
    free_hash();
    free_gid_hash(n2gidHash, gNN);
    */
}/*
void loadGUI()
{
    FILE *fp;
    printf("Inside c program\n");
    Py_SetProgramName("GUI");
    Py_Initialize();
    PySys_SetArgv(1, "GUI");
    fp = fopen("gui.py","r");
    PyRun_SimpleFile(fp, "gui.py");
    Py_Finalize();
}
*/
/*
int options_check(int argc, char **argv)
{
	int option;
	int cnt = 0;

  while(-1 != (option = getopt(argc, argv, "f:n:s:c:")))
  {
      switch (option)
      {

  		    case '?':
                  printf("Usage : %s -f {adjlist} -n {#vertice} -s {} -c {}\n", argv[0]);
  			    exit(-1);
  		    case 'f':
  			    strncpy(gAdjFile, optarg, MAX_NAME_LEN);
  			    cnt++;
  			    break;
  		    case 'n':
  			    gN = atoi(optarg);
  			    cnt++;
  			    break;
  		    case 's':
                  gS = atoi(optarg);
  			    cnt++;
  			    break;
  		    case 'c':
                  gC = atoi(optarg);
  			    cnt++;
  			    break;
  		}
	}
	return cnt;
}
*/
