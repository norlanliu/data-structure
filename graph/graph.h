#ifndef DATASTRUCTURE_GRAPH_
#define DATASTRUCTURE_GRAPH_

#define GRAPH_MAX 100
//graph structure : linked list
typedef struct _node
{
	int num;
	int weight;
	struct _node *next;
}node;

typedef struct _graph
{
	node *edges[GRAPH_MAX];
	int nvertices;
	int nedges;
	int directed;
}graph;

extern void InitialGraph(graph *g, int directed);

extern void ReadGraph(graph *g, int directed);

extern void PrintGraph(graph *g);

extern void InsertGraph(graph *g, int x, int y, int directed);

extern void InsertWeightGraph(graph *g, int x, int y, int weight, int directed);

extern void FreeGraph(graph *g);

extern void InitializeSearch(graph * g);

extern void BFS(graph *g, int starter);

extern void DFS(graph *g, int starter);

extern int Prim(graph *g, int starter);
#endif
