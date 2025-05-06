CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= main test

all: main tests
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

main: coord.o main.o ensemble.o animal.o population.o grille.o jeu.o
	$(CXX) -o $@ $^ $(LDFLAGS)
tests: coord.o test.o ensemble.o animal.o population.o grille.o jeu.o
	$(CXX) -o $@ $^ $(LDFLAGS)

main.o: coord.hpp ensemble.hpp animal.hpp population.hpp
coord.o: coord.hpp
test.o: coord.hpp ensemble.hpp animal.hpp population.hpp doctest.h
ensemble.o: ensemble.hpp
animal.o = animal.hpp coord.hpp espece.hpp
population.o = population.hpp animal.hpp ensemble.hpp 
grille.o = grille.hpp coord.hpp
jeu.o = jeu.hpp



check: tests
	./tests

clean:
	rm -f *.o $(EXEC_FILES)

