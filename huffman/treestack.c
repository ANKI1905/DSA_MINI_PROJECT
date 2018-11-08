#include<stdlib.h>
#include<stdio.h>
#include "treestack.h"
void dtinit(tree *t) {
	(*t) = NULL;
}
void dsinit(stack *s) {
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
void destroytree(tree t){
	if(t == NULL)
		return;
	destroytree(t->left);
	destroytree(t->right);
	free(t);
}					

