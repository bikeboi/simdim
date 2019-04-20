#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "alloc.h"

#define MAX_DM_COUNT 7
#define WINDOW_MANS_FILE "window-mans"

typedef struct {
  char *name;
  char *path;
} DM;

int read_into_dms(FILE *f, DM **dms);
void show_dms(DM **dms, int n);

char* get_conf_home() {
  char *conf = getenv("XDG_CONFIG_HOME");
	if(!conf) {
		char *home = getenv("HOME");
		printf("Can't find $XDG_CONFIG_HOME, home is %s\n", home);
		//
		conf = malloc (
                   // /home/xyz + / +         .config   + \0
                   strlen(home) + 1 + strlen(".config") + 1);
		sprintf(conf, "%s/%s%c", home, ".config", 0);
	}
  return conf;
}

char* get_conf_path(char* buffer) {
  char* conf = get_conf_home();
  char rc_path[ strlen(conf) + 1 + strlen(WINDOW_MANS_FILE) + 1 ];
	sprintf(rc_path, "%s/%s%c", conf, WINDOW_MANS_FILE, 0);

	printf("dman runconf path: %s\n", rc_path);
}

int main() {
  char* home = get_conf_home();
  printf("%s",home);

  Alloc* ally = new_alloc();

  char* four_bytes = alloc(4,ally);

  printf("%s",four_bytes);
  /*
	FILE *file = fopen(rc_path, "r");
	DM *dms = malloc(sizeof(DM) * MAX_DM_COUNT);
	if (file == NULL || dms == NULL) {
		printf("RIP");
	} else {
		int num_read = read_into_dms(file, &dms);
		printf("Read %i entries\n", num_read);
		show_dms(&dms,num_read);
	}
	//
	free(dms);
  */

  // UGHH
  free(home);

	return 0;
}

int read_into_dms(FILE *f, DM **dms) {
	size_t counted = 0;
	size_t read = 0;
	char *line;
	while((read=getline(&line, &read, f)) != -1) {
		size_t i, linelen = strlen(line);
		for(i=0; i < linelen && isspace(line[i]); i++) {}
		int notempty = linelen - i > 0;
		if(notempty) {
			sscanf(line, " %m[^:]: %ms ", &dms[counted]->name, &dms[counted]->path);
			printf("Read %lu (%zu) :: Name = <%s>, Path = <%s>\n",
					read, counted, (dms[counted])->name, (dms[counted])->path);

			counted++;
		}
	}
	printf("Found %zu display-manager entries\n", counted);
	return counted;
}

void show_dms(DM **dms, int n) {
  int i;
  printf("--\n");
  for(i = 0; i < n; ++i) {
    printf("Read %i :: Name = %s, Path = %s\n", i, dms[i]->name, dms[i]->path);
    printf("%s\n", (dms[i])->path);
  }
}
