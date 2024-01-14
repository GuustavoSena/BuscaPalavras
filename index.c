#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "src/lista_palavras.h"
#include "src/arvore_palavras.h"

#define TAMANHO 1000

// Funções de processamento para lista
void processarLinha(char *linha, int numeroLinha, ListaPalavras *lista)
{
    // Esta função processará cada linha do arquivo

    // Remove quebras de linha e pontuações
    for (int i = 0; linha[i]; i++)
    {
        linha[i] = tolower(linha[i]);
        if (ispunct(linha[i]))
        {
            linha[i] = ' ';
        }
    }

    // Extrai e insere palavras na lista
    char *palavra = strtok(linha, " ");
    while (palavra != NULL)
    {
        if (strlen(palavra) > 0)
        {
            inserirPalavra(lista, palavra, numeroLinha + 1);
        }
        palavra = strtok(NULL, " ");
    }
}

void processarArquivo(const char *nomeArquivo, ListaPalavras *lista)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[TAMANHO];
    int contadorLinha = 0;
    while (fgets(linha, TAMANHO, arquivo))
    {
        char *linhaCopia = strdup(linha);
        processarLinha(linhaCopia, contadorLinha, lista);
        free(linhaCopia);
        contadorLinha++;
    }

    fclose(arquivo);
}

// Funções de processamento para árvore (implementações devem ser adaptadas para a árvore)
void processarLinhaArvore(char *linha, int numeroLinha, ArvorePalavras *arvore)
{
    for (int i = 0; linha[i]; i++)
    {
        linha[i] = tolower(linha[i]);
        if (ispunct(linha[i]))
        {
            linha[i] = ' ';
        }
    }

    char *palavra = strtok(linha, " ");
    while (palavra != NULL)
    {
        if (strlen(palavra) > 0)
        {
            inserirNaArvore(arvore, palavra, numeroLinha + 1);
        }
        palavra = strtok(NULL, " ");
    }
}

void processarArquivoArvore(const char *nomeArquivo, ArvorePalavras *arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[TAMANHO];
    int contadorLinha = 0;
    while (fgets(linha, TAMANHO, arquivo))
    {
        char *linhaCopia = strdup(linha);
        processarLinhaArvore(linhaCopia, contadorLinha, arvore);
        free(linhaCopia);
        contadorLinha++;
    }

    fclose(arquivo);
}

// Funções para liberar a lista e a árvore
void liberarListaPalavras(ListaPalavras *lista)
{
    NoPalavra *atual = lista->cabeca;
    while (atual != NULL)
    {
        NoPalavra *temp = atual;
        atual = atual->proximo;

        free(temp->palavra);
        free(temp->linhas);
        free(temp);
    }
    free(lista);
}

void liberarNoArvore(NoArvore *no)
{
    if (no == NULL)
        return;
    liberarNoArvore(no->esquerda);
    liberarNoArvore(no->direita);
    free(no->palavra);
    free(no->linhas);
    free(no);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Uso: %s <nome_do_arquivo> <tipo_estrutura>\n", argv[0]);
        printf("tipo_estrutura: lista ou arvore\n");
        return 1;
    }

    const char *nomeArquivo = argv[1];
    const char *tipoEstrutura = argv[2];
    clock_t inicio, fim;
    double tempoUsado;
    char palavraBusca[TAMANHO];

    inicio = clock();

    if (strcmp(tipoEstrutura, "lista") == 0)
    {
        ListaPalavras *lista = criarListaPalavras();
        processarArquivo(nomeArquivo, lista);

        fim = clock();
        tempoUsado = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo para carregar e construir indice (lista): %.2f segundos\n", tempoUsado);

        while (1)
        {
            printf("Digite a palavra a ser buscada (ou 'sair' para encerrar): ");
            scanf("%999s", palavraBusca);

            if (strcmp(palavraBusca, "sair") == 0)
            {
                break;
            }

            buscarPalavra(lista, palavraBusca);
        }

        liberarListaPalavras(lista);
    }
    else if (strcmp(tipoEstrutura, "arvore") == 0)
    {
        ArvorePalavras *arvore = criarArvorePalavras();
        processarArquivoArvore(nomeArquivo, arvore);

        fim = clock();
        tempoUsado = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo para carregar e construir indice (arvore): %.2f segundos\n", tempoUsado);

        while (1)
        {
            printf("Digite a palavra a ser buscada (ou 'sair' para encerrar): ");
            scanf("%999s", palavraBusca);

            if (strcmp(palavraBusca, "sair") == 0)
            {
                break;
            }

            buscarNaArvore(arvore, palavraBusca);
        }

        liberarArvore(arvore);
    }
    else
    {
        printf("Tipo de estrutura inválido. Use 'lista' ou 'arvore'.\n");
        return 1;
    }

    return 0;
}
