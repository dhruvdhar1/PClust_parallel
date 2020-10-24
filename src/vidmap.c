#include "vidmap.h"
#include<stdio.h>
#include<omp.h>
/*----------------------------------------------------*
 * vidmap is used to track vertex's id in heap (array),
 * o/w a search of the heap is required.
 * NOTE: any time two nodes in the heap are swaped,
 *       these position in vidmap should be updated
 *----------------------------------------------------*/
void init_vidmap(int *vidmap, int nvidmap)
{
    int i;
    #pragma omp parallel for schedule(dynamic,200)
        for(i=0; i<nvidmap; i++)
        {
            vidmap[i] = i;
            //printf("vidmap [i]=%d\n",vidmap[i] );
        }
}
