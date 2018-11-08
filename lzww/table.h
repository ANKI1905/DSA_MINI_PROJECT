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
void init(table *t);
void addata(table *t, int prefix, char ch, int pos);
int search(table *t, int prefix, char ch);
void destroytable(table *t);
int getchr(table *t, int curr);
int get(table *t,int prev);
