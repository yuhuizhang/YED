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

#include "matrix.h"
#include <gsl/gsl_math.h>
#include <cmath> // sqrt(); cos(); sin()
#include <iostream>

void matrix::dStoreValue(int position, int rowTemp[], double ATemp[], int rNo)
{
  using namespace std;
  int p, s;
  switch (type[1])
    {
    case 'E':
      s = size;
      break;
    case 'C':
      s = pcol[position] + basisSctNo[position];
      break;
    }

  for (int i = 0; i < rNo; i++)
    {
      int RT = dim;
      double AT;
      for (int j = 0; j < rNo; j++)
	{
	  // pick out the smallest row number
	  if (rowTemp[j] < RT && rowTemp[j] != -1)
	    {
	      RT = rowTemp[j];
	      AT = ATemp[j];
	      p = j;
	    }
	}
      rowTemp[p] = -1;
      row[s] = RT;
      A[s] = AT;
      basisSctNo[position]++;
      s++;
      if (type[1] == 'E')
	size++;
    }
  return;
}
