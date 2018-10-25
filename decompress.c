#include<stdio.h>	
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>


typedef struct node{
	char ch;
	struct node *left, *right;
}node;
typedef node *tree;
typedef struct treestack{
	tree n;
	struct treestack *st;
}treestack;
typedef treestack *stack;
void buildtree(int fdr, tree *t);
void decode(int fdr, int fdw, tree *t);
void inorder(tree t);
void tinit(tree *t) {
	(*t) = NULL;
}
void sinit(stack *s) {
	(*s) = NULL;
}
void push(stack *s, tree t){
	treestack *tmp;
	tmp = (treestack *)malloc(sizeof(treestack));
	tmp->n = t;
	tmp->st = (*s);
	(*s) = tmp;
}
tree pop(stack *s){
	tree t;
	t = (*s)->n;
	(*s) = (*s)->st;
	return t;
}
int sisempty(stack *s) {
	return ((*s) == NULL);
}	
	
int main(int argc, char *argv[]) {
	int fdr, fdw;
	char str[100];
	tree t;
	tinit(&t);
	stack s;
	sinit(&s);
	fdr = open(argv[1], O_RDONLY, S_IRUSR);
	fdw = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	buildtree(fdr, &t);
	lseek(fdr, -1, SEEK_CUR);
	decode(fdr, fdw, &t);
	
}
	
	
void buildtree(int fdr, tree *t) {
	tree temp;
	int i = 0;
	char ch;
	stack s;
	sinit(&s);
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
	char  ch, c, cht;
	int num = 0;
	node *p;
	p = (*t);
	int i;
	while(read(fdr, &ch, sizeof(ch))) {
		num = 0;
		while(num <= 7){
			i = ch & 10000000;
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
	}
}
					
					
	
		
