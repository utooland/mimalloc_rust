#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

static inline void abort(void) {
    __builtin_trap();
}

static inline char* getenv(const char* name) {
    return NULL;
}

static inline long strtol(const char* nptr, char** endptr, int base) {
    long result = 0;
    // Minimal implementation if needed, or just 0
    return result;
}

static inline char* realpath(const char* path, char* resolved_path) {
    return NULL;
}

#endif
