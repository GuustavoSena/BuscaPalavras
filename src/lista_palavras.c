#include "lista_palavras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    NoPalavra *atual = lista->cabeca;

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            printf("A palavra '%s' ocorre %d vezes nas linhas: ", palavra, atual->contagem);
            for (int i = 0; i < atual->contagem; i++) {
                printf("%d ", atual->linhas[i]);
            }
            printf("\n");
            return;
        }
        atual = atual->proximo;
    }

    printf("A palavra '%s' nao foi encontrada.\n", palavra);
}
