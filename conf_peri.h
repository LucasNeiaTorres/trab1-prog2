#ifndef conf_peri_H_
#define conf_peri_H_  
#define TAM_MAX_STR 1024

typedef struct {
  char nome[TAM_MAX_STR];
  char estrato[TAM_MAX_STR];
  int ano;
  int quantidade;
} conf_peri_t; 

void converteLower(char *string, char *convertido);

// retorna posição adicionada
int adiciona_conf_peri(conf_peri_t* conf_peri, char* nome, char* estrato);

int busca_conf_peri(conf_peri_t* conf_peri, char* nome);

int ultima_posicao(conf_peri_t* conf_peri);

void exclui_conf_peri(conf_peri_t* conf_peri, int posicao);

void exibe_conf_peri(conf_peri_t* conf_peri);

#endif // conf_peri_H_