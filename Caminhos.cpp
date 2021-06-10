// Autor: Gustavo Oliveira de Souza GitHub: gdesouza-git

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int nroUSP() {
    return 11851042;
}

// Grafo
typedef struct listaAdjacencia {
    int vert;
    struct listaAdjacencia* prox;
} NO;

// Vertices
typedef struct {
    NO* inicio;
    int flag;
} VERTICE;

// Funções auxiliares da funcao caminhosGrafo
void inicializarFlags(VERTICE* g, int n){
    for (int i = 1; i <= n; ++i) g[i].flag = 0;
}

NO* encontrarPenultimo(NO* p){
    while(p->prox->prox) p = p->prox;
    return p;
}

void inserirElemLista(NO* p, int ch){
    if (p) {
        while (p->prox) p = p->prox;
        NO* novo = (NO*)malloc(sizeof(NO));
        novo->vert = ch;
        novo->prox = NULL;
        p->prox = novo;
    }
    if(p->vert == -1) {
        p->vert = ch;
        p->prox = NULL;
    }
}

void removerElemLista(NO* p){
    NO* ant = encontrarPenultimo(p);
    while (p->prox) p = p->prox;
    ant->prox = NULL;
    free(p);
}

int verificarTamanho(NO* p, int d){
    int it = 0;
    while (p){
        if (it > d) return 0;
        it++;
        p = p->prox;
    }
    return 1;
}

void concatenaListas(NO* lista, NO* resp, int d){
    if (verificarTamanho(lista, d) == 0) return;

    while (lista) {
        inserirElemLista(resp, lista->vert);
        lista = lista->prox;
    }
}

void buscaProfundidade(VERTICE* g, int x, int y, int d, NO* resp, NO* lista){

    if(y == x){ //Quando x == y ele chegou ao vertice procurado, anotando o caminho em resp
        concatenaListas(lista, resp, d);
        return;
    }

    NO* p = g[x].inicio;
    g[x].flag = 1;

    while(p){
        if(g[p->vert].flag == 0){
            inserirElemLista(lista, p->vert);
            if(g[p->vert].flag == 0) buscaProfundidade(g, p->vert, y, d, resp, lista);
            removerElemLista(lista);
        }
        p = p->prox;
    }
    g[x].flag = 0; //Permite que o vertice seja visitado novamente
}

// Funcao principal: encontra os caminhos entre os vertices x e y, com no maximo d arestas de distancia
NO* caminhosGrafo(VERTICE* g, int n, int x, int y, int d){

    //Testes de parametro:
    if(d==0) return NULL;
    if(n==0) return NULL;
    if(x==y) return NULL;

    inicializarFlags(g, n);

    // Primeiro nó:
    NO* lista = (NO*)malloc(sizeof(NO));
    lista->vert = x;
    lista->prox = NULL;

    // Primeiro nó lista resposta:
    NO* resp = (NO*)malloc(sizeof(NO));
    resp->vert = -1;
    resp->prox = NULL;

    buscaProfundidade(g, x, y, d, resp, lista);
    if (resp->vert == -1) return NULL;
    return resp;
}

/*
Funcoes basicas para criar e exibir grafos/lista,
algumas baseadas nas estruturas apresentadas
na aula 25 sobre grafos da disciplina ED da UNIVESP
*/

VERTICE* criarGrafo(int numeroDeVertices){
    VERTICE* g = (VERTICE*)malloc(sizeof(VERTICE)*(numeroDeVertices+1));
    for(int i=1; i<=numeroDeVertices; i++){
        g[i].inicio = NULL;
    }
    return g;
}

NO* criarAdj(int vertice){
    NO *temp = (NO*)malloc(sizeof(NO));
    temp->vert = vertice;
    temp->prox = NULL;
    return(temp);
}

void criarAresta(VERTICE *g, int vi, int vf){
    NO *novo = criarAdj(vf);
    novo->prox = g[vi].inicio;
    g[vi].inicio = novo;
}

void imprimirGrafo(VERTICE *gr, int n){
    for (int i = 1; i <= n; i++) {
        printf("v%d:",i);
        NO *ad = gr[i].inicio;
        while(ad){
            printf(" v%d |",ad->vert);
            ad=ad->prox;
        }
        printf("\n");
    }
}

void imprimirLista(NO* l){
    printf("\nLista: \n");
    while(l){
        printf("%d ",l->vert);
        l = l->prox;
    }
}

int main() {

int n = 6;
    VERTICE *gr = criarGrafo(n);

    criarAresta(gr, 1, 2);
    criarAresta(gr, 2, 3);
    criarAresta(gr, 2, 4);
    criarAresta(gr, 3, 2);
    criarAresta(gr, 3, 5);
    criarAresta(gr, 4, 3);
    criarAresta(gr, 3, 6);
    criarAresta(gr, 6, 3);
    criarAresta(gr, 6, 5);

    imprimirGrafo(gr, n);

    NO* resp = caminhosGrafo(gr, n, 4, 2, 10);
    if (resp) imprimirLista(resp);

return 0;
}
