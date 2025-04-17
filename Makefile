CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= main tests

all: main tests
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

tests: test.o coord.o
	$(CXX) -o $@ $^ $(LDFLAGS)

main: coord.o main.o
	$(CXX) -o $@ $^ $(LDFLAGS)


coord.o: coord.hpp
test.o: coord.hpp
main.o: coord.hpp

check: tests
	./tests

clean:
	rm -rf *.o $(EXEC_FILES)
