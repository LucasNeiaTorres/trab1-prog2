#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conf_peri.h"
#include <ctype.h>
#include "compara_string.h"

void converteLower(char *string, char *convertido) {
    int i;

    for(i=0; i < strlen(string); i++) {
        convertido[i] = tolower(string[i]);
    }
    convertido[i] = '\0';
}

int adiciona_conf_peri(conf_peri_t* conf_peri, char* nome, char* estrato) {
    int posicao = ultima_posicao(conf_peri);
    strcpy(conf_peri[posicao].nome, nome);
    strcpy(conf_peri[posicao].estrato, estrato);
    conf_peri[posicao].quantidade = 0;
    return posicao;
}

int busca_conf_peri(conf_peri_t* conf_peri, char* nome) {
    int i;
    int distancia;
    char nome_evento[TAM_MAX_STR] = "";
    char nome_busca[TAM_MAX_STR] = "";

    for(i=0; i<ultima_posicao(conf_peri)-1; i++) {
        converteLower(conf_peri[i].nome, nome_evento);
        converteLower(nome, nome_busca);
        distancia = levenshtein(nome_evento, nome_busca);

        if (distancia < strlen(nome)/5) 
            return i;       
    }
    return -1;
}
int ultima_posicao(conf_peri_t* conf_peri) {
    int i = 0;
    while(strcmp(conf_peri[i].nome, "")) 
        i++;
    return i++;
}

void exclui_conf_peri(conf_peri_t* conf_peri, int posicao) {
    strcpy(conf_peri[posicao].nome, "");
    strcpy(conf_peri[posicao].estrato, "");
    conf_peri[posicao].ano = 0;
    
}

void exibe_conf_peri(conf_peri_t* conf_peri) {
    int i;
    for(i=0; i<ultima_posicao(conf_peri); i++)
        printf("nome: %s | estrato: %s | %d\n", conf_peri[i].nome, conf_peri[i].estrato, i);
}