#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <stdlib.h>

typedef int pthread_mutex_t;
#define PTHREAD_MUTEX_INITIALIZER 0

#if defined(__wasm_atomics__)
static inline int pthread_mutex_lock(pthread_mutex_t* mutex) {
  while (__atomic_exchange_n(mutex, 1, __ATOMIC_ACQUIRE)) {
      __builtin_wasm_memory_atomic_wait32(mutex, 1, -1);
  }
  return 0;
}

static inline int pthread_mutex_trylock(pthread_mutex_t* mutex) {
  return __atomic_exchange_n(mutex, 1, __ATOMIC_ACQUIRE) == 0 ? 0 : 16; // EBUSY
}

static inline int pthread_mutex_unlock(pthread_mutex_t* mutex) {
  __atomic_store_n(mutex, 0, __ATOMIC_RELEASE);
  __builtin_wasm_memory_atomic_notify(mutex, 1);
  return 0;
}
#else
static inline int pthread_mutex_lock(pthread_mutex_t* mutex) { return 0; }
static inline int pthread_mutex_trylock(pthread_mutex_t* mutex) { return 0; }
static inline int pthread_mutex_unlock(pthread_mutex_t* mutex) { return 0; }
#endif

static inline int pthread_mutex_init(pthread_mutex_t* mutex, const void* attr) { return 0; }
static inline int pthread_mutex_destroy(pthread_mutex_t* mutex) { return 0; }

typedef int pthread_key_t;

static inline int pthread_key_create(pthread_key_t* key, void (*destructor)(void*)) {
    *key = 0;
    return 0;
}

static inline int pthread_setspecific(pthread_key_t key, const void* value) {
    return 0;
}

static inline void* pthread_getspecific(pthread_key_t key) {
    return NULL;
}

#endif
