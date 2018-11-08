#include "table.h"
#include<stdio.h>
#include<stdlib.h>
#define EMPTY -1

void init(table *t){
	int i;
	node *tmp;
	for(i = 0; i < 256; i++){
		tmp = (node *)malloc(sizeof(node));
		tmp->prefix = EMPTY;
		tmp->ch = i;
		tmp->ptr = NULL;
		tmp->i = 0;
		tmp->maloc = 0;
		t->arr[i] = tmp;
	}
	for(i = 256; i < 4096; i++){
		t->arr[i] = NULL;
	}
	return;
}
void addata(table *t, int prefix, char ch, int pos){
	node *p;
	p = t->arr[prefix];
	if(p->ptr == NULL){
		p->ptr = (int *)malloc(10 * sizeof(int));
		p->i = 0;
		p->maloc = 10;
	}
	else if(p->i == p->maloc){
		p->ptr = realloc(p->ptr, (10 + p->maloc)*(sizeof(int)));
		p->maloc = p->maloc + 10;
		
	}
	node *tmp;
	tmp = (node *)malloc(sizeof(node));
	tmp->prefix = prefix;
	tmp->ch = ch;
	tmp->ptr = NULL;
	tmp->i = 0;
	tmp->maloc = 0;
	t->arr[pos] = tmp;
	p->ptr[p->i] = pos;
	p->i++;
}
int search(table *t, int prefix, char ch){
	int j;
	int pos;
	node *p;
	p = t->arr[prefix];
	if(p->ptr == NULL)
		return prefix;
	for(j = 0; j < p->i; j++){
		pos = p->ptr[j];
		if(t->arr[pos]->ch == ch)
			return pos;
	}
	return prefix;
} 
	 
void destroytable(table *t){
	int i;
	int *p;
	node *q;
	while(i < 4096 && t->arr[i] != NULL){
		q = t->arr[i];
		p = t->arr[i]->ptr;
		q->ptr = NULL;
		if(p != NULL)
			free(p);
		t->arr[i] = NULL;
		free(q);
		i++;
	}
		
	
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
	return chr;
}
