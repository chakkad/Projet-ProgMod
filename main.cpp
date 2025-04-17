#include "ensemble.hpp"
#include "doctest.h"
using namespace std;

Ensemble::Ensemble() : card(0) {}

bool Ensemble::estVide() const { return card == 0; }
int Ensemble::cardinal() const { return card; }

void Ensemble::ajoute(int element) {
    if (card >= MAXCARD) {
        throw runtime_error("Ensemble plein");
    }
    t[card++] = element;
}

int Ensemble::tire() {
    if (estVide()) {
        throw runtime_error("Ensemble vide");
    }
    srand(time(nullptr));
    int index = rand() % card;
    int value = t[index];
    t[index] = t[card - 1];
    card--;
    return value;
}

ostream& operator<<(ostream& os, const Ensemble& e) {
    os << "{ ";
    for (int i = 0; i < e.card; ++i) {
        os << e.t[i] << " ";
    }
    os << "}";
    return os;
}

// Tests à mettre dans test.cpp
TEST_CASE("Constructeur par défaut") {
    Ensemble e;
    CHECK(e.estVide());
    CHECK(e.cardinal() == 0);
}

TEST_CASE("Ajoute et cardinal") {
    Ensemble e;
    e.ajoute(5);
    CHECK(e.cardinal() == 1);
    CHECK_FALSE(e.estVide());
}

TEST_CASE("Exceptions") {
    Ensemble e;
    CHECK_THROWS_AS(e.tire(), runtime_error);
    for (int i = 0; i < MAXCARD; i++) e.ajoute(i);
    CHECK_THROWS_AS(e.ajoute(MAXCARD), runtime_error);
}
