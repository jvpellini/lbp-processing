#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "pgm.h"

#define MAXVAL_LIMITE 65535

int le_inteiro(FILE *f, int *valor)
{
    int c;
    int v = 0;

    for (;;)
    {
        c = getc(f);

        if (c == EOF)
            return 0;

        if (c == '#')
        {
            while (((c = getc(f)) != '\n') && (c != EOF))
                ;

            if (c == EOF)
                return 0;

            continue;
        }

        if (!isspace(c))
            break;
    }

    if (!isdigit(c))
        return 0;

    while (isdigit(c))
    {
        v = v * 10 + (c - '0');
        c = getc(f);
    }

    if (c == '#')
        ungetc(c, f);
    else if (c == '\r')
    {
        int prox = getc(f);

        if ((prox != '\n') && (prox != EOF))
            ungetc(prox, f);
    }
    else if ((c != EOF) && !isspace(c))
        return 0;

    *valor = v;
    return 1;
}

int le_corpo_p2(FILE *f, PGMImage *img, size_t total)
{
    for (size_t i = 0; i < total; i++)
    {
        int v;

        if (!le_inteiro(f, &v))
        {
            fprintf(stderr, "Erro: corpo do PGM P2 incompleto ou invalido " 
                    "(esperados %zu valores, lidos %zu).\n", total, i);
            return 0;  
        }
        
        if (v > img->maxval)
        {
            fprintf(stderr, "Erro: valor de pixel %d maior que "
                    "MAXVAL (%d).\n", v, img->maxval);
            return 0;
        }

        img->pixels[i] = (uint16_t)v;
    }
    return 1;
}

int le_corpo_p5(FILE *f, PGMImage *img, size_t total)
{
    int dois_bytes = (img->maxval >= 256);

    for (size_t i = 0; i < total; i++)
    {
        int c = getc(f);
        
        if (c == EOF)
        {
            fprintf(stderr, "Erro: corpo do PGM P5 incompleto "
                    "(esperados %zu pixels, lidos %zu).\n", total, i);
            return 0;
        }

        unsigned v = (unsigned)c;
        
        if (dois_bytes)
        {
            int c2 = getc(f);

            if (c2 == EOF)
            {
                fprintf(stderr, "Erro: corpo do PGM P5 incompleto "
                        "(esperados %zu pixels, lidos %zu.\n", total, i);
                return 0;
            }

            v = (v << 8) | (unsigned)c2;
        }

        if (v > (unsigned)img->maxval)
        {
            fprintf(stderr, "Erro: valor de pixel %u maior que "
                    "MAXVAL (%d).\n", v, img->maxval);
            return 0;
        }

        img->pixels[i] = (uint16_t)v;
    }

    return 1;
}

PGMImage *le_imagem(FILE *arquivo)
{
    PGMImage *img;
    int lar, alt, maxval, c1, c2, c3, tipo, leitura_ok;
    size_t total;

    if (!arquivo)
    {
        fprintf(stderr, "Erro: arquivo PGM nao foi aberto.\n");
        return NULL;
    }

    c1 = getc(arquivo);
    while (c1 == '#' || isspace(c1))
    {
        if (c1 == '#')
            while ((c1 = getc(arquivo)) != '\n' && c1 != EOF)
                ;
        
        if (c1 != EOF)
            c1 = getc(arquivo);
    }

    c2 = getc(arquivo);
    if (c1 != 'P' || !isdigit(c2))
    {
        fprintf(stderr, "Erro: arquivo nao corresponde a um PGM valido.\n");
        return NULL;
    }

    if (c2 != '2' && c2 != '5')
    {
        fprintf(stderr, "Erro: formato PGM desconhecido (P%c). "
                "Apenas P2 e P5 sao suportados.\n", c2);
        return NULL;
    }

    tipo = c2 - '0';

    c3 = getc(arquivo);
    if (c3 == EOF || (!isspace(c3) && c3 != '#'))
    {
        fprintf(stderr, "Erro: cabecalho PGM invalido apos numero magico.\n");
        return NULL;
    }

    ungetc(c3, arquivo);
    if (!le_inteiro(arquivo, &lar) || !le_inteiro(arquivo, &alt) ||
        !le_inteiro(arquivo, &maxval))
    {
        fprintf(stderr, "Erro: cabecalho PGM invalido ou incompleto.\n");
        return NULL;
    }

    if (lar <= 0 || alt <= 0)
    {
        fprintf(stderr, "Erro: dimensoes invalidas no PGM (%d x %d).\n",
                lar, alt);
        return NULL;
    }

    if (maxval <= 0 || maxval > MAXVAL_LIMITE)
    {
        fprintf(stderr, "Erro: maxval invalido no PGM (%d). "
                "Deve estar entre 1 e %d.\n", maxval, MAXVAL_LIMITE);
        return NULL;
    }

    if ((size_t)lar > SIZE_MAX / (size_t)alt)
    {
        fprintf(stderr, "Erro: imagem PGM grande demais.\n");
        return NULL;
    }

    total = (size_t)lar * (size_t)alt;

    img = malloc(sizeof(PGMImage));
    if (!img)
    {
        fprintf(stderr, "Erro: falha de alocacao de memoria "
                "para a imagem.\n");
        return NULL;
    }

    img->largura = (int)lar;
    img->altura = (int)alt;
    img->maxval = (int)maxval;
    img->pixels = malloc(total * sizeof(uint16_t));
    if (!img->pixels)
    {
        fprintf(stderr, "Erro: falha de alocacao de memoria "
                "para os pixels.\n");
        free(img);
        return NULL;
    }

    if (tipo == 2)
        leitura_ok = le_corpo_p2(arquivo, img, total);
    else
        leitura_ok = le_corpo_p5(arquivo, img, total);

    if (!leitura_ok)
    {
        libera_imagem(img);
        return NULL;
    }

    return img;
}

void *libera_imagem(PGMImage *img)
{
    if (img)
    {
        free(img->pixels);
        free(img);
    }

    return NULL;
}






















