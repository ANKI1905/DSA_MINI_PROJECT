#include "functions.h"
#include "table.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
unsigned int rembits;
/*write bits in file*/
int writeinfile(int fdw, int prev){
	unsigned int num;
	static unsigned  int rem;
	/*no remaininig bits*/
	if(rem == 0){
		rembits = prev & 0x0000000f;
		rem = 1;
		num = prev >> 4;
		write(fdw, &num, sizeof(char));
	}
	else {
	/*if earlier bits are remaining the  they are padded*/
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
	tlinit(&t);   /*initialise table*/
	read(fdr, &chr, sizeof(chr));
	prev = chr;
	while(read(fdr, &chr, sizeof(chr))){
		ch = chr;
		value = tsearch(&t, prev, chr);  /*search for coming charcater*/
		if(value == prev){
			rem = writeinfile(fdw, prev);
			if(pos < 4096){
				taddata(&t, prev, chr, pos);  /*add data in table*/
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
	tdestroytable(&t);
	close(fdr);
	close(fdw);
}
		
