#ifndef E_LIB_H_
#define E_LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>


void eprintf(char *fmt, ...);

char *estrdup(char *s);
void *emalloc(size_t n);
void *ecalloc(size_t nmemb, size_t size);
void *efopen(char *fileName, char *mode);

void set_prog_name(char *str);
char *prog_name(void);

#endif /* end of elib.h */
