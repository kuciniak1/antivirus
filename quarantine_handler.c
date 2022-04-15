#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <math.h>


#include "cipher.h"


const char* get_field(char* line, int num)
{
    const char* tok;
    char* tmp_line = malloc(strlen(line));
    strcpy(tmp_line, line);
    for (tok = strtok(tmp_line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
    {
	if (!--num)
            return tok;
    }
    return NULL;
}


int main(int argc,char *argv[])
{	
	if(argc != 2)
	{	
		printf("%s\n", "Usage: ./quarantine_hander <number_of_file>");
		return 0;
	}
	FILE* info_file = fopen("program_files/quarantine/info.csv", "r");
	char path_in_q[60];
	snprintf(path_in_q, 60, "%s/%s", "program_files/quarantine", argv[1]);	
    	char* line= NULL;
    	size_t len = 0;
    	ssize_t read;

    	while ((read = getline(&line, &len, info_file))!=-1)
    	{		
    			
        		if(!strcmp(get_field(line, 1),argv[1]))
        		{
        			int i;
        			const char *permissions = get_field(line, 2);
        			i = strtol(permissions, 0,8);
        			chmod(path_in_q, i);
        			const char *output = get_field(line, 3);
				decrypt_file(path_in_q, output);
				chmod(output, i);
	 			remove(path_in_q);
        		}
        }
    	fclose(info_file);
}


