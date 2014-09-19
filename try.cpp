#include "./basis/basis.h"
#include "./interaction/interaction.h"
#include "./matrix/matrix.h"
#include "./ED/ED.h"
#include <cmath> // sqrt
#include <gsl/gsl_math.h> // pi
#include <iostream>

int main()
{
  using namespace std;
  cout << "==============================================================" << endl;
  cout << "=========================== YED ==============================" << endl;
  cout << "==============================================================" << endl;
  int t = 0, s = 0; // !! quantum numbers in torus, appearing in Chapter 7 of Chakraborty's book
  cout << "t = " << t << "; s = " << s << endl;
  // basis:
  int n1 = 4, n2 = 4,  // !! if it just has one component, make n1 = 0, n2 = n
    nOrb = 16, qn = t; // !! nOrb is the orbital number
  char geometry = 'T';
  basis bases(n1, n2, nOrb, qn, s, geometry); // !! define a basis class called bases
  bases.bGen(); // !! function in basis class to generate the bases
  bases.print(); // !! print out the bases in terminal
  cout << "==============================================================" << endl;
  cout << "==============================================================" << endl;
}

