#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "cipher.h"

void put_in_quarantine(char *file, int *files_in_quarantine)
{
	(*files_in_quarantine)++;
	
	
    	FILE *infoFile = fopen("quarantine/info.txt", "a");
    	
    	char newFilePath[4096];
    	char info[5000];
    	memset(info, 0, sizeof info);
    	memset(newFilePath, 0, sizeof newFilePath);
    	
    	
    	time_t timer;
    	struct tm* tm_info;
    	char buffer[26];
    	timer = time(NULL);
    	tm_info = localtime(&timer);
    	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    	
    	char path_buffer[4097];
    	realpath(file, path_buffer); 
    	
    	
    	snprintf(info, sizeof info, "%d || %s || %s\n", *files_in_quarantine, path_buffer, buffer);
    	
    	
    	snprintf(newFilePath, sizeof newFilePath, "%s/%d", "quarantine", *files_in_quarantine);
    	fwrite(info, strlen(info), 1, infoFile);
    	fclose(infoFile);
    	
    	
    	encrypt_file(file, newFilePath);
    	chmod(newFilePath, 666);
    	
}
