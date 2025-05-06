#include "grille.hpp"
#include "population.hpp"
using namespace std;

class Jeu {

private:
    Grille grille;
    Population population;

public :
    //Constructor
    Jeu();
    //Methodes
    void ajouteAnimal(Espece espece, Coord coord); //Add an animal to the game
    Population& getPopulation() { return population; }
    const Population& getPopulation() const { return population; }
    Grille& getGrille() { return grille; }
    const Grille& getGrille() const { return grille; }
};