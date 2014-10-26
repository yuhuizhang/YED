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
#include <complex>
#include <iostream>

int matrix::sgnChange(int m1, int m2, int m3, int m4, int n1, int n2, int i1, int i2, int oB1[], int oB2[], long newStateDeci, long newDeci, char type)
{
  using namespace std;
  //  cout << "m1: " << m1 << ", m2: " << m2 << "; m3: " << m3 << ", m4: " << m4 << endl;
  int sign = 1;
  /*
    step 1: 4e in 8orb:
    sign change of the process: |4, 5, 6, 9> -> |1, 4, 5, 6>
  */
  long b1 = newStateDeci / (long)(pow(2, nOrb) + 0.5),
    b2 = newStateDeci % (long)(pow(2, nOrb) + 0.5);
  int i = 0;
  long movB;
  long b = newStateDeci, nb = -1, nb1, nb2;
  while (nb != b)
    {
      /* change to another term */
      i++;
      nb1 = b1 * (long)(pow(2, i * q) + 0.5);
      if (nb1 >= (long)(pow(2, nOrb) + 0.5))
	{
	  movB = nb1 / (long)(pow(2, nOrb) + 0.5);
	  nb1 = nb1 - movB * (long)(pow(2, nOrb) + 0.5) + movB;
	}
      nb2 = b2 * (long)(pow(2, i * q) + 0.5);
      if (nb2 >= (long)(pow(2, nOrb) + 0.5))
	{
	  movB = nb2 / (long)(pow(2, nOrb) + 0.5);
	  nb2 = nb2 - movB * (long)(pow(2, nOrb) + 0.5) + movB;
	}
      nb = nb1 * (long)(pow(2, nOrb) + 0.5) + nb2;
      if (nb == newDeci)
	{
	  /* count electron-number from the 0th to (i * q - 1)th orbital in each spin component */
	  switch (type)
	    {
	    case 'U':
	      {
		int movE = 0;
		for (int m = nOrb - i * q; m <= nOrb - 1; m++)
		  if (oB1[m] == 1 && m != m1 && m != m2)
		    movE++;
		  else if (m == m3 || m == m4)
		    movE++;
		sign *= (int)(pow(-1.0, n1 - movE) * 1.5);
		sign = (int)(pow(sign, movE) * 1.5);
		movE = 0;
		int sign2 = 1;
		for (int m = nOrb - i* q; m <= nOrb - 1; m++)
		  if (oB2[m] == 1)
		    movE++;
		sign2 *= (int)(pow(-1.0, n2 - movE) * 1.5);
		sign2 = (int)(pow(sign2, movE) * 1.5);
		sign *= sign2;
	      }
	      break;

	    case 'D':
	      {
		int movE = 0;
		for (int m = nOrb - i * q; m <= nOrb - 1; m++)
		  if (oB1[m] == 1)
		    movE++;
		sign *= (int)(pow(-1.0, n1 - movE) * 1.5);
		sign = (int)(pow(sign, movE) * 1.5);
		movE = 0;
		int sign2 = 1;
		for (int m = nOrb - i * q; m <= nOrb - 1; m++)
		  if (oB2[m] == 1 && m != m1 && m != m2)
		    movE++;
		  else if (m == m3 || m == m4)
		    movE++;
		sign2 *= (int)(pow(-1.0, n2 - movE) * 1.5);
		sign2 = (int)(pow(sign2, movE) * 1.5);
		sign *= sign2;
	      }
	      break;

	    case 'B':
	      {
		int movE = 0;
		for (int m = nOrb - i * q; m <= nOrb - 1; m++)
		  if (oB1[m] == 1 && m != m1)
		    {
		      movE++; 
		      //cout << "m is " << m << endl;
		    }
		  else if (m == m3)
		    {
		      movE++; 
		      //		      cout << "m is " << m << endl;
		    }
		sign *= (int)(pow(-1.0, n1 - movE) * 1.5);
		sign = (int)(pow(sign, movE) * 1.5);
		//		cout << "! " << movE << endl;
		movE = 0;
		int sign2 = 1;
		for (int m = nOrb - i * q; m <= nOrb - 1; m++)
		  if (oB2[m] == 1 && m != m2)
		    {
		      movE++; 
		      //		      cout << "m is " << m << endl;
		    }
		  else if (m == m4)
		    {
		      movE++; 
		      //		      cout << "m is " << m << endl;
		    }
		//		cout << "! " << movE << endl;
		sign2 *= (int)(pow(-1.0, n2 - movE) * 1.5);
		sign2 = (int)(pow(sign2, movE) * 1.5);
		sign *= sign2;
	      }
	      break;
	    }
	}
    }
  //  cout << "sign: " << sign << endl;
  /*
    step 2: 4e in 8orb:
    sign change of the process: |1, 4, 5, 6> -> |(4, 5), 1, 6> (if (4, 5) are scattered state)
   */
  switch (type)
    {
    case 'U':
      for (int m = m1 + 1; m < m2; m++)
	if (oB1[m] == 1) 
	  sign *= -1;
      for (int m = m3 + 1; m < m4; m++)
	if (m != m1 && m != m2 && oB1[m] == 1)
	  sign *= -1;
      break;
    case 'D':
      for (int m = m1 + 1; m < m2; m++)
	if (oB2[m] == 1) 
	  sign *= -1;
      for (int m = m3 + 1; m < m4; m++)
	if (m != m1 && m != m2 && oB2[m] == 1)
	  sign *= -1;
      break;
    case 'B':
      sign *= (int)(pow(-1.0, i1) * 1.5);
      sign *= (int)(pow(-1.0, i2) * 1.5);
      for (int m = 0; m < m3; m++)
	if (m != m1 && oB1[m] == 1)
	  sign *= -1;
      for (int m = 0; m < m4; m++)
	if (m != m2 && oB2[m] == 1)
	  sign *= -1;
      break;
    }
  return sign;
}

