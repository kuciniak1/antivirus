#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>


#include "cipher.h"




int main(int argc,char *argv[])
{
	if(argc != 3)
	{	
		printf("%s\n", "Usage: ./quarantine_hander <number_of_file> <destination>");
		return 0;
	}
	
	
	
    	decrypt_file(argv[1], argv[2]);
    	remove(argv[1]);
}

