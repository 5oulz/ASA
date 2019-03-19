#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"

/**
 * printGraph - debug function to print the graph
 * @Graph G - graph to print
 */
void printGraph(Graph G) {
    printf("Nods: %d\n", G->V - 1);
    printf("Edges: %d\n", G->E);
    puts("Graph edges:");

    for( int z = 1; z < G->V; z++ ) {
        printf("Edge %d connections: ", z);
        for( link k = G->adj[z]; k != NULL; ) {
            printf("%d", k->v);
            k = k->next;
            if( k != NULL ) {
                printf(", ");
            }
        }
        printf("\n");
    }
    return;
}

int main(int argc, char** argv) {
    /**
    * N - number of routers
    * M - number of connections
    * */
    int N, M;
    Graph routerG;

    scanf("%d", &N);
    scanf("%d", &M);

    int j = 0, temp[2];

    /** init graph */
    routerG = GRAPHinit(N+1);

    /** scan input */
    while(j<M) {
        scanf("%d %d", &temp[0], &temp[1]);
        GRAPHinsertE(routerG, EDGE(temp[0], temp[1]));
        j++;
    }

    /** comment later, just for debug */
    printGraph(routerG);
    
    return 0;
}