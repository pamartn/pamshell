# Ces cibles ne sont pas des vrais fichiers
.PHONY: clean

# On désactive toutes les règles implicites

# Déclarations de constantes
CC = gcc
CFLAGS = -Wall -Werror -W  -g
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
LDFLAGS=-lreadline

program: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $^

makefile.dep: $(SRC)
	gcc -MM $^ > $@

clean:
	rm -f *.o program

include makefile.dep
