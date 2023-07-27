#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "arquivo.h"
#include "conf_peri.h"
#include "pesquisador.h"
#include "liblista.h"

int conta_linhas(char *nomeArquivo)
{
  int qtde = 0;
  FILE *arquivo;
  char linha[TAM_MAX_STR];

  arquivo = fopen(nomeArquivo, "r");

  if (!arquivo)
  {
    perror("Erro ao abrir arquivo");
    exit(1);
  }

  while (!feof(arquivo))
  {
    fgets(linha, TAM_MAX_STR, arquivo);
    qtde++;
  }
  return qtde;
}

conf_peri_t *le_arquivo(char *nomeArquivo)
{
  FILE *arquivo;
  char *linha = malloc(sizeof(char) * TAM_MAX_STR);
  char *pt = "";
  char *token = " ";
  char valorAtributo[TAM_MAX_STR] = "";
  char estrato[TAM_MAX_STR] = "";
  char nome[TAM_MAX_STR] = "";
  int posicao;

  conf_peri_t *conf_peri = malloc(sizeof(conf_peri_t) * conta_linhas(nomeArquivo));
  if (conf_peri == NULL)
  {
    perror("Erro na alocação das conferencias ou periódicos!");
    exit(1);
  }

  arquivo = fopen(nomeArquivo, "r");

  if (!arquivo)
  {
    char error_msg[100];
    sprintf(error_msg, "Erro ao abrir o arquivo %s", nomeArquivo);
    perror(error_msg);
    exit(1);
  }

  while (!feof(arquivo))
  {
    fgets(linha, TAM_MAX_STR, arquivo);

    // reseta variavel nome
    nome[strlen(linha) - 4] = '\0';
    strncpy(nome, linha, strlen(linha) - 4);
    pt = strtok(linha, token);
    while (pt)
    {
      strcpy(valorAtributo, pt);
      pt = strtok(NULL, token);
    }
    if (valorAtributo)
      strncpy(estrato, valorAtributo, 2);

    posicao = adiciona_conf_peri(conf_peri, nome, estrato);
  }
  // exclui ultima posicao
  exclui_conf_peri(conf_peri, ultima_posicao(conf_peri) - 1);
  fclose(arquivo);
  free(linha);
  return (conf_peri);
}

char *corta_info(char *string, char info[TAM_MAX_STR], FILE *xml) {
  char *tag;
  tag = strtok(string, "\"");
  tag = strtok(NULL, "=");
    
  while(!strstr(tag, "\"")) {
    strcat(info, tag);
    strcat(info, " ");
    fscanf(xml, "%s", tag);
  }
  strtok(tag, "\"");
  strcat(info, tag);
  return info;
}


void le_xml(char *nomeArquivo, pesquisador_t *pesquisadores, conf_peri_t *conferencias, conf_peri_t *periodicos, lista_t *conferencias_nao_classificadas, lista_t *periodicos_nao_classificados) {
  FILE *arquivo;
  char linha[TAM_MAX_STR];
  char *ocorrencia;
  char periodico[TAM_MAX_STR] = "";
  char ano[TAM_MAX_STR] = "";
  int posicao_pesquisador;
  int posicao_conf, posicao_peri; 
  int ano_int;
  int verificacao = 0;
  int qtde_ano = 0;
  arquivo = fopen(nomeArquivo, "r");

  if (!arquivo)
  {
    char error_msg[100];
    sprintf(error_msg, "Erro ao abrir o arquivo %s", nomeArquivo);
    perror(error_msg);
    exit(1);
  }
  // funcao trata_linha?
  while (!feof(arquivo)) {
    fscanf(arquivo, "%s", linha);

    if(strstr(linha, "DADOS-GERAIS") && !verificacao) {
      fscanf(arquivo, "%s", linha); 
      char nome[TAM_MAX_STR] = "";
      corta_info(linha, nome, arquivo);
      posicao_pesquisador = adiciona_pesquisador(pesquisadores, nome);
      //printf("%s %d\n", pesquisadores[posicao_pesquisador].nome, posicao_pesquisador);
      verificacao = 1;

    } else if(strstr(linha, "<TRABALHO-EM-EVENTOS")) {
      fscanf(arquivo, "%s", linha);

      while(!strstr(linha, "<AUTORES")) {

        if(strstr(linha, "ANO-DO-TRABALHO=") || strstr(linha, "ANO=")) {
          ano[0] = '\0';
          corta_info(linha, ano, arquivo);
          ano_int = atoi(ano);

        } else if(strstr(linha, "NOME-DO-EVENTO=\"")) {
          char conferencia[TAM_MAX_STR] = "";
          corta_info(linha, conferencia, arquivo);
          
          posicao_conf = busca_conf_peri(conferencias, conferencia);
          if(posicao_conf != -1) {
            conferencias[posicao_conf].ano = ano_int;
            conferencias[posicao_conf].quantidade++;
            lista_insere_inicio(pesquisadores[posicao_pesquisador].conferencias, conferencias[posicao_conf].nome, ano_int);
            pesquisadores[posicao_pesquisador] = adiciona_estrato_conferencia(conferencias[posicao_conf].estrato, pesquisadores[posicao_pesquisador]);
          } 
          else {
            if(busca_nome(conferencias_nao_classificadas, conferencia) == NULL)
              lista_insere_inicio(conferencias_nao_classificadas, conferencia, ano_int);
            else
              busca_nome(conferencias_nao_classificadas, conferencia)->quantidade++;
            
          }
        }
        fscanf(arquivo, "%s", linha);
      }
    }

    if(strstr(linha, "ANO-DO-ARTIGO=")) {
      ano[0] = '\0';
      corta_info(linha, ano, arquivo);
      ano_int = atoi(ano);
  
    } else if(strstr(linha, "TITULO-DO-PERIODICO-OU-REVISTA")) {
      char periodico[TAM_MAX_STR] = "";
      corta_info(linha, periodico, arquivo);
      
      posicao_peri = busca_conf_peri(periodicos, periodico);
      
      if(posicao_peri != -1) {
        periodicos[posicao_peri].ano = ano_int;
        periodicos[posicao_peri].quantidade++;
            
        lista_insere_inicio(pesquisadores[posicao_pesquisador].periodicos, periodicos[posicao_peri].nome, ano_int);
        pesquisadores[posicao_pesquisador] = adiciona_estrato_periodico(periodicos[posicao_peri].estrato, pesquisadores[posicao_pesquisador]);
      
      } else {

        if(busca_nome(periodicos_nao_classificados, periodico) == NULL)
          lista_insere_inicio(periodicos_nao_classificados, periodico, ano_int);
        else
          busca_nome(periodicos_nao_classificados, periodico)->quantidade++;

      }
    }  
  }
  fclose(arquivo);
}

int calcula_qtde_arquivos(char *diretorio)
{
  DIR *dirstream;
  struct dirent *direntry;
  int qtde = 0;
  dirstream = opendir(diretorio);
  if (!dirstream)
  {
    perror("Não foi possível abrir o diretório");
    return 1;
  }

  // varre as entradas do diretório aberto
  for (;;)
  {

    // pega a próxima entrada
    direntry = readdir(dirstream);

    // se for nula, encerra a varredura
    if (!direntry)
      break;

    // se for arquivo "." ou ".." nao ira ler
    if (strcmp(direntry->d_name, ".") && strcmp(direntry->d_name, ".."))
      qtde++;
  }
  // fecha o diretório
  (void)closedir(dirstream);
  return qtde;
}