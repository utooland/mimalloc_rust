#ifndef _UNISTD_H
#define _UNISTD_H

#include <stddef.h>
#include <stdint.h>

static void* sbrk(intptr_t increment) {
  // Ensure we never return address 0 (NULL) as it is treated as failure
  if (__builtin_wasm_memory_size(0) == 0) {
      if (__builtin_wasm_memory_grow(0, 1) == (size_t)-1) {
          return (void*)-1;
      }
  }

  if (increment == 0) {
      return (void*)(__builtin_wasm_memory_size(0) * 65536);
  }
  if (increment < 0) return (void*)-1;
  
  size_t pages = (increment + 65535) / 65536;
  size_t old_pages = __builtin_wasm_memory_grow(0, pages);
  if (old_pages == (size_t)-1) {
      return (void*)-1;
  }
  return (void*)(old_pages * 65536);
}

static inline unsigned int sleep(unsigned int seconds) {
    return 0;
}

#endif
