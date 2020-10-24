#include "lib.h"

ulong large_prime(void){
    ulong randPrime = 43451ul;
    /* ulong randPrime = 108571ul; */
    return randPrime;
}


int fetch_rands(ulong *a, ulong *b, int size, ulong p){
	int i;

    /* get rid of the starting '0' case */

    lrand48();
    for(i=0; i<size; i++){
		a[i] = lrand48()%p;
    //printf("fppp %d\n",lrand48() );
	}
	for(i=0; i<size; i++){
		b[i] = lrand48()%p;
	}

	return TRUE;
}

void array_cpy(void *dest, void *src, int size, int nelems){
    int i;
    for(i=0; i<nelems; i++)
    {
        memcpy((char *)dest+i*size, (char *)src+i*size, size);
    }//printf("xx : %d\n",nelems );
}

int int_cmp(const void *vp1, const void *vp2){
    int *t1 = (int *)vp1;
    int *t2 = (int *)vp2;

    if(*t1 > *t2){
        return 1;
    }else if(*t1 == *t2){
        return 0;
    }else{
        return -1;
    }
}

int sgl_val_cmp(const void *vp1, const void *vp2){
    SGL *t1 = (SGL *)vp1;
    SGL *t2 = (SGL *)vp2;

    if(t1->sVal > t2->sVal){
        return 1;
    }else if(t1->sVal == t2->sVal){
        return 0;
    }else{
        return -1;
    }
}

int node_val_cmp(const void *vp1, const void *vp2){
    SGL *t1 = (SGL *)vp1;
    SGL *t2 = (SGL *)vp2;

    if(t1->node > t2->sVal){
        return 1;
    }else if(t1->node == t2->sVal) {
        return 0;
    }else{
        return -1;
    }
}

/* TODO better algorithm should be used */
int setize(int *outLinks, int nols){
    int pVal, cVal;
    int i, j;

    qsort(outLinks, nols, sizeof *outLinks, int_cmp);

    /* first elem will remain definitely */
    pVal = outLinks[0];
    for(i=1,j=1; i<nols; i++){
        cVal = outLinks[i];
        if(cVal != pVal){
            outLinks[j++] = cVal;
            pVal = cVal;
        }
    }

    return j;
}

/*TODO change into base */
/* int ndigits(int val, int base){  */
int ndigits(int val){
    assert(val >= 0);
    int cnt=0;

    while(val){
        cnt++;
        val /= 10;
    }
    return cnt;
}


int ndlts(char *s, char *dlt){
    int cnt=0;
    int stride;
    int ndlt = strlen(dlt);

    for(; *s; s+=stride){
        if(!strncmp(s, dlt, ndlt)){
            cnt++;
            stride = ndlt;
        }else{
            stride = 1;
        }
    }
    return cnt;
}

void swap_int(int *i1, int *i2){
    int tmp;
    tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}

void swap_node(NODE *node1, NODE *node2){
    NODE tmp;

    tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}

/* not for performance */
inline void swap(void *vp1, void *vp2, int size){
    char tmp[size];
    memcpy(tmp, vp1, size);
    memcpy(vp1, vp2, size);
    memcpy(vp2, tmp, size);
}

void swap_ulong(ulong *a, ulong *b){
    ulong tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
