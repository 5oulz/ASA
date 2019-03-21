typedef struct {
    long v;
    long w;
} Edge;

typedef struct node *link;

struct node {
	long v;
	link next;
};

typedef struct graph *Graph;

struct graph {
	long V;
	long E;
	link *adj; /* array of lists */
};

typedef struct {
	long d;
	long f;
	long visited;
	long pred;
	long low;
	long ap;
} Info;


typedef struct { 
    int top; 
    long size; 
    int *list; 
} Stack;


Edge EDGE(long x, long y);
Graph GRAPHinit(long);
void GRAPHinsertE(Graph, Edge);
void GRAPHremoveE(Graph, Edge);
int GRAPHedges(Edge a[], Graph G);
Graph GRAPHcopy(Graph);
void GRAPHdestroy(Graph); 
void DFS(Graph G, Info *list);
void DFSaux(Graph G, Info *list, long i);
Stack* reverseDFS(Graph G, Info *list, long size);

Stack* createStack(long size);
int stackEmpty(Stack* s);
int stackFull(Stack* s);
int stackPop(Stack* s);
void stackPush(Stack* s, int data);
int stackPeek(Stack* s);
int isStack(Stack* s, int data);

void tarjan(Graph G, Info *list);
void tarjanAux(Graph G, Info *list, long u);