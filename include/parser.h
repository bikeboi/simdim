// Config Parser

#include <stdlib.h>
#include <stdio.h>
#include <alloc.h>

typedef struct {
  char *key;
  char *val;
} Pair;

Pair* mk_pair(char* k, char* v, Alloc* ally) {
  Pair pair = { k, v };
  Pair *out = alloc(sizeof(pair),ally);
  out = &pair;
  return out;
}

Pair* key_val(char *str, Alloc* ally) {
  char key[50];
  char val[50];
  int parsed = sscanf(str," %[a-zA-Z] = %[a-zA-Z] ",key,val);
  if (parsed < 2) {
    printf("Could not parse key-value from: %s, Parsed: %i", str, parsed);
    return mk_pair(key,val,ally);
  } else {
    printf("Parsed key-value: %s %s", key,val);
    return NULL;
  }
}
