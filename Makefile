CC = gcc
CFLAGS = -Wall -I. -Ipocketpy -Wno -char -subscripts

SRC = main.c levenshtein.c pocketpy/pocketpy.c hamming.c

BIN = main

default: $(BIN)

#Comando de compilaçao no terminal
$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) -lm

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)
