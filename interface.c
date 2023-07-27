#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conf_peri.h"
#include "pesquisador.h"

void cabecalho_por_estrato_peri() {
    printf("-------------------------------------------------------------\n");
    printf("|PRODUÇÃO SUMARIZADA DE PERIÓDICOS DISCRIMINANDO OS ESTRATOS|\n");
    printf("-------------------------------------------------------------\n");
}

void cabecalho_por_estrato_conf() {
    printf("---------------------------------------------------------------\n");
    printf("|PRODUÇÃO SUMARIZADA DE CONFERÊNCIAS DISCRIMINANDO OS ESTRATOS|\n");
    printf("---------------------------------------------------------------\n");
}

void evento_por_estrato(conf_peri_t* evento) {
    char estratos[9][2] = {"A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "C"};
    char estrato_atual[3];
    int i, evento_atual;

    for(i=0; i<9; i++) {
        estrato_atual[0] = estratos[i][0];
        estrato_atual[1] = estratos[i][1];
        estrato_atual[2] = '\0';
        // if (existe)
        printf("-----------------------------------------------------------\n\n");
        printf("Estrato %s:\n", estrato_atual);

        for(evento_atual=0; evento_atual<ultima_posicao(evento); evento_atual++) {
            if((!strcmp(evento[evento_atual].estrato, estrato_atual) || ((evento[evento_atual].estrato[0] == 'C') && (estrato_atual[0] == 'C'))) && (evento[evento_atual].quantidade > 0))
                printf("%s: %d\n", evento[evento_atual].nome, evento[evento_atual].quantidade);
        }
    }
    printf("-----------------------------------------------------------\n");
}

void eventos_pesquisador_estratos(pesquisador_t* pesquisadores, int tam) {
    char estratos[9][2] = {"A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "C"};
    char estrato_atual[3];
    int i, pesquisador, evento;

    for(pesquisador=0; pesquisador<tam; pesquisador++) {
        printf("Pesquisador: %s\n", pesquisadores[pesquisador].nome);
        printf("+------------+------------+\n");
        printf("|Conferencias| Periódicos |\n");
        printf("+------------+------------+\n");

        for(i=0; i<9; i++) {
            estrato_atual[0] = estratos[i][0];
            estrato_atual[1] = estratos[i][1];
            estrato_atual[2] = '\0';
            printf("| %-2s: %-2d     |   %-2s: %-2d   |\n", estrato_atual, pesquisadores[pesquisador].estratos_conferencias[i], estrato_atual, pesquisadores[pesquisador].estratos_periodicos[i]);
        }
        printf("+------------+------------+\n\n");
    }
}

void eventos_ano_estratos(conf_peri_t* conferencias, conf_peri_t* periodicos) {
    char estratos[9][2] = {"A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "C"};
    char estrato_atual[3];
    int i, ano, evento;
    int menor_ano = 2021;
    int qtde_conf = 0;
    int qtde_peri = 0;

    for(ano=2022; ano>=menor_ano; ano--) {
        printf("Ano: %d\n", ano);
        printf("+------------+------------+\n");
        printf("|Conferencias| Periódicos |\n");
        printf("+------------+------------+\n");

        for(i=0; i<9; i++) {
            estrato_atual[0] = estratos[i][0];
            estrato_atual[1] = estratos[i][1];
            estrato_atual[2] = '\0';
            qtde_conf = 0;
            qtde_peri = 0;

            for(evento=0; evento<ultima_posicao(conferencias); evento++) {
                if((conferencias[evento].ano == ano) && (!strcmp(conferencias[evento].estrato, estrato_atual)))
                    qtde_conf++;
                if((conferencias[evento].ano < menor_ano) && (conferencias[evento].ano != 0))
                    menor_ano = conferencias[evento].ano;
            }

            for(evento=0; evento<ultima_posicao(periodicos); evento++) {
                if((periodicos[evento].ano == ano) && (!strcmp(periodicos[evento].estrato, estrato_atual)))
                    qtde_peri++;
                if((periodicos[evento].ano < menor_ano) && (periodicos[evento].ano != 0))
                    menor_ano = periodicos[evento].ano;
            }
            printf("| %-2s: %-2d     |   %-2s: %-2d   |\n", estrato_atual, qtde_conf, estrato_atual, qtde_peri);
        }
        printf("+------------+------------+\n\n");
    }
}

void evento_estrato_c(conf_peri_t* conferencias, conf_peri_t* periodicos) {
    int evento_atual;

    printf("------------------------------------------------------------\n\n");
    printf("EVENTOS NO ESTRATO C:\n");
    printf("----------------------- CONFERÊNCIAS -----------------------\n");
    for(evento_atual=0; evento_atual<ultima_posicao(conferencias); evento_atual++) {
        if((conferencias[evento_atual].estrato[0] == 'C') && (conferencias[evento_atual].quantidade > 0))
            printf("%s: %d\n", conferencias[evento_atual].nome, conferencias[evento_atual].quantidade);
    }
    printf("------------------------------------------------------------\n\n");
    printf("------------------------ PERIÓDICOS ------------------------\n");
    for(evento_atual=0; evento_atual<ultima_posicao(periodicos); evento_atual++) {
        if((periodicos[evento_atual].estrato[0] == 'C') && (periodicos[evento_atual].quantidade > 0))
            printf("%s: %d\n", periodicos[evento_atual].nome, periodicos[evento_atual].quantidade);
    }
    printf("------------------------------------------------------------\n");
}

void eventos_nao_classificados(lista_t* conferencias, lista_t* periodicos) {
    nodo_l_t* aux;

    printf("------------------------------------------------------------\n\n");
    printf("EVENTOS NÃO CLASSIFICADOS:\n");
    printf("----------------------- CONFERÊNCIAS -----------------------\n");

    aux = conferencias->ini;
    while(aux) {
        printf("%s: %d\n", aux->evento->nome, aux->evento->quantidade);
        aux = aux->prox;
    }

    printf("------------------------------------------------------------\n\n");
    printf("------------------------ PERIÓDICOS ------------------------\n");

    aux = periodicos->ini;
    while(aux) {
        printf("%s: %d\n", aux->evento->nome, aux->evento->quantidade);
        aux = aux->prox;
    }
    printf("------------------------------------------------------------\n");
}