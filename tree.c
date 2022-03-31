#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include "hashing.h"

typedef struct tree_node tree_node;

struct tree_node
{
	char hash[2*MD5_DIGEST_LENGTH];
	struct tree_node *left_node;
    	struct tree_node *right_node;
};




void insert_node(tree_node **tree, char hash_from_DB[2*MD5_DIGEST_LENGTH])
{	
    	if ((*tree)==NULL)
    	{ 
    		tree_node *tmp = NULL;
    		tmp = (tree_node *)malloc(sizeof(tree_node));
    		tmp->left_node = tmp->right_node = NULL;
    		memcpy(tmp->hash, hash_from_DB, 2*MD5_DIGEST_LENGTH);
    		*tree = tmp;
    		return;
    	}	
    
    	if (hash_comparer((*tree)->hash, hash_from_DB) == 1) 
    	{
        	insert_node(&((*tree)->left_node), hash_from_DB);
    	}
    	else if (hash_comparer(hash_from_DB, (*tree)->hash) == 1)
    	{
        	insert_node((&(*tree)->right_node), hash_from_DB);
    	}
}


int search(tree_node **tree, char hash[])
{
    	if(!(*tree))
    	{
        	return 0;
    	}
    	if(hash_comparer((*tree)->hash, hash)==0)
    	{	
        	return 1;
    	} 
    	else if (hash_comparer((*tree)->hash, hash) == 1)
    	{	
        	search(&((*tree)->left_node), hash);
    	}
    	else if (hash_comparer((*tree)->hash, hash) == 2)
    	{
        	search(&((*tree)->right_node), hash);
    	}
    	
}


void delete_tree(tree_node *tree)
{
    	if(tree)
    	{
        	delete_tree(tree->left_node);
        	delete_tree(tree->right_node);
        	free(tree);
    	}
}

void display_tree(tree_node **tree)
{	
if (*tree != NULL)
{
	display_tree(&((*tree)->left_node));
	printf("%s\n", (*tree)->hash);
	display_tree(&((*tree)->right_node));
}

}


