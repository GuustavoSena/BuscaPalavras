#include "lista_palavras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 1000
#define TAMANHO_INICIAL_LINHAS 10

ListaPalavras *criarListaPalavras()
{
    ListaPalavras *lista = (ListaPalavras *)malloc(sizeof(ListaPalavras));
    lista->cabeca = NULL;
    return lista;
}

void inserirPalavra(ListaPalavras *lista, char *palavra, int linha)
{
    NoPalavra *atual = lista->cabeca;
    NoPalavra *anterior = NULL;

    // Busca a palavra na lista
    while (atual != NULL && strcmp(atual->palavra, palavra) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        // Palavra não encontrada, insere um novo nó
        NoPalavra *novo = (NoPalavra *)malloc(sizeof(NoPalavra));
        novo->palavra = strdup(palavra);
        novo->linhas = (int *)malloc(TAMANHO_INICIAL_LINHAS * sizeof(int));
        novo->linhas[0] = linha;
        novo->contagem = 1;
        novo->tamanho = TAMANHO_INICIAL_LINHAS;
        novo->proximo = NULL;

        if (anterior == NULL)
        {
            // Insere no início da lista
            lista->cabeca = novo;
        }
        else
        {
            // Insere após o nó anterior
            anterior->proximo = novo;
        }
    }
    else
    {
        // Palavra encontrada, atualiza as informações
        if (atual->contagem >= atual->tamanho)
        {
            // Redimensiona o array de linhas se necessário
            atual->tamanho *= 2;
            atual->linhas = (int *)realloc(atual->linhas, atual->tamanho * sizeof(int));
        }
        atual->linhas[atual->contagem] = linha;
        atual->contagem++;
    }
}

void buscarPalavra(ListaPalavras *lista, const char *palavra) {
    clock_t inicio, fim;
    double tempoUsado;
    NoPalavra *atual = lista->cabeca;

    inicio = clock();

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n", atual->contagem, palavra);
            for (int i = 0; i < atual->contagem; i++) {
                printf("%05d\n", atual->linhas[i]);
            }
            fim = clock();
            tempoUsado = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
            printf("Tempo de busca: %.2f ms\n", tempoUsado);
            return;
        }
        atual = atual->proximo;
    }

    fim = clock();
    tempoUsado = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("Palavra '%s' nao foi encontrada.\nTempo de busca: %.2f ms\n", palavra, tempoUsado);
}

