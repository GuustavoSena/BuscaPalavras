#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "src/lista_palavras.h"
#include "src/arvore_palavras.h"

#define TAMANHO 1000

// Funções de processamento para lista
void processarLinha(char *linhaOriginal, int numeroLinha, ListaPalavras *lista)
{
    char *linha = strdup(linhaOriginal); // Faz uma cópia da linha para manipulação

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
            inserirPalavra(lista, palavra, numeroLinha + 1, linhaOriginal);
        }
        palavra = strtok(NULL, " ");
    }

    free(linha); // Libera a cópia da linha
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
    printf("Numero de linhas no arquivo: %d\n", contadorLinha);
}

void processarLinhaArvore(char *linhaOriginal, int numeroLinha, ArvorePalavras *arvore)
{
    char *linha = strdup(linhaOriginal); // Faz uma cópia da linha para manipulação
    // Remove quebras de linha e pontuações
    for (int i = 0; linha[i]; i++)
    {
        linha[i] = tolower(linha[i]);
        if (ispunct(linha[i]))
        {
            linha[i] = ' ';
        }
    }

    // Extrai e insere palavras na árvore
    char *palavra = strtok(linha, " ");
    while (palavra != NULL)
    {
        if (strlen(palavra) > 0)
        {
            inserirNaArvore(arvore, palavra, numeroLinha + 1, linhaOriginal);
        }
        palavra = strtok(NULL, " ");
    }

    free(linha); // Libera a cópia da linha
}

// Funções de processamento para árvore (implementações devem ser adaptadas para a árvore)
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
    printf("Numero de linhas no arquivo: %d\n", contadorLinha);
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

    printf("Tipo de indice: '%s'\n", tipoEstrutura);
    printf("Arquivo texto: '%s'\n", nomeArquivo);

    inicio = clock();

    if (strcmp(tipoEstrutura, "lista") == 0)
    {
        ListaPalavras *lista = criarListaPalavras();
        processarArquivo(nomeArquivo, lista);

        fim = clock();
        tempoUsado = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo para carregar e construir indice: %.2f segundos\n", tempoUsado);

        while (1)
        {
            printf("> ");
            scanf("%999s", palavraBusca);

            if (strcmp(palavraBusca, "fim") == 0)
            {
                break;
            }
            else if (strcmp(palavraBusca, "busca") == 0)
            {
                scanf("%999s", palavraBusca);
                buscarPalavra(lista, palavraBusca);
            }
            else
            {
                printf("Opcao invalida!\n");
            }
        }

        liberarListaPalavras(lista);
    }
    else if (strcmp(tipoEstrutura, "arvore") == 0)
    {
        ArvorePalavras *arvore = criarArvorePalavras();
        processarArquivoArvore(nomeArquivo, arvore);

        fim = clock();
        tempoUsado = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Tempo para carregar e construir indice: %.2f segundos\n", tempoUsado);

        while (1)
        {
            printf("> ");
            scanf("%999s", palavraBusca);

            if (strcmp(palavraBusca, "fim") == 0)
            {
                break;
            }
            else if (strcmp(palavraBusca, "busca") == 0)
            {
                scanf("%999s", palavraBusca);
                buscarNaArvore(arvore, palavraBusca);
            }
            else
            {
                printf("Opcao invalida!\n");
            }
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
