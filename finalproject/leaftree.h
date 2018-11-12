typedef struct data{
	unsigned char ch; 
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
void insert(leaf *t, unsigned char ch, int num);
int search(leaf *t, unsigned char ch);
void sort(leaf *t);
void buildtree(leaf *l, tree *t);
void treeinsert(leaf *l, tree *t);
void destroytree(tree t);
