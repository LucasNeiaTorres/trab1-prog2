#include "liblista.h"

#ifndef PESQUISADOR_H_
#define PESQUISADOR_H_  
#define TAM_MAX_STR 1024

typedef struct {
  char nome[TAM_MAX_STR];
  lista_t* periodicos;
  lista_t* conferencias;
  int estratos_conferencias[9];
  int estratos_periodicos[9];
} pesquisador_t; 

void reseta_pesquisadores(pesquisador_t* pesquisadores, int qtde_arquivos);

pesquisador_t adiciona_estrato_conferencia(char* estrato, pesquisador_t pesquisador);

pesquisador_t adiciona_estrato_periodico(char* estrato, pesquisador_t pesquisador);

int ultima_posicao_pesquisador(pesquisador_t* pesquisadores);

int adiciona_pesquisador(pesquisador_t* pesquisadores, char* nome);

void destroi_pesquisadores (pesquisador_t* pesquisadores, int tam);

#endif // PESQUISADOR_H_