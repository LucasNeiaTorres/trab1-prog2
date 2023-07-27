#include "liblista.h"
#include "conf_peri.h"
#include "compara_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

lista_t* lista_cria() {
    /* aloca lista */
    lista_t* l = malloc(sizeof(lista_t));

    /* verifica falha de alocação */
    if (l == NULL)
        return NULL; 

    l->ini = NULL;
    l->tamanho = 0;

    return l;
}

int lista_vazia(lista_t* l) {
    if (l->tamanho == 0)
        return 1;
    return 0;
}

int lista_tamanho(lista_t* l) {
    return l->tamanho;
}

void limpa_lista(lista_t* l) {
    nodo_l_t* aux = l->ini;
    while(aux) {
        //printf("%s | %s\n", aux->evento->nome);
        strcpy(aux->evento->nome, "");
        aux->evento->quantidade = 0; 
        aux = aux->prox;
    }
}

conf_peri_t* busca_nome(lista_t* l, char* nome) {
    nodo_l_t* aux = l->ini;
    char nome_evento[TAM_MAX_STR] = "";
    char nome_busca[TAM_MAX_STR] = "";
    int distancia;

    while(aux) {
        converteLower(aux->evento->nome, nome_evento);
        converteLower(nome, nome_busca);
        distancia = levenshtein(nome_evento, nome_busca);
        
        if (distancia < strlen(nome)/5) 
            return aux->evento;
        aux = aux->prox;
    }
    return NULL;
}


int lista_insere_inicio(lista_t* l, char nome[TAM_MAX_STR], int ano) {
    nodo_l_t* n;
    conf_peri_t* evento;

    if( ! (n = malloc(sizeof(nodo_l_t))))
        return 0;
    if( ! (evento = malloc(sizeof(conf_peri_t))))
        return 0;

    strcpy(evento->nome, nome);
    evento->ano = ano;
    evento->quantidade = 1;

    n->evento = evento;
    n->prox = NULL;

    if (! (lista_vazia(l)))
        n->prox = l->ini;
    l->ini = n;
    l->tamanho++;
    return 1;
}

int lista_retira_inicio (lista_t* l, char* elemento) {
    nodo_l_t* n = l->ini;

    if (lista_vazia(l))
        return 0;

    l->ini = n->prox;
    n->prox = NULL;
    strcpy(elemento, n->evento->nome);
    free(n);
    l->tamanho--;
    
    return 1;
}

int lista_retira_fim (lista_t* l, char* elemento) {
    if (lista_vazia(l))
        return 0;

    nodo_l_t* aux = l->ini;
    
    /* verifica se a lista tem apenas um elemento */
    if (aux->prox) {
        nodo_l_t* ultimo;
        
        /* encontra ultimo elemento */
        while (aux->prox->prox) 
            aux = aux->prox;
        ultimo = aux->prox;
        strcpy(elemento, ultimo->evento->nome);
        aux->prox = NULL;
        aux = ultimo;
    } else {
        strcpy(elemento, aux->evento->nome);
        l->ini = NULL;
    }

    free(aux);
    l->tamanho--;

    return 1;
}

int lista_retira_elemento (lista_t* l, char* elemento) {
    if (lista_vazia(l))
        return 0;

    nodo_l_t* aux = l->ini;
    nodo_l_t* nodo_elem;

    if(!strcmp(l->ini->evento->nome, elemento))
        return (lista_retira_inicio(l, elemento));
    
    /* procura elemento na lista e para no nodo anterior*/
    while (aux->prox) {
        if (!strcmp(aux->prox->evento->nome, elemento)) {
            if (! (aux->prox->prox))
                return (lista_retira_fim(l, elemento));
            nodo_elem = aux->prox;
            aux->prox = aux->prox->prox;
            aux = aux->prox;
                
            free(nodo_elem);
            l->tamanho--;
                
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

int lista_pertence (lista_t* l, char* elemento) {
    if (lista_vazia(l))
        return 0;
    
    nodo_l_t* aux = l->ini;

    while (aux->prox){
        if (!strcmp(aux->evento->nome, elemento))
            return 1;
        aux = aux->prox;
    }
    return 0;
}


void lista_imprime (lista_t* l) {
    nodo_l_t* tmp = l->ini;
    
    if (tmp) {
        while(tmp->prox != NULL) {
            printf("%s ", tmp->evento->nome);
            tmp = tmp->prox;
        }
        printf("%s\n", tmp->evento->nome);
    }
}

lista_t* lista_destroi (lista_t* l) {
    nodo_l_t* nodo;
    
    if (! lista_vazia(l)) {
        while (l->ini != NULL) {
            nodo = l->ini;
	        l->ini = l->ini->prox;
            free(nodo->evento);
	        free(nodo);
        }
    }
    
    free(l);
    return l;
}