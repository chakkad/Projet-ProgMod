#include <iostream>
using namespace std;

const int TAILLEGRILLE = 40;

class Coord {

private :
	int lig; // Lines
	int col; // Columns

public :
	// Constructors
	Coord(int lig, int col);
  //Getters
	int getLig() const ; 
	int getCol() const ; 
  //Operators
  friend std::ostream &operator<<(std::ostream &out, const Coord &c); //So the operator can access lig and col (private members of the class)


};
