#include "leaftree.h"
#include<stdio.h>
#include<stdlib.h>
void init (leaf *t){
/*initialising leaf nodes*/
	t->head = t->tail = NULL;
}
void tinit(tree *t){
/*initialise tree*/
	(*t) = NULL;
}
void destroytree(tree t){
/*destroy huffman tree when its use is complete*/
	if(t == NULL)
		return;
	destroytree(t->left);
	destroytree(t->right);
	free(t);
}					
void insert(leaf *t, unsigned char ch, int num){
/*insert the character encountered during file reading*/
	node *temp;
	temp = (node *)malloc(sizeof(node));
	temp->d.ch = ch;
	temp->d.freq = 1;
	if(t->head == NULL) {
		t->head = t->tail = temp;
		temp->left = NULL;
		temp->right = temp->next = NULL;
		return;
	}
	temp->next = t->head;
	temp->left = temp->right = NULL;
	t->head = temp;
}
int search(leaf *t, unsigned char ch) {
/*search the character whether it exists in list or not*/
	node *p;
	p = t->head;
	while(p != NULL) {
		if(p->d.ch == ch) {
			(p->d.freq)++;
			return p->d.freq;
		}
		else 
			p = p->next;
	}
	return 0;
}
void sort(leaf *t){
/*sort the list acording to frequency*/
	node *p, *q;
	p = t->head;
	data temp;
	while (p != NULL) {
		q = p->next;
		while(q != NULL){
			if(p->d.freq > q->d.freq) {
				temp = p->d;
				p->d = q->d;
				q->d = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
	return;
}
void treeinsert(leaf *l, tree *t) {
/*buiding tree and inserting it inlist*/
	node *p, *q;
	p = l->head;
	q = NULL;
	while(p != NULL){
		if((*t)->d.freq < p->d.freq) {
			(*t)->next = p;
			if(p == l->head)
				l->head = (*t);
			if(q != NULL)
				q->next = (*t);
			return; 
		}
		q = p;
		p = p->next;
	}
	q->next = (*t);
	(*t)->next = NULL;
	l->tail = (*t);	
	return;
}
void buildtree(leaf *l, tree *t) {
/*build the tree from list*/
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
		return;
	}
	treeinsert(&(*l), &(*t));
	buildtree(&(*l), &(*t));
	return;
	
}
