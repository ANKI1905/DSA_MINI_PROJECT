typedef struct data{
	char ch; 
	int freq;
}data;
typedef struct node {
	data d;
	struct node *left, *next, *right;
}node;
typedef struct leaf {
	struct node *head, *tail;
}leaf;
typedef node *tree;
void init(leaf *t);
void tinit(tree *t);
void insert(leaf *t, char ch, int num);
int search(leaf *t, char ch);
void sort(leaf *t);
void buildtree(leaf *l, tree *t);
void treeinsert(leaf *l, tree *t);
