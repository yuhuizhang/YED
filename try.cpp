/*
  This file is part of YED.

  Copyright (C) 2014 Yuhui Zhang. 

  YED is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>. */

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

