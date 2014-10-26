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
#include <complex>
#include <iostream>

void matrix::diaMET(int position, long deci, int pB1[], int pB2[], int rowTemp[], std::complex<double> ACTemp[])
{
  using namespace std;
  int m1, m2;
  long subSize;
  switch (type[1])
    {
    case 'E':
      /*
      subSize = size;
      row[subSize] = position;
      pcol[position] = subSize;
      */
      break;
    case 'C':
      rowTemp[0] = position;
      break;
    }
  ACTemp[0] = std::complex<double>(0.0,0.0);
  // spin up and up
  for (int i1 = 0; i1 < n1; i1++)
    {
      m1 = pB1[i1];
      for (int i2 = i1 + 1; i2 < n1; i2++)
	{
	  m2 = pB1[i2];
	  ACTemp[0] += itrAC[m1 * nOrb * nOrb + m2 * nOrb + m1] - itrAC[m1 * nOrb * nOrb + m2 * nOrb + m2];
	}
    }
  // spin down and down
  for (int i1 = 0; i1 < n2; i1++)
    {
      m1 = pB2[i1];
      for (int i2 = i1 + 1; i2 < n2; i2++)
	{
	  m2 = pB2[i2];
	  ACTemp[0] += itrAC[m1 * nOrb * nOrb + m2 * nOrb + m1] - itrAC[m1 * nOrb * nOrb + m2 * nOrb + m2];
	}
    }
  // spin up and down
  for (int i1 = 0; i1 < n1; i1++)
    {
      m1 = pB1[i1];
      for (int i2 = 0; i2 < n2; i2++)
	{
	  m2 = pB2[i2];
	  ACTemp[0] += itrRC[m1 * nOrb * nOrb + m2 * nOrb + m1];
	}
    }
}

void matrix::diaMED(int position, long deci, int pB1[], int pB2[], int rowTemp[], double ATemp[])
{
  using namespace std;
  int m1, m2;
  long subSize;
  switch (type[1])
    {
    case 'E':
      /*
      subSize = size;
      row[subSize] = position;
      pcol[position] = subSize;
      */
      break;
    case 'C':
      rowTemp[0] = position;
      break;
    }
  ATemp[0] = 0;
  if (n1 != 0 && n2 != 0)
  // spin up and up
  for (int i1 = 0; i1 < n1; i1++)
    {
      m1 = pB1[i1];
      for (int i2 = i1 + 1; i2 < n1; i2++)
	{
	  m2 = pB1[i2];
	  ATemp[0] += itrA[m1 * nOrb * nOrb + m2 * nOrb + m1] - itrA[m1 * nOrb * nOrb + m2 * nOrb + m2];
	}
    }

  // spin down and down
  for (int i1 = 0; i1 < n2; i1++)
    {
      m1 = pB2[i1];
      for (int i2 = i1 + 1; i2 < n2; i2++)
	{
	  m2 = pB2[i2];
	  ATemp[0] += itrA[m1 * nOrb * nOrb + m2 * nOrb + m1] - itrA[m1 * nOrb * nOrb + m2 * nOrb + m2];
	}
    }

  if (n1 != 0 && n2 != 0)
  // spin up and down
  for (int i1 = 0; i1 < n1; i1++)
    {
      m1 = pB1[i1];
      for (int i2 = 0; i2 < n2; i2++)
	{
	  m2 = pB2[i2];
	  ATemp[0] += itrR[m1 * nOrb * nOrb + m2 * nOrb + m1];
	}
    }
}
