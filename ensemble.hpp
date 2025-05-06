#include <iostream>
#include <stdexcept>
#include <cstdlib> //For rand()
using namespace std;

//For large data processing
//Can be changed to 1600 if wanted to (fitting the TAILLEGRILLE value)
const int MAXCARD = 1000; //EXO 3 (1)

class Ensemble { //EXO 3 (1)

private :
    int t[MAXCARD]; //EXO 3 (1)
    int card; //EXO 3 (1)

public :
    //Methods
    bool estVide() const; //EXO 3 (4)
    int cardinal() const; //EXO 3 (4)
    void ajoute(int objet); //EXO 3 (5)
    int tire(); //EXO 3 (5)
    //Constructor
    Ensemble(); //EXO 3 (3)

    //Operator
    friend std::ostream &operator<<(std::ostream &out, const Ensemble& e); //EXO 3(2)


};

