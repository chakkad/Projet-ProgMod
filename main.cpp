#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "coord.hpp" 
#include <iostream>

int main() {
    //Coord.cpp 
	Coord c(23,24);
	cout << "Coordonnees : " << c << endl; //EXO 2 (8) testing the << operator
	return 0;

    //Ensemble.cpp
    Ensemble e;
    e.ajoute(1);
    e.ajoute(2);
    e.ajoute(3);

    std::cout << "Tirage: ";
    while (!e.estVide()) {
        std::cout << e.tire() << " ";
    }
    std::cout << std::endl;
    return 0;
}
