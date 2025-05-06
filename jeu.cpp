#include "jeu.hpp"
#include "doctest.h"
#include <stdexcept>
#include <cstdlib>
#include <ctime>

//Constructor
Jeu::Jeu() = default;

Jeu::Jeu(double probLapins, double probRenard) {
    // Seed random generator
    std::srand(std::time(0));
    
    // Validate probabilities
    if(probLapins < 0 || probRenard < 0 || (probLapins + probRenard) > 1) {
        throw std::invalid_argument("Invalid probabilities");
    }

    // Initialize grid
    for(int lig = 0; lig < TAILLEGRILLE; lig++) {
        for(int col = 0; col < TAILLEGRILLE; col++) {
            double r = static_cast<double>(rand()) / RAND_MAX;
            Coord pos(lig, col);
            
            if(r < probLapins) {
                ajouteAnimal(Espece::Lapin, pos);
            } 
            else if(r < probLapins + probRenard) {
                ajouteAnimal(Espece::Renard, pos);
            }
        }
    }
}

//Getter Methods
Population& Jeu::getPopulation() { 
    return population; 
}

const Population& Jeu::getPopulation() const { 
    return population; 
}

Grille& Jeu::getGrille() { 
    return grille; 
}

const Grille& Jeu::getGrille() const { 
    return grille; 
}

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

void Jeu::verifieGrille() {
    // Check all animals are correctly placed
    Ensemble ids = population.getIds();
    for(int i = 0; i < ids.cardinal(); i++) {
        int id = ids.tire();
        Animal a = population.get(id);
        if(grille.getCase(a.getCoord()) != id) {
            throw std::runtime_error("Animal position mismatch");
        }
    }
    
    // Check grid consistency
    for(int lig = 0; lig < TAILLEGRILLE; lig++) {
        for(int col = 0; col < TAILLEGRILLE; col++) {
            int id = grille.getCase(Coord(lig, col));
            if(id != -1 && !population.getIds().contient(id)) {
                throw std::runtime_error("Orphaned grid entry");
            }
        }
    }
}

Ensemble Jeu::voisinsVides(Coord pos) const {
    Ensemble voisins = pos.voisines();
    Ensemble vides;
    
    for(int i = 0; i < voisins.cardinal(); i++) {
        int id = voisins.tire();
        Coord c = Coord(id);  // Use fromInt constructor
        if(grille.caseVide(c)) {
            vides.ajoute(c.Toint());
        }
    }
    return vides;
}

Ensemble Jeu::voisinsEspece(Coord pos, Espece espece) const {
    Ensemble voisins = pos.voisines();
    Ensemble resultat;
    
    for(int i = 0; i < voisins.cardinal(); i++) {
        int id = voisins.tire();
        Coord c = Coord(id);
        int animalId = grille.getCase(c);
        
        if(animalId != -1) {
            Animal a = population.get(animalId);
            if(a.getEspece() == espece) {
                resultat.ajoute(id);
            }
        }
    }
    return resultat;
}

void Jeu::deplaceAnimal(int idAnimal) {
    Animal& a = population.get(idAnimal);
    Coord anciennePos = a.getCoord();
    
    // Get empty neighbors
    Ensemble vides = voisinsVides(anciennePos);
    if(vides.estVide()) return;
    
    // Choose random empty cell
    int choix = vides.tire();
    Coord nouvellePos = Coord(choix);
    
    // Update position
    a.setCoord(nouvellePos);
    
    // Update grid
    grille.videCase(anciennePos);
    grille.setCase(nouvellePos, idAnimal);
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