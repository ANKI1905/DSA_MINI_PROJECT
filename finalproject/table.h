typedef struct node{
	int prefix;
	char ch;
	int *ptr;
	int i;
	int maloc;
}node;
typedef struct table{
	node *arr[4096];
}table;
void tlinit(table *t);
void taddata(table *t, int prefix, char ch, int pos);
int tsearch(table *t, int prefix, char ch);
void tdestroytable(table *t);
int getchr(table *t, int curr);
int get(table *t,int prev);
