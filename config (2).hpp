#include <iostream>
using namespace std;


class Config {
public:
    static const double ProbBirthLapin;  // = 0.30
    static const int MinFreeBirthLapin;   // = 4

    // Fox constants
    static const int FoodInit;           // = 5
    static const int FoodLapin;          // = 5
    static const int FoodReprod;         // = 8
    static const int MaxFood;            // = 10
    static const double ProbBirthRenard; // = 0.05
};