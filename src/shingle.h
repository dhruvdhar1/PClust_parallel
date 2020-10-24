#ifndef SHINGLE_H_
#define SHINGLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#include "type.h"
#include "lib.h"
#include "search.h"
#include "strhash.h"

#define RADIX_BASE 11 


extern ulong *gA;
extern ulong *gB;
extern ulong gLgPrime;
extern int gN;
extern int gC; 
extern int gS; 
extern char **n2gidHash; /* i -> gid */

void shingle(ulong node, int *ols, int nols, SGL *sgl, int *sIndex);
void print_sgl(SGL *sgl, int nsgl);
int re_shingle(SGL *sgl, int nsgl, SGL *newSgl, int nnewSgl);
void free_sgl(SGL *sgl, int nsgl);
#endif /* end of shingle.h */
