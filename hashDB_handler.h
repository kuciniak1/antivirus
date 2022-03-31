#pragma once

#include "tree.h"

int DB_init(char* path_to_DB, tree_node **root);

int check_in_DB(tree_node *root, char hash[]);
