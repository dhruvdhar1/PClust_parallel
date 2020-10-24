#include "search.h"

/*----------------------------------------------*
 * use the last elem in the passed array as the
 * pivot, and partition the array into two parts
 * NOTE: the passed array is modified
 *
 * || <=x || > x || unresticted || x ||
 *----------------------------------------------*/
int partition(ulong *arr, int p, int r){
    ulong x;
    int i,j;
    
    x = arr[r];
    i = p-1;    
    for(j=p; j<r; j++){
        if(arr[j]<=x)
            swap_ulong(&arr[++i], &arr[j]);
    } 
    
    swap_ulong(&arr[++i], &arr[r]);
    return i;
}

/*----------------------------------------------*
 * random pick up a pivot, and swap it with the 
 * last elem in the array, then a normal partition
 * algoithm for quick sort is called after
 *----------------------------------------------*/
int rand_partition(ulong *arr, int p, int r){
    int i;

    srand((int)time(NULL));
    /* i = p + range * fraction */ 
    i = p + (int)((r-p+1)*(rand()/(RAND_MAX+1.0)));
    
    swap_ulong(&arr[i], &arr[r]);
    return partition(arr, p, r);
}
 
/*----------------------------------------------*
 * select the ith elem. After rand_select(), 
 * the orignal input array is modified, 
 * and the elems before ith elem should be all
 * less than the ith elem 
 *----------------------------------------------*/
ulong rand_select(ulong *arr, int p, int r, int i){
    int k;
    int q;

    if(p == r) 
        return arr[p]; 

    q = rand_partition(arr, p, r);
    k = q-p+1; /* the rank of q elem */
        
    if(k == i) 
        return arr[q];
    else if(i < k) 
        return rand_select(arr, p, q-1, i);
    else 
        return rand_select(arr, q+1, r, i-k); 
}

