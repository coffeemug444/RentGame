CC=g++
CFLAGS = -g -std=c++20 -I$(IDIR)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

IDIR=include
ODIR=.obj
SRCDIR=src

_DEPS = game.hpp ui.hpp util.hpp
DEPS = Makefile $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o game.o ui.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/* bin/main 