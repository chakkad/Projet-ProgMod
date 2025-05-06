#include "animal.hpp"
#include <vector>
#include <stdexcept>
using namespace std;

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