#include "functions.h"
#include "leaftree.h"
#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
void getfrequency(int fdr, leaf *l);
void compress(int fdr, int fdw, list *s);
void traverse(tree t, char *str, int pos, list *s);
void writeheader(int fdw, tree t);
void compression(int fdr, int fdw) {
	char str[100];
	leaf l;
	tree t;
	tinit(&t);
	init(&l);
	list s;
	sinit(&s);
	getfrequency(fdr, &l);
	sort(&l);
	buildtree(&l, &t);
	traverse(t, str, 0, &s);
	writeheader(fdw, t);
	lseek(fdr, 0, SEEK_SET);
	compress(fdr, fdw, &s);
}
void getfrequency(int fdr, leaf *l) {
	char ch;
	int i = 0;
	int num = 0;
	while(read(fdr, &ch, sizeof(ch))) {
		if(ch == '\n') 
			num++;
		else {
			i = search(&(*l), ch);
			if(i == 0) 
				insert(&(*l), ch, 1);
		}
	}
	insert(&(*l), '\n', num);
}
void traverse(tree t, char *str, int pos, list *s) {
	if(t->left) {
		str[pos] = '0';
		traverse(t->left, str, pos + 1, &(*s));
	}
	if(t->right) {
		str[pos] = '1';
		traverse(t->right, str, pos + 1, &(*s));
	}
	if(!((t->left) || (t->right))){
		str[pos] = '\0';
		addata(t->d.ch, str, &(*s));
	}
}

void writeheader(int fdw, tree t) {
	char ch;
	if(t->left == NULL && t->right == NULL) {
		ch = '1';
		write(fdw, &ch, sizeof(ch));
		write(fdw, &(t->d.ch), sizeof(ch));
		return;
	}
	writeheader(fdw, t->left);
	writeheader(fdw, t->right);
	ch = '0';
	write(fdw, &ch, sizeof(ch));
}
void compress(int fdr, int fdw, list *s){
	int countbits = 0, i;
	int length;
	char ch, buffer;
	char stri[100];
	int num;
	while(read(fdr, &ch, sizeof(ch))) {
		strcpy(stri, searchchar(&(*s), ch)); 
		length = strlen(stri);
		i = 0;
		while(i < length){
			if(stri[i] == '0')
				buffer = buffer & 0xfe;
			else if(stri[i] == '1')
				buffer = buffer | 0x01;
			countbits++;
			if(countbits == 8 ) {
				write(fdw, &buffer, sizeof(buffer));
				countbits = 0;
				buffer = '\0';
			}
			else 
				buffer = buffer << 1;
			i++;
		}
	}
	num = countbits;
	if(countbits != 0){
		while(countbits < 7){
			buffer = buffer << 1;
			countbits++;
		}
		write(fdw, &buffer, sizeof(buffer));
		
	}
	ch = '0' + num;
	write(fdw, &ch, sizeof(ch));
		
}	
