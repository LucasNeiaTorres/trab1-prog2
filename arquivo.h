#include <stdio.h>
#include "conf_peri.h"
#include "pesquisador.h"

#ifndef ARQUIVO_H_
#define ARQUIVO_H_  
#define TAM_MAX_STR 1024

// conta quantidade de linhas de um arquivo
int conta_linhas (char *nomeArquivo);

conf_peri_t* le_arquivo (char *nomeArquivo);

// corta dado do atributo requerido do arquivo xml e o retorna
char *corta_info(char *string, char info[TAM_MAX_STR], FILE *xml);

void le_xml(char *nomeArquivo, pesquisador_t *pesquisadores, conf_peri_t *conferencias, conf_peri_t *periodicos, lista_t *conferencias_nao_classificadas, lista_t *periodicos_nao_classificados);

int calcula_qtde_arquivos(char *diretorio);

#endif // ARQUIVO_H_