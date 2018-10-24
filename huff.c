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
	struct dataa *next;
}dataa;
typedef struct stack{
	struct dataa *head, *tail;
}stack;
void sinit(stack *s) {
	s->head = s->tail = NULL;
}
void printdata(stack *s);
char *searchchar(stack *s, char ch);
void compression(int fdr, int fdw);
void compress(int fdr, int fdw, stack *s);
void treeinsert(leaf *l, tree *t);
void getfrequency(int fdr, leaf *l);
void buildtree(leaf *l, tree *t);
void addata(data d, char *str, int pos, stack *s);
void traverse(tree t, char *str, int pos, stack *s);

 
int main(int argc, char *argv[]) {
	leaf t;
	stack *s;
	init(&t);
	if(argc < 4)
		printf("error : usage ./a <filenam1> <filename2> compress/decompress\n");
	int fdr, fdw;
	fdr = open(argv[1], O_RDONLY, S_IRUSR);
	if(fdr == -1)
		printf("erreor");
	fdw = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR);
	if(fdw == -1)
		printf("erreor");
	compression(fdr, fdw);
	return 0;
	
}
void printdata(stack *s){
	dataa *temp;
	temp = s->head;
	while (temp != NULL) {
		printf("%c", temp->ch);
		printf("%s\n",temp->str);
		temp = temp->next;
	}
}
char *searchchar(stack *s, char ch){
	dataa *temp;
	temp = s->head;
	while(temp != NULL) {
		if(temp->ch == ch) { 
			printf("got %c\n", ch);
			return temp->str;
		}
		else 
			temp = temp->next;
		
	}
}
void compression(int fdr, int fdw) {
	char str[100];
	int i;
	leaf l;
	tree t;
	tinit(&t);
	init(&l);
	stack s;
	sinit(&s);
	getfrequency(fdr, &l);
	sort(&l);
	i = length(&l);
	printtree(&l);
	buildtree(&l, &t);
	traverse(t, str, 0, &s);
	//printdata(&s);
	lseek(fdr, 0, SEEK_SET);
	compress(fdr, fdw, &s);
}
void compress(int fdr, int fdw, stack *s){
	int countbits = 0, i;
	int length;
	char ch, buffer;
	char stri[100];
	while(read(fdr, &ch, sizeof(ch))) {
		strcpy(stri, searchchar(&(*s), ch)); 
		length = strlen(stri);
		i = 0;
		while(i < length){
			if(stri[i] == 0)
				buffer = buffer & 11111110;
			else if(stri[i] == 1)
				buffer = buffer | 00000001;
			buffer = buffer << 1;
			countbits++;
			if(countbits == 8) {
				write(fdw, &buffer, sizeof(buffer));
				countbits = 0;
				printf("done");
			}
			i++;
		}
	}
}	
	
void getfrequency(int fdr, leaf *l) {
	char ch;
	int i = 0;
	int num = 0;
	char str[256];
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
	p = s->head;
	printf("%c - %s\n",d.ch, str);
	temp = (dataa *)malloc(sizeof(data));
	temp->ch = d.ch;
	strcpy(temp->str, str);
	if(s->head == NULL){
		s->head = s->tail = temp;
		temp->next = NULL;
		return;
	}
	while(p->next != NULL) 
		p = p->next;
		
	p->next = temp;
	temp->next = NULL;
	s->tail = temp;
}


