#ifndef LBP_H
#define LBP_H

#include "pgm.h"
#include <stdint.h>

/*
    Calcula lbp p8 
    no pixel (x, y).
*/
uint16_t lbp_p8(PGMImage *img, int x, int y);

/*
    Calcula lbp p16
    no pixel (x, y).
*/
uint16_t lbp_p16(PGMImage *img, int x, int y);

/*
    Calcula histograma p8.
    Aloca dinamicamente vetor
    de 256 posições.
*/
uint32_t *histograma_p8(PGMImage *img);

/*
    Calcula histograma p16.
    Aloca dinamicamente vetor
    de 65536 posições.
*/
uint32_t *histograma_p16(PGMImage *img);

uint16_t *gera_lbp(PGMImage *img, int vizinhos);

#endif
