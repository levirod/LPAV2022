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

bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista);

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista);

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista);

void lista_eventos_listar(lista_eventos_t *lista);

evento_t* criar_evento(double tempo, int alvo, int tipo);

#endif