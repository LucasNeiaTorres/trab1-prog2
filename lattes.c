#include "arquivo.h"
#include "conf_peri.h"
#include "pesquisador.h"
#include "interface.h"
#include "liblista.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define MAX 1024

int main(int argc, char **argv) {
    DIR *dirstream;
    struct dirent *direntry;
    char diretorioArquivo[MAX] = "";
    char* dir_name; // diretorio requerido dos arquivos de xml
    char* arq_conf; // arquivo requerido das conferencias
    char* arq_perd; // arquivo requerido dos periodicos
    int opt;
    while ((opt = getopt (argc, argv, "d:c:p:")) != -1) {
        switch (opt) {
            case 'd':
                dir_name = optarg;
                break;
            case 'c':
                arq_conf = optarg;
                break;
            case 'p':
                arq_perd = optarg;
                break;
            default:
                fprintf(stderr, "Erro na execução - utilize os parâmetros -d, -c e -p com o diretório de argumento, arquivo de conferências e arquivo de periódicos, respectivamente.\n");
                exit(1);
        }
    }
    conf_peri_t* conferencias = le_arquivo(arq_conf);
    conf_peri_t* periodicos = le_arquivo(arq_perd);
    lista_t* conferencias_nao_classificadas = lista_cria();
    lista_t* periodicos_nao_classificados = lista_cria();
    // exibe_conf_peri(periodicos);
    // exibe_conf_peri(conferencias);
    
    int qtde_arquivos = calcula_qtde_arquivos(dir_name);
    
    pesquisador_t* pesquisadores = malloc(sizeof(pesquisador_t) * qtde_arquivos);
    reseta_pesquisadores(pesquisadores, qtde_arquivos);

    // abre um diretório
    dirstream = opendir (dir_name);
    if (! dirstream ) {
        perror("Não foi possível abrir o diretório");
        return 1;
    }

    // varre as entradas do diretório aberto
    for (;;) {
    
        // pega a próxima entrada
        direntry = readdir(dirstream);
        
        // se for nula, encerra a varredura
        if (! direntry)
            break;
    
        // se for arquivo "." ou ".." nao ira ler
        if (strcmp(direntry->d_name, ".") && strcmp(direntry->d_name, "..")) {
            strcpy(diretorioArquivo, dir_name);
            strcat(diretorioArquivo, "/");
            strcat(diretorioArquivo, direntry->d_name);
            le_xml(diretorioArquivo, pesquisadores, conferencias, periodicos, conferencias_nao_classificadas, periodicos_nao_classificados);
        }
    }  

    // fecha o diretório
    (void) closedir (dirstream);

    // demonstração dos dados
    cabecalho_por_estrato_peri();
    evento_por_estrato(periodicos);

    cabecalho_por_estrato_conf();
    evento_por_estrato(conferencias);
    // ordenar
    // nao mostrar se nao houver

    eventos_pesquisador_estratos(pesquisadores, qtde_arquivos);

    eventos_ano_estratos(conferencias, periodicos);

    evento_estrato_c(conferencias, periodicos);

    eventos_nao_classificados(conferencias_nao_classificadas, periodicos_nao_classificados);

    lista_destroi(conferencias_nao_classificadas);
    lista_destroi(periodicos_nao_classificados);
    destroi_pesquisadores(pesquisadores, qtde_arquivos);
    free(conferencias);
    free(periodicos);
    return 0;
}