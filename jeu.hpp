#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

const int TAILLEGRILLE = 40; //EXO 2 (1) Can be changed
const int MAXCARD = 1000; //EXO 3 (1)

class Ensemble { //EXO 3 (1)

private :
    int t[MAXCARD]; //EXO 3 (1)
    int card; //EXO 3 (1)

public :
    //Methods
    bool estVide() const; //EXO 3 (4)
    bool contient(int e) const;
    int cardinal() const; //EXO 3 (4)
    void ajoute(int objet); //EXO 3 (5)
    int tire(); //EXO 3 (5)
    //Constructor
    Ensemble(); //EXO 3 (3)

    //Operator
    friend std::ostream &operator<<(std::ostream &out, const Ensemble& e); //EXO 3(2)


};

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

enum class Espece {
    Lapin,  // Represents a rabbit
    Renard  // Represents a fox
};

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

class Population {

private:
    vector<Animal> animaux;
    vector<int> idLibres;

public :
    //Constructor
    Population(); //Initializes an empty population
    //Methods
    int reserve();
    void set(const Animal& a);
    void supprime(int id);
    Animal& get(int id);
    const Animal& get(int id) const;
    Ensemble getIds() const;
};

class Grille {

private :
    const int VIDE = -1;
    vector<vector<int>> grille;
    

public :
    // Constructor
    Grille();

    //Methodes
    bool caseVide(Coord pos) const; // Check if cell is empty
    int getCase(Coord pos) const; // Get animal ID at position
    void videCase(Coord pos); // Clear a cell
    void setCase(Coord pos, int idAnimal); // Place animal in cell
};

class Jeu {

private:
    Grille grille;
    Population population;

public :
    //Constructor
    Jeu();
    Jeu(double probLapins, double probRenard);
    //Methodes
    void ajouteAnimal(Espece espece, Coord coord); //Add an animal to the game
    void verifieGrille();
    void deplaceAnimal(int idAnimal);
    Ensemble voisinsVides(Coord pos) const;
    Ensemble voisinsEspece(Coord pos, Espece espece) const;
    Population& getPopulation();
    const Population& getPopulation() const;
    Grille& getGrille();
    const Grille& getGrille() const;
};











