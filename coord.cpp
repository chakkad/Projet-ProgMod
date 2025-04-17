#include "doctest.h"
#include "coord.hpp"
using namespace std;

Coord::Coord(int lig, int col) {
    if (lig < 0 || lig > TAILLEGRILLE || col < 0 || col >= TAILLEGRILLE) {
        throw std::invalid_argument("coordonnées invalides");
    }
}

int Coord::getLig() const {
    return lig;
}

int Coord::getCol() const {
    return col;
}

std::ostream& operator<<(std::ostream& out, const Coord& coord) {
    out << "(" << coord.lig << ", " << coord.col << ")";
    return out;
}
