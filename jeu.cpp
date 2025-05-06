#include "jeu.hpp"
#include "doctest.h"
#include <stdexcept>

//Constructor
Jeu::Jeu() = default;

//Methodes

void Jeu::ajouteAnimal(Espece espece, Coord coord) {
    // Check if cell is empty
    if (!grille.caseVide(coord)) {
        throw std::runtime_error("Cell already occupied");
    }

    // Reserve ID and create animal
    int id = population.reserve();
    Animal animal(id, espece, coord);

    // Update population and grid
    population.set(animal);
    grille.setCase(coord, id);
}

//TESTS

TEST_CASE("Ajout d'un animal") {
    Jeu jeu;
    Coord pos(3, 4);

    // Add rabbit
    jeu.ajouteAnimal(Espece::Lapin, pos);

    // Verify population
    CHECK(jeu.getPopulation().getIds().cardinal() == 1);

    // Verify grid
    CHECK(jeu.getGrille().getCase(pos) == 0); // First ID is 0
    CHECK_FALSE(jeu.getGrille().caseVide(pos));
}

TEST_CASE("Ajout sur case occupée") {
    Jeu jeu;
    Coord pos(2, 2);

    // Add fox
    jeu.ajouteAnimal(Espece::Renard, pos);

    // Try adding rabbit to same cell
    CHECK_THROWS_AS(jeu.ajouteAnimal(Espece::Lapin, pos), std::runtime_error);
}

TEST_CASE("Accesseurs") {
    Jeu jeu;
    jeu.ajouteAnimal(Espece::Lapin, Coord(1,1));

    // Check mutable access
    jeu.getPopulation().get(0).setCoord(Coord(2,2));
    CHECK(jeu.getGrille().getCase(Coord(1,1)) == -1); // Old coord is empty
    CHECK(jeu.getGrille().getCase(Coord(2,2)) == 0);  // New coord has ID 0

    // Check const access
    const Jeu& jeuConst = jeu;
    CHECK(jeuConst.getPopulation().getIds().cardinal() == 1);
}