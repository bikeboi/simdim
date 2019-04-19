#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DM_COUNT 7

typedef struct {
  char* name;
  char* path;
} DM;

int read_into_dms(FILE* f, DM* dms);
void show_dms(DM* dms, int n);

int main() {
  FILE *file = fopen("/home/bikeboi/.config/dman/display-managers.txt", "r");
  DM *dms = malloc(sizeof(DM*) * MAX_DM_COUNT);
  if (file == NULL || dms == NULL) {
    printf("RIP");
  } else {
      int num_read = read_into_dms(file,dms);
      show_dms(dms,num_read);
  }
  //
  free(dms);
  return 0;
}

int read_into_dms(FILE* f, DM* dms) {
  int i;
  for(i = 0; !feof(f) && i < MAX_DM_COUNT; ++i) {
    // Will these get deallocated out of scope? Please no
    char name[100];
    char path[100];

    fscanf(f," %s : %s ",name,path);

    (dms+i)->name = name;
    (dms+i)->path = path;

    printf("Read %i :: Name = %s, Path = %s\n", i, (dms+i)->name, (dms+i)->path);
  }
  printf("Found %i display-manager entries\n", i);
  return i;
}

void show_dms(DM* dms, int n) {
  int i;
  printf("--\n");
  for(i = 0; i < n; ++i) {
    printf("Read %i :: Name = %s, Path = %s\n", i, (dms+i)->name, (dms+i)->path);
    printf("%s", (dms+i)->path);
  }
}
