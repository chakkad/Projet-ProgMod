CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= main test

all: main tests
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

main: coord.o main.o ensemble.o
	$(CXX) -o $@ $^ $(LDFLAGS)
tests: coord.o test.o ensemble.o
	$(CXX) -o $@ $^ $(LDFLAGS)

main.o: coord.hpp
coord.o: coord.hpp
test.o: coord.hpp
ensemble.o: ensemble.hpp

check: tests
	./tests

clean:
	rm -f *.o $(EXEC_FILES)
