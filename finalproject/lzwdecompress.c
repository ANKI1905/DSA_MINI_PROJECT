#include "functions.h"
#include "table.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int decoding(unsigned char ch);
void writestr(int fdw, int prev, table *t);
void lzwdecompress(int fdr, int fdw){
	unsigned int prev, pos = 256, rem, code, curr;
	unsigned char ch, c;
	table t;
	tlinit(&t);
	read(fdr, &ch, sizeof(char));
	code = decoding(ch);
	if(code == -1){
		read(fdr, &ch, sizeof(char));
		code = decoding(ch);
	}
	prev = code;	
	while(read(fdr, &ch, sizeof(char))){
		code = decoding(ch);
		if(code != -1 ){
			curr = code;
			if(curr < 256 && pos < 4096){
					taddata(&t, prev, curr, pos);
					pos++;
				
			}
			else if(pos < 4096){
				if(t.arr[curr] != NULL){
					rem = getchr(&t, curr);
					ch = rem;
				}
				else {
					rem = get(&t, prev);
					ch = rem;
				}
				taddata(&t, prev, ch, pos);
				pos++;
			}
			if(prev < 256){
				c = prev;
				write(fdw, &c, sizeof(c));
			}
			else
				writestr(fdw, prev, &t); 
			
		}
		prev = curr;
	}
	if(prev < 256){
		c = prev;
		write(fdw, &c, sizeof(c));
	}
	else
		writestr(fdw, prev, &t);
	tdestroytable(&t);
	close(fdw);
	close(fdr);
}
void writestr(int fdw, int prev, table *t){
	char ch;
	node *p;
	if(prev == -1){
	return;
	}
	p = t->arr[prev];
	writestr(fdw, p->prefix, &(*t));
	ch = p->ch;
	write(fdw, &ch, sizeof(ch));
	return;
}
int decoding(unsigned char ch){
	static unsigned int rem;
	static unsigned int num;
	static unsigned char c;
	unsigned int code;
	if(rem == 0){
		num = ch;
		num = num << 4;
		rem = 1;
		code = -1;
	}
	else if(rem == 1){
		c = ch;
		ch = ch >> 4;
		num = num | ch;
		code = num;
		num = 0;
		rem = 2;
		
	}
	else if(rem == 2){
		c = c << 4;
		num = c;
		num = num << 4;
		num = num | ch;
		code = num;
		rem = 0;
		num = 0;
		c = '\0';
	}
	return code;
}	
	

 	
	
	
