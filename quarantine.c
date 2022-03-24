#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void put_in_quarantine(char *file, int *files_in_quarantine)
{
	chmod(file, 666);
    	FILE *infoFile = fopen("quarantine/info.txt", "a");
    	(*files_in_quarantine)++;
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
    	snprintf(info, sizeof info, "%d || %s || %s\n", *files_in_quarantine, file, buffer);
    	snprintf(newFilePath, sizeof newFilePath, "%s/%d", "quarantine", *files_in_quarantine);
    	fwrite(info, strlen(info), 1, infoFile);
    	fclose(infoFile);
    	rename(file, newFilePath);
}
