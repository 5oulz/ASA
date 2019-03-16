#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"

typedef struct node *link;

struct node {
	int v;
	link next;
};

struct graph {
	int V;
	int E;
	link *adj;
};

link InsertBegin(int v, link head) {
    link x = malloc(sizeof(struct node));
    x->v = v;
    x->next = head;
    return x;
}

Graph GRAPHinit(int V) {
    int v;

    Graph G = malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    G->adj = malloc(V * sizeof(link));

    for (v = 0; v < V; v++) {
        G->adj[v] = NULL;
    }
    return G;
}

void GRAPHinsertE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    G->adj[v] = InsertBegin(w, G->adj[v]);
    G->adj[w] = InsertBegin(v, G->adj[w]);
    G->E++;
}

void GRAPHremoveE(Graph G, Edge e){

}

/*int GRAPHedges(Edge a[], Graph G) {
    int v, E = 0;
    link t;

    for (v = 0; v < G->V; v++) {
        for (t = G->adj[v]; t != NULL; t = t->next) {
            if (v < t->v ) {
                a[E++] = EDGE(v, t->v);
            }
        }
    }

    return E;
}*/

int main() {
    int temp = 10; /** replace temp for V */

    Graph mainGraph = GRAPHinit(temp);
    
    return 0;
}