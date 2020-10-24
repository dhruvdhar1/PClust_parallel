#ifndef TYPE_H_
#define TYPE_H_

typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct sgl{
    ulong node;
    ulong sVal;
    int *vids;
}SGL;

typedef struct node{
    int vid;
    int degree; // is the key
}NODE;

enum{FALSE, TRUE};
enum{NO, YES};

enum{PRUNED=-1, ADJ_END =-2};

#endif /* end of TYPE_H_ */

