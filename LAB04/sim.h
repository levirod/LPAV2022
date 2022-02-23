#ifndef _myLib
#define _myLib

struct evento_t{
	double tempo;
	int alvo;
	int tipo;
};

typedef struct evento_t evento_t;

struct lista_eventos_t{
	evento_t *evento;
	struct lista_eventos_t *prox;
};

typedef struct lista_eventos_t lista_eventos_t;

typedef struct dado_vertice{
   int id;
   double pos_x;
   double pos_y;
   bool pacote_enviado;
}dado_vertice;

 struct lista_vizinhos_t{
    dado_vertice *dado_vertice;
    struct lista_vizinhos_t *proximo;
    
};
typedef struct lista_vizinhos_t lista_vizinhos_t;

typedef struct grafo_t{
    lista_vizinhos_t **lista;
    int tamanho;
}grafo_t;

evento_t* criar_evento(double tempo, int alvo, int tipo);

bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista);

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista);

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista);

bool lista_vizinhos_adicionar_inicio(dado_vertice *dv, lista_vizinhos_t **lista);

grafo_t * criar_grafo(int tam);

dado_vertice * vertice(int id, double pos_x, double pos_y);

void adicionar_grafo(grafo_t *grafo, dado_vertice *vertice, int pos);

void atualizar_grafo(grafo_t *grafo, dado_vertice *vertice, int pos);

void atualizar_vizinho(grafo_t *grafo, int raio_comunicacao);

void simulacao_iniciar(lista_eventos_t *lista_eventos, grafo_t *grafo);

#endif