/*
 * =====================================================================================
 *
 *       Filename:  bst.c
 *
 *    Description:  binary search tree
 *
 *        Version:  1.0
 *        Created:  09/03/2013 11:10:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (Qi Liu), liuqi.edward@gmail.com
 *   Organization:  antq.com
 *
 * =====================================================================================
 */
#include	<stdlib.h>
#include	<stdio.h>
#include	"bst.h"
/*
 * insert a element in the tree
 */
BStree *insert_tree(BStree *tree, BStree *parent, item_type element)
{
	if(tree == NULL)
	{
		tree = (BStree *)malloc(sizeof(BStree));
		tree->element = element;
		tree->parent = parent;
		tree->right = tree->left = NULL;
		if(parent != NULL)
		{
			if(element < parent->element)
				parent->left = tree;
			else
				parent->right = tree;
		}
		return tree;
	}
	else if( element < tree->element)
		return insert_tree(tree->left, tree, element);
	else if( element > tree->element)
		return insert_tree(tree->right, tree, element);
	else
		return tree;
}
BStree *find_min(BStree *tree)
{
	if(tree == NULL)
		return NULL;
	if(tree->left != NULL)
		return find_min(tree->left);
	return
		tree;
}
/*
 * find the max element of the tree's chidren.
 */
BStree *find_max(BStree *tree)
{
	if(tree == NULL)
		return NULL;
	if(tree->right != NULL)
		return find_max(tree->right);
	else
		return tree;
}
/*
 * judge whether the node is a leaf.
 */
short is_leaf(BStree *tree)
{
	if(tree->left == NULL && tree->right == NULL)
		return 1;
	return 0;
}
/*
 * replace the node's element with max elment of his children.
 */
BStree *replace_with_max(BStree *tree)
{
	if(is_leaf(tree))
		return tree;
	else if(tree->left != NULL)
	{
		BStree *tmp = find_max(tree->left);
		tree->element = tmp->element;
		return replace_with_max(tmp);
	}
	else
	{
		BStree *tmp = find_min(tree->right);
		tree->element = tmp->element;
		return replace_with_max(tmp);
	}
}
void delete_tree(BStree *tree, item_type element)
{
	if(tree == NULL)
		return;
	else if(element == tree->element)
	{
		BStree *tmp = replace_with_max(tree);
		if(tmp != NULL && tmp->parent != NULL)
		{
			if(tmp->parent->left == tmp)
				tmp->parent->left = NULL;
			else
				tmp->parent->right = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
	else if(element < tree->element)
		delete_tree(tree->left, element);
	else
		delete_tree(tree->right, element);
}
/*
 * find the element in the tree
 */
BStree *find_tree(BStree *tree, item_type element)
{
	if(tree == NULL)
		return NULL;
	else if(element == tree->element)
		return tree;
	else if(element < tree->element)
		return find_tree(tree->left, element);
	else
		return find_tree(tree->right, element);
}
/*
 * print all of the node of the tree.
 */
void print_tree(BStree *tree)
{
	if(tree == NULL)
		return;
	else
		printf("%d\n", tree->element);
	print_tree(tree->left);
	print_tree(tree->right);
}
void clear(BStree *tree)
{
	if(tree == NULL)
		return;
	else if(is_leaf(tree))
	{
		if(tree->parent == NULL)
			;
		else if(tree->parent->left == tree)
			tree->parent->left = NULL;
		else
			tree->parent->right = NULL;
		free(tree);
		tree = NULL;
	}
	else 
	{
		clear(tree->left);
		clear(tree->right);
		free(tree);
		tree = NULL;
	}
}
