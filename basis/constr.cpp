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

void basis::constr(int n, long b[], int qn[])
{
  using namespace std;
  // initialize the particle basis
  int i, pBasis[n];
  for (i = 0; i < n; i++)
    pBasis[i] = i;

  // loop for generating bases
  int no = 0, np;
  while (pBasis[0] != nOrb - n)
    { 
      if (pBasis[n - 1] < nOrb - 1)
	{
	  b[no] = pBToDeci(pBasis, n);
	  qn[no] = pBToQN(pBasis, n);
	  no++;
	  pBasis[n - 1] ++;
	}
      else
	{
	  b[no] = pBToDeci(pBasis, n);
	  qn[no] = pBToQN(pBasis, n);
	  no++;
	  // count how many particles are at the very end
	  np = 0;
	  for (i = 0; i < n; i++)
	    if (pBasis[n - 1 - i] == nOrb - 1 - i)
	      np++;
	    else
	      break;
	  // move the very right one, which is not at the very end, to the right by 1
	  pBasis[n - 1 - np]++;
	  // move the "np" very end particles, to the right of the "n - np"th particle
	  for (i = n - np; i < n; i++) 
	    pBasis[i] = pBasis[n - 1 - np] + i - n + np + 1;
	}
    }
  b[no] = pBToDeci(pBasis, n);
  qn[no] = pBToQN(pBasis, n);
  no++;
}
