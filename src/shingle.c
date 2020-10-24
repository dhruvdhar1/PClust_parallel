#include "shingle.h"
#include <omp.h>
/* outLinks include the header node itself */
void shingle(ulong node, int *ols, int nols, SGL *sgl, int *sIndex){
    ulong x[nols], y[nols], z[nols];
    int i, j, k;
    char *gid;
    int *vids;
    ulong sthElem;
    ulong p, q, s, t; /* tmp vars */
    int ndts = ndigits(gN);
    char catVids[(ndts+1)*gS+1];
    char tmpStr[ndts+2];
    //#pragma omp parallel for schedule(dynamic,10)
      for(i=0; i<nols; i++){
          gid = n2gidHash[ols[i]];
          x[i] = DEK_hash(gid, strlen(gid), 0);
      }
    //printf("xx : %d\n",nols );
    //#pragma omp parallel for schedule(dynamic,100)
    for(i=0; i<gC; i++)
    {
          for(j=0; j<nols; j++)
          {
              p = gA[i]%gLgPrime;
              q = x[j]%gLgPrime;
              assert(ULONG_MAX/p > q);

              s = (p*q)%gLgPrime;
              t = gB[i]%gLgPrime;
              assert(ULONG_MAX-s > t);

              y[j] = (s+t)%gLgPrime;
          }

          sgl[*sIndex].node = node;
          /* alloc mem for gS vids */
          vids = ecalloc(gS, sizeof *vids);
          sgl[*sIndex].vids = vids;
          array_cpy(z, y, sizeof(z[0]), nols);
          sthElem = rand_select(z, 0, nols-1, gS);
          /* all elems in y is diff
           * TODO how to check duplicated entries efficiently? */
          for(j=0, k=0; j<nols; j++)
          {
              if(y[j] <= sthElem && k < gS)
              {
                  sgl[*sIndex].vids[k++] = ols[j];
              }
          }
          assert(k == gS);
          //sgl[*sIndex].sVal = 0;
          /* sort the vids[] to make min*max(RADIX) to avoid overflow*/
          /* TODO better way to compute SGL val? */
          qsort(sgl[*sIndex].vids, gS, sizeof(*vids), int_cmp);
          catVids[0] = '\0';
          for(j=0; j<gS; j++)
          {
              //sgl[*sIndex].sVal += ((ulong)pow(RADIX_BASE, gS-1-j)*sgl[*sIndex].vids[j]);
              //assert(sgl[*sIndex].sVal < ULONG_MAX);
              sprintf(tmpStr, "%d#", sgl[*sIndex].vids[j]);
              strncat(catVids, tmpStr, ndts+1);
          }

          sgl[*sIndex].sVal = DEK_hash(catVids, strlen(catVids), 0);

          (*sIndex)++;
    }
}

void print_sgl(SGL *sgl, int nsgl){
	int i,k;
	printf(" -----starting to print SHGL-------\n");
	for(i = 0; i< nsgl; i++){
		printf("sNode: %ld, sVal: %ld -- [", sgl[i].node, sgl[i].sVal);
		for(k=0; k <gS; k++)
    {
			printf("%d, ", sgl[i].vids[k]);
		}
		printf("]\n");
	}
}

int re_shingle(SGL *sgl, int nsgl, SGL *newSgl, int nnewSgl){
    int i;
    int olCnt, uCnt; /* uCnt: set size */
    int sIndex;
    ulong pVal, cVal;
    int outLinks[gN*gC];
    qsort(sgl, nsgl, sizeof(*sgl), sgl_val_cmp);


    /* TODO: shingle val can never be '0'
     * NOTE: starts from the 0th elem,
     *       no start val is required */
    pVal = 0;
    olCnt = 0;
    sIndex = 0;
    //int num=0;
    //double d1=omp_get_wtime();
    //#pragma omp parallel for //firstprivate(gS) private(i) shared(olCnt,outLinks)
    for(i=0; i<nsgl; i++)
    {
        cVal = sgl[i].sVal;
        if(cVal != pVal)
        {
            if(olCnt >= gS)
            {
                // unique outlinks >= gS

                uCnt = setize(outLinks, olCnt);
                if(uCnt >= gS)
                {
                    shingle(pVal, outLinks, uCnt, newSgl, &sIndex);
                }
            }
            olCnt = 0;
            outLinks[olCnt++] = sgl[i].node;
            pVal = cVal;
        }
        else
        {
            //printf("cnt : %d\n",num++ );
            outLinks[olCnt++] = sgl[i].node;
        }
    }
    //double d2=omp_get_wtime();
    //printf("Shin : %lf : %d\n",d2-d1,nsgl );

    /* handling last case */
    if(olCnt >= gS){
        /* unique outlinks >= gS */
        uCnt = setize(outLinks, olCnt);
        if(uCnt >= gS){
            shingle(pVal, outLinks, uCnt, newSgl, &sIndex);
        }
    }
    assert(sIndex <= nnewSgl);

    return sIndex;

}

void free_sgl(SGL *sgl, int nsgl){
    int i;
    #pragma omp parallel for schedule(dynamic,1000) num_threads(2)
      for(i=0; i<nsgl; i++)
      {
          free(sgl[i].vids);
      }
    free(sgl);
}
