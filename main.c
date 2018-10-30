#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#define MAX 4096
#include "mytable.h"
int prev;
int ch;
char chr;
int pos;
int value = 256;
int main(int argc, char *argv[]){
	data d;
	int pos;
	if(argc < 3)
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
	dlist l;
	dinit(&l);
	read(fdr, &chr, sizeof(chr));
	prev = chr;
	while(read(fdr, &chr, sizeof(chr))){
		ch = chr;
		pos = findchar(&l,prev, ch);
		if(pos != -1){
			prev = pos;
		}
		else {
			d.pos = value++;
			d.prev = prev;
			d.ch = ch;
			writeinfile(fdw, prev);
			adddata(&l, d);
			prev = ch;
		}
	}
	writeinfile(fdr, prev);
}
void writeinfile(int fdw, int prev){
	static int rem;
	static int rembits;
	int num;
	if(rem == 0){
		printf("in 0\n");
		rembits = prev & 0x0000000f;
		rem = 1;
		num = prev >> 4;
		write(fdw, &num, sizeof(char));
	}
	else {
		printf("in 1\n");
		printf("prev 1 %d\n",prev);
		rem = 0;
		rembits = rembits << 4;
		num = prev >> 8;
		num = num | rembits;
		write(fdw, &num, sizeof(char));

		write(fdw, &prev, sizeof(char));
	}
}
		
		
	
	

 	
	
	
