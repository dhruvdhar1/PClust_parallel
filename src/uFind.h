#ifndef UFIND_H_
#define UFIND_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "elib.h"

struct ufind {
  int parent;
  int rank;
};

struct link {
  int id;
  struct link *next;
};

struct clusters {
  int count;
  char singleton;      /* 1 if singleton 0 if no */
  struct link *head;
};

extern char **n2gidHash; /* i -> gid */

struct ufind *init_union(int size);
void free_union(struct ufind *uf);
 int find(struct ufind *ufSet,int elemIndex);
 void	union_elems(struct ufind *ufSet,int elem1,int elem2);
 void	merge_elems(struct ufind *ufSet,int elem1,int elem2);

void disp(struct ufind *ufSet,int size);
int disp_all_clusters(struct ufind *uf, int size, int *singletons, char *dir);
void list_union(struct ufind *ufset, int *list1, int nlist1, int *list2, int nlist2);

#endif /* end of uFind.h */
