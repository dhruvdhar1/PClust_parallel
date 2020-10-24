#ifndef STR_HASH_H_
#define STR_HASH_H_

#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "type.h"

ulong DEK_hash(char *str, int len, int offset);
ulong BP_hash(char *str, int len, int offset);
ulong BKDR_hash(char *str, int len, int offset);
ulong DJB_hash(char *str, int len, int offset);

#endif /* end of strhash.h */
