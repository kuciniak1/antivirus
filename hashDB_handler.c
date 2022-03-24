#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <openssl/md5.h>
#include "queue.h"
#include "hashing.h"
#include "quarantine.h"
#include "tree.h"

int DB_init(char* path_to_DB, tree_node **root)
{
	FILE *database;
    	unsigned char line[2*MD5_DIGEST_LENGTH];
    	memset(line, 0, sizeof line);
    	if ((database = fopen(path_to_DB, "rb")) == NULL)
    	{
        	fclose(database);
        	return -1;
    	}
   
    	while ((fread(line, sizeof(line), 1, database)) >= 1)
    	{	
        	insert_node(root, line);
        	memset(line, 0, sizeof line);
        	fgetc(database);
    	}
    	fclose(database);
}


int check_in_DB(tree_node *root, unsigned char *hash)
{
    	if(search(&root, hash) == 1)
    	{
        	return 1;
    	}
    	else
    	{
    		return 0;
    	}
}
