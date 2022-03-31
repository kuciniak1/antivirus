#include <stdio.h>
#include <openssl/md5.h>


int count_hash(char *filepath, char hash[])
{
    	unsigned char c[MD5_DIGEST_LENGTH];
    	int i;
    	FILE *inFile = fopen (filepath, "rb");
    	MD5_CTX mdContext;
    	int bytes;
    	unsigned char data[1024];
    	if (inFile == NULL)
    	{
        	printf ("%s can't be opened.\n", filepath);
        	return 0;
    	}
    	MD5_Init (&mdContext);
    	while ((bytes = fread (data, 1, 1024, inFile)) != 0)
        	MD5_Update (&mdContext, data, bytes);
    	MD5_Final (c,&mdContext);
    	for(int j =0; j<16; ++j)
    	{	
    		sprintf(&hash[j*2], "%02X", (unsigned char) c[j]);
    	}
    	fclose (inFile);
    	return 0;
}


int hash_comparer(unsigned char hash1[],unsigned char hash2[])
{	
	
	//for(int i = 0; i < 2*MD5_DIGEST_LENGTH; i++)
	//{
	//	printf("%d", hash1[i]);
	//}
	//printf("\n");
	//for(int i = 0; i < 2*MD5_DIGEST_LENGTH; i++)
	//{
	//	printf("%d", hash2[i]);
	//}
	//printf("\n");
	
	for(int i = 0; i < 2*MD5_DIGEST_LENGTH; i++)
	{
		if(hash1[i] > hash2[i])
		{		
			return 1;
			
		}
		else if (hash1[i] < hash2[i])
		{
			return 2;
		}
	}
	return 0;
}






