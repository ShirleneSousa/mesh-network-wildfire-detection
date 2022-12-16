CFLAGS = -Wall
CC = gcc

OBJDIR = objects
BINDIR = bin

SRC := $(shell find . -name '*.c')
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

all: 
	@./bin/detector_incendio

compile: binfolder objfolder bin/detector_incendio

bin/detector_incendio: $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

binfolder:
	@mkdir -p $(BINDIR)

objfolder:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%main.o: src/main.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c %.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	@rm -Rf bin objects incendios.log