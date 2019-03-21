#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"

Edge EDGE(int x, int w) {
    Edge* temp = (Edge*)malloc(sizeof(Edge));
    temp->v = x;
    temp->w = w;
    return *temp;
}

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
    int v = e.v;
    int w = e.w;
    G->adj[v] = InsertBegin(w, G->adj[v]);
    G->adj[w] = InsertBegin(v, G->adj[w]);
    G->E++;
}


/** a variavel precisa de ser global
   por causa da recursao (Causa problemas) **/
int time = 1;

void DFS(Graph G, Info *list) {
    for(int v = 1; v < G->V; v++) {
        if(list[v].visited == 0)
            DFSaux(G, list, v);
    }
}


void DFSaux(Graph G, Info *list, int u) {
    list[u].visited = 1;
    list[u].d = time;
    time = time + 1;
    
    for (link p = G->adj[u]; p != NULL; p = p->next) {
        int v = p->v;
        if(list[v].visited == 0) {
            list[v].pred = u;
            DFSaux(G, list, v);
        }
    }

    list[u].visited = 2;
    list[u].f = time;
    time = time + 1;
}


/**
void GRAPHremoveE(Graph G, Edge e){

}

int GRAPHedges(Edge a[], Graph G) {
    int v, E = 0;
    link t;

    for (v = 0; v < G->V; v++) {
        for (t = G->adj[v]; t != NULL; t = t->next) {
            if (v < t->v) {
                a[E++] = EDGE(v, t->v);
            }
        }
    }
    return E;
}  **/