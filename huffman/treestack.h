typedef struct node{
	char ch;
	struct node *left, *right;
}node;
typedef node *tree;
typedef struct treestack{
	tree n;
	struct treestack *st;
}treestack;
typedef treestack *stack;
void dtinit(tree *t);
void dsinit(stack *s);
void push(stack *s, tree);
tree pop(stack *s);
int sisempty(stack *s);
void destroytree(tree t);
