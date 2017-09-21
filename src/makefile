IDIR =../include
CC=g++

ODIR=obj

LIBS=-lm

_OBJ_TEST = main.o testa_string_soma.o string_soma.o lista_func.o
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ_TEST))

_DEPS_TEST = string_soma.hpp catch.hpp lista_func.hpp
DEPS_TEST = $(patsubst %,$(IDIR)/%,$(_DEPS_TEST))

_OBJ = testa_soma_string_stdin.o string_soma.o lista_func.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS = string_soma.hpp lista_func.hpp 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

FLAGS = -I$(IDIR) -ftest-coverage -fprofile-arcs

$(ODIR)/%.o: %.cpp $(DEPS_TEST)
	$(CC) -c -o $@ $< $(FLAGS)

testa_string_soma: $(OBJ_TEST)
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)
	./testa_string_soma
	gcovr -r . --html -o gcov/coverage.html --html-details

testa_soma_string_stdin: $(OBJ)
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)
	./testa_soma_string_stdin

.PHONY: clean

clean:
	-rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	-rm -f $(ODIR)/*.gcno
	-rm -f $(ODIR)/*.gcda