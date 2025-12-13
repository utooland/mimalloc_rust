#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>

typedef struct FILE FILE;

#define stdout ((FILE*)1)
#define stderr ((FILE*)2)

static inline int fputs(const char* s, FILE* stream) {
    return 0;
}

static inline int fprintf(FILE* stream, const char* format, ...) {
    return 0;
}

#endif
