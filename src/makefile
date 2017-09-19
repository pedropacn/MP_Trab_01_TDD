IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lm

_DEPS = string_soma.hpp catch.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o testa_string_soma.o string_soma.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testmake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	./testmake

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~