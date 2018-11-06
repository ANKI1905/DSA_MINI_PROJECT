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
int decode(unsigned char ch);
int rembits;
int main(int argc, char *argv[]){
	unsigned int value, chr, prev, pos = 256, rem, code, curr;
	unsigned char ch, c;
	if(argc < 4)
		printf("error");
	unsigned int fdr, fdw;
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
	read(fdr, &ch, sizeof(char));
	code = decode(ch);
	if(code == -1){
		read(fdr, &ch, sizeof(char));
		code = decode(ch);
	}
	prev = code;	
	while(read(fdr, &ch, sizeof(char))){
		code = decode(ch);
		if(code != -1 ){
			curr = code;
			if(curr < 256 && pos < 4096){
				//if(t.arr[prev] != NULL){
					addata(&t, prev, curr, pos);
					printf("%d %d %c\n", pos, prev, curr);
				//print(&t);
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
				
					if(pos < 4096){
					addata(&t, prev, ch, pos);
					printf("%d %d %c\n", pos, prev, curr);
				//print(&t);
					pos++;
					}
				
			}
			if(prev < 256){
				c = prev;
				write(fdw, &c, sizeof(c));
			}
			else {
				//if(t.arr[prev] != NULL)
					writestr(fdw, prev, &t);
				//c = t.arr[prev]->ch;
				//write(fdw, &c, sizeof(c)); 
			}
		}
		prev = curr;
	}
}
void print(table *t){
	int i = 0;
	while(t->arr[i] != NULL){
		printf("%d %d %c\n", i, t->arr[i]->prefix, t->arr[i]->ch);
		i++;
	}
}
void writestr(int fdw, int prev, table *t){
	printf("lol\n");
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
int getchr(table *t, int curr){
	char chr;
	if(t->arr[curr]->prefix < 256)
		return t->arr[curr]->prefix;
	
	chr = getchr(&(*t), t->arr[curr]->prefix);
	return chr;
}
int get(table *t,int prev){
	int chr;
	if(prev < 256)
		return prev;
	chr = get(&(*t),t->arr[prev]->prefix);
}
int decode(unsigned char ch){
	static unsigned int rem;
	static unsigned int num;
	static unsigned char c;
	unsigned int n;
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
		printf("1:%d\n", num);
		num = 0;
		rem = 2;
		
	}
	else if(rem == 2){
		c = c << 4;
		num = c;
		num = num << 4;
		num = num | ch;
		printf("2:%d\n", num);
		code = num;
		rem = 0;
		num = 0;
		c = '\0';
	}
	return code;
}
/*void decompress(int fdr, int fdw) { 
	table t;
	init(&t);   
	static unsigned int rem;
	static unsigned int rembits;
	unsigned int num, next, curr, value;
	unsigned char ch;
	int prev = -1;
	int pos = 256;
	while(read(fdr, &ch, sizeof(char))){
		num = ch;
		printf("written %d\n",num);
    		if(rem > 0) {
      		  	num = (rembits << 8) + num;
       			rem = 0;
       			printf("pos %d\n", num);
       			if(prev == -1)
       				prev = num;
       			else{
       				curr = num;
       				value = search(&t, prev, curr);
       				if(value == prev){
        				writein(fdw, &t, value);
        				addata(&t, prev, curr, pos);
        				pos++;
        				prev = curr;
        			}
        			else
        				prev = value;
        		}
       		} 
   		 else {
       			read(fdr, &ch ,sizeof(char));
       			next = ch;
       			printf("written %d\n", next);
       			rembits = next & 0xF;
        		rem = 1;
        		num = (num << 4) + (next >> 4);
        		printf("pos %d\n", num);
        		curr = num;
        		value = search(&t, prev, curr);
        		if(value == prev){
        			writein(fdw, &t, value);
        			addata(&t, prev, curr, pos);
        			pos++;
        			prev = curr;
        		}
        		else
        			prev = value;
        			
        	}
    	}
    return;
}


void writein(int fdw, table *t, int value){
	node *p;
	char ch;
	p = t->arr[value];
	if(value < 256){
		ch = value;
		write(fdw, &ch, sizeof(char));
		return;
	}
	else
		writestr(fdw, p->prefix, &(*t));
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
}*/
	 
		
		
		
		
		
		
	
