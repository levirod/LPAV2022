#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <winsock2.h>

struct ethernet_hdr_t{    
    uint8_t  daddr[6]; 
    uint8_t  saddr[6]; 
    uint16_t protocol; 
} __attribute__ ((packed));;

typedef struct ip_hdr_t {    
    uint8_t  hdr_len:4,  version:4; 
    uint8_t  tos;       
    uint16_t tot_len;   
    uint16_t id;        
    uint16_t frag_off;  
    uint8_t  ttl;       
    uint8_t  protocol;  
    uint16_t check;     
    uint8_t saddr[4];   
    uint8_t daddr[4];   
} ip_hdr_t;

typedef struct tcp_hdr_t {    
    uint16_t sport;       
    uint16_t dport;       
    uint32_t seq;         
    uint32_t ack_seq;     
    uint8_t  reservado:4,  hdr_len:4; 
    uint8_t  flags;       
    uint16_t check;       
    uint16_t urg_ptr;     
    } tcp_hdr_t;


int main(int argc, char *argv[]){

    FILE *tcp_ip_file = fopen(argv[1], "rb");

    struct ethernet_hdr_t  *ethernet_hdr = malloc(sizeof( struct ethernet_hdr_t));
    struct ip_hdr_t  *ip_hdr = malloc(sizeof(ip_hdr_t));
    struct tcp_hdr_t  *tcp_hdr = malloc(sizeof(tcp_hdr_t));

    fread(ethernet_hdr, sizeof(struct ethernet_hdr_t), 1, tcp_ip_file);
    printf("Lendo Ethernet...\n");
    printf("--> MAC de Origem: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", ethernet_hdr->daddr[0],ethernet_hdr->daddr[1], ethernet_hdr->daddr[2], ethernet_hdr->daddr[3], ethernet_hdr->daddr[4], ethernet_hdr->daddr[5]);
    printf("--> MAC de Destino: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", ethernet_hdr->saddr[0],ethernet_hdr->saddr[1], ethernet_hdr->saddr[2], ethernet_hdr->saddr[3], ethernet_hdr->saddr[4], ethernet_hdr->saddr[5]);

    fread(ip_hdr, sizeof(ip_hdr_t), 1, tcp_ip_file);
    printf("Lendo IP...\n");
    printf("--> Versão do IP: %d\n", ip_hdr->version);
    printf("--> Tamanho do cabeçalho: %d bytes\n", ip_hdr->hdr_len*4);
    printf("--> Tamanho do pacote: %d bytes\n", ntohs(ip_hdr->hdr_len));
    printf("--> Endereço IP de Origem: %d.%d.%d.%d\n", ip_hdr->saddr[0],ip_hdr->saddr[1], ip_hdr->saddr[2], ip_hdr->saddr[3]);
    printf("--> Endereço IP de Destino: %d.%d.%d.%d\n", ip_hdr->daddr[0],ip_hdr->daddr[1], ip_hdr->daddr[2], ip_hdr->daddr[3]);
    

    fread(tcp_hdr, sizeof(tcp_hdr_t), 1, tcp_ip_file);
    printf("Lendo tcp...\n");
    printf("--> Porta de Origem: %d\n", ntohs(tcp_hdr->sport));
    printf("--> Porta de Destino: %d\n", ntohs(tcp_hdr->dport));
    printf("--> Tamanho do cabeçalho: %d bytes\n", tcp_hdr->hdr_len * 4);
    
    fseek( tcp_ip_file, tcp_hdr->hdr_len*4 - sizeof(tcp_hdr_t), SEEK_CUR);

    printf("Lendo Dados (HTTP) ..\n");
    int tam_dados = ntohs(ip_hdr->tot_len) - (ip_hdr->hdr_len*4) - (tcp_hdr->hdr_len*4);
    printf("--> Tamanho dos dados: %d bytes\n", tam_dados);
    printf("--> Dados: \n");
    
    int c, i;
    char buffer[tam_dados];

    c = fgetc(tcp_ip_file);
    printf( "%c", c);
    
    for( i=0; (i < tam_dados) && ( feof( tcp_ip_file ) == 0 ); i++ ){
        buffer[i] = (char)c;
        c = fgetc(tcp_ip_file);
        printf( "%c", buffer[i]);
    }
    buffer[i] = '\0';

}