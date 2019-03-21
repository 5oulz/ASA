typedef struct {
    int v;
    int w;
} Edge;

typedef struct node *link;

struct node {
	int v;
	link next;
};

typedef struct graph *Graph;

struct graph {
	int V;
	int E;
	link *adj; /* array of lists */
};

typedef struct {
	int d;
	int f;
	int visited;
	int pred;
} Info;


Edge EDGE(int x, int y);
Graph GRAPHinit(int);
void GRAPHinsertE(Graph, Edge);
void GRAPHremoveE(Graph, Edge);
int GRAPHedges(Edge a[], Graph G);
Graph GRAPHcopy(Graph);
void GRAPHdestroy(Graph); 
void DFS(Graph G, Info *list);
void DFSaux(Graph G, Info *list, int i);