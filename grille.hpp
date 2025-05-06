#ifndef GRILLE_HPP
#define GRILLE_HPP

#include "coord.hpp"
#include <vector>

class Grille {
private:
    std::vector<std::vector<int>> grille;

public:
    // Constructeur
    Grille(int largeur, int hauteur);

    // Vérifie si une case est vide
    bool caseVide(const Coord& c) const;

    // Récupère l'identifiant de la case
    int getCase(const Coord& c) const;

    // Définit l'identifiant d'une case
    void setCase(const Coord& c, int id);

    // Vide une case
    void videCase(const Coord& c);
};

#endif
