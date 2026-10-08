#ifndef DIRETORIO_H
#define DIRETORIO_H

/*
    Retorna lista de arquivos pgm
    no diretório.
*/
char **lista_pgm(char *diretorio, int *quantidade);

/*
    Libera memória utilizada
    pela lista de arquivos.
*/
void libera_lista(char **lista, int quantidade);

#endif
