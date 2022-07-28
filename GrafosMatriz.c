#include <stdio.h>
#include <stdlib.h>

typedef struct {int v; int w;} Aresta;
// cria uma aresta (v,w)

//estrutura de matriz adjacencia.
struct grafo {
    int **matriz;
    int v;//quantidade de vértices maximo
};

typedef struct grafo * Grafo;

//cria uma aresta
Aresta ARESTA(int v,int w){
    Aresta a;
    a.v = v;
    a.w = w;
    return a;
}


//inicializa um grafo com |V| vertices
Grafo inicializa(int V){
    Grafo novo = (struct grafo*) malloc(sizeof(struct grafo));
    printf("Alocou grafo!!\n");
    novo->v = V;
    novo->matriz = (int**) malloc(V*sizeof(int*));
    printf("Alocou matriz!!!\n");
    for(int i = 0; i < V;i++){
        novo->matriz[i] = (int*) malloc(V*sizeof(int));
    }
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            novo->matriz[i][j] = 0;//incia todos os elementos com 0;
        }
    }
    return novo;
}
//Insere a aresta e no grafo g
void grafoInsere(Grafo g, Aresta e){
    g->matriz[e.v][e.w] = 1;
    g->matriz[e.w][e.v] = 1;
}
//Remove a aresta e do grafo g
void grafoRemove(Grafo g, Aresta e){
    g->matriz[e.v][e.w] = 0;
    g->matriz[e.w][e.v] = 0;
}
//Preenche o vetor com as arestas de g
//Retorna |E|, quantidade de arestas
int grafoArestas(Aresta a[], Grafo g){
    int count = 0;
    for(int i = 0; i < g->v; i++){
        for(int j = 0; j < g->v; j++){
            if(g->matriz[i][j] == 1){
                a[count++] = ARESTA(i,j);
            }
        }
    }
    return count;
}
//imprime um grafo G = (V,E);
void imprimirGrafo(Grafo g){
    for(int i = 0;i < g->v; i++){
        for(int j = 0; j < g->v; j++){
            if(g->matriz[i][j] == 1){
                printf("(%d,%d)\n",i,j);
            }
        }
    }
}


int pertence(Grafo g, Aresta e) {
    return (g->matriz[e.v][e.w] == 1);
}


int timestamp = 0;

void DFS_visit(Grafo g,int *v,cor u[],int d[],int f[],int indice) {
    cor[indice] = cinza;
    timestamp++;
    d[indice] = timestamp;
    for(int i = 0; i < g->v) {
        if(v[i] == 1) {
            if(cor[i] == branco) {
                pi[i] = indice;
                DFS_visit(g,g->matriz[i],cor,d,f,i);
            }
        }
    }
    cor[indice] = preto;
    timestamp++;
    f[indice] = timestamp;
}

void DFS(Grafo g) {
    cor[g->v];
    int pi[g->v];
    int d[g->v];
    int f[g->v];

    for(int i = 0; i < g->v; i++) {
        cor[i] = branco;
        pi[i] = NULL;
    }

    timestamp = 0;
    for(int i = 0; i < g->v; i++) {
        if(cor[i] == branco)
            DFS_visit(g,g->matriz[i],cor,d,f,i);
    }
}

void DFS_origem(Grafo g,int vertice) {
    cor[g->v];
    int pi[g->v];
    int d[g->v];
    int f[g->v];

    for(int i = 0; i < g->v; i++) {
        cor[i] = branco;
        pi[i] = NULL;
    }

    timestamp = 0;

    DFS_visit(g,g->matriz[vertice],cor,d,f,vertice);

}


int main(){
    Grafo g = NULL;
    g = inicializa(5);
    printf("inicializou!\n");
    printf("g->v: %d\n",g->v);
    grafoInsere(g,ARESTA(1,2));
    imprimirGrafo(g);
    printf("Pertence (1,2): %d\n",pertence(g,ARESTA(1,2)));
    return 0;
}
