#pragma once

#include "queue.h"
#include "tree.h"

int fileExists(char path[PATH_MAX]);

void files_scan(queue *file_queue, tree_node *root, int *files_in_quarantine);

void file_scan(char *file, tree_node *root, int *files_in_quarantine);

int directory_scan(char *file, queue *dir_queue, queue *file_queue,
                   tree_node *root, int *files_in_quarantine);
                   
void log_pointer(char *log_message);

void log_table(char log_message[5000]);

