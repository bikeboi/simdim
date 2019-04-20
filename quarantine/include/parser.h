// Config Parser

#include <stdlib.h>
#include <stdio.h>
#include <alloc.h>

// PAIR
typedef struct {
  char *key;
  char *val;
} Pair;

Pair* mk_pair(char* k, char* v, Alloc* ally) {
  Pair pair = { k, v };
  Pair *out = alloc(sizeof(Pair*),ally);
  out = &pair;
  return out;
}

Pair* parse_key_val(char *str, Alloc* ally) {
  char key[50], val[50];
  int parsed = sscanf(str," %[a-zA-Z] = %[a-zA-Z] ",key,val);
  if (parsed < 2) {
    printf("Could not parse key-value from: %s, Parsed: %i", str, parsed);
    return NULL;
  } else {
    return mk_pair(key,val,ally);
  }
}
