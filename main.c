#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"

/**
 * printGraph - debug function to print the graph
 * @Graph G - graph to print
 */
void printGraph(Graph G, Info *list) {
	printf("--------------------------------------------\n");
    printf("Nodes: %d\n", G->V - 1);
    printf("Edges: %d\n\n", G->E);
    puts("Graph edges");

    for(int z = 1; z < G->V; z++) {
        printf("Edge %d connections: ", z);

        for(link k = G->adj[z]; k != NULL;  ) {
            printf("%d", k->v);
            k = k->next;
            if(k != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }

    printf("\n");
    for(int z = 1; z < G->V; z++) {
    	Info node = list[z];
    	printf("router %d\n", z);
    	printf("d %d, f %d\n", node.d, node.f);
    	printf("predecessor %d\n", node.pred);
    	printf("\n");
    }
    printf("--------------------------------------------\n");
    return;
}

int main(int argc, char** argv) {
    /**
    * N - number of routers
    * M - number of connections
    * */
    int N, M;
    Graph routerG, forestG;

    scanf("%d", &N);
    scanf("%d", &M);

    int j = 0, temp[2];

    /** init graph */
    routerG = GRAPHinit(N+1);

    /** scan input */
    while(j < M) {
        scanf("%d %d", &temp[0], &temp[1]);
        GRAPHinsertE(routerG, EDGE(temp[0], temp[1]));
        j++;
    }

    /** init DFS list **/
    Info list[N+1];
    for (int v = 0; v < N+1; v++) {
    	list[v].f = 0;
    	list[v].d = 0;
    	list[v].pred = 0;
    	list[v].visited = 0;
    }

    /** primeira resposta ao output **/
  	DFS(routerG, list);
  	forestG = GRAPHinit(N+1);
  	int subredes = 0;
	for(int z = 1; z < routerG->V; z++) {
    	Info node = list[z];
    	if (node.pred != 0)
    		GRAPHinsertE(forestG, EDGE(node.pred, z));
    	else
    		subredes++;
    }

    /** comment later, just for debug */
    printGraph(routerG, list);   
    printGraph(forestG, list);     
    return 0;
}