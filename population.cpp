#include "population.hpp"
#include "doctest.h"
using namespace std;

//Constructors
Population::Population() = default;

//Methods
int Population::reserve() {
    if (!idLibres.empty()) {
        int id = idLibres.back();
        idLibres.pop_back();
        return id;
    }
    int id = static_cast<int>(animaux.size());
    animaux.emplace_back();
    return id;
}

void Population::set(const Animal& a) {
    const int id = a.getId();
    if (id < 0 || static_cast<size_t>(id) >= animaux.size()) {
        throw std::invalid_argument("Invalid animal ID");
    }
    animaux[id] = a;
}


void Population::supprime(int id) {
    if (id < 0 || static_cast<size_t>(id) >= animaux.size()) {
        throw std::invalid_argument("Invalid animal ID");
    }
    idLibres.push_back(id);
}

Animal& Population::get(int id) {
    if (id < 0 || static_cast<size_t>(id) >= animaux.size()) {
        throw std::invalid_argument("Invalid animal ID");
    }
    return animaux[id];
}

const Animal& Population::get(int id) const {
    if (id < 0 || static_cast<size_t>(id) >= animaux.size()) {
        throw std::invalid_argument("Invalid animal ID");
    }
    return animaux[id];
}

Ensemble Population::getIds() const {
    Ensemble activeIds;
    for (size_t i = 0; i < animaux.size(); ++i) {
        bool isFree = false;
        for (const int freeId : idLibres) {
            if (static_cast<size_t>(freeId) == i) {
                isFree = true;
                break;
            }
        }
        if (!isFree) {
            activeIds.ajoute(static_cast<int>(i));
        }
    }
    return activeIds;
}

//TESTS

TEST_CASE("Reserve IDs in order") {
    Population pop;
    CHECK(pop.reserve() == 0);
    CHECK(pop.reserve() == 1);
    CHECK(pop.reserve() == 2);
}

TEST_CASE("Reuse deleted IDs") {
    Population pop;
    int id1 = pop.reserve();
    pop.supprime(id1);
    CHECK(pop.reserve() == id1);
}

TEST_CASE("getIds() returns active IDs") {
    Population pop;
    pop.reserve();  // ID 0
    pop.reserve();  // ID 1
    Ensemble ids = pop.getIds();
    CHECK(ids.cardinal() == 2);
}

TEST_CASE("getIds() excludes deleted IDs") {
    Population pop;
    int id = pop.reserve();
    pop.supprime(id);
    Ensemble ids = pop.getIds();
    CHECK(ids.cardinal() == 0);
}

TEST_CASE("Access invalid ID throws exception") {
    Population pop;
    CHECK_THROWS_AS(pop.get(-1), std::invalid_argument);
    CHECK_THROWS_AS(pop.get(0), std::invalid_argument);
}

TEST_CASE("Set and retrieve valid animal") {
    Population pop;
    int id = pop.reserve();
    Animal fox(id, Espece::Renard, Coord(2,3));
    pop.set(fox);
    Animal& a = pop.get(id);
    CHECK(a.getEspece() == Espece::Renard);
    CHECK(a.getCoord() == Coord(2,3));
}

TEST_CASE("Handle large number of animals") {
    Population pop;
    for(int i = 0; i < 1000; i++) {
        int id = pop.reserve();
        Animal a(id, Espece::Lapin, Coord(i%40, i/40));
        pop.set(a);
    }
    CHECK_NOTHROW(pop.get(999));
    CHECK_THROWS_AS(pop.get(1000), std::invalid_argument);
}