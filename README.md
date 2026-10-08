# LBP Image Processing

Implementação em C de um programa para processamento e análise de imagens utilizando o descritor **Local Binary Pattern (LBP)**.

Projeto desenvolvido como atividade acadêmica na disciplina de Programação 2 — Ciência da Computação, UFPR.

## Funcionalidades

- Leitura de imagens PGM nos formatos P2 e P5
- Implementação do LBP(8,1)
- Implementação do LBP(16,2)
- Geração de histogramas LBP
- Geração opcional de imagens LBP
- Processamento de múltiplas imagens
- Argumentos de linha de comando
- Tratamento de erros
- Gerenciamento dinâmico de memória

## Tecnologias

- C
- C11
- Makefile
- Linux
- Git

## Organização

```text
src/
├── main.c
├── argumentos.c
├── argumentos.h
├── diretorio.c
├── diretorio.h
├── pgm.c
├── pgm.h
├── lbp.c
├── lbp.h
├── saida.c
└── saida.h
```

## Compilação

```bash
cd src
make
```

## Execução

```bash
./lbp -d ./imagens -n 8 -o resultado.txt
```

Para utilizar 16 vizinhos e gerar imagens LBP:

```bash
./lbp -d ./imagens -n 16 -o resultado.txt -i ./lbp_images
```

## Conceitos praticados

O projeto envolve leitura e escrita de arquivos, processamento de imagens, manipulação de diretórios, ponteiros, alocação dinâmica de memória, modularização, argumentos de linha de comando e desenvolvimento com Makefile.
