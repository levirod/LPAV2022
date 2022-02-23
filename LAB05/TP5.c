#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char * inserir_char(char c, char texto[]){
    int tam = strlen(texto);
    char *aux = malloc(tam+1);
    for(int i=0; i< tam; i++){
        aux[i] = texto[i];
    }
    aux[tam] = c;
    aux[tam+1] = '\0';
    return aux;
    
}

char * inverte( char * palavra ){
    int tam = strlen(palavra);
    int k, i, j;

    for (i = 0, j = tam - 1; i < j; i++, j--){
        k = palavra[i];
        palavra[i] = palavra[j];
        palavra[j] = k;
    }
    return palavra;
}

int main(int argc, char *argv[]){
    
    int tam_max = atoi(argv[1]);
    
    char caracteres[100];
    strcpy(caracteres, argv[2]);
    int tam_caractere = strlen(caracteres);

    int i,j = 0;
    
    float possibi = pow(tam_caractere, tam_max);
    possibi = possibi + (possibi/2);

    //printf("%d palavras total\n", (int) possibi);
   
    char * palavra = malloc(tam_caractere);

    int val;

    for(i = 1; i < (int) possibi; i++){
        val = i;
        palavra = "";

        while (j < i && j < tam_max){ 
           
            int ch = (val-1) % tam_caractere;
            palavra = inserir_char(caracteres[ch], palavra);
            val = (val-1) /tam_caractere;  
            j++;
        }
        j = 0;

        printf("%s\n", inverte(palavra)); 
    }
  
}