std::complex<double> matrix::tScatteredValue(int m1, int m2, int m3, int m4, int phase, int sign, int position, int newPosition, char typ)
{
  std::complex<double> meM;
  using namespace std;
  //  double meMAbs;
  // phase obtained here is the "distance" from the scattered state to the representative state
  // but now translate it to the "distance" from the representative state to the scattered state
  phase = (tStSetNo[newPosition] - phase) % tStSetNo[newPosition];

  switch (typ)
    {
    case 'S':
      meM = (1.0 * sign) * (itrAC[m1 * nOrb * nOrb + m2 * nOrb + m3] - itrAC[m1 * nOrb * nOrb + m2 * nOrb + m4]);
      break;
    case 'B':
      meM = (1.0 * sign) * itrRC[m1 * nOrb * nOrb + m2 * nOrb + m3];
      break;
    }
  meM /= (sqrt(tStSetNo[position]) * sqrt(tStSetNo[newPosition]));
  if (tStSetNo[position] > tStSetNo[newPosition])
    {
      std::complex<double> exponents (0, 0);
      for (int i = 0; i < tStSetNo[position]; i++)
	{
	  if (phase >= tStSetNo[newPosition])
	    phase = 0;
	  double power = (2 * M_PI * s / N) * 
	    (phase - i);
	  exponents += std::polar(1.0, power);
	  phase++;
	}
      meM *= exponents;
    }
  else
    {
      std::complex<double> exponents (0, 0);
      for (int i = 0; i < tStSetNo[position]; i++)
	{
	  if (phase >= tStSetNo[newPosition])
	    phase = 0;
	  double power = (2 * M_PI * s / N) * 
	    (phase - i);
	  exponents += std::polar(1.0, power);
	  phase++;
	}
      meM *= exponents;
    }
  return meM;
}

int matrix::tStoreValueTemp(std::complex<double> meM, int position, int newPosition, int rowTemp[], std::complex<double> ACTemp[], int& rNo)
{
  using namespace std;
  int i;
  for (i = rNo - 1; i >= 0; i--)
    if (newPosition == rowTemp[i])
      {
	ACTemp[i] += meM;
	return 0;
      }
  ACTemp[rNo] = meM;
  rowTemp[rNo++] = newPosition;
  return 1;
}

void matrix::tStoreValue(int position, int rowTemp[], std::complex<double> ACTemp[], int rNo)
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
      std::complex<double> ACT;
      for (int j = 0; j < rNo; j++)
	{
	  // pick out the smallest row number
	  if (rowTemp[j] < RT && rowTemp[j] != -1)
	    {
	      RT = rowTemp[j];
	      ACT = ACTemp[j];
	      p = j;
	    }
	}
      rowTemp[p] = -1;
      row[s] = RT;
      AC[s] = ACT;
      basisSctNo[position]++;
      s++;
      if (type[1] == 'E')
	size++;
    }
  return;
}

int matrix::tNewJudge(int position, int newPosition, int& rNo, int pseudoRow[])
{
  using namespace std;
  for (int i = rNo - 1; i >= 0;  i--)
    if (newPosition == pseudoRow[i])
	return 0;
  pseudoRow[rNo++] = newPosition;
  return 1;
}
