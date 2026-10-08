#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"

int le_argumentos(int argc, char **argv, Argumentos *args)
{
    int i;

    args->diretorio = NULL;
    args->saida = NULL;
    args->vizinhos = 0;
    args->diretorio_imagens = NULL;

    for (i = 1; i < argc; i++)
    {

        if (strcmp(argv[i],"-h") == 0)
        {
            mostra_ajuda();
            return 0;
        }

        else if (strcmp(argv[i], "-d") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Erro: -d precisa de um diretorio.\n");
                return 0;
            }
            
            args->diretorio = argv[i + 1];
            i++;
        }

        else if (strcmp(argv[i], "-n") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Erro: -n precisa de um valor.\n");
                return 0;
            }

            args->vizinhos = atoi(argv[i + 1]);

            if ((args->vizinhos != 8) && (args->vizinhos != 16))
            {
                fprintf(stderr, "Erro: -n deve ser 8 ou 16.\n");
                return 0;
            }
            
            i++;
        }

        else if (strcmp(argv[i],"-o") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Erro: -o precisa de um arquivo.\n");
                return 0;
            }
            
            args->saida = argv[i + 1];
            i++;
        }

        else if (strcmp(argv[i],"-i") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Erro: -i precisa de um diretorio.\n");
                return 0;
            }

            args->diretorio_imagens = argv[i + 1];
            i++;
        }
        
        else
        {
            fprintf(stderr, "Erro: opcao desconhecida: %s\n", argv[i]);
            return 0;
        }    
    }

    
    if (args->diretorio == NULL)
    {
        fprintf(stderr, "Erro: diretorio de entrada nao informado.\n");
        return 0;
    }

    if (args->vizinhos == 0)
    {
        fprintf(stderr, "Erro: numero de vizinhos nao informado.\n");
        return 0;
    }
    
    if (args->saida == NULL)
    {
        fprintf(stderr, "Erro: arquivo de saida nao informado.\n");
        return 0;
    }

    return 1;
}

void mostra_ajuda(void)
{
    printf("Uso:\n");
    printf(" ./lbp -d <diretorio> -n <vizinhos> -o <arquivo_saida>\n");
    printf("\n");
    printf("Opcoes:\n");
    printf(" -d <diretorio>       Diretorio com imagens PGM\n");
    printf(" -n <vizinhos>        Numero de vizinhos: 8 ou 16\n");
    printf(" -o <arquivo_saida>   Arquivo para salvar caracteristicas\n");
    printf(" -i <diretorio>       Diretorio para salvar imagens LBP\n");
    printf(" -h                   Mostra essa ajuda\n");
}














