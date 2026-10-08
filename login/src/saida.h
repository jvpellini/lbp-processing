#ifndef SAIDA_H
#define SAIDA_H

#include <stdio.h>
#include <stdint.h>
#include "pgm.h"

/*
    Imprime informações da imagem
    no arquivo de saída.
*/
int imprime_informacoes
(
    FILE *arquivo,
    char *nome,
    PGMImage *img,
    int vizinhos,
    uint32_t *histograma
);

/*
    Imprime imagem lbp no formato
    PGM.
*/
int imprime_lbp
(
    char *caminho,
    PGMImage *img,
    uint16_t *lbp,
    int vizinhos
);

#endif
