#ifndef LISTA_PALAVRAS_H
#define LISTA_PALAVRAS_H

// Estrutura para um nó da lista de palavras...
typedef struct NoPalavra
{
    char *palavra;
    int *linhas;  // Array dinâmico para armazenar as linhas
    char **textos; // Array de strings para armazenar os textos das linhas
    int contagem; // Contagem do número de vezes que a palavra aparece
    int tamanho;  // Tamanho atual do array 'linhas'
    struct NoPalavra *proximo;
} NoPalavra;

typedef struct {
    struct NoPalavra *cabeca; // Note que NoPalavra é apenas declarado, não definido
} ListaPalavras;

ListaPalavras *criarListaPalavras();
void inserirPalavra(ListaPalavras *lista, char *palavra, int linha, char *textoLinha);
void buscarPalavra(ListaPalavras *lista, const char *palavra);

#endif
