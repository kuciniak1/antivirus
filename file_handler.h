#pragma once

#include "tree.h"
#include "queue.h"



void files_scan(queue *file_queue, tree_node *root, int *files_in_quarantine);

void file_scan(char *file, tree_node *root, int *files_in_quarantine);

int is_dir(char *path);

int directory_scan(char* file, queue *dir_queue, queue *file_queue, tree_node *root, int *files_in_quarantine);
