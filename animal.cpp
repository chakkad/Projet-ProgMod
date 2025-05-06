#include "animal.hpp"
#include "doctest.h"
#include <iostream>
#include <cstdlib> //Rand()
#include <ctime> //Time()

//Constructors
Animal::Animal(int id, Espece e, const Coord& c) 
    : id(id), espece(e), coord(c), faim(0), age(0) {}

Animal::Animal() 
    : id(-1), espece(Espece::Lapin), coord(Coord(0,0)), faim(0), age(0) {}

//Methods

//Getters
int Animal::getId() const { 
    return id; 
}

Coord Animal::getCoord() const { 
    return coord; 
}

Espece Animal::getEspece() const { 
    return espece; 
}
//

void Animal::setCoord(const Coord& c) { 
    coord = c; 
}

//Functions
bool Animal::meurt() const {
    if (espece == Espece::Renard) {
        return (faim >= 50);
    } else if (age>50) {
        int chance = rand() % 100;
        return (chance < 20);
    }
    return false;    
}
   

bool Animal::seReprodruit(int nbVoisinsVides) const {
    if(espece == Espece::Lapin) {
        // Rabbit reproduces if: age >= 3 and at least 1 empty neighbor
        return (age >= 3) && (nbVoisinsVides >= 1);
    } else {
        // Fox reproduces if: age >= 5 and at least 2 empty neighbors
        return (age >= 5) && (nbVoisinsVides >= 2);
    }
}

void Animal::mange() { 
    if(espece == Espece::Renard) {
        faim = 0;  // Reset hunger counter
    }
    age++;
}

void Animal::jeune() { 
    if(espece == Espece::Renard) {
        faim++;    // Increment hunger counter
    }
    age++;
}


void Animal::affiche(std::ostream& out) const {
    out << "Animal [ID=" << id 
       << ", Espece=" << (espece == Espece::Lapin ? "Lapin" : "Renard")
       << ", Coord=" << coord
       << ", Age=" << age
       << ", Faim=" << faim << "]";
}

//Operator
std::ostream& operator<<(std::ostream& out, const Animal& a) {
    a.affiche(out);
    return out;
}

//TESTS
TEST_CASE("Animal Basics") {
    srand(time(0));  // Initialize random seed

    Animal fox(1, Espece::Renard, Coord(2,3));
    CHECK(fox.getEspece() == Espece::Renard);
    CHECK(fox.getCoord() == Coord(2,3));
    
    Animal rabbit;
    CHECK(rabbit.getEspece() == Espece::Lapin);
}

TEST_CASE("Fox Starvation") {
    Animal fox(2, Espece::Renard, Coord(1,1));
    
    for(int i = 0; i < 4; i++) fox.jeune();
    CHECK(fox.meurt() == false);
    
    fox.jeune();  // 5th hunger
    CHECK(fox.meurt() == true);
}

TEST_CASE("Rabbit Aging") {
    Animal rabbit(3, Espece::Lapin, Coord(0,0));
    
    for(int i = 0; i < 6; i++) rabbit.jeune();
    CHECK(rabbit.meurt() == true);  // Has 20% chance
    
    bool died = false;
    for(int i = 0; i < 20; i++) {
        if(rabbit.meurt()) died = true;
    }
    CHECK(died == true);
}

