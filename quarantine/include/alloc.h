#pragma once

#include <stdlib.h>

#define MEM_SIZE 100000 // 100 Kb

// RUDIMENTARY ALLOCATOR
// (It's just a reference counter ayyy)

typedef struct {
  void** mem;
  size_t offset;
} Alloc;

Alloc *new_alloc() {
  Alloc* ally = malloc(sizeof(Alloc));
  ally->mem = malloc(sizeof(char*) * MEM_SIZE);
  ally->offset = 0;
  return ally;
}

void *alloc(size_t size, Alloc* ally) {
  if (ally->offset + size > MEM_SIZE) {
    printf("WARNING: Allocator maximum capacity reached. Gibbe more space bo$$");
    exit(1);
  }
  char* out = *(ally->mem + ally->offset);
  ally->offset += size;
  out = malloc(size);
  return out;
}

void *alloc_cpy_n(char* source, size_t n, Alloc* ally) {
  void* dest = alloc(n,ally);
  memcpy(dest,source,n);
  return dest;
}


void *alloc_cpy(char* source, Alloc* ally) {
  size_t len = strlen(source);
  return alloc_cpy_n(source,len,ally);
}

void free_alloc(Alloc* ally) {
  free(ally->mem);
  free(ally);
}
