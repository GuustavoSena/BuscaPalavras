#ifndef ARVORE_PALAVRAS_H
#define ARVORE_PALAVRAS_H

// Estrutura para um nó da árvore de palavras
typedef struct NoArvore {
    char *palavra;
    int *linhas;
    int contagem;
    int tamanho;
    struct NoArvore *esquerda, *direita;
} NoArvore;

typedef struct {
    NoArvore *raiz;
} ArvorePalavras;

ArvorePalavras *criarArvorePalavras();
void inserirNaArvore(ArvorePalavras *arvore, char *palavra, int linha);
void buscarNaArvore(ArvorePalavras *arvore, const char *palavra);
void liberarArvore(ArvorePalavras *arvore);

#endif
