#ifndef _BSTREE
#define _BSTREE
typedef int item_type;

struct bstree {
	item_type element;
	struct bstree *parent;
	struct bstree *left;
	struct bstree *right;
};				/* ----------  end of struct bstree  ---------- */

typedef struct bstree BStree;
/*
 * insert a element
 */

BStree * insert_tree(BStree *tree, BStree *parent, item_type element);

void delete_tree(BStree *root, item_type element);

BStree *find_tree(BStree *root, item_type elment);

void print_tree(BStree *tree);

void clear(BStree *tree);
#endif
