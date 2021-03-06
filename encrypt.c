#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <errno.h>

void encrypt_file(char *input_file, char *output_file)
{	

	FILE *input = fopen(input_file, "r");
	FILE *output = fopen(output_file, "w");
	

	
    	
    	fseek(input, 0, SEEK_END);
    	
    	
    	long fsize = ftell(input);
    	fseek(input, 0, SEEK_SET);
    	EVP_CIPHER_CTX *ctx;
    	ctx = EVP_CIPHER_CTX_new();
    	int outlen=0;
    	unsigned char *indata = malloc(fsize);
    	unsigned char *outdata;
    	unsigned blocksize;
	unsigned char ckey[] = "thiskeyisverybadaaaaaaaaaaaaaaab";
    	unsigned char ivec[] = "dontusethisinputaaaaaaaaaaaaaaab";

    	fread(indata, sizeof(unsigned char), fsize, input);

    	EVP_EncryptInit(ctx, EVP_aes_256_cbc(), ckey, ivec);
   
    	blocksize = EVP_CIPHER_CTX_block_size(ctx);
    	outdata = malloc(((fsize + blocksize)/blocksize) * blocksize);

    	EVP_EncryptUpdate(ctx, outdata, &outlen, indata, (int)fsize);
    	fwrite(outdata, 1, outlen,  output);
    	EVP_EncryptFinal(ctx, outdata, &outlen);
    	fwrite(outdata, 1, outlen, output);
    	
    	
    	fclose(input);
    	fclose(output);
    	
    	free(indata);
    	free(outdata);
	
	remove(input_file);
    	
    	EVP_CIPHER_CTX_free(ctx);
}
