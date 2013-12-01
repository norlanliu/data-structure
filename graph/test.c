/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/28/2013 10:20:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (Qi Liu), liuqi.edward@gmail.com
 *   Organization:  antq.com
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include	"graph.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	graph g;
	ReadGraph(&g, 0);
	printf("min spanning tree distance: %d\n", Prim(g, 1));
	PrintGraph(&g);
	InitialGraph(g);
	BFS(&g, 1);
	FreeGraph(&g);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
