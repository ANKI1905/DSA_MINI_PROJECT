#include "functions.h"
#include "table.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
unsigned int rembits;
int writeinfile(int fdw, int prev){
	unsigned int num;
	static unsigned  int rem;
	if(rem == 0){
		rembits = prev & 0x0000000f;
		rem = 1;
		num = prev >> 4;
		write(fdw, &num, sizeof(char));
	}
	else {
		rem = 0; 
		rembits = rembits << 4;
		num = prev >> 8;
		num = num | rembits;
		prev = prev & 0x000000ff;
		write(fdw, &num, sizeof(char));
		write(fdw, &prev, sizeof(char));
	}
	return rem; 
}

void lzwcompress(int fdr, int fdw){
	unsigned int value, ch, prev, pos = 256, rem;
	unsigned char chr;
	table t;
	init(&t);
	read(fdr, &chr, sizeof(chr));
	prev = chr;
	while(read(fdr, &chr, sizeof(chr))){
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
		rembits = rembits << 4;
		write(fdw, &rembits, sizeof(char));
	}
	destroytable(&t);
	close(fdr);
	close(fdw);
}
		
