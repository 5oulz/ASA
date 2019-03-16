typedef struct {
    int v;
    int w;
} Edge;

typedef struct graph *Graph;

Edge EDGE(int x, int y);
Graph GRAPHinit(int);
void GRAPHinsertE(Graph, Edge);
void GRAPHremoveE(Graph, Edge);
int GRAPHedges(Edge a[], Graph G);
Graph GRAPHcopy(Graph);
void GRAPHdestroy(Graph); 