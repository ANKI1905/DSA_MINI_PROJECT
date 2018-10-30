#include "mytable.h"
#include<stdio.h>
#include<stdlib.h>
void dinit(dlist *l){
	int i;
	node *tmp;
	l->head = l->tail = NULL;
	for(i = 0; i < 256; i++) {
		tmp = (node *)malloc(sizeof(node));
		tmp->d.pos = i;
		tmp->d.prev = -1;
		tmp->d.ch = i;
		tmp->next = NULL;
		if(l->head == NULL){
			l->head = l->tail = tmp;
	
		}
		else {
			l->tail->next = tmp;
			l->tail = tmp;
		}
	}
}
int findchar(dlist *l, int prev, int ch){
	node *tmp;
	tmp = l->head;
	while(tmp){
		if(tmp->d.prev == prev && tmp->d.ch == ch)
			return tmp->d.pos;
		tmp = tmp->next;
	}
	return -1;
}
void adddata(dlist *l, data d){
	printf("%d %d %d\n", d.pos, d.prev, d.ch);
	node *tmp;
	tmp = (node *)malloc(sizeof(node));
	tmp->d.pos = d.pos;
	tmp->d.prev = d.prev;
	tmp->d.ch = d.ch;
	tmp->next = NULL;
	if(l->head == NULL){
		l->head = l->tail = tmp;
	}
	else {
		l->tail->next = tmp;
		l->tail = tmp;
	}
	return;
}

		
