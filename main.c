#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"

/**
 * printGraph - debug function to print the graph
 * @Graph G - graph to print
 */
void printGraph(Graph G, Info *list) {
	printf("--------------------------------------------\n");
    printf("Nodes: %ld\n", G->V - 1);
    printf("Edges: %ld\n\n", G->E);
    puts("Graph edges");

    for(long z = 1; z < G->V; z++) {
        printf("Edge %ld connections: ", z);

        for(link k = G->adj[z]; k != NULL;  ) {
            printf("%ld", k->v);
            k = k->next;
            if(k != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }

    printf("\n");
    for(long z = 1; z < G->V; z++) {
    	Info node = list[z];
    	printf("router %ld\n", z);
    	printf("d %ld, f %ld\n", node.d, node.f);
    	printf("predecessor %ld\n", node.pred);
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
    long int N, M;
    Graph routerG;

    scanf("%ld", &N);
    scanf("%ld", &M);

    long j = 0, temp[2];

    /** init graph */
    routerG = GRAPHinit(N+1);

    /** scan input */
    while(j < M) {
        scanf("%ld %ld", &temp[0], &temp[1]);
        GRAPHinsertE(routerG, EDGE(temp[0], temp[1]));
        j++;
    }


    /** primeira resposta ao output **/
    Info* list = (Info*)malloc((N+1)*sizeof(Info));

  	DFS(routerG, list);
    tarjan(routerG, list);

  	int subredes = 0;
  	int ap = 0;
	for(int z = 1; z < routerG->V; z++) {
    	Info node = list[z];
    	if (node.pred == 0)
    		subredes++;
    	if (list[z].ap == 1)
    		ap++;
    }

  	Stack *id = reverseDFS(routerG, list, subredes);

    /** comment later, just for debug */
    //printGraph(routerG, list);

    printf("%d\n", subredes);
    for (int i = 0; i < id->size; i++) {
    	if (i == id->size - 1)
    		printf("%d\n", stackPop(id));
    	else
    		printf("%d ", stackPop(id));
    }
    printf("%d\n", ap);


    return 0;
}