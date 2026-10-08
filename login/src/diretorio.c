#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "diretorio.h"

char **lista_pgm(char *diretorio, int *quantidade)
{
    DIR *dir;
    struct dirent *entrada;
    
    char **lista = NULL;
    int capacidade = 0;
    int n = 0;

    dir = opendir(diretorio);

    if (dir == NULL)
    {
        fprintf(stderr, "Erro: nao foi possivel abrir o diretorio '%s'.\n", diretorio);
        return NULL;
    }

    while ((entrada = readdir(dir)) != NULL)
    {
        char *nome = entrada->d_name;
        char *formato;

        formato = strrchr(nome,'.');

        if (formato == NULL)
            continue;

        if (strcmp(formato, ".pgm") != 0)
            continue;
        
        if (n == capacidade)
        {
            char **temp;
            
            if (capacidade == 0)
                capacidade = 10;
            else
                capacidade *= 2;

            temp = realloc(lista, capacidade * sizeof(char *));

            if (temp == NULL)
            {
                fprintf(stderr, "Erro: memoria insuficiente.\n");
                libera_lista(lista, n);
                closedir(dir);
                return NULL;
            }

            lista = temp;
        }

        lista[n] = malloc((strlen(nome) + 1) * sizeof(char));

        if (lista[n] == NULL)
        {
            fprintf(stderr, "Erro: memoria insuficiente.\n");
            libera_lista(lista, n);
            closedir(dir);
            return NULL;
        }

        strcpy(lista[n], nome);

        n++;
    }

    closedir(dir);

    *quantidade = n;

    return lista;
}

void libera_lista(char **lista, int quantidade)
{
    int i;

    if (lista == NULL)
        return;

    for (i = 0; i < quantidade; i++)
    {
        free(lista[i]);
    }

    free(lista);
}

















