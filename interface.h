#ifndef INTERFACE_H_
#define INTERFACE_H_  

void cabecalho_por_estrato_peri();

void cabecalho_por_estrato_conf();

void evento_por_estrato(conf_peri_t* evento);

void eventos_pesquisador_estratos(pesquisador_t* pesquisadores, int tam);

void eventos_ano_estratos(conf_peri_t* conferencias, conf_peri_t* periodicos);

void evento_estrato_c(conf_peri_t* conferencias, conf_peri_t* periodicos);

void eventos_nao_classificados(lista_t* conferencias, lista_t* periodicos);

#endif // INTERFACE_H_