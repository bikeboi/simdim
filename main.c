#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAX_DM_COUNT 7

typedef struct {
  char *name;
  char *path;
} DM;

int read_into_dms(FILE *f, DM **dms);
void show_dms(DM **dms, int n);

const char *rc_file = "dmanrc";

int main() {
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
	printf("Config home: %s\n", conf);

	char rc_path[ strlen(conf) + 1 + strlen(rc_file) + 1 ];
	sprintf(rc_path, "%s/%s%c", conf, rc_file, 0);

	printf("dman runconf path: %s\n", rc_path);

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
