#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "alloc.h"
#include "parser.h"

#define MAX_WM_COUNT 7
#define CONF_DIR "/simdim"
#define CONF_FILE "/simdim.conf"

typedef struct {
  char *name;
  char *exec;
} WM_Entry;

WM_Entry* mk_WM_Entry(char* name, char* exec, Alloc* ally) {
  WM_Entry wm = { name, exec };
  WM_Entry* out = alloc(sizeof(wm),ally);
  out = &wm;
  return out;
}

char* get_config_dir(Alloc* ally) {
  char *xdg_conf = getenv("XDG_CONFIG_HOME");
  char *home = getenv("HOME");
  char *home_conf = home == NULL ? NULL : strcat(home, "/.config");
  char default_home[50];
  getcwd(default_home,50);

  // This should be freed when it goes out of scope hopefully
  char *found_home = xdg_conf ? xdg_conf : home_conf ? home_conf : default_home;
  return alloc_cpy(strcat(found_home,CONF_DIR),ally);
}

char* mk_WM_path(char* config_dir, Alloc* ally) {
  //                                                Damn you -v-  null char
  char *path = alloc(strlen(config_dir) + strlen(CONF_FILE) + 1, ally);
  strcpy(path, config_dir);
  strcat(path, CONF_FILE);
  return path;
}

WM_Entry* parse_WM_Entry(char* str, Alloc* ally) {
  char name[50], exec[50];
  int parsed = sscanf(str," %[a-zA-Z_-] : %[a-zA-Z_-/0-9] ", name, exec);
  if (parsed < 2) {
    printf("Could not parse entry: %s",str);
    exit(1);
  }
  return mk_WM_Entry(name,exec,ally);
}

char** token_n(char* str, char* delim, size_t n, Alloc* ally) {
  char in_str[strlen(str)];
  sprintf(in_str,"%s",str);

  printf("Tokenizing %s\n",in_str);

  char** tokens = alloc(sizeof(char*) * n, ally);
  char* token = strtok(in_str,delim);
  size_t cnt = 0;
  while(cnt < n && token != NULL) {
    printf("Token: %s\n", token);
    *(tokens+cnt) = token;
    token = strtok(NULL,delim);
    printf("Token: %s\n", *(tokens+cnt));
    ++cnt;
  }
  return tokens;
}


WM_Entry** parse_WM_Entries(char* str, Alloc* ally) {
  WM_Entry** entries = alloc(sizeof(WM_Entry*) * MAX_WM_COUNT,ally);
  char** lines = token_n(str,"\n",MAX_WM_COUNT,ally);
  size_t cnt = 0;
  while(cnt < MAX_WM_COUNT && *(lines+cnt) != NULL) {
    printf("Thing %s\n",*(lines+cnt));
    ++cnt;
  }

  return entries;
}

int main() {
  Alloc* ally = new_alloc();

  char feed[] = "xmonad: blah\nsome_other: blech";
  parse_WM_Entries(feed,ally);

  // Open file and display window manager
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
