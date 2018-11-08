#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#define MAX 4096
#include "table.h"
#include "functions.h"
#define TABLE_SIZE 4096
#define INIT 256
unsigned int rembits;
int decode(unsigned char ch);
int main(int argc, char *argv[]){
	if(argc < 4){
		printf("usage: <operation> <filename1> <filename2>\n");
		printf("operations: -c1 := firstcompression\n");
		printf("	    -c2 := second compression\n");
		printf("	    -uc1 := first decompression\n");
		printf("	    -uc2 := second decompression\n");
		return 0;	
	}
	int fdr, fdw;
	fdr = open(argv[2], O_RDONLY);
	if(fdr == -1){
		perror("open failed");
		return errno;
	}
	fdw = open(argv[3], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fdr == -1){
		perror("open failed");
		return errno;
	}
	if(strcmp(argv[1], "-c2") == 0){
		lzwcompress(fdr, fdw);
	}
	else if(strcmp(argv[1], "-uc2") == 0){
		lzwdecompress(fdr, fdw);
	}
	return 0;
}


