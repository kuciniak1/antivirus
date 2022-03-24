#pragma once
#include <openssl/md5.h>

typedef struct tree_node tree_node;

struct tree_node
{
    char hash[2*MD5_DIGEST_LENGTH];
    struct tree_node *left_node;
    struct tree_node *right_node;
    
};



void display_tree(tree_node **tree);

void insert_node(struct tree_node **tree, char hash[2*MD5_DIGEST_LENGTH]);

int search(struct tree_node **tree, unsigned char *hash);

void delete_tree(struct tree_node *tree);
