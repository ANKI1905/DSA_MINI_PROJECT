#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sinit(list *s) {
	 s->i = 0;
}
char *searchchar(list *s, char ch){
	int i = ch;
	return (s->arr[i].str);
}
void addata(char ch, char *str, list *s){
	int i = ch;
	strcpy(s->arr[i].str, str);
	return;
}
	
