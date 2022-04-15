#include <dirent.h>
#include <linux/limits.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "file_handler.h"
#include "hashDB_handler.h"
#include "hashing.h"
#include "quarantine.h"
#include "queue.h"
#include "tree.h"

int fileExists(char path[PATH_MAX]) {
  FILE *file = fopen(path, "r");
  if (file == NULL)
        return 0;
  fclose(file);
  return 1;
}

int directory_scan(char *file, queue *dir_queue, queue *file_queue,
                   tree_node *root, int *files_in_quarantine) {
  struct dirent *ent;
  DIR *dir;
  if ((dir = opendir(file)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (!strcmp(ent->d_name, "."))
        continue;
      if (!strcmp(ent->d_name, ".."))
        continue;

      char buffer[PATH_MAX];
      snprintf(buffer, PATH_MAX, "%s/%s", file, ent->d_name);
      struct stat *st;
      st = (struct stat *)malloc(sizeof(struct stat));
      stat(buffer, st);
      if (S_ISDIR(st->st_mode)) {
        enqueue(&dir_queue, buffer);
      } else if (S_ISREG(st->st_mode)) {
        char path_buffer[PATH_MAX];
        realpath(buffer, path_buffer);
        enqueue(&file_queue, path_buffer);
      } else if (S_ISLNK(st->st_mode)) {
        printf("%s\n", "test");
        struct stat *link_st;
        link_st = (struct stat *)malloc(sizeof(struct stat));
        char link_buff[PATH_MAX];
        memset(link_buff, 0, PATH_MAX);
        readlink(buffer, link_buff, PATH_MAX);
        stat(link_buff, link_st);
        if (S_ISREG(link_st->st_mode) && fileExists(link_buff)) {
          enqueue(&file_queue, link_buff);
        }
        free(link_st);
      }
      memset(buffer, 0, PATH_MAX);
      free(st);
    }

    if (is_empty(&dir_queue) == 0) {
      char path[PATH_MAX];
      memset(path, 0, PATH_MAX);
      dequeue(&dir_queue, path);
      directory_scan(path, dir_queue, file_queue, root, files_in_quarantine);
      memset(path, 0, PATH_MAX);
    }
    closedir(dir);
  } else {
    char buffer[5000];
    snprintf(buffer, sizeof(buffer), "%s%s\n", "[ERROR] Folder cannot be opened - ", file);
    log_table(buffer);
    return 0;
  }
  files_scan(file_queue, root, files_in_quarantine);
  return 1;
}

void files_scan(queue *file_queue, tree_node *root, int *files_in_quarantine) {
  while (is_empty(&file_queue) == 0) {
    char path[PATH_MAX];
    memset(path, 0, PATH_MAX);
    dequeue(&file_queue, path);
    file_scan(path, root, files_in_quarantine);
  }
}

void file_scan(char *file, tree_node *root, int *files_in_quarantine) {
  char hash[2 * MD5_DIGEST_LENGTH];
  memset(hash, '0', 2 * MD5_DIGEST_LENGTH);
  count_hash(file, hash);
  if (check_in_DB(root, hash) == 1) {
    put_in_quarantine(file, hash);
    *files_in_quarantine += 1;
  }
}

void log_pointer(char *log_message) {
  FILE *logFile = fopen("program_files/logs.txt", "a+");
  fwrite(log_message, strlen(log_message), 1, logFile);
  fclose(logFile);
}

void log_table(char log_message[5000]) {
  FILE *logFile = fopen("program_files/logs.txt", "a+");
  fwrite(log_message, strlen(log_message), 1, logFile);
  fclose(logFile);
}



