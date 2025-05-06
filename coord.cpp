#include "doctest.h"
#include "coord.hpp"
#include <algorithm> //For max and min
using namespace std;


//Constructor
Coord::Coord(int lig, int col) : lig(lig), col(col) { //EXO 3 (3)
	if ( lig < 0 || lig > TAILLEGRILLE ){
		throw invalid_argument ("Invalid Coordinates");
	} else if (col < 0 || col > TAILLEGRILLE) {
		throw invalid_argument ("Invalid Coordinates");
	}
}

Coord::Coord(int entier) {
    if (entier < 0 || entier >= TAILLEGRILLE * TAILLEGRILLE){
        throw invalid_argument("Entier Invalide");
    }
    //entier = ligne * TAILLEGRILLE + colonne;
    //ligne = entier / TAILLEGRILLE - colonne;
    //colonne = entier / TAILLEGRILLE - ligne
    lig = entier / TAILLEGRILLE;
    col = entier % TAILLEGRILLE;
}

//Getters
int Coord::getLig() const {
	return lig;
}

int Coord::getCol() const {
	return col;
}

//Methodes
int Coord::Toint() const {
    return lig * TAILLEGRILLE + col;
}

Ensemble Coord::voisines() const {
    Ensemble ev; //Initiate a new ensemble
    //Calculate min and max rows
    int i_min = max(lig - 1, 0);
    int i_max = min(lig + 1, TAILLEGRILLE - 1);
    //Calculate min and max columns
    int j_min = max(col - 1, 0);
    int j_max = min(col + 1, TAILLEGRILLE - 1);

    for (int i = i_min; i <= i_max; i++) {
        for (int j = j_min; j <= j_max; j++) {
            // Skip the current coordinate (lig, col)
            if (i == lig && j == col) continue;
            ev.ajoute(Coord(i, j).Toint());
        }
    }

    return ev;
}

//Operators
std::ostream &operator<<(std::ostream &out, const Coord &c) { //EXO 2 (7)
    out << "(" << c.lig << ", " << c.col << ")";
    return out;
}

bool operator==(const Coord &c1, const Coord &c2) { //EXO 2 (10)
    return (c1.lig == c2.lig) && (c1.lig == c2.lig);
}

bool operator!=(const Coord &c1, const Coord &c2) { //EXO 2 (10)
    return !(c1 == c2);
}

//TEST CASE
TEST_CASE("Coordinates") { //EXO 2 (4)
	Coord c(23,24);
	CHECK(c.getLig() == 23); //reactivating counts as EXO 2 (6)
	CHECK(c.getCol() == 24);
	CHECK_THROWS_AS(Coord(-2,25), invalid_argument);
}

TEST_CASE("Operator <<") { //EXO 2 (9)
    Coord c(23,24);
    Coord c2(39,38);
    cout << c << endl;
    cout << c2 << endl;
}

TEST_CASE("Operator ==") {
    Coord c1(23,24);
    Coord c2(23,24);
    Coord c3(24,24);
    CHECK(c1 == c2);
    CHECK_FALSE(c1 == c3);
}

TEST_CASE("Operator !=") {
    Coord c1(23,24);
    Coord c2(23,24);
    Coord c3(24,24);
    CHECK(c1 != c3);
    CHECK_FALSE(c1 != c2);
}