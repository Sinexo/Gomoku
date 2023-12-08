
CC = gcc


CFLAGS = -Wall -g -Werror -fsanitize=address


TARGET = gomoku

# Fichiers source
SOURCES = main.c gomoku.c minmax.c move.c

HEADERS = gomoku.h minmax.h

all: $(TARGET)


$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)


clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
