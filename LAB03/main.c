#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "grafos.h"

int main(int argc, char *argv[1]){
    
    FILE *fp;
    fp = fopen(argv[1], "r+");
    int qtd_nos=0;
    double raio_comunicacao =0;

    fscanf(fp,"%d\t%lf\n", &qtd_nos, &raio_comunicacao);
    

    grafo_t *grafo = criar_grafo(qtd_nos);
    
    int id=0;
    double pos_x, pos_y;
    while (fscanf(fp,"%d\t%lf\t%lf\n", &id, &pos_x, &pos_y)!= EOF){
        
        dado_vertice *dv = vertice(id, pos_x, pos_y);
        adicionar_grafo(grafo, dv, id);  
   
    }
    atualizar_vizinho(grafo, raio_comunicacao);

    imprimir_grafo(grafo);

}