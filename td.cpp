#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

enum class Espece { Lapin, Renard };

struct Coord {
    int x, y;

    Coord(int x, int y) : x(x), y(y) {}
};

struct Animal {
    int id;
    Espece espece;
    Coord coord;

    Animal(int id, Espece espece, Coord coord) : id(id), espece(espece), coord(coord) {}

    void affiche() const {
        cout << "Animal ID: " << id << ", Espece: "
             << (espece == Espece::Lapin ? "Lapin" : "Renard")
             << ", Coord: (" << coord.x << ", " << coord.y << ")\n";
    }
};

class Grille {
private:
    vector<vector<int>> grille;

public:
    Grille(int largeur, int hauteur) : grille(hauteur, vector<int>(largeur, -1)) {}

    bool caseVide(const Coord& c) const {
        return grille[c.y][c.x] == -1;
    }

    void setCase(const Coord& c, int id) {
        grille[c.y][c.x] = id;
    }

    void videCase(const Coord& c) {
        grille[c.y][c.x] = -1;
    }
};

class Jeu {
private:
    Grille grille;
    vector<Animal> population;

public:
    Jeu(int largeur, int hauteur, double probLapins, double probRenards)
        : grille(largeur, hauteur) {
        srand(time(0));
        int id = 0;
        for (int y = 0; y < hauteur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                double r = (double)rand() / RAND_MAX;
                if (r < probLapins) {
                    ajouteAnimal(Espece::Lapin, Coord(x, y), id++);
                } else if (r < probLapins + probRenards) {
                    ajouteAnimal(Espece::Renard, Coord(x, y), id++);
                }
            }
        }
    }

    void ajouteAnimal(Espece espece, const Coord& coord, int id) {
        if (!grille.caseVide(coord)) {
            cout << "Case déjà occupée\n";
            return;
        }
        Animal animal(id, espece, coord);
        population.push_back(animal);
        grille.setCase(coord, id);
    }

    void affichePopulation() const {
        for (const auto& animal : population) {
            animal.affiche();
        }
    }
};

int main() {
    Jeu jeu(5, 5, 0.3, 0.2); // Grille 5x5 avec 30% de lapins et 20% de renards
    jeu.affichePopulation();
    return 0;
}
