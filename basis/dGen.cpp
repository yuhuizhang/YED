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
#include <boost/math/special_functions/binomial.hpp>
#include <cmath>


int basis::dGen()
{
  using namespace std;
  int dim1 = (int)(boost::math::binomial_coefficient<double>(nOrb, n1) + 0.5), 
    dim2 = (int)(boost::math::binomial_coefficient<double>(nOrb, n2) + 0.5);
  long b1[dim1], b2[dim2];
  int qn1[dim1], qn2[dim2];
  cout << "dim1 = " << dim1 << endl
       << "dim2 = " << dim2 << endl;

  if (n1 != 0)  
    constr(n1, b1, qn1);
  if (n2 != 0)
    constr(n2, b2, qn2);

  long dimApprox = (long)(dim1) * dim2 / nOrb * 1.2;
  dim = 0;
  bases = new long[dimApprox];
  int i, j;
  int deciShift = (int) (pow(2, nOrb) + 0.5);
  if (n1 != 0 && n2 != 0)
    {
      for (i = 0; i < dim1; i++)
	for (j = 0; j < dim2; j++)
	  if (qn1[i] + qn2[j] == qn)
	    bases[dim++] = b1[i] * deciShift + b2[j];
    }
  else if (n1 == 0)
    {
      for (j = 0; j < dim2; j++)
	if (qn2[j] == qn)
	  bases[dim++] = b2[j];
    }
  else if (n2 == 0)
    {
      for (j = 0; j < dim1; j++)
	if (qn1[j] == qn)
	  bases[dim++] = b1[j];
    }
  return dim;
}

