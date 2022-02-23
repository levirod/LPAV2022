#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"

bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	if (item_novo == NULL)
		return false;			
	item_novo->evento = evento; 
	item_novo->prox = *lista;	
	*lista = item_novo;			
	return true;
}

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));
	lista_eventos_t *aux = *lista;
	if (item_novo == NULL)
		return false;
	item_novo->evento = evento;
	item_novo->prox = NULL;

	if (*lista == NULL){
		*lista = item_novo;
	}
	else{
		while (aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = item_novo;
	}
}

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){

	if (*lista == NULL || (*lista)->evento->tempo > evento->tempo){
		return lista_eventos_adicionar_inicio(evento, lista);
	}
	else if ((*lista)->prox == NULL){
		return lista_eventos_adicionar_fim(evento, lista);
	}
	else{
		lista_eventos_t *aux = *lista;
		while (aux->prox != NULL && aux->prox->evento->tempo < evento->tempo){
			aux = aux->prox;
		}
		lista_eventos_t *d3 = malloc(sizeof(lista_eventos_t));
		d3->evento = evento;
		d3->prox = aux->prox;
		aux->prox = d3;
		return true;
	}
}

void lista_eventos_listar(lista_eventos_t *lista){
	lista_eventos_t *aux = lista;
	while (aux != NULL){
		printf("%3.6lf\t%d\t%d\n", aux->evento->tempo, aux->evento->alvo, aux->evento->tipo);
		aux = aux->prox;
	}
}

evento_t* criar_evento(double tempo, int alvo, int tipo) {
    evento_t *evento = malloc(sizeof(evento_t));
	evento->tempo = tempo;
	evento->alvo = alvo;
	evento->tipo = tipo;
    return evento;
}
