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

#include "interaction.h"
#include <complex>
#include <iostream>

interaction::interaction(int nOrb_, int LLn_, double param_[], char type_[])
{
  using namespace std;
  nOrb = nOrb_;
  LLn = LLn_;
  int i;
  for (i = 0; i < 4; i++)
    param[i] = param_[i];
  for (i = 0; i < 3; i++)
    type[i] = type_[i];
}

void interaction::itrGen()
{
  using namespace std;
  int m1, m2, m3;
  switch (type[0])
    {
    case 'D':
      itr = new double[nOrb * nOrb * nOrb];
      for (m1 = 0; m1 < nOrb; m1++)
	for (m2 = 0; m2 < nOrb; m2++)
	  for (m3 = 0; m3 < nOrb; m3++)
	    itr[m1 * nOrb * nOrb + m2 * nOrb + m3] = dItr(m1, m2, m3);
      break;
    case 'T':
      itrC = new std::complex<double>[nOrb * nOrb * nOrb];
      for (m1 = 0; m1 < nOrb; m1++)
	for (m2 = 0; m2 < nOrb; m2++)
	  for (m3 = 0; m3 < nOrb; m3++)
	    itrC[m1 * nOrb * nOrb + m2 * nOrb + m3] = tItr(m1, m2, m3);
      break;
    }
}

void interaction::print()
{
  using namespace std;
  for (int i = 0; i < 10; i++)
    cout << itrC[i] << " ";
  cout << endl;
}

void interaction::itrPrint(int m1, int m2, int m3)
{
  using namespace std;
  cout << type[0] << endl;
  switch (type[0])
    {
    case 'D':
      cout << "(" << m1 << ", " << m2 << "|V|" << m3 << ", " << m1 + m2 - m3 << ") = " << dItr(m1, m2, m3) << endl;
      break;
    case 'T':
      cout << "(" << m1 << ", " << m2 << "|V|" << m3 << ", " << (m1 + m2 - m3 + nOrb) % nOrb << ") = " << tItr(m1, m2, m3) << endl;
      cout << "<" << m1 << ", " << m2 << "|V|" << m3 << ", " << m1 + m2 - m3 << "> = " << tItr(m1, m2, m3) - tItr(m1, m2, (m1 + m2 - m3 + nOrb) % nOrb) << endl;
      break;
    default :
      cout << "Wrong input." << endl;
      break;
    }
    cout << "no. 4 diagonalized matrix element is: " << 
    (tItr(0, 2, 0) - tItr(0, 2, 2))
    + (tItr(0, 6, 0) - tItr(0, 6, 6))
    + tItr(0, 0, 0) + tItr(0, 6, 0) + tItr(2, 0, 2) + tItr(2, 6, 2) << endl;
}
