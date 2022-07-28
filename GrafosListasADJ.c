#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

enum cor {branco,cinza,preto};
typedef enum cor cor;

typedef int TipoItem; // tipo dos elementos na lista
typedef struct no { //estrutura para lista encadeada
    TipoItem info;
    struct no * prox; // ponteiro para proximo elemento
} Lista;


void imprimir(Lista* l) {
    Lista* aux ;//= (Lista*) malloc(sizeof(Lista));
    int i = 1;
    aux = l;
    while(aux != NULL) {
        printf("elemento%d: %d\n",i,aux->info);
        aux = aux->prox;
        i++;
    }
}

Lista* insere(Lista* l, TipoItem info) {
    Lista* aux = (Lista*) malloc(sizeof(Lista));
    aux->info = info;
    aux->prox = l; //encadeia com a cabeca da lista
    return aux;// retorna a nova cabeca
}

Lista* busca(Lista* l, TipoItem info) {
    while(l != NULL) {
        if(l->info == info) {
            return l;
        }
        l = l->prox;
    }
    return NULL;
}

Lista* organizarCrescente(Lista* l) {
    Lista* prox = l->prox;
    Lista* ant = l;
    while(prox != NULL) {
        if(ant->info > prox->info) {
            Lista* aux2 =
                ant->prox = prox->prox;
            prox->prox = ant;
            if(ant == l) {
                l = prox;
            }
            prox = ant->prox;
        }
    }
}

Lista* ordenar(Lista* l) {
    if(l != NULL) {
        if(l->prox != NULL) {
            printf("l->info: %d l->prox->info: %d\n",l->info,l->prox->info);
            if(l->info > l->prox->info) {
                printf("entrou!!");
                Lista* aux = l;
                /*printf("aux->info: %d\n",aux->info);
                aux->prox = l->prox->prox;
                l = l->prox;
                printf("l: %d\n",l->info);
                l->prox = aux;
                //l->prox = ordenar(l->prox);*/

                l = l->prox;
                aux->prox = l->prox;
                l->prox = aux;
                l->prox = ordenar(l->prox);

                printf("L: %d\n",l->info);
                printf("L->prox: %d\n",l->prox->info);
            }
        }
    }
    return l;
}

Lista * retira(Lista* l, TipoItem info) {
    Lista * ant = l; // elemento anterior
    Lista * p = l; // usado para encontrar o elemento
// a ser retirado
    while(p!= NULL && p->info != info) { // localiza o elemento
        ant = p;
        p = p->prox;
    }
    if(p != NULL) { // elemento encontrado
        if(p == l) // remoc~ao na cabeca
            l = l->prox; // atualiza a cabeca
        else // remoc~ao no meio
            ant->prox = p->prox;
        free(p); // libera o no do elemento removido
    } else
        printf("Elemento n~ao encontrado");
    return l;
}

typedef struct {
    int v;
    int w;
} Aresta;
// cria uma aresta (v,w)

//estrutura de matriz adjacencia.
struct grafo {
    Lista **vetor;
    int v;//quantidade de vértices maximo
    int ordenado;
};

typedef struct grafo * Grafo;

//cria uma aresta
Aresta ARESTA(int v,int w) {
    Aresta a;
    a.v = v;
    a.w = w;
    return a;
}


//inicializa um grafo com |V| vertices
Grafo inicializa(int V,int ordenado) {
    Grafo novo = (struct grafo*) malloc(sizeof(struct grafo));
    printf("Alocou grafo!!\n");
    novo->v = V;
    novo->ordenado = ordenado;
    novo->vetor = (Lista**) malloc(V*sizeof(Lista*));
    printf("Alocou vetor!!!\n");
    for(int i = 0; i < V; i++) {
        novo->vetor[i] = NULL;
    }
    return novo;
}


//Insere a aresta e no grafo g
void grafoInsere(Grafo g, Aresta e) {
    g->vetor[e.v] = insere(g->vetor[e.v],e.w);
    if(g->ordenado == 0){
        g->vetor[e.w] = insere(g->vetor[e.w],e.v);
        g->vetor[e.w] = ordenar(g->vetor[e.w]);
    }
    g->vetor[e.v] = ordenar(g->vetor[e.v]);

}
//Remove a aresta e do grafo g
void grafoRemove(Grafo g, Aresta e) {
    g->vetor[e.v] = retira(g->vetor[e.v],e.w);
    if(g->ordenado == 0){
        g->vetor[e.w] = retira(g->vetor[e.w],e.v);
    }
}
//Preenche o vetor com as arestas de g
//Retorna |E|, quantidade de arestas
int grafoArestas(Aresta a[], Grafo g) {
    int count = 0;
    Lista* aux = NULL;
    for(int i = 0; i < g->v; i++) {
        aux = g->vetor[i];
        while(aux != NULL) {
            a[count++] = ARESTA(i,aux->info);
            aux = aux->prox;
        }
    }
    return count;
}
//imprime um grafo G = (V,E);
void imprimirGrafo(Grafo g) {
    Aresta a[50];
    int n = grafoArestas(a,g);
    for(int i = 0; i < n; i++) {
        printf("(%d,%d)\n",a[i].v,a[i].w);
    }
}


