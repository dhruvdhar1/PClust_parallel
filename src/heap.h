#ifndef HEAP_H_
#define HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "type.h"
#include "lib.h"
#include "elib.h"

NODE *alloc_heap(int nhp);
void free_heap(NODE *hp);

int parent(int i);
int left(int i);
int right(int i);

void build_min_heap(NODE *hp, int nhp, int *vidmap);
void min_heapify(NODE *hp, int nhp, int i, int *vidmap);
NODE *heap_min(NODE *hp, int nhp);
void heap_extract_min(NODE *hp, int *nhp, int *adjList[], int *vidmap);
void heap_decrease_key(NODE *hp, int nhp, int i, int key, int *vidmap);

void print_heap(NODE *hp, int nhp);
void print_vidmap(int *vidmap, int nvidmap);
void print_heap_vertex(NODE *hp, int nhp);
#endif /* HEAP_H_ */

