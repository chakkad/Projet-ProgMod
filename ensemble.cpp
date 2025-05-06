#include "doctest.h"
#include "ensemble.hpp"
//#include <sstream> //stringstream for testing the "<<" operator


//Constructor
Ensemble::Ensemble() : card(0) {} //EXO 3 (3)

//Methods
bool Ensemble::estVide() const { //EXO 3 (4)
    return card == 0;
}

int Ensemble::cardinal() const { //EXO 3 (4)
    return card;
}

void Ensemble::ajoute(int objet) { //EXO 3 (5)
    if (card >= MAXCARD) {
        throw runtime_error("Ensemble Plein");
    }
    t[card] = objet;
    card++;
}

int Ensemble::tire() { //EXO 3 (5)
    if (estVide()) {
        throw runtime_error("Ensemble vide");
    }
    int index = rand() % card;  //Restricts the random to the amount od card - 1
    int value = t[index];
    t[index] = t[card-1]; //Swapping to avoid leaving a gap
    card--;
    return value;
}



//Operator
std::ostream &operator<<(std::ostream &out, const Ensemble& e) { //EXO 3 (2)
    out << "{";
    for (int i = 0 ; i < e.card; i++) {
        out << e.t[i];
        if (i < e.card - 1) {
            out << ",";
        }
    }
    out << "}";
    return out;
}

//TESTS

TEST_CASE("Tire") {
    Ensemble e;
    e.ajoute(1);
    e.ajoute(2);
    e.ajoute(3);

    int val = e.tire();
    CHECK((val == 1 || val == 2 || val == 3)); //Checking if the value removed is matched with the array
    CHECK(e.cardinal() == 2);//Checking the cardinality after its removed 
}

TEST_CASE("Ajoute") {
    Ensemble e;
    e.ajoute(5);
    CHECK(e.cardinal() == 1);
    e.ajoute(10);
    CHECK(e.cardinal() == 2);
    CHECK_FALSE(e.estVide());
}




