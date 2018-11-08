#include<stdio.h>	
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include"treestack.h"
void builttree(int fdr, tree *t);
void decode(int fdr, int fdw, tree *t);	
void decompress(int fdr, int fdw) {
	tree t;
	dtinit(&t);
	builttree(fdr, &t);
	lseek(fdr, -1, SEEK_CUR);
	decode(fdr, fdw, &t);
	
}
void builttree(int fdr, tree *t) {
	tree temp;
	int i = 0;
	char ch;
	stack s;
	dsinit(&s);
	while(read(fdr, &ch, sizeof(ch))){
		i++;
		if(ch == '1') {
			temp = (node *)malloc(sizeof(node));
			read(fdr, &ch, sizeof(ch));
			i++;
			temp->ch = ch;
			temp->right = temp->left = NULL;
			push(&s, temp);
		}
		else if(ch == '0') {
			temp = (node *)malloc(sizeof(node));
			temp->ch = '\0';
			temp->right = pop(&s);
			temp->left = pop(&s);
			push(&s, temp);
		}
		else  {
			*t = pop(&s);
			break;
		}
	}
}	
void decode(int fdr, int fdw, tree *t){
	char  ch, cht;
	int num = 0;
	node *p;
	p = (*t);
	int i, n;
	char next, prev;
	read(fdr, &ch, sizeof(ch));
	read(fdr, &prev, sizeof(prev));
	while(read(fdr, &next, sizeof(next))) { 
		num = 0;
		while(num <= 7){
			i = ch & 0x80;
			if(i != 0){
				if(p->left == NULL && p->right == NULL) {
				 	cht = p->ch;
					write(fdw, &cht, sizeof(cht));
					p = (*t);
				}
			p = p->right;
			ch = ch << 1;
		
			}
		else if(i == 0){
			if(p->left == NULL && p->right == NULL){  
				cht = p->ch; 
				write(fdw, &cht, sizeof(cht));
				p = (*t);
			}
			p = p->left;
			ch = ch << 1;
		}
		num++;	
		}
		ch = prev;
		prev = next;
	}
	
	n = prev - '0';
	if(n == 0)
		n = 8;
	num = 0;
	while(num < n){
		i = ch & 0x80;
			if(i != 0){
				if(p->left == NULL && p->right == NULL) {
				 	cht = p->ch;
					write(fdw, &cht, sizeof(cht));
					p = (*t);
				}
			p = p->right;
			ch = ch << 1;
		
			}
		else if(i == 0){
			if(p->left == NULL && p->right == NULL){  
				cht = p->ch; 
				write(fdw, &cht, sizeof(cht));
				p = (*t);
			}
			p = p->left;
			ch = ch << 1;
		}
		num++;	
	}
	ch = p->ch;
	write(fdw, &ch, sizeof(ch));
}
						
		
