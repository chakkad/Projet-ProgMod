#include <iostream>
#include "espece.hpp"
#include "coord.hpp"
using namespace std;

class Animal {

private :
    int id; //Unique Identifier
    Espece espece; //Lapin or Renard
    Coord coord;//Current Position
    int faim;//Hunger counter for foxes
    int age;//Age counter for reproduction

public :
    //Constructors
    Animal(int id, Espece e, const Coord& c); // Primary constructor
    Animal();// Default constructor (if needed for arrays)
    //Methods
    int getId() const;           // Returns the animal's identifier
    Coord getCoord() const;      // Returns the animal's coordinates
    Espece getEspece() const;    // Returns the species
    void setCoord(const Coord& c); // Updates the animal's coordinates
    bool meurt() const;          // Returns true if the animal dies of hunger
    bool seReprodruit(int nbVoisinsVides) const; // Returns true if reproduction is possible
    void mange(); // Feeds the animal (e.g., resets hunger counter)
    void jeune(); // The animal does not eat (e.g., increments hunger counter)
    void affiche(std::ostream& os) const; // Prints the animal's state
    //Operators
    friend std::ostream& operator<<(std::ostream& out, const Animal& a);
};

