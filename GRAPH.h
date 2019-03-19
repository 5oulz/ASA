typedef struct {
    int v;
    int w;
} Edge;

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

Edge EDGE(int x, int y);
typedef struct graph *Graph;
Graph GRAPHinit(int);
void GRAPHinsertE(Graph, Edge);
void GRAPHremoveE(Graph, Edge);
int GRAPHedges(Edge a[], Graph G);
Graph GRAPHcopy(Graph);
void GRAPHdestroy(Graph); 