#ifndef PGM_H
#define PGM_H

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    int largura;
    int altura;
    int maxval;
    uint16_t *pixels;
} PGMImage;

/*
    Lê imagem pgm (p2 ou p5).
    Retorna estrutura com a imagem.
*/
PGMImage *le_imagem(FILE *arquivo);

/*
    Libera a memória utilizada pela
    imagem.
*/
void *libera_imagem(PGMImage *img);

#endif


