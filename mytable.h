typedef struct data{
	int pos;
	int prev;
	int ch;
}data;
typedef struct node {
	data d;
	struct node *next;
}node;
typedef struct dlist{
	 node *head, *tail;
}dlist;
void dinit(dlist *l);
int findchar(dlist *l, int prev, int ch);
void adddata(dlist *l, data d);
