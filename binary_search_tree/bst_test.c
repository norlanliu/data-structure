/*
 * =====================================================================================
 *
 *       Filename:  bst_test.c
 *
 *    Description:  test for binary search tree.
 *
 *        Version:  1.0
 *        Created:  09/03/2013 02:23:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (Qi Liu), liuqi.edward@gmail.com
 *   Organization:  antq.com
 *
 * =====================================================================================
 */


#include	<stdio.h>
#include	<stdlib.h>
#include	"bst.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	BStree *root = NULL;
	printf("insert the data 1 7 4 8 3 6 5\n");
	root = insert_tree(root, NULL, 2);
	delete_tree(root, 2);
	root = NULL;
	root = insert_tree(root,NULL, 2);
	insert_tree(root, NULL, 1);
	insert_tree(root, NULL, 7);
	insert_tree(root, NULL, 4);
	insert_tree(root, NULL, 8);
	insert_tree(root, NULL, 3);
	insert_tree(root, NULL, 6);
	insert_tree(root, NULL, 5);

	print_tree(root);

	printf("delete 7\n");
	delete_tree(root, 7);
	print_tree(root);
	printf("delete 2\n");
	delete_tree(root, 2);
	print_tree(root);

	printf("find 8\n");
	printf("%d\n", find_tree(root, 8)->element);
	clear(root);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
