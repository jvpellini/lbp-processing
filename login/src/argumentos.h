#ifndef ARQUIVOS_H
#define ARQUIVOS_H

typedef struct
{
    char *diretorio;
    char *saida;
    int vizinhos;
    char *diretorio_imagens;
} Argumentos;

/*
    Interpreta argumentos da linha
    de comando.
*/
int le_argumentos(int argc, char **argv, Argumentos *args);

/*
    Mostra as informações de
    utilização do programa.
*/
void mostra_ajuda(void);

#endif
