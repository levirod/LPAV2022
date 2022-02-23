#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "hash.h"


bool lista_pessoas_adicionar(dado_pessoa *pessoa, lista_pessoas **lista){
	lista_pessoas *item_novo = malloc(sizeof(lista_pessoas));
	lista_pessoas *aux = *lista;
	if (item_novo == NULL) return false;
	
	item_novo->pessoa = pessoa;
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

void lista_eventos_listar(lista_pessoas *lista){
	lista_pessoas *aux = lista;
	while (aux != NULL){
		printf("-%s\t%lld\t%d\n",aux->pessoa->nome, aux->pessoa->cpf, aux->pessoa->idade);
		aux = aux->prox;
	}
}

dado_pessoa* criar_pessoa(char nome[50], long long int cpf, int idade) {
    dado_pessoa *pessoa = (dado_pessoa*)malloc(sizeof(dado_pessoa));
	if(pessoa == NULL) printf("foi n");
	pessoa->cpf = cpf;
	pessoa->idade = idade;
	strcpy(pessoa->nome, nome);
    return pessoa;
}

tabela_hash **tabela_hash_pessoas_criar(){ 
	tabela_hash **tab = (tabela_hash **)malloc(sizeof(tabela_hash*)*tabela_hash_tam);
 	for(int i = 0; i < tabela_hash_tam; i++){
  		tab[i] = NULL;
 	}
	 return tab;
}

int funcao_hash(dado_pessoa *dp){
  return(dp->cpf % tabela_hash_tam);
}

bool tabela_hash_pessoas_adicionar(dado_pessoa *dp, tabela_hash **tab){
	int key = funcao_hash(dp);
	
	lista_pessoas_adicionar(dp, &tab[key]);
	
	return true;
}

void tabela_hash_pessoas_listar(tabela_hash **tab){

	for (int i=0; i< tabela_hash_tam; i++){
		printf("POSIÇÃO %d DA TABELA HASH\n", i);
		lista_eventos_listar(tab[i]);
	}

}