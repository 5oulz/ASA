#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

Edge EDGE(long x, long w) {
    Edge* temp = (Edge*)malloc(sizeof(Edge));
    temp->v = x;
    temp->w = w;
    return *temp;
}

link InsertBegin(long v, link head) {
    link x = malloc(sizeof(struct node));
    x->v = v;
    x->next = head;
    return x;
}

Graph GRAPHinit(long V) {
    long v;

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
    long v = e.v;
    long w = e.w;
    G->adj[v] = InsertBegin(w, G->adj[v]);
    G->adj[w] = InsertBegin(v, G->adj[w]);
    G->E++;
}



/**********
    DFS
**********/

void DFS(Graph G, Info *list) {
    for (int v = 0; v < G->V; v++) {
        list[v].f = 0;
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
    }

    for(int v = 1; v < G->V; v++) {
        if(list[v].visited == 0)
            DFSaux(G, list, v);
    }
}


Stack* reverseDFS(Graph G, Info *list, long size) {
    Stack* s = createStack(size);

    for (long v = 0; v < G->V; v++) {
        list[v].f = 0;
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
    }

    for(int v = G->V - 1; v > 0; v--) {
        if(list[v].visited == 0) {
            stackPush(s, v);
            DFSaux(G, list, v);
        }
    }
    return s;
}


void DFSaux(Graph G, Info *list, long u) {
    static int time = 1;
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


/** ----------------------**/

void tarjan(Graph G, Info *list) {
    for (long v = 0; v < G->V; v++) {
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
        list[v].low = 0;
        list[v].ap = 0;
    }

    for(long v = 1; v < G->V; v++) {
        if(list[v].visited == 0)
            tarjanAux(G, list, v);
    }
}

void tarjanAux(Graph G, Info *list, long u) {
    static int time = 0;
    long children = 0;
    list[u].visited = 1;
    time = time + 1;
    list[u].d = time;
    list[u].low = time;
    
    for (link p = G->adj[u]; p != NULL; p = p->next) {
        int v = p->v;
        if(list[v].visited == 0) {
            children++;
            list[v].pred = u;
            tarjanAux(G, list, v);

            list[u].low = MIN(list[u].low, list[v].low);

            if(list[u].pred == 0 && children > 1) {
                list[u].ap = 1;
            }

            if(list[u].pred != 0 && list[v].low >= list[u].d) {
                list[u].ap = 1;
            }
        }
        else if (v != list[u].pred)
            list[u].low = MIN(list[u].low, list[v].d);
    }
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