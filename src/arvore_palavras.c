#include "arvore_palavras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_INICIAL_LINHAS 10

// Função auxiliar para criar um novo nó da árvore
static NoArvore *criarNoArvore(char *palavra, int linha) {
    NoArvore *novo = (NoArvore *)malloc(sizeof(NoArvore));
    novo->palavra = strdup(palavra);
    novo->linhas = (int *)malloc(TAMANHO_INICIAL_LINHAS * sizeof(int));
    novo->linhas[0] = linha;
    novo->contagem = 1;
    novo->tamanho = TAMANHO_INICIAL_LINHAS;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Criar a árvore de palavras
ArvorePalavras *criarArvorePalavras() {
    ArvorePalavras *arvore = (ArvorePalavras *)malloc(sizeof(ArvorePalavras));
    arvore->raiz = NULL;
    return arvore;
}

// Inserir palavra na árvore
void inserirNaArvoreAux(NoArvore **no, char *palavra, int linha) {
    if (*no == NULL) {
        *no = criarNoArvore(palavra, linha);
    } else if (strcmp(palavra, (*no)->palavra) < 0) {
        inserirNaArvoreAux(&((*no)->esquerda), palavra, linha);
    } else if (strcmp(palavra, (*no)->palavra) > 0) {
        inserirNaArvoreAux(&((*no)->direita), palavra, linha);
    } else {
        // Palavra já existe, atualizar linhas e contagem
        if ((*no)->contagem == (*no)->tamanho) {
            (*no)->tamanho *= 2;
            (*no)->linhas = realloc((*no)->linhas, (*no)->tamanho * sizeof(int));
        }
        (*no)->linhas[(*no)->contagem] = linha;
        (*no)->contagem++;
    }
}

void inserirNaArvore(ArvorePalavras *arvore, char *palavra, int linha) {
    inserirNaArvoreAux(&(arvore->raiz), palavra, linha);
}

// Buscar palavra na árvore
void buscarNaArvoreAux(NoArvore *no, const char *palavra) {
    if (no == NULL) {
        printf("A palavra '%s' não foi encontrada.\n", palavra);
        return;
    }

    if (strcmp(palavra, no->palavra) < 0) {
        buscarNaArvoreAux(no->esquerda, palavra);
    } else if (strcmp(palavra, no->palavra) > 0) {
        buscarNaArvoreAux(no->direita, palavra);
    } else {
        printf("A palavra '%s' ocorre %d vezes nas linhas: ", palavra, no->contagem);
        for (int i = 0; i < no->contagem; i++) {
            printf("%d ", no->linhas[i]);
        }
        printf("\n");
    }
}

void buscarNaArvore(ArvorePalavras *arvore, const char *palavra) {
    buscarNaArvoreAux(arvore->raiz, palavra);
}

// Função auxiliar para liberar a memória de um nó
static void liberarNoArvore(NoArvore *no) {
    if (no == NULL) return;
    liberarNoArvore(no->esquerda);
    liberarNoArvore(no->direita);
    free(no->palavra);
    free(no->linhas);
    free(no);
}

// Liberar a árvore de palavras
void liberarArvore(ArvorePalavras *arvore) {
    liberarNoArvore(arvore->raiz);
    free(arvore);
}
