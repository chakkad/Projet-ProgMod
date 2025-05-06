#include "grille.hpp"
#include <stdexcept>

Grille::Grille(int largeur, int hauteur)
    : grille(hauteur, std::vector<int>(largeur, -1)) {}

bool Grille::caseVide(const Coord& c) const {
    if (c.getLig() < 0 || c.getLig() >= grille.size() || c.getCol() < 0 || c.getCol() >= grille[0].size()) {
        throw std::invalid_argument("Coordonnées hors de la grille");
    }
    return grille[c.getLig()][c.getCol()] == -1;
}

int Grille::getCase(const Coord& c) const {
    if (c.getLig() < 0 || c.getLig() >= grille.size() || c.getCol() < 0 || c.getCol() >= grille[0].size()) {
        throw std::invalid_argument("Coordonnées hors de la grille");
    }
    return grille[c.getLig()][c.getCol()];
}

void Grille::setCase(const Coord& c, int id) {
    if (c.getLig() < 0 || c.getLig() >= grille.size() || c.getCol() < 0 || c.getCol() >= grille[0].size()) {
        throw std::invalid_argument("Coordonnées hors de la grille");
    }
    grille[c.getLig()][c.getCol()] = id;
}

void Grille::videCase(const Coord& c) {
    if (c.getLig() < 0 || c.getLig() >= grille.size() || c.getCol() < 0 || c.getCol() >= grille[0].size()) {
        throw std::invalid_argument("Coordonnées hors de la grille");
    }
    grille[c.getLig()][c.getCol()] = -1;
}
