CC = gcc
CFLAGS = -Wall -g -Iinclude
SRCS = src/main.c src/parser.c src/printer.c src/sexp.c src/builtins.c
TARGET = c-sexp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)