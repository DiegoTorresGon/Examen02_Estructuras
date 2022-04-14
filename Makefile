SRCDIR=src
INCDIR=include
TESTDIR=test

TESTFLAGS=-g3 -O0 \
	-fsanitize=address \
	-fsanitize=undefined \
	-fno-sanitize-recover=all \
	-fsanitize=float-divide-by-zero \
	-fsanitize=float-cast-overflow

CC=gcc
CFLAGS=-std=c18 -Wall -Wpedantic -Werror -Wextra -I$(INCDIR)/

all: test-imp

test-imp: $(TESTDIR)/imp.o
	@./$<

$(TESTDIR)/imp.o: $(TESTDIR)/imp.c $(SRCDIR)/imp.o $(SRCDIR)/mem.o
	@echo "Compilando casos de prueba de lenguaje IMP"
	@$(CC) $(CFLAGS) $(TESTFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compilando $<"
	@$(CC) $(CFLAGS) $(TESTFLAGS) -c -o $@ $<

$(SRCDIR)/imp.o: $(INCDIR)/imp.h


$(SRCDIR)/mem.o: $(SRCDIR)/mem.c
	@echo "Compilando $<"
	@$(CC) $(CFLAGS) $(TESTFLAGS) -c -o $@ $<

clean:
	@rm -rf test/*.o src/*.o
