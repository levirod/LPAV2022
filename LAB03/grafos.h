#ifndef _myLib
#define _myLib

typedef struct dado_vertice{
   int id;
   double pos_x;
   double pos_y;
}dado_vertice;

/// lista
 struct lista_vizinhos_t{
    dado_vertice *dado_vertice;
    struct lista_vizinhos_t *proximo;
    
};
typedef struct lista_vizinhos_t lista_vizinhos_t;

/////grafo
typedef struct grafo_t{
    lista_vizinhos_t **lista;
    int tamanho;
}grafo_t;

grafo_t * criar_grafo(int tam);

dado_vertice * vertice(int id, double pos_x, double pos_y);

bool lista_vizinhos_adicionar_inicio(dado_vertice *dv, lista_vizinhos_t **lista);

void adicionar_grafo(grafo_t *grafo, dado_vertice *vertice, int pos);

void atualizar_grafo(grafo_t *grafo, dado_vertice *vertice, int pos);

void atualizar_vizinho(grafo_t *grafo, int raio_comunicacao);

void lista_vizinhos_listar(lista_vizinhos_t *lista);

void imprimir_grafo(grafo_t * grafo);

#endif