#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "sim.h"

evento_t* criar_evento(double tempo, int alvo, int tipo) {
    evento_t *evento = malloc(sizeof(evento_t));
	evento->tempo = tempo;
	evento->alvo = alvo;
	evento->tipo = tipo;
    return evento;
}

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

bool lista_vizinhos_adicionar_inicio(dado_vertice *dv, lista_vizinhos_t **lista){
	lista_vizinhos_t *item_novo = malloc(sizeof(lista_vizinhos_t)); 
	if (item_novo == NULL) return false;			
	item_novo->dado_vertice = dv; 
	item_novo->proximo = *lista;
	*lista = item_novo;		
	return true;
}

grafo_t * criar_grafo(int tam){ ///ok
    grafo_t *grafo = (grafo_t *)malloc(sizeof(grafo_t));
    grafo->lista = calloc(tam, sizeof(lista_vizinhos_t*)); /// alocar o vetor de ponteiros do grafo com calloc
    grafo->tamanho = tam;
    return grafo;
}

dado_vertice * vertice(int id, double pos_x, double pos_y){
    dado_vertice *novo_dado_vertice = malloc(sizeof(dado_vertice));

    if(novo_dado_vertice == NULL) return NULL;
    novo_dado_vertice->id = id;
    novo_dado_vertice->pos_x = pos_x;
    novo_dado_vertice->pos_y = pos_y;
    novo_dado_vertice->pacote_enviado = false;
    
    return novo_dado_vertice;
}


void adicionar_grafo(grafo_t *grafo, dado_vertice *vertice, int pos){
   lista_vizinhos_adicionar_inicio(vertice, &grafo->lista[pos]);
}

void atualizar_grafo(grafo_t *grafo, dado_vertice *vertice, int pos){
    lista_vizinhos_adicionar_inicio(vertice, &grafo->lista[pos]->proximo);
}

void atualizar_vizinho(grafo_t *grafo, int raio_comunicacao){
    double calculo;
    for(int i=0; i < grafo->tamanho;i++){
        for(int j=0; j < grafo->tamanho; j++){
            
            if(j != i){
                calculo = sqrt(pow(grafo->lista[i]->dado_vertice->pos_x - grafo->lista[j]->dado_vertice->pos_x, 2) +
            pow(grafo->lista[i]->dado_vertice->pos_y - grafo->lista[j]->dado_vertice->pos_y, 2));
                if(calculo < raio_comunicacao){
                    dado_vertice *novo_vertice = malloc(sizeof(dado_vertice));
                    novo_vertice->id = j;
                    novo_vertice->pos_x = grafo->lista[j]->dado_vertice->pos_x;
                    novo_vertice->pos_y = grafo->lista[j]->dado_vertice->pos_y;
                    atualizar_grafo(grafo, novo_vertice, i);
                }
            }
        }
    }

}

void simulacao_iniciar(lista_eventos_t *lista_eventos, grafo_t *grafo){
    lista_eventos_t *aux_e = lista_eventos;
    double tempo = 0;
    while (aux_e != NULL){
        evento_t *prim_evento = aux_e->evento;
        lista_eventos = aux_e->prox;

        printf("[%3.6f] Nó %d recebeu pacote.\n", prim_evento->tempo, prim_evento->alvo);
        
        if(grafo->lista[prim_evento->alvo]->dado_vertice->pacote_enviado != true){
            lista_vizinhos_t *aux_v = grafo->lista[prim_evento->alvo]->proximo;
            while (aux_v !=NULL){
                printf("\t--> Repassando pacote para o nó %d ...\n", aux_v->dado_vertice->id);
                tempo = prim_evento->tempo + (0.1 + (grafo->lista[aux_v->dado_vertice->id]->dado_vertice->id * 0.01));
                evento_t *e = criar_evento(tempo, grafo->lista[aux_v->dado_vertice->id]->dado_vertice->id, 1); // tempo, alvo, tipo
                lista_eventos_adicionar_ordenado(e, &aux_e);
                aux_v = aux_v->proximo;
            }
            grafo->lista[prim_evento->alvo]->dado_vertice->pacote_enviado = true;
        }
        aux_e = aux_e->prox;
    }
}
