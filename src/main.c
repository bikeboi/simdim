#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "alloc.h"
#include "parser.h"

#define MAX_DM_COUNT 7
#define CONFIG_DIR "/simdim"
#define WMAN_FILE "/window-mans"

typedef struct {
  char *name;
  char *path;
} DM;

int read_into_dms(FILE *f, DM **dms);
void show_dms(DM **dms, int n);

char* get_config_dir(Alloc* ally) {
  char *xdg_conf = getenv("XDG_CONFIG_HOME");
  char *home = getenv("HOME");
  char *home_conf = home == NULL ? NULL : strcat(home, "/.config");
  char default_home[50];
  getcwd(default_home,50);

  // This should be freed when it goes out of scope hopefully
  char *found_home = xdg_conf ? xdg_conf : home_conf ? home_conf : default_home;
  return alloc_cpy(strcat(found_home,CONFIG_DIR),ally);
}

char* mk_wman_path(char* config_dir, Alloc* ally) {
  //                                                Damn you -v-  null char
  char *path = alloc(strlen(config_dir) + strlen(WMAN_FILE) + 1, ally);
  strcpy(path, config_dir);
  strcat(path, WMAN_FILE);
  return path;
}

int main() {
  Alloc* ally = new_alloc();

  char *conf_home = get_config_dir(ally);
  char *wman_filepath = mk_wman_path(conf_home, ally);

  printf("Conf home: %s\n",conf_home);
  printf("Window Man file: %s\n", wman_filepath);

  Pair* parsed = key_val("bob = steve",ally);
  if (parsed == NULL) printf("RIP");
  printf("Key: %s, Val: %s",parsed->key, parsed->val);

  // Open file and display window managers
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

  free_alloc(ally);

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
