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
#include <algorithm>

int basis::sTBasisJudge(long b)
{
  long nb = -1;
  int i = 0, movB;
  while (nb != b)
    {
      i ++;
      nb = b * (int)(pow(2, i * q) + 0.5);
      if (nb >= (int)(pow(2, nOrb) + 0.5))
      {
	movB = nb / (int)(pow(2, nOrb) + 0.5);
	nb = nb - movB * (int)(pow(2, nOrb) + 0.5) + movB;
      }
      if (nb > b)
	return 0; // not chosen
    }
  // to here, already make sure that b is the representative b
  if (i < N)
    {
      int oB[nOrb];
      int movE = 0;
      int sign, add;
      deciToOB(b, oB);
      for (int m = nOrb - q; m <= nOrb - 1; m++)
	if (oB[m] == 1) 
	  movE++;
      sign = pow(-1, std::max(n1, n2) - movE);
      sign = pow(sign, movE);
      if (sign == 1)
	add = 0;
      else 
	add = 1;
      if ((2 * s * i / N + add) % 2 != 0) //even
	return 0;
    }
  return i; // chosen
}

int basis::biTBasisJudge(long b)
{
  using namespace std;
  long b1 = b / (long)(pow(2, nOrb) + 0.5),
    b2 = b % (long)(pow(2, nOrb) + 0.5);
  long nb = -1, nb1 = -1, nb2 = -1;
  int i = 0;
  long movB;
  //  cout << "------------" << endl;
  //  cout << "q = " << q << endl;
  //  cout << "b = " << b << ", b1 = " << b1 << ", b2 = " << b2 << endl;
  while (nb != b)
    {
      i ++;
      //      cout << endl;
      //      cout << "nb = " << nb << endl;
      nb1 = b1 * (long)(pow(2, i * q) + 0.5);
      nb2 = b2 * (long)(pow(2, i * q) + 0.5);
      //      cout << "then nb1 = " << nb1 << ", nb2 = " << nb2 << endl;
      if (nb1 >= (long)(pow(2, nOrb) + 0.5))
      {
	movB = nb1 / (long)(pow(2, nOrb) + 0.5);
	nb1 = nb1 - movB * (long)(pow(2, nOrb) + 0.5) + movB;
      }
      if (nb2 >= (long)(pow(2, nOrb) + 0.5))
      {
	movB = nb2 / (long)(pow(2, nOrb) + 0.5);
	nb2 = nb2 - movB * (long)(pow(2, nOrb) + 0.5) + movB;
      } 
      //      cout << "then then nb1 = " << nb1 << ", nb2 = " << nb2 << endl;
      nb = nb1 * (long)(pow(2, nOrb) + 0.5) + nb2;
      //      cout << "then nb = " << nb << endl;
      if (nb > b)
	return 0; // not chosen
    }
  // to here, already make sure that b is the representative b
  if (i < N)
    {
      int oB1[nOrb], oB2[nOrb];
      deciToOB(b, oB1, oB2);

      // show the oB[]
      cout << "---------------------" << endl;
      cout << "small subset: " << b 
	   << ": ";
      for (int m = 0; m < nOrb; m++)
	cout << oB1[m] << " ";
      cout << "|";
      for (int m = 0; m < nOrb; m++)
	cout << oB2[m] << " ";
      cout << endl;
      cout << ". |L|: " << i << endl;

      // sign change by writing by using the same orbital basis
      int movE = 0;
      int sign, add;
      int m;
      for (m = 0; m < i * q; m++)
	if (oB1[m] == 1) 
	  movE++;
      sign = pow(-1, n1 - movE);
      sign = pow(sign, movE);
      int sign2;
      movE = 0;
      for (m = 0; m < i * q; m++)
	if (oB2[m] == 1) 
	  movE++;
      sign2 = pow(-1, n2 - movE);
      sign2 = pow(sign2, movE);

      //
      sign *= sign2;
      if (sign == 1)
	add = 0;
      else 
	add = 1;
      int phs = 2 * s * i;
      if (phs % N == 0 && (phs / N + add) % 2 == 0) // go to the first element
	{
	  cout << "keep the base: " << b << endl;
	}
      else if (phs % N == 0 && (phs / N + add) % 2 != 0) // go to the (negative) first element
	{
	  cout << "the deleted base: " << b << endl;
	  return 0;
	}
      else 
	{
	  cout << "some other phase appears at the base: " << b << endl;
	  return 0;
	}
    }
  return i; //chosen
}


int basis::tGen()
{
  using namespace std;
  int dim1 = (int)(boost::math::binomial_coefficient<double>(nOrb, n1) + 0.5), 
    dim2 = (int)(boost::math::binomial_coefficient<double>(nOrb, n2) + 0.5);
  long b1[dim1], b2[dim2];
  int qn1[dim1], qn2[dim2];

  if (n1 != 0)  
    constr(n1, b1, qn1);
  if (n2 != 0)
    constr(n2, b2, qn2);

  // obtain the parameters in torus
  tParameter(); 
  long dimApprox = (long)(dim1) * dim2 / nOrb / N * 1.2; // times 1.05 since some set of states have less than N states.
  dim = 0;
  int judge;
  bases = new long[dimApprox];
  tStSetNo = new int[dimApprox];
  cout << "dimApprox = " << dimApprox << endl;
  int i, j;
  long deciShift = (long) (pow(2, nOrb) + 0.5);
  if (n1 != 0 && n2 != 0)
    {
      for (i = 0; i < dim1; i++)
	for (j = 0; j < dim2; j++)
	  {
	    if ((qn1[i] + qn2[j]) % nOrb != qn)
	      continue;
	    judge = biTBasisJudge(b1[i] * deciShift + b2[j]);
	    if (judge != 0)
	      {
		// std::cout << qn1[i] << " " << qn2[j] << endl;
		tStSetNo[dim] = judge;
		bases[dim++] = b1[i] * deciShift + b2[j];
	      }
	  }
    }
  else if (n1 == 0)
    {
      for (j = 0; j < dim2; j++)
	{
	  if (qn2[j] % nOrb != qn)
	    continue;
	  judge = sTBasisJudge(b2[j]);
	  if (judge != 0)
	  {
	    tStSetNo[dim] = judge;
	    bases[dim++] = b2[j];
	  }
	}
    }
  else if (n2 == 0)
    {
      for (j = 0; j < dim1; j++)
	{
	  if (qn1[j] % nOrb != qn)
	    continue;
	  judge = sTBasisJudge(b1[j]);
	  if (judge != 0)
	    {	 
	      tStSetNo[dim] = judge;
	      bases[dim++] = b1[j];
	    }
	}
    }
  return dim;
}

