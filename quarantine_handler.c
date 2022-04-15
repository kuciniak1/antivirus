#include <dirent.h>
#include <math.h>
#include <linux/limits.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cipher.h"
#include "file_handler.h"

int fileExists(char path[PATH_MAX]) {
  FILE *file = fopen(path, "r");
  if (file == NULL)
        return 0;
  fclose(file);
  return 1;
}

int get_field(char *line, int num, char buffer[PATH_MAX]) {
  const char *tok;
  char *tmp_line = malloc(strlen(line)+1);
  strcpy(tmp_line, line);
  for (tok = strtok(tmp_line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
    if (!--num){
      strcpy(buffer, tok);
      free(tmp_line);
      return(1);
    }
  }
  free(tmp_line);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("%s\n", "Usage: ./quarantine_hander <number_of_file>");
    return 0;
  }
  FILE *info_file = fopen("program_files/quarantine/info.csv", "r");
  char path_in_q[60];
  snprintf(path_in_q, 60, "%s/%s", "program_files/quarantine", argv[1]);
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, info_file)) != -1) {
    char buffer[PATH_MAX];
    get_field(line,1, buffer);
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s","program_files/quarantine",argv[1]);
    if (!strcmp(buffer, argv[1]) && fileExists(path)==1) {
      int i;
      get_field(line, 2, buffer);
      i = strtol(buffer, 0, 8);
      chmod(path_in_q, i);
      get_field(line, 3, buffer);
      decrypt_file(path_in_q, buffer);
      chmod(buffer, i);
      remove(path_in_q);
    }
  }
  
  free(line);
  fclose(info_file);
}

