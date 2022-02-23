#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "grafos.h"

grafo_t * criar_grafo(int tam){ 
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
    
    return novo_dado_vertice;
}

bool lista_vizinhos_adicionar_inicio(dado_vertice *dv, lista_vizinhos_t **lista){
	lista_vizinhos_t *item_novo = malloc(sizeof(lista_vizinhos_t)); 
	if (item_novo == NULL) return false;			
	item_novo->dado_vertice = dv; 
	item_novo->proximo = *lista;
	*lista = item_novo;		
	return true;
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

void lista_vizinhos_listar(lista_vizinhos_t *lista){
	lista_vizinhos_t *aux = lista->proximo;
	while (aux != NULL){
		printf("%d ", aux->dado_vertice->id);
		aux = aux->proximo;
	}
    printf("\n");
}

void imprimir_grafo(grafo_t * grafo){
    for(int i = 0;i<grafo->tamanho; i++){
        printf("NO %d: ", i);
        lista_vizinhos_listar(grafo->lista[i]);
    }

}