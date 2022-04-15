#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include "cipher.h"

void put_in_quarantine(char *file, char hash[])
{
	
	
	
    	FILE *infoFile = fopen("program_files/quarantine/info.csv", "a");
    	
    	char newFilePath[4096];
    	char info[5025];
    	memset(info, 0, sizeof info);
    	memset(newFilePath, 0, sizeof newFilePath);
    	
    	
    	time_t timer;
    	struct tm* tm_info;
    	char time_buffer[26];
    	timer = time(NULL);
    	tm_info = localtime(&timer);
    	strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    	
    	char path_buffer[4097];
    	realpath(file, path_buffer); 
    	
    	
    	
	
	
	struct stat statbuf;
	stat(file, &statbuf);
	char stat_buffer[7];
	snprintf(stat_buffer, 7, "%o", statbuf.st_mode);
	char perm_buffer[4];
	for(int i = 0; i<3; i++)
	{
		perm_buffer[i] = stat_buffer[i+3];
	}
		
    	snprintf(info, sizeof info, "%s,%s,%s,%s\n", hash, perm_buffer, path_buffer, time_buffer);
    	
    	
    	snprintf(newFilePath, sizeof newFilePath, "%s/%s", "program_files/quarantine", hash);
    	fwrite(info, strlen(info), 1, infoFile);
    	fclose(infoFile);
    	
    	
    	encrypt_file(file, newFilePath);
    	chmod(newFilePath, 0000);
    	
}



