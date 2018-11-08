typedef struct dataa{
	char str[256];
}dataa;
typedef struct list{
	dataa  arr[256];
	int i;
}list;
void sinit(list *s);
char *searchchar(list *s, char ch);
void addata(char ch, char *str, list *s);
	
