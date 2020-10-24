#ifndef HASH_TBL_H_
#define HASH_TBL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "type.h"
#include "elib.h"

#define HASH_SIZE 50000

struct nlist{
    struct nlist *next;
    char *key;
    int val;
};

uint hash(char *str);
int hsearch(char *str);
void hinsert(char *str, int val);
void free_hash();
#endif /* end of hashtbl.h */
