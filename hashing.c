#include <openssl/md5.h>
#include <stdio.h>

#include "file_handler.h"

int count_hash(char *filepath, char hash[]) {
  unsigned char c[MD5_DIGEST_LENGTH];
  FILE *inFile = fopen(filepath, "rb");
  MD5_CTX mdContext;
  int bytes = 0;
  unsigned char data[1024];
  if (inFile == NULL) {
    char buffer[5000];
    snprintf(buffer, sizeof buffer, "%s%s\n", "[ERROR] File cannot be opened - ", filepath);
    log_table(buffer);
    return 0;
  }
  MD5_Init(&mdContext);
  while ((bytes = fread(data, 1, 1024, inFile)) != 0)
    MD5_Update(&mdContext, data, bytes);
  MD5_Final(c, &mdContext);
  for (int j = 0; j < 16; ++j) {
    sprintf(&hash[j * 2], "%02X", c[j]);
  }
  fclose(inFile);
  return 0;
}

int hash_comparer(char hash1[], char hash2[]) {
  for (int i = 0; i < 2 * MD5_DIGEST_LENGTH; i++) {
    if (hash1[i] > hash2[i]) {
      return 1;

    } else if (hash1[i] < hash2[i]) {
      return 2;
    }
  }
  return 0;
}
