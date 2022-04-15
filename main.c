#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "file_handler.h"
#include "hashDB_handler.h"
#include "hashing.h"
#include "queue.h"
#include "tree.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("%s\n", "Usage: ./antivirus <file_name> <virus_DB>");
    return 0;
  } else if (argc < 3 && strcmp(argv[1], "man")) {
    printf("%s\n", "Usage: ./antivirus <file_name> <virus_DB>");
    return 0;
  } else if (!strcmp(argv[1], "man")) {
    // TODO: instruction
    printf("%s\n", "Instruction");
    return 0;
  } else if (argc > 3) {
    printf("%s\n", "Usage: ./antivirus <file_name> <virus_DB>");
    return 0;
  }
  
  DIR* dir = opendir("mydir");
  if (dir) {
    closedir(dir);
  } else if (ENOENT == errno) {
    mkdir("program_files", 0777);
    mkdir("program_files/quarantine", 0777);
  }
  int files_in_quarantine = 0;
  tree_node *root = NULL;
  queue *dir_queue = NULL;
  queue *file_queue = NULL;

  if (DB_init(argv[2], &root) == -1) {
    char *message = "[ERROR] Database cannot be opened.\n";
    char *end = "=============================================\n";
    log_pointer(message);
    log_pointer(end);
    return 0;
  }
  char *message = "[INFO] Database opened.\n";
  log_pointer(message);
  dir_queue = init(dir_queue);
  file_queue = init(file_queue);

  struct stat *st;
  st = (struct stat *)malloc(sizeof(struct stat));
  stat(argv[1], st);

  if (!st->st_mode) {
    char buffer[5000];
    snprintf(buffer, sizeof buffer, "%s%s\n", "[ERROR] File cannot be opened - ", argv[1]);
    char *end = "=============================================\n";
    log_table(buffer);
    log_pointer(end);
    delete_tree(root);
    free(dir_queue);
    free(file_queue);
    free(st);
    return 0;
  }

  if (S_ISDIR(st->st_mode)) {
    directory_scan(argv[1], dir_queue, file_queue, root, &files_in_quarantine);
  } else if (S_ISREG(st->st_mode)) {
    char path_buffer[PATH_MAX];
    realpath(argv[1], path_buffer);
    file_scan(path_buffer, root, &files_in_quarantine);
    remove(argv[1]);
  } else if (S_ISLNK(st->st_mode)) {
    struct stat *link_st;
    link_st = (struct stat *)malloc(sizeof(struct stat));
    char link_buff[PATH_MAX];
    memset(link_buff, 0, PATH_MAX);
    readlink(argv[1], link_buff, PATH_MAX);
    stat(link_buff, link_st);
    if (S_ISDIR(link_st->st_mode)) {
      directory_scan(link_buff, dir_queue, file_queue, root,
                     &files_in_quarantine);
    } else if (S_ISREG(link_st->st_mode)) {
      file_scan(link_buff, root, &files_in_quarantine);
    }
    free(link_st);
  }

  char buffer[5000];
  snprintf(buffer,sizeof buffer, "%s%d\n", "[INFO] Suspicious files - ", files_in_quarantine);
  log_table(buffer);
  
  char *success = "[INFO] Program ended with succes.\n";
  log_pointer(success);
    
    
  char *end = "=============================================\n";
  log_pointer(end);
    
    
  free(st);
  delete_tree(root);
  free(dir_queue);
  free(file_queue);
}

