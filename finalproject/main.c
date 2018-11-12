#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include "functions.h"
void print();
int main(int argc, char *argv[]){
	if(argc < 4){
		print();
		return 0;	
	}
	int fdr, fdw;
	fdr = open(argv[2], O_RDONLY);   //open file for reading
	if(fdr == -1){
		perror("open failed");
		return errno;
	}
	fdw = open(argv[3], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);  //open file for writing
	if(fdr == -1){
		perror("open failed");
		return errno;
	}
	if(strcmp(argv[1], "-c1") == 0){
		huffcompress(fdr, fdw);      //huffman compression
	}
	else if(strcmp(argv[1], "-uc1") == 0){
		huffdecompress(fdr, fdw);      //huffman decompresssion
	}
	else if(strcmp(argv[1], "-c2") == 0){
		lzwcompress(fdr, fdw);         //lzwcompression
	}
	else if(strcmp(argv[1], "-uc2") == 0){
		lzwdecompress(fdr, fdw);	//lzwdecompression
	}
	else
		print();
	return 0;
}
void print(){
	/*print the usage if not proper arguements*/
	printf("usage: <operation> <filename1> <filename2>\n");
	printf("operations: -c1 := firstcompression\n");
	printf("	    -c2 := second compression\n");
	printf("	    -uc1 := first decompression\n");
	printf("	    -uc2 := second decompression\n");
	return;
}
	
