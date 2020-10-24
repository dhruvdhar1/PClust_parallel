#ifndef LIB_H_
#define LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "type.h"
#include "shingle.h"
#include "uFind.h"
#include "heap.h"

ulong large_prime(void);
int fetch_rands(ulong *a, ulong *b, int size, ulong p);
void array_cpy(void *dest, void *src, int size, int nelems);
int int_cmp(const void *vp1, const void *vp2);
int sgl_val_cmp(const void *vp1, const void *vp2);
int node_val_cmp(const void *vp1, const void *vp2);
int setize(int *outLinks, int nols);

void swap_int(int *i1, int *i2);
void swap_ulong(ulong *a, ulong *b);
void swap_node(NODE *node1, NODE *node2);
//inline void swap(void *vp1, void *vp2, int size);

int ndigits(int val);
int ndlts(char *s, char *dlt);
#endif /* end of lib.h */
