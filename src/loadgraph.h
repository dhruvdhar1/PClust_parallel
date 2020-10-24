#ifndef LOAD_GRAPH_H_
#define LOAD_GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "type.h"
#include "hashtbl.h"
#include "shingle.h"
#include "heap.h"
#include "elib.h"

/* syntax: #define name (var name) arbitrary text */
#define HEAD_DEL ":"
#define LIST_DEL ";"
#define MAX_GID_LEN 40


extern char **n2gidHash;
extern SGL *gFSgl;
extern int gN;
extern int gC;
extern int gS;

void load_graph(char *fileName, int nline, int *vidmap);
void free_gid_hash(char **n2gidHash, int size);
void free_adjList(int *adjList[], int size);

void load_hash(FILE *fp, int nline, char *line, int lineLen);
int prune_graph(FILE *fp, int nline, char *line, int lineLen, int *vidmap);
int first_shingle(FILE *fp, int nl, char *line, int lineLen, int *vidmap,int nline);
#endif /* end of load_graph.h */
