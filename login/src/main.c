#include <stdio.h>
#include <stdlib.h>

#include "argumentos.h"
#include "diretorio.h"
#include "pgm.h"
#include "lbp.h"
#include "saida.h"

int main(int argc, char **argv)
{
    Argumentos args;

    char **arquivos;
    int quantidade;
    int i;

    FILE *saida;

    /* Le os argumentos da linha de comando */
    if (le_argumentos(argc, argv, &args) == 0)
        return 1;

    /* Procura os arquivos PGM */
    arquivos = lista_pgm(args.diretorio, &quantidade);

    if (arquivos == NULL)
        return 1;

    /* Abre o arquivo de saida */
    saida = fopen(args.saida, "w");

    if (saida == NULL)
    {
        fprintf(stderr,
                "Erro: nao foi possivel criar o arquivo '%s'.\n",
                args.saida);

        libera_lista(arquivos, quantidade);
        return 1;
    }

    /* Processa cada imagem */
    for (i = 0; i < quantidade; i++)
    {
        FILE *arquivo;
        PGMImage *imagem;
        uint32_t *histograma;
        char caminho[1024];

        /* Monta o caminho da imagem */
        snprintf(caminho, sizeof(caminho),
                 "%s/%s",
                 args.diretorio,
                 arquivos[i]);

        /* Abre a imagem */
        arquivo = fopen(caminho, "rb");

        if (arquivo == NULL)
        {
            fprintf(stderr,
                    "Erro: nao foi possivel abrir '%s'.\n",
                    caminho);
            continue;
        }

        imagem = le_imagem(arquivo);

        fclose(arquivo);

        if (imagem == NULL)
        {
            fprintf(stderr,
                    "Erro: nao foi possivel ler '%s'.\n",
                    caminho);
            continue;
        }

        /*
         * Calcula o histograma de acordo com
         * a quantidade de vizinhos escolhida.
         */
        if (args.vizinhos == 8)
            histograma = histograma_p8(imagem);
        else
            histograma = histograma_p16(imagem);

        if (histograma == NULL)
        {
            fprintf(stderr,
                    "Erro: nao foi possivel calcular o histograma de '%s'.\n",
                    caminho);

            libera_imagem(imagem);
            continue;
        }

        /*
         * Escreve as caracteristicas no arquivo
         * de saida.
         */
        if (imprime_informacoes(
                saida,
                arquivos[i],
                imagem,
                args.vizinhos,
                histograma) == 0)
        {
            fprintf(stderr,
                    "Erro: nao foi possivel escrever a saida.\n");

            free(histograma);
            libera_imagem(imagem);
            fclose(saida);
            libera_lista(arquivos, quantidade);

            return 1;
        }

        /*
         * Se foi informado -i, gera e salva
         * a imagem LBP.
         */
        if (args.diretorio_imagens != NULL)
        {
            uint16_t *imagem_lbp;
            char caminho_lbp[1024];

            imagem_lbp = gera_lbp(imagem, args.vizinhos);

            if (imagem_lbp == NULL)
            {
                fprintf(stderr,
                        "Erro: nao foi possivel gerar a imagem LBP de '%s'.\n",
                        arquivos[i]);
            }
            else
            {
                snprintf(caminho_lbp, sizeof(caminho_lbp),
                         "%s/%s",
                         args.diretorio_imagens,
                         arquivos[i]);

                if (!imprime_lbp(caminho_lbp,
                                 imagem,
                                 imagem_lbp,
                                 args.vizinhos))
                {
                    fprintf(stderr,
                            "Erro: nao foi possivel salvar '%s'.\n",
                            caminho_lbp);
                }

                free(imagem_lbp);
            }
        }

        free(histograma);

        libera_imagem(imagem);
    }

    fclose(saida);

    libera_lista(arquivos, quantidade);

    return 0;
}
