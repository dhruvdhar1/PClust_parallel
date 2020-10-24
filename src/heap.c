#include "heap.h"

NODE *alloc_heap(int nhp){
    NODE *hp;

    hp = ecalloc(nhp, sizeof *hp);

    return hp;
}

/* symmetric to init_heap */
void free_heap(NODE *hp)
{
    free(hp);
}

void min_heapify(NODE *hp, int nhp, int i, int *vidmap){
    assert(i >= 0);
    int min;
    int lt = left(i);
    int rt = right(i);

    /* if lt>nhp, hp[lt] will not be checked, and it is invilid, too */
    if(lt<nhp && hp[lt].degree<hp[i].degree) min = lt;
    else min = i;

    if(rt<nhp && hp[rt].degree<hp[min].degree) min = rt;

    if(min != i) {
        swap_int(&(vidmap[hp[i].vid]), &(vidmap[hp[min].vid]));
        swap_node(&hp[i], &hp[min]);
        min_heapify(hp, nhp, min, vidmap);
    }
}

/* NOTE: vidmap starts from index 1 */
void build_min_heap(NODE *hp, int nhp, int *vidmap)
{
    assert(nhp >= 2);
    int i;
    for(i=(nhp-2)/2; i>=0; i--)
    {
        min_heapify(hp, nhp, i, vidmap);
    }
}

void print_heap(NODE *hp, int nhp){
    assert(hp != NULL);
    int i;

    printf("==== printing heap ====\n");
    for(i=0; i<nhp; i++){
        printf("[%d,%d]\n", hp[i].vid, hp[i].degree);
    }
}

void print_heap_vertex(NODE *hp, int nhp){
    assert(hp != NULL);
    int i;

    for(i=0; i<nhp; i++)
    {
        printf("vertex:%d\n", hp[i].vid);
    }
}

void print_vidmap(int *vidmap, int nvidmap){
    int i;

    printf("=== printing vidmap ===\n");
    for(i=0; i<nvidmap; i++)
    {
        printf("vidmap[%d]=%d\n", i, vidmap[i]);
    }
}

/* return the ptr to the min elem */
NODE *heap_min(NODE *hp, int nhp)
{
    if(!hp) return NULL;
    return &(hp[0]);
}

/*----------------------------------------------------*
 * this ops will modify the heap, the extracted elem is
 * filled by the last elem in the heap. Heap size is
 * modified, too
 *----------------------------------------------------*/
void heap_extract_min(NODE *hp, int *nhp, int *adjlist[], int *vidmap){
    assert(*nhp > 0);
    NODE min;
    int *head;
    int i, degree;
    int index;

    min = hp[0];
    /* update vidmap, becz node swap */
    swap_int(&(vidmap[hp[0].vid]), &(vidmap[hp[*nhp-1].vid]));
    hp[0] = hp[*nhp-1];
    *nhp = *nhp-1;
    min_heapify(hp, *nhp, 0, vidmap);

    /* adjlist starts from 0 */
    head = adjlist[min.vid];

    /* mark it as invalid, means it has been deleted */
    vidmap[min.vid] = PRUNED;
    degree = min.degree;

    for(i=0; head[i]!=ADJ_END; i++)
    {
        index = vidmap[head[i]];
        if(index != PRUNED) heap_decrease_key(hp, *nhp, index, hp[index].degree-1, vidmap);
    }
}

/* decrease the key of hp[i] into key */
void heap_decrease_key(NODE *hp, int nhp, int i, int key, int *vidmap)
{
    assert(key < hp[i].degree);
    hp[i].degree = key;

    while(i>0 && hp[parent(i)].degree > hp[i].degree)
    {
        swap_int(&(vidmap[hp[i].vid]), &(vidmap[hp[parent(i)].vid]));
        swap_node(&hp[i], &hp[parent(i)]);
        i = parent(i);
    }
}

/* parent index */
int parent(int i){
    assert(i>=0);
    if(i == 0) return 0;
    return (i-1)/2;
}

/* left child index */
int left(int i){
    assert(i>=0);
    return (2*i+1);
}

/* right child index */
int right(int i){
    assert(i>=0);
    return (2*i+2);
}
