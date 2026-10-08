#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lbp.h"

#define BINS_P8 256u
#define BINS_P16 65536u

static const int DX8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int DY8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

static const int DX16[16] = {-2, -1, 0, 1, 2, -2, 2, -2, 2, -2, 2, -2, -1, 0, 1, 2};
static const int DY16[16] = {-2, -2, -2, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 2, 2, 2};

typedef uint16_t (*LBPFunction)(PGMImage *img, int x, int y);

uint16_t lbp_pixel(PGMImage *img, int x, int y, int n, int raio,
                   const int *dx, const int *dy)
{
    uint16_t centro, codigo = 0;

    if (!img || !img->pixels)
        return 0;

    if (x < raio || y < raio || x >= img->largura - raio ||
        y >= img->altura - raio)
        return 0;

    centro = img->pixels[(size_t)y * img->largura + x];

    for (int i = 0; i < n; i++)
    {
        uint16_t vizinho = 
            img->pixels[(size_t)(y + dy[i]) * img->largura + (x + dx[i])];
        
        if (vizinho >= centro)
            codigo |= (uint16_t)(1u << i);
    }

    return codigo;
}

uint16_t lbp_p8(PGMImage *img, int x, int y)
{
    return lbp_pixel(img, x, y, 8, 1, DX8, DY8);
}

uint16_t lbp_p16(PGMImage *img, int x, int y)
{
    return lbp_pixel(img, x, y, 16, 2, DX16, DY16);
}

uint32_t *histograma(PGMImage *img, unsigned bins, int raio, LBPFunction lbp)
{
    uint32_t *hist;

    if (!img || !img->pixels)
    {
        fprintf(stderr, "Erro: imagem invalida ao calcular o histograma.\n");
        return NULL;
    }

    hist = calloc(bins, sizeof(uint32_t));
    if (!hist)
    {
        fprintf(stderr, "Erro: falha de alocacao de memoria para "
                "o histograma.\n");
        return NULL;
    }

    for (int y = raio; y < img->altura - raio; y++)
        for (int x = raio; x < img->largura - raio; x++)
            hist[lbp(img, x, y)]++;

    return hist;
}

uint32_t *histograma_p8(PGMImage *img)
{
    return histograma(img, BINS_P8, 1, lbp_p8);
}

uint32_t *histograma_p16(PGMImage *img)
{
    return histograma(img, BINS_P16, 2, lbp_p16);
}

uint16_t *gera_lbp(PGMImage *img, int vizinhos)
{
    uint16_t *resultado;
    size_t total;
    int raio;

    if (img == NULL || img->pixels == NULL)
        return NULL;

    if (vizinhos == 8)
        raio = 1;
    else if (vizinhos == 16)
        raio = 2;
    else
        return NULL;

    total = (size_t)img->largura * (size_t)img->altura;

    resultado = calloc(total, sizeof(uint16_t));

    if (resultado == NULL)
        return NULL;

    for (int y = raio; y < img->altura - raio; y++)
    {
        for (int x = raio; x < img->largura - raio; x++)
        {
            size_t pos = (size_t)y * img->largura + x;

            if (vizinhos == 8)
                resultado[pos] = lbp_p8(img, x, y);
            else
                resultado[pos] = lbp_p16(img, x, y);
        }
    }

    return resultado;
}



















