#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "hash.h"

int main(int argc, char *argv[]){

	dado_pessoa *dp;
	tabela_hash_tam = atoi(argv[1]);
	tabela_hash **tab = tabela_hash_pessoas_criar();
	
	FILE *fp = NULL;
	fp = fopen(argv[2], "r+");

	if(fp == NULL){
		printf("arquivo nao existe!\n");
		return 1;
	}

	char nome[50];
	int idade=0;
	long long int cpf=0;

	while(fscanf(fp,"%50[^\t]\t%lld\t%d\n", nome, &cpf, &idade) != EOF){ // le o arquivo pelo terminal
		dp = criar_pessoa(nome, cpf, idade);
		tabela_hash_pessoas_adicionar(dp, tab);
	}
	tabela_hash_pessoas_listar(tab);
}