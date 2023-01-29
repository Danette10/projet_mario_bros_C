CC = gcc
EXEC = bin/MarioBros
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall `sdl2-config --cflags --libs`

all: $(EXEC) clean

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) icon.res

clean:
	rm -rf src/*.o