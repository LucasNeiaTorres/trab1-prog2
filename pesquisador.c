#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesquisador.h"
#include "liblista.h"

void reseta_pesquisadores(pesquisador_t* pesquisadores, int qtde_arquivos) {
    int i = 0;
    while((strcmp(pesquisadores[i].nome, "")) && (i < qtde_arquivos)) {
        strcpy(pesquisadores[i].nome, "");
        i++;
    }
}

pesquisador_t adiciona_estrato_conferencia(char* estrato, pesquisador_t pesquisador) {
    if(!strcmp(estrato, "A1")) 
        pesquisador.estratos_conferencias[0]++;
    else if(!strcmp(estrato, "A2")) 
        pesquisador.estratos_conferencias[1]++;
    else if(!strcmp(estrato, "A3")) 
        pesquisador.estratos_conferencias[2]++;
    else if(!strcmp(estrato, "A4")) 
        pesquisador.estratos_conferencias[3]++;
    else if(!strcmp(estrato, "B1")) 
        pesquisador.estratos_conferencias[4]++;
    else if(!strcmp(estrato, "B2")) 
        pesquisador.estratos_conferencias[5]++;
    else if(!strcmp(estrato, "B3")) 
        pesquisador.estratos_conferencias[6]++;
    else if(!strcmp(estrato, "B4")) 
        pesquisador.estratos_conferencias[7]++;
    else
        pesquisador.estratos_conferencias[8]++;
    return pesquisador;
}

pesquisador_t adiciona_estrato_periodico(char* estrato, pesquisador_t pesquisador) {
    if(!strcmp(estrato, "A1")) 
        pesquisador.estratos_periodicos[0]++;
    else if(!strcmp(estrato, "A2")) 
        pesquisador.estratos_periodicos[1]++;
    else if(!strcmp(estrato, "A3")) 
        pesquisador.estratos_periodicos[2]++;
    else if(!strcmp(estrato, "A4")) 
        pesquisador.estratos_periodicos[3]++;
    else if(!strcmp(estrato, "B1")) 
        pesquisador.estratos_periodicos[4]++;
    else if(!strcmp(estrato, "B2")) 
        pesquisador.estratos_periodicos[5]++;
    else if(!strcmp(estrato, "B3")) 
        pesquisador.estratos_periodicos[6]++;
    else if(!strcmp(estrato, "B4")) 
        pesquisador.estratos_periodicos[7]++;
    else
        pesquisador.estratos_periodicos[8]++;
    return pesquisador;
}

int ultima_posicao_pesquisador(pesquisador_t* pesquisadores) {
    int i = 0;
    while(strcmp(pesquisadores[i].nome, ""))
        i++;
    return i++;
}

void adiciona_periodico_pesquisador(pesquisador_t* pesquisadores, char* evento, char* estrato, int ano) {
    // adiciona estrato em pesquisador (add no vetor)
}

int adiciona_pesquisador(pesquisador_t* pesquisadores, char* nome) {
    int ultima_posicao = ultima_posicao_pesquisador(pesquisadores);
    strcpy(pesquisadores[ultima_posicao].nome, nome);
    pesquisadores[ultima_posicao].periodicos = lista_cria();
    pesquisadores[ultima_posicao].conferencias = lista_cria();
    int i;
    for(i=0; i<9; i++) {
        pesquisadores[ultima_posicao].estratos_conferencias[i] = 0;
        pesquisadores[ultima_posicao].estratos_periodicos[i] = 0;
    }
    return ultima_posicao;
}

void destroi_pesquisadores(pesquisador_t* pesquisadores, int tam) {
    int i;
    //printf("%d\n", ultima_posicao_pesquisador(pesquisadores));
    for(i=0; i<tam; i++) {
        lista_destroi(pesquisadores[i].conferencias);
        lista_destroi(pesquisadores[i].periodicos);
    }
    free(pesquisadores);
}