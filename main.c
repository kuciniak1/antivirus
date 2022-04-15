#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


#include "hashing.h"
#include "queue.h"
#include "tree.h"
#include "hashDB_handler.h"
#include "file_handler.h"


int main(int argc, char *argv[])
{
	if(argc==1)
	{	
		printf("%s\n", "Usage: ./antivirus <file_name> <virus_DB>");
		return 0;
	}
	else if(argc < 3 && strcmp(argv[1], "man"))
	{
		printf("%s\n", "Usage: ./antivirus <file_name> <virus_DB>");
		return 0;
	}
	else if(!strcmp(argv[1], "man"))
   	{
        // TODO: instruction
        	printf("%s\n", "Instruction");
        	return 0;
	}
	else if (argc > 3)
	{	
		printf("%s\n", "Usage: ./antivirus <file_name> <virus_DB>");
		return 0;
	}


	

	mkdir("program_files", 0777);
	mkdir("program_files/quarantine", 0777);
    	int files_in_quarantine = 0;
    	tree_node *root = NULL;
    	queue *dir_queue = NULL;
    	queue *file_queue = NULL;
    	
    	if(DB_init(argv[2], &root)==-1)
    	{
    		printf("%s\n", "Database cannot be opened");
    		return 0;
    	}
    
        	
    	dir_queue = init(dir_queue);
    	file_queue = init(file_queue);
    	
    
	struct stat *st;
     	st = (struct stat *) malloc(sizeof(struct stat));
     	stat(argv[1],st);
     	
     	
     	
     	
     	if(!st->st_mode)
     	{
     		printf("%s\n", "File cannot be opened");
     		delete_tree(root);
    		free(dir_queue);
    		free(file_queue);
     		free(st);
     		return 0;
     	}
     	
	if(S_ISDIR(st->st_mode))
	{
        	directory_scan(argv[1], dir_queue, file_queue, root, &files_in_quarantine);
        }
    	else if(S_ISREG(st->st_mode))
    	{
    	    	file_scan(argv[1], root, &files_in_quarantine);
    	}
    	else if(S_ISLNK(st->st_mode))
    	{
    		struct stat *link_st;
        	link_st = (struct stat *) malloc(sizeof(struct stat));
     		char link_buff[4097];
        	memset(link_buff, 0, 4097);
        	readlink(argv[1], link_buff, 4097);
        	stat(link_buff, link_st);
        	if(S_ISDIR(link_st->st_mode))
        	{
        		directory_scan(link_buff, dir_queue, file_queue, root, &files_in_quarantine);
        	}
      		else if(S_ISREG(link_st->st_mode))
      		{
    			file_scan(link_buff, root, &files_in_quarantine);
      		}
        	free(link_st);
    	}
	
    //TODO: statystyki
    free(st);
    delete_tree(root);
    free(dir_queue);
    free(file_queue);

}
