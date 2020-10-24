#include "hashtbl.h"
#include<omp.h>
/* all static vars are initilized into 0 */
static struct nlist *hashTbl[HASH_SIZE];

uint hash(char *str)
{
    uint hashVal;
    for(hashVal=0; *str; str++)
    {
        hashVal = *str + 31*hashVal;
    }
    return hashVal%HASH_SIZE;
}

int hsearch(char *str)
{
    int index;
    struct nlist *p;
    index = hash(str);
    for(p=hashTbl[index]; p!=NULL; p=p->next)
    {
        if(!strcmp(str, p->key))
            return p->val;
    }
    perror("no hash exist!\n");
    exit(EXIT_FAILURE);
}

/* all keys are unique, so NO need to check
 * duplicate when hashed in */
void hinsert(char *str, int val)
{
    int index;
    struct nlist *nelem;

    /* do not use struct nlist nelem to alloc
     * mem, becz this mem requires to be seen
     * outsize of this function */
    nelem = emalloc(sizeof *nelem);
    index = hash(str);
    nelem->next = hashTbl[index];
    nelem->key = estrdup(str);
    nelem->val = val;

    hashTbl[index] = nelem;
}

void free_hash(){
    int i;
    struct nlist *p, *q;
    //double d1=omp_get_wtime();
    #pragma omp parallel for schedule(dynamic,500) num_threads(4)
      for(i=0; i<HASH_SIZE; i++)
      {
          if(hashTbl[i])
          {
              for(p=hashTbl[i]; p!=NULL; p=q)
              {
                  q = p->next;
                  free(p->key);
                  free(p);
              }
          }
      }
      //double d2=omp_get_wtime();
      //printf("TTT : %lf\n",d2-d1 );
}
