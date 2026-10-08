CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11

TARGET = ../bin/lbp

OBJ = main.o argumentos.o diretorio.o pgm.o lbp.o saida.o

tudo: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p ../bin
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

main.o: main.c argumentos.h diretorio.h pgm.h lbp.h saida.h
	$(CC) $(CFLAGS) -c main.c

argumentos.o: argumentos.c argumentos.h
	$(CC) $(CFLAGS) -c argumentos.c

diretorio.o: diretorio.c diretorio.h
	$(CC) $(CFLAGS) -c diretorio.c

pgm.o: pgm.c pgm.h
	$(CC) $(CFLAGS) -c pgm.c

lbp.o: lbp.c lbp.h pgm.h
	$(CC) $(CFLAGS) -c lbp.c

saida.o: saida.c saida.h pgm.h
	$(CC) $(CFLAGS) -c saida.c

clean:
	rm -f *.o

.PHONY: tudo clean
