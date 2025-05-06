#include <iostream>
#include "ensemble.hpp"
using namespace std;

const int TAILLEGRILLE = 40; //EXO 2 (1) Can be changed

class Coord { //EXO 2 (2)

private : //EXO 2 (2)
	int lig; // Lines
	int col; // Columns

public :
	// Constructors
	Coord(int lig, int col); //EXO 2 (3)
    Coord(int entier); //EXO 2 (11)
    //Getters
	int getLig() const; //EXO 2 (5)
	int getCol() const; //EXO 2 (5)
    //Methodes
    int Toint() const; //EXO 2 (11)
    Ensemble voisines() const; //EXO 4 (1)
    //Operators
    friend std::ostream &operator<<(std::ostream &out, const Coord &c); //So the operator can access lig and col (private members of the class) EXO 2 (7)
    friend bool operator==(const Coord &c1, const Coord &c2); //EXO 2 (10)
    friend bool operator!=(const Coord &c1, const Coord &c2); //EXO 2 (10)
    
};