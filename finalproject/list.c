#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sinit(list *s) {
	 s->i = 0;
}
char *searchchar(list *s, unsigned char ch){
	unsigned int i = ch;
	return (s->arr[i].str);
}
void addata(unsigned char ch, char *str, list *s){
	unsigned int i = ch;
	strcpy(s->arr[i].str, str);
	return;
}
	
