#include <stddef.h>

int errno = 0;

// Weak definitions for C++ ABI support if needed, though we are compiling C.
// Sometimes destructors/constructors trigger these.
void* __dso_handle = NULL;

int __cxa_atexit(void (*destructor) (void *), void *arg, void *dso_handle) {
    return 0;
}

void __cxa_finalize(void *f) {
}
