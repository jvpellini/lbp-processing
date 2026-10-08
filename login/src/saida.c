#include <stdio.h>
#include <stdint.h>
#include "saida.h"

#define BINS_P8 256u
#define BINS_P16 65536u

int imprime_informacoes(FILE *arquivo, char *nome, PGMImage *img,
                        int vizinhos, uint32_t *histograma)
{
    unsigned bins;

    if (!arquivo || !nome || !img || !histograma)
    {
        fprintf(stderr, "Erro: argumentos invalidos ao gravar "
                "as informacoes da imagem.\n");
        return 0;
    }

    if (vizinhos == 8)
        bins = BINS_P8;
    else if (vizinhos == 16)
        bins = BINS_P16;
    else
    {
        fprintf(stderr, "Erro: numero de vizinhos invalido (%d). "
                "Valores permitidos: 8 ou 16.\n", vizinhos);
        return 0;
    }

    if (fprintf(arquivo, "%s %d %d %d", nome, img->largura,
                img->altura, vizinhos) < 0)
    {
        fprintf(stderr, "Erro: falha ao escrever no arquivo de saida.\n");
        return 0;
    }

    for (unsigned i = 0; i < bins; i++)
    {
        if (fprintf(arquivo, " %lu", (unsigned long)histograma[i]) < 0)
        {
            fprintf(stderr, "Erro: falha ao escrever no arquivo de saida.\n");
            return 0;
        }
    }

    if (fputc('\n', arquivo) == EOF)
    {
        fprintf(stderr, "Erro: falha ao escrever no arquivo de saida.\n");
        return 0;
    }

    return 1;
}

int imprime_lbp(char *caminho, PGMImage *img, uint16_t *lbp, int vizinhos)
{
    FILE *arquivo;
    size_t total;

    if (!caminho || !img || !lbp)
    {
        fprintf(stderr, "Erro: argumentos invalidos ao gravar a imagem.\n");
        return 0;
    }

    if (vizinhos != 8 && vizinhos != 16)
    {
        fprintf(stderr, "Erro: numero de vizinhos invalido (%d). "
                "Valores permitidos: 8 ou 16.\n", vizinhos);
        return 0;
    }

    arquivo = fopen(caminho, "wb");
    if (!arquivo)
    {
        fprintf(stderr, "Erro: nao foi possivel criar o arquivo de "
                "imagem LBP '%s'.\n", caminho);
        return 0;
    }

    if (fprintf(arquivo, "P5\n%d %d\n255\n", img->largura, img->altura) < 0)
    {
        fprintf(stderr, "Erro: falha ao escrever imagem LBP '%s'.\n", caminho);
        fclose(arquivo);
        return 0;
    }

    total = (size_t)img->largura * (size_t)img->altura;
    for (size_t i = 0; i < total; i++)
    {
        unsigned valor = lbp[i];

        if (vizinhos == 16)
            valor = valor / 257;

        if (fputc((int)valor, arquivo) == EOF)
        {
            fprintf(stderr, "Erro: falha ao escrever a "
                    "imagem LPB '%s'.\n", caminho);
            fclose(arquivo);
            return 0;
        }
    }

    if (fclose(arquivo) == EOF)
    {
        fprintf(stderr, "Erro: falha ao fechar a imagem LPB '%s'.\n", caminho);
        return 0;
    }

    return 1;
}




















