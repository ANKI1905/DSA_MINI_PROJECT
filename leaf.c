#include "leaf.h"
#include<stdio.h>
#include<stdlib.h>
void init (leaf *t){
	t->head = t->tail = NULL;
}
void tinit(tree *t){
	(*t) == NULL;
}
void insert(leaf *t, char ch, int num){
	node *temp, *p;
	temp = (node *)malloc(sizeof(node));
	temp->d.ch = ch;
	temp->d.freq = 1;
	if(t->head == NULL) {
		t->head = t->tail = temp;
		temp->left = NULL;
		temp->right = temp->next = NULL;
		return;
	}
	p = t->head;
	temp->next = t->head;
	temp->left = temp->right = NULL;
	t->head = temp;
	printf("%c",temp->d.ch);
}
	
	
int search(leaf *t, char ch) {
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
int length(leaf *t) {
	node *p;
	p = t->head;
	int i = 0;
	while(p != NULL){
		i++;
		p = p->next;
	}
	return i;
}
void printtree(leaf *t){
	node *p;
	p = t->head;
	while(p != NULL) {	
			printf("%c %d\n", p->d.ch, p->d.freq);
			p = p->next;
	}
		
}
	

void sort(leaf *t){
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
