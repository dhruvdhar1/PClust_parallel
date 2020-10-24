/* The following hash function is adapted from:
 *
 * URL: http://www.partow.net/programming/hashfunctions/index.html
 * By Arash Partow - 2000
 *
 */
#include "strhash.h"

ulong DEK_hash(char *str, int len, int offset){
    assert(len > offset && offset >= 0);
    ulong hash = len;
    int i = 0;
    for(i=offset,str+=offset; i<len; str++,i++){
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }
    return hash;
} /* end of DEK hash */

ulong BP_hash(char *str, int len, int offset){
    assert(len > offset && offset >= 0);
    ulong hash = 0;
    int i = 0;

    for(i=offset,str+=offset; i<len; str++,i++){
        hash = hash << 7 ^ (*str);
    }

    return hash;
} /* end of BP hash */

ulong BKDR_hash(char *str, int len, int offset){
    assert(len > offset && offset >= 0);
    ulong seed = 31; /* 31 131 1313 13131 131313 etc.. */
    ulong hash = 0;
    int i;

    for(i=offset,str+=offset; i<len; str++,i++){
        hash = (hash * seed) + (*str);
    }

    return hash;
} /* end of BKDR hash */

ulong DJB_hash(char *str, int len, int offset){
    assert(len > offset && offset >= 0);
    ulong hash = 5381;
    int i = 0;

    for(i=offset,str+=offset; i<len; str++,i++){
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
} /* end of DJB hash */
