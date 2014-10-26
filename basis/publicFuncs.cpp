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

#include "basis.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <complex>

basis::basis(int n1_, int n2_, int nOrb_, int qn_, int s_, char type_)
{
  n1 = n1_;
  n2 = n2_;
  nOrb = nOrb_;
  qn = qn_;
  s = s_;
  type = type_; 
}

int basis::bGen()
{
  switch(type)
    {
    case 'D': dGen();
      break;
    case 'T': tGen();
      break;
    }
  std::cout << "dim = " << dim << std::endl;
  return dim;
}

void basis::print()
{
  using namespace std;
  int i;
  cout << "The generated bases are:" << endl;
  cout << "n1 = " << n1 << ", n2 = " << n2 << ", nOrb = " << nOrb << ", qn = " << qn << endl;
  cout << "------ from the large orbital to the small ------" << endl;
  for (i = 0; i < dim; i++)
    {
      cout << bases[i]
	   << " "
	   << i << ": ";
      if (type == 'T')
	cout << tStSetNo[i] << " -> ";
      deciToPBShow(bases[i]);
      cout <<endl;
    }
  cout << "dim = " << dim << endl;
}

