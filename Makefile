CC=g++
CFLAGS = -g -std=c++20 -I$(IDIR)

IDIR=include
ODIR=.obj
SRCDIR=src

_DEPS = game.hpp
DEPS = Makefile $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o game.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(ODIR)/* bin/main 