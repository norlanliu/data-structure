/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  graph structure
 *
 *        Version:  1.0
 *        Created:  09/28/2013 10:01:45 AM
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
#include	"graph.h"

static int discovered[GRAPH_MAX];
static int parent[GRAPH_MAX];

/* *
 * Initial a graph
 * */
void InitialGraph(graph *g, int directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	
	int i;
	for(i = 0; i < GRAPH_MAX; i++)
		g->edges[i] = NULL;
}

void ReadGraph(graph *g, int directed)
{
	int i, nedges, x, y;
	InitialGraph(g, directed);

	scanf("%d %d", &(g->nvertices), &nedges);
	for(i = 0; i < nedges; i++)
	{
		scanf("%d %d", &x, &y);
		InsertGraph(g, x, y, z, directed);
	}
}
void InsertWeightGraph(graph *g, int x, int y, int weight, int directed)
{
	int i, nedges, x, y, z;
	InitialGraph(g, directed);

	scanf("%d %d", &(g->nvertices), &nedges);
	for(i = 0; i < nedges; i++)
	{
		scanf("%d %d %d", &x, &y, &z);
		InsertWeightGraph(g, x, y, z, directed);
	}
}
/*
 * insert an edge into a graph.
 */
void InsertGraph(graph *g, int x, int y, int directed)
{
	if(g == NULL)
		return;
	node *new_node = (node *)malloc(sizeof(node));
	new_node->num = y;
	new_node->weight = 0;
	new_node->next = g->edges[x];

	g->edges[x] = new_node;
	
	if(!directed)
		InsertGraph(g, y, x, !directed);
	else
		g->nedges++;
}

void InsertWeightGraph(graph *g, int x, int y, int weight, int directed)
{
	if(g == NULL)
		return;
	node *new_node = (node *)malloc(sizeof(node));
	new_node->num = y;
	new_node->weight = weight;
	new_node->next = g->edges[x];

	g->edges[x] = new_node;
	
	if(!directed)
		InsertGraph(g, y, x, !directed);
	else
		g->nedges++;

}
/*
 * print the graph
 */
void PrintGraph(graph *g)
{
	int nv = g->nvertices;
	int i;
	node *temp;
	for(i = 1; i <= nv; ++i)
	{
		printf("%d: ", i);
		temp = g->edges[i];
		while(temp != NULL)
		{
			printf("%d ", temp->num);
			temp = temp->next;
		}
		printf(".\n");
	}
}
void FreeGraph(graph *g)
{
	int i;
	node *temp;
	for(i = 0; i < GRAPH_MAX; i++)
		if(g->edges[i] != NULL)
		{
			temp = g->edges[i];
			while(temp != NULL)
			{
				g->edges[i] = temp->next;
				free(temp);
				temp = g->edges[i];
			}
		}
}
static void enqueue(int *q, int x, int *tailer)
{
	q[(*tailer)++] = x;
}
static int dequeue(int *q, int *header)
{
	return q[(*header)++];
}
static void process_edge(int first, int second)
{
	printf("process edge : %d %d\n", first, second);
}

void InitializeSearch(graph *g)
{
	int i;
	for(i = 0; i < g->nvertices; i++)
	{
		discovered[i] = 0;
		parent[i] = -1;
	}
}
void BFS(graph *g, int starter)
{
	//temp variables
	int queue[GRAPH_MAX];
	int header = 0, tailer = 0;

	discovered[starter] = 1;
	enqueue(queue, starter, &tailer);
	int temp;
	node *cur_node;
	while(header != tailer)
	{
		temp = dequeue(queue, &header);
		if(discovered[temp] != 2)
		{
			cur_node = g->edges[temp];
			while(cur_node != NULL)
			{
				if(discovered[cur_node->num] != 2)
					process_edge(temp, cur_node->num);
				if(discovered[cur_node->num] == 0)
				{
					discovered[cur_node->num] = 1;
					enqueue(queue, cur_node->num, &tailer);
					parent[cur_node->num] = temp;
				}
				cur_node = cur_node->next;
			}
			discovered[temp] = 2;
		}
	}
}
void DFS(graph *g, int starter)
{
	discovered[starter] = 1;
	int i;
	node *temp = g->edges[starter];
	while(temp != NULL)
	{
		if(discovered[temp->num] == 0)
		{
			parent[temp->num] = starter;
			process_edge(starter, temp->num);
			DFS(g, temp->num);
		}
		else if((discovered[temp->num] != 2) || g->directed)
			process_edge(starter, temp->num);
		temp = temp->next;
	}
	discovered[starter] = 2;
}
int Prim(graph *g, int starter)
{
	int *data = (int *)malloc(g->nvertices * 4);
	int vertices[GRAPH_MAX];
	int i, j, size;
	int temp_vertice, temp_weight;
	int max; 
	int distance;
	node *temp_node;

	size = 1;
	distance = 0;
	data[0] = starter;
	vertices[starter] = 1;
	for(i = 0; i < g->nvertices; ++i)
	{
		max = INT_MAX;
		for(j = 0; j < size; ++j)
		{
			temp_node = g->edges[data[j]];
			while(temp_node != NULL)
			{
				if(vertices[temp_node->num] != 1 && temp_node->weight < max)
				{
					max = temp_node->weight;
					temp_vertice = temp_node->num;
					temp_weight = temp_node->weight;
				}
				temp_node = temp_node->next;
			}
		}
		data[i+1] = temp_vertice;
		vertices[temp_vertice] = 1;
		distance += temp_weight;
		size++;
	}
	for(i = 0; i < g->nvertices; ++i)
		printf("%d\n", data[i]);
	return distance;
}
