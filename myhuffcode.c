#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include "leaf.h"
#include<string.h>
typedef struct dataa{
	char ch;
	char str[256];
	struct data *next;
}dataa;
typedef dataa *stack;
void sinit(stack *s) {
	(*s) = NULL;
}
//void codes(tree *t, char *str, pos) {
//	if((*t) == NULL)
//		return; 

void addata(data d, char *str, int pos, stack *s);
void traverse(tree t, char *str, int pos, stack *s) {
	if(t->left) {
		str[pos] = '0';
		traverse(t->left, str, pos + 1, &(*s));
	}
	if(t->right) {
		str[pos] = '1';
		traverse(t->right, str, pos + 1, &(*s));
	}
	if(!((t->left) || (t->right))) {
		str[pos] = '\0';
		addata(t->d, str, pos, &(*s));
	}
}

void addata(data d, char *str, int pos, stack *s){
	dataa *temp;
	dataa *p;
	p = (*s);
	printf("%c - %s\n",d.ch, str);
	temp = (dataa *)malloc(sizeof(data));
	temp->ch = d.ch;
	strcpy(temp->str, str);
	if((*s) == NULL){
		(*s) = temp;
		temp->next = NULL;
		return;
	}
	while(p->next != NULL) 
		p = p->next;
		
	p->next = temp;
	temp->next = NULL;
}

void treeinsert(leaf *l, tree *t);
void buildtree(leaf *l, tree *t);	  
void getfrequency(int fdr) {
	leaf l;
	tree t;
	tinit(&t);
	init(&l);
	stack s;
	sinit(&s);
	char ch;
	int i = 0;
	int num = 0;
	char str[256];
	while(read(fdr, &ch, sizeof(ch))) {
		if(ch == '\n') 
			num++;
		else {
			i = search(&l, ch);
			if(i == 0) 
				insert(&l, ch, 1);
			}
	}
	insert(&l, '\n', num);
	sort(&l);
	i = length(&l);
	printf("length = %d\n", i);
	printtree(&l);
	buildtree(&l, &t);
	printf("%d",t->d.freq);
	traverse(t, str, 0, &s);
			
	return;
}
void treeinsert(leaf *l, tree *t) {
	node *p, *q;
	p = l->head;
	while(p->next != NULL){
		if((*t)->d.freq < p->d.freq) {
			(*t)->next = p;
			if(p == l->head)
				l->head = (*t);
			q->next = (*t);
			return; 
		}
		q = p;
		p = p->next;
	}
	if((*t)->d.freq > p->d.freq) {
		p->next = (*t);
		l->tail = (*t);
	}
	else {
		(*t)->next = p;
		q->next = (*t);
	}	
	return;
}
	
void buildtree(leaf *l, tree *t) {
	if(l->head != NULL && l->head == l->tail && l->head == (*t))
		return;
	node *temp;
	node *p;
	p = l->head;
	temp = (node*)malloc(sizeof(node));
	temp->d.ch = '\0';
	temp->d.freq = p->d.freq + p->next->d.freq;
	temp->left = p;
	temp->right = p->next;
	l->head = p->next->next;
	p->next = p->next->next = NULL;
	(*t) = temp;
	if(l->head == NULL) {
		printf("%d\n",(*t)->d.freq);
		return;
	}
	treeinsert(&(*l), &(*t));
	printf("%d\n",(*t)->d.freq);
	buildtree(&(*l), &(*t));
	return;
	
}
int main(int argc, char *argv[]) {
	leaf t;
	init(&t);
	if(argc < 4)
		printf("error : usage ./a <filenam1> <filename2> compress/decompress\n");
	int fdr, fdw;
	fdr = open(argv[1], O_RDONLY, S_IRUSR);
 	getfrequency(fdr);
	//sort(&t);
	//printtree(&t);
	return 0;
	
}