int pertence(Grafo g, Aresta e) {
    if(busca(g->vetor[e.v],e.w) != NULL)
        return 1;
    return 0;
}

//(d) Implemente a busca em profundidade a partir de um vertice de origem s, tal que imprima a
//arvore de busca obtida.

int timestamp = 0;

void DFS_visit(Grafo g,Lista *v,cor c[],int pi[],int d[],int f[],int indice) {
    c[indice] = cinza;
    timestamp++;
    d[indice] = timestamp;
    while(v != NULL) {
        if(c[v->info] == branco) {
            pi[v->info] = indice;
            DFS_visit(g,g->vetor[v->info],c,pi,d,f,v->info);
        }
        v = v->prox;
    }
    c[indice] = preto;
    timestamp++;
    f[indice] = timestamp;
}


void printVet(int vet[],int n) {
    for(int i = 0; i < n; i++) {
        printf("%d\n",vet[i]);
    }
    printf("\n");
}


void showArvore(Grafo g,int d[]) {
    printf("show arvore!!:\n");
    int newline = 0;
    for(int i = 0; i <= g->v; i++) {
        for(int j = 0; j < g->v; j++) {
            if(d[j] == i) {
                printf("%d ",j);
                newline = 1;
            }
        }
        if(newline == 1){
            printf("\n");
            newline = 0;
        }
    }
    //printf("\n");
}

void DFS(Grafo g) {
    cor c[g->v];
    int pi[g->v];
    int d[g->v];
    int f[g->v];

    for(int i = 0; i < g->v; i++) {
        c[i] = branco;
        pi[i] = -1;
    }

    timestamp = 0;
    for(int i = 0; i < g->v; i++) {
        if(c[i] == branco)
            DFS_visit(g,g->vetor[i],c,pi,d,f,i);
    }

    showArvore(g,d);
    /*printVet(c,g->v);
    printVet(pi,g->v);
    printVet(d,g->v);
    printVet(f,g->v);*/
}

void DFS_origem(Grafo g,int vertice) {
    cor c[g->v];
    int pi[g->v];
    int d[g->v];
    int f[g->v];

    for(int i = 0; i < g->v; i++) {
        c[i] = branco;
        pi[i] = -1;
    }

    timestamp = 0;
    DFS_visit(g,g->vetor[vertice],c,pi,d,f,vertice);
    showArvore(g,d);
}





/*(e) Implemente a busca em largura a partir de um vertice de origem s, tal que imprima a arvore de
busca obtida.*/


//FILAS:
typedef struct {
    struct no* inicio;
    struct no* fim;
} Fila;

int vazia(Fila* f) {
    return (f->inicio == NULL);
}
Fila* cria_fila_vazia() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

//Enfileira um elemento
void enqueue(Fila* f, TipoItem x) {
    struct no* aux = (struct no*) malloc(sizeof(struct no));
    aux->info = x;
    aux->prox = NULL;
    if(vazia(f)) {
        f->inicio = aux;
    } else {
        f->fim->prox = aux;
    }
    f->fim = aux;
}

//Desenfileira um elemento
TipoItem* dequeue(Fila* f) {
    if(!vazia(f)) {
        TipoItem* x = (TipoItem*) malloc(sizeof(TipoItem));
        struct no* aux = f->inicio;
        *x = f->inicio->info;
        if(f->inicio == f->fim) // so tem 1 elemento
            f->fim = NULL;
        f->inicio = f->inicio->prox;
        free(aux);
        return x;
    } else
        return NULL;
}

TipoItem* head(Fila* f){
    if(!vazia(f)) {
        TipoItem* x = (TipoItem*) malloc(sizeof(TipoItem));
        *x = f->inicio->info;
        return x;
    } else
        return NULL;
}


