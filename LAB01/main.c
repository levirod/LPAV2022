#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"

int main(int argc, char *argv[1]){
	// declara a lista de o struct
	lista_eventos_t *l = NULL;
	evento_t *e;
	
	FILE *fp = NULL;
	fp = fopen(argv[1], "r+");
	if(fp == NULL){
		printf("arquivo nao existe!\n");
		return 1;
	}

	double tempo;
	int alvo, tipo;
	while (fscanf(fp,"%lf\t%d\t%d\n", &tempo, &alvo, &tipo) != EOF){ // le o arquivo pelo terminal
		e = criar_evento(tempo, alvo, tipo);
		//lista_eventos_adicionar_inicio(e, &l);
		//lista_eventos_adicionar_fim(e, &l);
		lista_eventos_adicionar_ordenado(e, &l);
	}
	lista_eventos_listar(l);
}