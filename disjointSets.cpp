#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
	int src; 
	int dst;
}Edge;

typedef struct Graph{
	int vCount; 
	int eCount; 
	Edge * edges; 
}Graph;

Graph * createGraph (int vCount, int eCount){
	Graph * newGraph = (Graph*)malloc(sizeof(Graph)); 
	newGraph->vCount = vCount; 
	newGraph->eCount = eCount; 
	newGraph->edges = (Edge*)malloc(sizeof(Edge)*eCount); 
//	newGraph->edges = (Edge*)calloc(eCount, sizeof(Edge)); 
	
	return newGraph;
}

void printEdge(Graph * g){
	for(int i=0; i<g->eCount; i++){
		printf("Src: %d, Dst: %d\n", g->edges[i].src, g->edges[i].dst );
	}
}

void makeSet(int *parent, int i){
	parent[i] = i; 
}

int findParent(int *parent, int toFind){
	if(parent[toFind] == toFind){
		return toFind; 
	} else {
		return parent[toFind] = findParent(parent, parent[toFind]); 
	}
}

void unionSet(int *parent, int src, int dst){
	parent[src] = dst; 
}

bool isCyclic(Graph*g){
	int parent[g->vCount+1];

	for(int i=1; i <= g->vCount; i++){
		makeSet(parent, i); 
	}

	for(int i=0; i<g->eCount; i++){
		int src = g->edges[i].src; 
		int dst = g->edges[i].dst; 

		int srcParent = findParent(parent, src); 
		int dstParent = findParent(parent, dst);

		if(srcParent != dstParent){
			unionSet(parent, srcParent, dstParent);
		} else {
			return true; 
		}
	}
	return false; 
}

int main(){
	Graph * graph1 = createGraph(4, 4); 
	graph1->edges[0].src = 1;
	graph1->edges[0].dst = 2; 
	
	graph1->edges[1].src = 1;
	graph1->edges[1].dst = 3;
	
	graph1->edges[2].src = 1;
	graph1->edges[2].dst = 4; 
	
	graph1->edges[3].src = 3;
	graph1->edges[3].dst = 4;  
	
	printEdge(graph1);  	

	puts(""); 
	printf("graph is %s.\n",isCyclic(graph1)? "Cyclic":"not Cyclic"); 

	return 0; 
}
