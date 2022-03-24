#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <openssl/md5.h>
#include <unistd.h>
#include "queue.h"
#include "hashing.h"
#include "quarantine.h"
#include "hashDB_handler.h"
#include "tree.h"
#include "file_handler.h"


int directory_scan(char* file, queue *dir_queue, queue *file_queue, tree_node *root, int *files_in_quarantine)
{
	struct dirent *ent;
    	DIR *dir;
    	if ((dir = opendir(file)) != NULL)
    	{
        	while ((ent = readdir(dir)) != NULL)
        	{
            		if (!strcmp(ent->d_name, "."))
                		continue;
            		if (!strcmp(ent->d_name, ".."))
                		continue;
     	     
            		char buffer[4097];           
            		snprintf(buffer, sizeof buffer, "%s/%s", file, ent->d_name);
            		struct stat *st;
    			st = (struct stat *) malloc(sizeof(struct stat));
            		stat(buffer, st);
            		printf("%s\n", buffer);
            		if(S_ISDIR(st->st_mode))
            		{	
               		enqueue(&dir_queue, buffer);
            		}
            		else if(S_ISREG(st->st_mode))
            		{
                		enqueue(&file_queue, buffer);
            		} 
            		else if(S_ISLNK(st->st_mode))
            		{
            			struct stat *link_st;
            			link_st = (struct stat *) malloc(sizeof(struct stat));
            			char link_buff[4097];
            			memset(link_buff, 0, 4097);
            			readlink(buffer, link_buff, 4097);
            			stat(link_buff, link_st);
            			if(S_ISDIR(link_st->st_mode))
            			{
            				enqueue(&dir_queue, link_buff);
            			}
      				else if(S_ISREG(link_st->st_mode))
      				{
      					enqueue(&file_queue, link_buff);
      				}
            			free(link_st);
            		}	
            		memset(buffer, 0, 4097);
            		free(st);
        	}
        	
        	if(is_empty(&dir_queue) ==0)
        	{	
        		char path[4097];
        		memset(path, 0, 4097);
        		dequeue(&dir_queue, path);
            		directory_scan(path, dir_queue, file_queue, root, files_in_quarantine);
        	}
        	closedir(dir);
    	}
    	else
    	{
    		printf ("%s cannot be opened.\n", file);
        	return 0;
    	}
	files_scan(file_queue, root, files_in_quarantine);
}



void files_scan(queue *file_queue, tree_node *root, int *files_in_quarantine)
{
	while(is_empty(&file_queue) == 0)
	{
		char path[4097];
        	memset(path, 0, 4097);
        	dequeue(&file_queue, path);
        	file_scan(path, root, files_in_quarantine);
	}
}



void file_scan(char *file, tree_node *root, int *files_in_quarantine)
{
    	char hash[2*MD5_DIGEST_LENGTH];
    	memset(hash, '0', 2*MD5_DIGEST_LENGTH);
    	count_hash(file, hash);
    	if(check_in_DB(root, hash)==1)
    	{	
    		char buffer[4097];           
            	realpath(file, buffer);
      		put_in_quarantine(buffer, files_in_quarantine);
    	}
}


void _logs(char *log_message)
{




}


