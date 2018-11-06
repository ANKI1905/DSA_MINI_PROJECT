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
unsigned int rembits;
int main(int argc, char *argv[]){
	unsigned int value, ch, prev, pos = 256, rem;
	unsigned char chr;
	if(argc < 4)
		printf("error");
	int fdr, fdw;
	fdr = open(argv[1], O_RDONLY);
	if(fdr == -1){
		perror("open failed");
		return errno;
	}
	fdw = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fdr == -1){
		perror("open failed");
		return errno;
	}
	table t;
	init(&t);
	read(fdr, &chr, sizeof(chr));
	prev = chr;
	while(read(fdr, &chr, sizeof(chr))){
		//if(pos == TABLE_SIZE)
			//reset(&t);
		//printf("%d\n",prev);
		//if (pos >= 4096)
		//	return;
		ch = chr;
		value = search(&t, prev, chr);
		if(value == prev){
			rem = writeinfile(fdw, prev);
			if(pos < 4096){
				addata(&t, prev, chr, pos);
				pos++;
			}
			prev = ch;
		}
		else{
			prev = value;
		}
	}
	rem = writeinfile(fdw, prev);
	if(rem == 1){
		//printf("wrote");
		rembits = rembits << 4;
		write(fdw, &rembits, sizeof(char));
	}
}
int writeinfile(int fdw, int prev){
	static unsigned int leftover;
	static unsigned int leftoverBits;
	unsigned int codes;
	unsigned int previousCode;
	unsigned int num;
	static unsigned  int rem;
	//printf("%d\n", prev);
	if(rem == 0){
		printf("0 pos:%d\n", prev);
		rembits = prev & 0x0000000f;
		rem = 1;
		num = prev >> 4;
		//printf("written code %d\n",num);
		write(fdw, &num, sizeof(char));
	}
	else {
		printf("1 pos:%d\n",prev);
		rem = 0; 
		rembits = rembits << 4;
		num = prev >> 8;
		num = num | rembits;
		//printf("written code %d\n",num);
		prev = prev & 0x000000ff;
		//printf("written code %d\n", prev);
		write(fdw, &num, sizeof(char));
		write(fdw, &prev, sizeof(char));
	}
	 /*if (leftover > 0) {
         previousCode = (leftoverBits << 4) + (code >> 8);
        write(fdw, &previousCode, sizeof(char));
         write(fdw, &code, sizeof(char));
       // fputc(previousCode, output);
       // fputc(code, output);
        
        leftover = 0; // no leftover now
    } else {
        leftoverBits = code & 0xF; // save leftover, the last 00001111
        leftover = 1;
        codes = code >> 4;
        write(fdw, &codes, sizeof(char));
    }*/
}


		
		
	
	

 	
	
	
