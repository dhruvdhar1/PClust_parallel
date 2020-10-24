#include "elib.h"

static char *name = NULL; /* program name */

char *estrdup(char *s){
    char *t;

    t = malloc(strlen(s)+1);
    if(t == NULL)
        eprintf("estrdup(\"%.20s\") failed:", s);

    strcpy(t, s);
    return t;
}

void eprintf(char *fmt, ...){

    va_list args;
    fflush(stdout);

    if(prog_name() != NULL)
        fprintf(stderr, "%s: ", prog_name());

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if(fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
        fprintf(stderr, " %s", strerror(errno));
    fprintf(stderr, "\n");

    exit(EXIT_FAILURE);
}

void *emalloc(size_t n){
    void *p;

    p = malloc(n);
    if(p == NULL)
        eprintf("malloc of %u bytes failed:", n);

    return p;
}

void *ecalloc(size_t nmemb, size_t size){
    void *p;

    p = calloc(nmemb, size);
    //printf("calloc of (%u*%u) bytes allocated:", nmemb, size);
    if(p == NULL)
        eprintf("calloc of (%u*%u) bytes failed:", nmemb, size);
    return p;
}

void *efopen(char *fileName, char *mode){
    FILE *fp;

    fp = fopen(fileName, mode);
    if(fp == NULL)
        eprintf("open file \"%.20s\" in mode \"%.20s\" failed:", fileName, mode);

    return fp;
}

void set_prog_name(char *str){
    name = estrdup(str);
}

char *prog_name(void){
    return name;
}
