#ifndef SEARCH_H_
#define SEARCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "type.h"
#include "lib.h"

int partition(ulong *arr, int p, int r);
int rand_partition(ulong *arr, int p, int r);
ulong rand_select(ulong *arr, int p, int r, int i);

#endif /*SEARCH_H_*/
