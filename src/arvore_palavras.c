#include "arvore_palavras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TAMANHO_INICIAL_LINHAS 10

// Função auxiliar para criar um novo nó da árvore
static NoArvore *criarNoArvore(char *palavra, int linha)
{
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
ArvorePalavras *criarArvorePalavras()
{
    ArvorePalavras *arvore = (ArvorePalavras *)malloc(sizeof(ArvorePalavras));
    arvore->raiz = NULL;
    return arvore;
}

// Inserir palavra na árvore
void inserirNaArvoreAux(NoArvore **no, char *palavra, int linha, char *textoLinha)
{
    if (*no == NULL)
    {
        *no = (NoArvore *)malloc(sizeof(NoArvore));
        (*no)->palavra = strdup(palavra);
        (*no)->linhas = (int *)malloc(TAMANHO_INICIAL_LINHAS * sizeof(int));
        (*no)->textos = (char **)malloc(TAMANHO_INICIAL_LINHAS * sizeof(char *));
        (*no)->linhas[0] = linha;
        (*no)->textos[0] = strdup(textoLinha);
        (*no)->contagem = 1;
        (*no)->tamanho = TAMANHO_INICIAL_LINHAS;
        (*no)->esquerda = (*no)->direita = NULL;
    }
    else if (strcmp(palavra, (*no)->palavra) < 0)
    {
        inserirNaArvoreAux(&((*no)->esquerda), palavra, linha, textoLinha);
    }
    else if (strcmp(palavra, (*no)->palavra) > 0)
    {
        inserirNaArvoreAux(&((*no)->direita), palavra, linha, textoLinha);
    }
    else
    {
        // Palavra já existe, atualizar linhas e contagem
        if ((*no)->contagem == (*no)->tamanho)
        {
            (*no)->tamanho *= 2;
            (*no)->linhas = (int *)realloc((*no)->linhas, (*no)->tamanho * sizeof(int));
            (*no)->textos = (char **)realloc((*no)->textos, (*no)->tamanho * sizeof(char *));
        }
        (*no)->linhas[(*no)->contagem] = linha;
        (*no)->textos[(*no)->contagem] = strdup(textoLinha);
        (*no)->contagem++;
    }
}

void inserirNaArvore(ArvorePalavras *arvore, char *palavra, int linha, char *textoLinha)
{
    inserirNaArvoreAux(&(arvore->raiz), palavra, linha, textoLinha);
}

// Buscar palavra na árvore
void buscarNaArvore(ArvorePalavras *arvore, const char *palavra)
{
    clock_t inicio = clock();

    if (!buscarNaArvoreAux(arvore->raiz, palavra, inicio))
    {
        clock_t fim = clock();
        double tempoUsado = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
        printf("Palavra '%s' nao encontrada.\nTempo de busca: %.2f ms\n", palavra, tempoUsado);
    }
}

bool buscarNaArvoreAux(NoArvore *no, const char *palavra, clock_t inicio)
{
    if (no == NULL)
    {
        return false;
    }

    if (strcmp(palavra, no->palavra) < 0)
    {
        return buscarNaArvoreAux(no->esquerda, palavra, inicio);
    }
    else if (strcmp(palavra, no->palavra) > 0)
    {
        return buscarNaArvoreAux(no->direita, palavra, inicio);
    }
    else
    {
        clock_t fim = clock();
        double tempoUsado = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
        printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", no->contagem, palavra);
        for (int i = 0; i < no->contagem; i++)
        {
            printf("%05d: %s", no->linhas[i], no->textos[i]);
        }
        printf("Tempo de busca: %.5f ms\n", tempoUsado);
        return true;
    }
}

// Função auxiliar para liberar a memória de um nó
static void liberarNoArvore(NoArvore *no)
{
    if (no == NULL)
        return;
    liberarNoArvore(no->esquerda);
    liberarNoArvore(no->direita);
    free(no->palavra);
    free(no->linhas);
    free(no);
}

// Liberar a árvore de palavras
void liberarArvore(ArvorePalavras *arvore)
{
    liberarNoArvore(arvore->raiz);
    free(arvore);
}