void BFS(Grafo g,int vertice) {
    Fila* q = cria_fila_vazia();
    cor c[g->v];
    int pi[g->v];
    int d[g->v];
    int f[g->v];

    for(int i = 0; i < g->v; i++) {
        if(i != vertice) {
            c[i] = branco;
            d[i] =  INT_MAX;//maior valor de int = infinito.
            pi[i] = -1;
        }
    }

    c[vertice] = cinza;
    pi[vertice] = -1;
    d[vertice] = 0;
    enqueue(q,vertice);

    while(!vazia(q)){
        int *u = head(q);
        //printf("u = %d\n",*u);
        //printf("U = %d\n",*u);
        Lista* aux = g->vetor[*u];
        while(aux != NULL){
            int info = aux->info;
            if(c[info] == branco){
                //printf("%d ",info);
                c[info] = cinza;
                d[info] = d[*u] + 1;
                pi[info] = (*u);
                enqueue(q,info);
            }
            aux = aux->prox;
        }
        dequeue(q);
        c[*u] = preto;
        free(u);
    }
    printf("\n\n\n");
    showArvore(g,d);
    /*printVet(c,g->v);
    printVet(pi,g->v);
    printVet(d,g->v);
    printVet(f,g->v);*/
}


//ORDENAÇÃO TOPOLÓGICA:

void DFS_visit_OT(Grafo g,Lista *v,cor c[],int pi[],int d[],int f[],int indice,Lista**l) {
    c[indice] = cinza;
    timestamp++;
    d[indice] = timestamp;
    while(v != NULL) {
        if(c[v->info] == branco) {
            pi[v->info] = indice;
            DFS_visit_OT(g,g->vetor[v->info],c,pi,d,f,v->info,l);
        }
        v = v->prox;
    }
    c[indice] = preto;
    timestamp++;
    f[indice] = timestamp;
    (*l) = insere(*l,indice);
}


Lista* DFS_OT(Grafo g) {
    Lista* l = NULL;
    cor c[g->v];
    int pi[g->v];
    int d[g->v];
    int f[g->v];

    for(int i = 0; i < g->v; i++) {
        c[i] = branco;
        pi[i] = -1;
    }

    timestamp = 0;
    for(int i = 0; i < g->v; i++) {
        if(c[i] == branco)
            DFS_visit_OT(g,g->vetor[i],c,pi,d,f,i,&l);
    }
    return l;
}


Lista* ordenacaoTopologica(Grafo g){
    Lista* l = DFS_OT(g);
    return l;
}



int main() {
    setlocale(LC_ALL,"Portuguese");
    Grafo g = NULL;
    g = inicializa(6,0);
    printf("inicializou!\n");
    printf("g->v: %d\n",g->v);

    grafoInsere(g,ARESTA(0,2));
    grafoInsere(g,ARESTA(0,1));
    grafoInsere(g,ARESTA(2,5));
    grafoInsere(g,ARESTA(2,4));
    grafoInsere(g,ARESTA(2,3));
    grafoInsere(g,ARESTA(3,5));
    grafoInsere(g,ARESTA(3,4));
    grafoInsere(g,ARESTA(1,3));
    grafoInsere(g,ARESTA(4,5));
    imprimirGrafo(g);
    DFS(g);
    DFS_origem(g,3);
    BFS(g,3);
    printf("Pertente (1,3) : %d\n",pertence(g,ARESTA(1,3)));

    Grafo ordenado = NULL;
    ordenado = inicializa(6,1);
    /*grafoInsere(ordenado,ARESTA(0,4));
    grafoInsere(ordenado,ARESTA(1,4));
    grafoInsere(ordenado,ARESTA(1,2));
    grafoInsere(ordenado,ARESTA(1,3));
    grafoInsere(ordenado,ARESTA(1,5));
    grafoInsere(ordenado,ARESTA(1,0));
    grafoInsere(ordenado,ARESTA(2,3));
    grafoInsere(ordenado,ARESTA(3,5));
    grafoInsere(ordenado,ARESTA(7,4));
    grafoInsere(ordenado,ARESTA(7,6));
    grafoInsere(ordenado,ARESTA(10,7));
    grafoInsere(ordenado,ARESTA(11,10));
    grafoInsere(ordenado,ARESTA(11,6));
    grafoInsere(ordenado,ARESTA(11,12));
    grafoInsere(ordenado,ARESTA(12,9));*/
    grafoInsere(ordenado,ARESTA(0,2));
    grafoInsere(ordenado,ARESTA(1,2));
    grafoInsere(ordenado,ARESTA(1,0));
    grafoInsere(ordenado,ARESTA(2,4));
    grafoInsere(ordenado,ARESTA(3,1));
    grafoInsere(ordenado,ARESTA(3,4));
    grafoInsere(ordenado,ARESTA(5,2));
    imprimirGrafo(ordenado);
    printf("Ordenação Topológica: \n");
    Lista* ord = ordenacaoTopologica(ordenado);
    imprimir(ord);
    return 0;
}

