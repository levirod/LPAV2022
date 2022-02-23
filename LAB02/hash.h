#ifndef _myLib
#define _myLib

int tabela_hash_tam;

struct dado_pessoa{
	char nome[50];
	long long int cpf;
	int idade;
};

typedef struct dado_pessoa dado_pessoa;

struct lista_pessoas{
	dado_pessoa *pessoa;
	struct lista_pessoas *prox;
};

typedef struct lista_pessoas lista_pessoas;

typedef lista_pessoas tabela_hash;

bool lista_pessoas_adicionar(dado_pessoa *pessoa, lista_pessoas **lista);

void lista_eventos_listar(lista_pessoas *lista);

dado_pessoa* criar_pessoa(char nome[50], long long int cpf, int idade);

tabela_hash **tabela_hash_pessoas_criar();

int funcao_hash(dado_pessoa *dp);

bool tabela_hash_pessoas_adicionar(dado_pessoa *dp, tabela_hash **tab);

void tabela_hash_pessoas_listar(tabela_hash **tab);

#endif