#include "loadgraph.h"
#include <omp.h>
void load_graph(char *fileName, int nline, int *vidmap){
    FILE *fp=NULL;
    int maxLineLen;
    char *line;
    /*
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                fp = efopen(fileName, "r");
            }
            #pragma omp section
            {
              maxLineLen = nline*(MAX_GID_LEN+1)+1;
              line = emalloc(maxLineLen*sizeof(*line));
            }
        }
    }
    */
    fp = efopen(fileName, "r");
    maxLineLen = nline*(MAX_GID_LEN+1)+1;
    line = emalloc(maxLineLen*sizeof(*line));

    /* load two hashes */
    load_hash(fp, nline, line, maxLineLen);
    /* update global gN */
    gN = prune_graph(fp, nline, line, maxLineLen, vidmap);
    first_shingle(fp, gN, line, maxLineLen, vidmap,nline);

    free(line);
    fclose(fp);
}

void load_hash(FILE *fp, int nline, char *line, int lineLen){
    int i=0;//int j=0;
    char *header;
    //double d1=omp_get_wtime();
    //#pragma omp parallel for //shared(i) lastprivate(j)
      for(i=0;fgets(line, lineLen, fp);i++)
      {
          line[strlen(line)-1] = '\0';
          header = strtok(line, HEAD_DEL);
          //#pragma omp critical
          n2gidHash[i] = estrdup(header);
          hinsert(header, i);
          //printf("es=%d\n",i );
      }
    /*
    while(fgets(line, lineLen, fp))
    {
        line[strlen(line)-1] = '\0';

        header = strtok(line, HEAD_DEL);
        n2gidHash[i] = estrdup(header);
        hinsert(header, i);
        i++;
    }*/
    //double d2=omp_get_wtime();
    //printf("while : %lf : %d : %d\n",d2-d1,nline,j );
    assert((i) == nline);
}

int prune_graph(FILE *fp, int nline, char *line, int lineLen, int *vidmap){
    int i, j;
    int nDlts;
    int *adjList[nline];
    char *tmp;
    NODE *hp;
    NODE *min;
    int nl;

    rewind(fp);
    i = 0;
    hp = alloc_heap(nline);
    while(fgets(line, lineLen, fp))
    {
        line[strlen(line)-1] = '\0';
        nDlts = ndlts(line, LIST_DEL);
        // one more for the end delimiter '-2'
        adjList[i] = emalloc((nDlts+2)*sizeof(*adjList[i]));
        j = 0;
        strtok(line, HEAD_DEL);
        while((tmp=strtok(NULL, LIST_DEL)))
        {
            adjList[i][j++] = hsearch(tmp);
        }
        // mark the end
        adjList[i][j] = ADJ_END;
        // initialize the heap
        hp[i].vid = i;
        hp[i].degree = nDlts+1;
        i++;
    }
    assert(i == nline);

    build_min_heap(hp, nline, vidmap);
    min = heap_min(hp, nline);

    nl = nline;
    while(min && min->degree < gS)
    {
        heap_extract_min(hp, &nl, adjList, vidmap);
        min = heap_min(hp, nl);
    }
    /* free unused resource */
    free_heap(hp);
    free_adjList(adjList, nline); /* #nline != nl */
    return nl;
}

/* nl is #valid lines, and equals to updated gN */
int first_shingle(FILE *fp, int nl, char *line, int lineLen, int *vidmap,int nline)
{
    int sIndex;//int semiCount=0;
    char *header, *tmp , line2[lineLen];
    int vertexId, olId;
    int outLinks[nl];
    int olCnt=0;
    int i=0;
    rewind(fp);
    sIndex = 0;
    //while(fgets(line, lineLen, fp))
    for(i=0;i<nline;i++)
    {
        line=fgets(line, lineLen, fp);
        line[strlen(line)-1] = '\0';
        strcpy(line2,line);

        header = strtok(line, HEAD_DEL);
        vertexId = hsearch(header);
        /* vertex has been deleted */
        if(vidmap[vertexId] == PRUNED)
        {
          continue;
        }

        else
        {
            /*for(j=0;j<strlen(line2);j++)
            {
                if(line2[j]==';')
                {
                  semiCount++;
                }
            }*/
            olCnt = 0;
            outLinks[olCnt++] = vertexId;
              //for(j=0;j<semiCount+1;j++)
              while((tmp = strtok(NULL, LIST_DEL)))
              {
                  //tmp = strtok(NULL, LIST_DEL);
                  olId = hsearch(tmp);
                  if(vidmap[olId] == PRUNED)
                  {
                      continue;
                  }
                  else
                  {
                      outLinks[olCnt++] = olId;
                  }
              }
            //semiCount=0;
            assert(olCnt <= nl);
            shingle(vertexId, outLinks, olCnt, gFSgl, &sIndex);
        }

    }
    assert(sIndex == nl*gC);
    return sIndex;
}

void free_gid_hash(char **n2gidHash, int size)
{
    int i;
    //#pragma omp parallel for schedule(dynamic,1200) num_threads(2)
      for(i=0; i<size; i++)
      {
          free(n2gidHash[i]);
      }
    free(n2gidHash);
}

/* sysmetric to malloc() in loadadj() */
void free_adjList(int *adjList[], int size)
{
    int i;
    //#pragma omp parallel for schedule(dynamic,1200) num_threads(2)
      for(i=0; i<size; i++)
      {
          free(adjList[i]);
      }
}
