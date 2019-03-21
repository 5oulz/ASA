#include <stdlib.h>
#include <stdio.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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

Stack* createStack(long size) {
   Stack* s = (Stack*) malloc(sizeof(Stack));
   s->size = size;
   s->top = -1;
   s->list = (int*) malloc(size*sizeof(int));
   return s;
}

int stackPeek(Stack* s) {
   return s->list[s->top];
}

int isStack(Stack* s, int data) {
   int t = s->top;
   while ((s->list[t] != data) && (t != -1)) {
      if (s->list[t] == data)
         return 1;
      t = t - 1;
   }
   return 0;
}

int stackEmpty(Stack* s) {
   if(s->top == -1)
      return 1;
   else
      return 0;
}
   
int stackFull(Stack* s) {
   if(s->top == s->size)
      return 1;
   else
      return 0;
}

int stackPop(Stack* s) {
   if(!stackEmpty(s)) {
      return s->list[s->top--];
   } 
   return -1;
}

void stackPush(Stack* s, int data) {
   if(!stackFull(s)) {
      s->top = s->top + 1;   
      s->list[s->top] = data;
   }
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
    int v;
    for (v = 0; v < G->V; v++) {
        list[v].f = 0;
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
    }

    for(v = 1; v < G->V; v++) {
        if(list[v].visited == 0)
            DFSaux(G, list, v);
    }
}


Stack* reverseDFS(Graph G, Info *list, long size) {
    Stack* s = createStack(size);
    long v;

    for (v = 0; v < G->V; v++) {
        list[v].f = 0;
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
    }

    for(v = G->V - 1; v > 0; v--) {
        if(list[v].visited == 0) {
            stackPush(s, v);
            DFSaux(G, list, v);
        }
    }
    return s;
}


/** ----------------------**/

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

void tarjan(Graph G, Info *list) {
    long v;
    for (v = 0; v < G->V; v++) {
        list[v].d = 0;
        list[v].pred = 0;
        list[v].visited = 0;
        list[v].low = 0;
        list[v].ap = 0;
    }

    for(v = 1; v < G->V; v++) {
        if(list[v].visited == 0)
            tarjanAux(G, list, v);
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

/**
 * printGraph - debug function to print the graph
 * @Graph G - graph to print
 */
void printGraph(Graph G, Info *list) {
	printf("--------------------------------------------\n");
    printf("Nodes: %ld\n", G->V - 1);
    printf("Edges: %ld\n\n", G->E);
    puts("Graph edges");
    long z;

    for(z = 1; z < G->V; z++) {
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
    for(z = 1; z < G->V; z++) {
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
    /*printGraph(routerG, list);*/

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