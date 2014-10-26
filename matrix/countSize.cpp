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
#include <boost/math/special_functions/binomial.hpp>
#include <iostream>
//#include <omp.h>

long matrix::estimateSize()
{
  using namespace boost::math;
  switch (type[0])
    {
    case 'D':
      size = ((binomial_coefficient<double>(n1, 2) * (nOrb - n1) * (1.0 * n1 / nOrb) 
	       + binomial_coefficient<double>(n2, 2) * (nOrb - n2) * (1.0 * n2 / nOrb) 
	       + n1 * n2 * (nOrb - n1) * (1.0 * n2 / nOrb))) 
	* dim / 2
	* 1.1;
      break;
    case 'T':
      size = ((binomial_coefficient<double>(n1, 2) * (nOrb - n1) * (1.0 * n1 / nOrb) 
	       + binomial_coefficient<double>(n2, 2) * (nOrb - n2) * (1.0 * n2 / nOrb) 
	       + n1 * n2 * (nOrb - n1) * (1.0 * n2 / nOrb))) 
	* dim / 2 / N
	* 1.1;
      break;
    }
  return size;
}

long matrix::countSize()
{
  using namespace std;
  basisSctNo = new int[dim];
  cout << "dim = " << dim << endl;
  int pB1[n1], antiPB1[nOrb - n1], oB1[nOrb],
    pB2[n2], antiPB2[nOrb - n2], oB2[nOrb];
  int rNo;
  //  int th_id;
  //#pragma omp parallel for default(shared) private(pB1, antiPB1, oB1, pB2, antiPB2, oB2, th_id)
  for (int i = 0; i < dim; i++)
    {
      /*
      if (i % 5000 == 0)
	{
	  std::cout << i << std::endl;
	  th_id = omp_get_thread_num();
	  std::cout << "Hello World from thread " << th_id << '\n';
	}
      */
      basisSctNo[i] = 1;
      if (n1 == 0 || n2 == 0)
	deciToPOS(bases[i], pB2, antiPB2, oB2, max(n1, n2));
      else
	deciToPOB(bases[i], pB1, antiPB1, oB1, pB2, antiPB2, oB2, n1, n2);

      switch (type[0])
	{
	case 'D': 
	  rNo = dOffME(i, bases[i], pB1, antiPB1, oB1, pB2, antiPB2, oB2, 'C');
	  break;
	case 'T': 
	  tOffME(i, bases[i], pB1, antiPB1, oB1, pB2, antiPB2, oB2, 'C');
	  break;
	}
    }
  size = 0;
  for (int i = 0; i < dim; i++)
    {
      pcol[i] = size;
      size += basisSctNo[i];
    }
  pcol[dim] = size;
  return size;
}

