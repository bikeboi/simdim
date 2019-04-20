#pragma once

#include <stdlib.h>

#define MEM_SIZE 100000 // 100 Kb

// RUDIMENTARY ALLOCATOR

typedef struct {
  char** mem;
  size_t offset;
} Alloc;

Alloc *new_alloc() {
  Alloc* ally = malloc(sizeof(Alloc));
  ally->mem = malloc(sizeof(char*) * MEM_SIZE);
  ally->offset = 0;
  return ally;
}

void *alloc(size_t bytes, Alloc* ally) {
  if (ally->offset + bytes > MEM_SIZE) {
    printf("WARNING: Allocator maximum capacity reached. Memory overflow");
    exit(1);
  }
  char* out = *(ally->mem + ally->offset);
  ally->offset += bytes;
  out = malloc(sizeof(char) * bytes);
  return out;
}

void *alloc_cpy(void* source, Alloc* ally) {
  size_t len = strlen(source);
  char* dest = alloc(len,ally);
  memcpy(dest,source,len);
  return dest;
}

void free_alloc(Alloc* ally) {
  free(ally->mem);
  free(ally);
}
