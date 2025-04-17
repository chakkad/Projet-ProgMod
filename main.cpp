#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "coord.hpp" 
#include <iostream>

int main() {
	Coord c(23,24);
	cout << "Coordonnees : " << c << endl;
	return 0;
}
