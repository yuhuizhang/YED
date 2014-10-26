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
#include <cmath>
#include <boost/math/common_factor.hpp>

void basis::deciToOB(long dec, int oB1[], int oB2[])
{
  using namespace std;
  long deciShift = (long)(pow(2, nOrb) + 0.5);
  long dec1 = dec / deciShift, dec2 = dec % deciShift,
    orb = nOrb - 1;

  do {
    switch (dec1 % 2)
      {
      case 1:
	oB1[orb--] = 1;
	break;
      case 0:
	oB1[orb--] = 0;
	break;
      }
    dec1 = dec1 / 2;
  } while (orb >= 0);

  orb = nOrb - 1;
  do
    {
      switch (dec2 % 2)
	{
	case 1:
	  oB2[orb--] = 1;
	  break;
	case 0:
	  oB2[orb--] = 0;
	  break;
	}
      dec2 = dec2 / 2;
    } while (orb >= 0);

  return;
}

void basis::deciToOB(long dec, int oB[])
{
  deciToOB(dec, NULL, oB);
  return;
}

int basis::pBToDeci(int b[], int n)
{
  int i, deci = 0;
  for (i = 0; i < n; i++)
    {
      deci += (int)(pow(2.0, nOrb - 1 - b[i]) + 0.5);
      //      std::cout << b[i] << ", " << nOrb - 1 - b[i] << "; " << (int)(pow(2.0, nOrb - 1 - b[i]) + 0.5) << endl;
    }
  return deci;
}

int basis::pBToQN(int b[], int n)
{
  int i, qn = 0;
  for (i = 0; i < n; i++)
    qn += b[i];
  return qn;
}

void basis::deciToOBShow(long dec)
{
  int deciShift = (int) (pow(2, nOrb) + 0.5);
  int dec1 = dec / deciShift, dec2 = dec % deciShift; 
  int orb = nOrb - 1;
  do
    {
      switch (dec1 % 2)
	{
	case 1:
	  std::cout << 1 << " ";
	  orb--;
	  break;
	case 0:
	  std::cout << 0 << " ";
	  orb--;
	  break;
	}
      dec1=dec1/2;
    } while (orb >= 0);
  std::cout << "||";
  orb = nOrb - 1;
  do
    {
      switch (dec2 % 2)
	{
	case 1:
	  std::cout << 1 << " ";
	  orb--;
	  break;
	case 0:
	  std::cout << 0 << " ";
	  orb--;
	  break;
	}
      dec2=dec2/2;
    } while (orb >= 0);
}

void basis::deciToPBShow(long dec)
{
  int deciShift = (int) (pow(2, nOrb) + 0.5);
  int dec1 = dec / deciShift, dec2 = dec % deciShift; 
  std::cout << "dec = " << dec << " ";
  std::cout << "dec1 = " << dec1 << " dec2 = " << dec2 << "       ";
  int orb = nOrb - 1;
  do
    {
      switch (dec1 % 2)
	{
	case 1:
	  switch (type)
	    {
	    case 'T':
	      std::cout << orb + 1 << " ";
	      break;
	    case 'D':
	      std::cout << orb << " ";
	      break;
	    }
	  orb--;
	  break;
	case 0:
	  orb--;
	  break;
	}
      dec1=dec1/2;
    } while (orb >= 0);
  std::cout << "||";
  orb = nOrb - 1;
  do
    {
      switch (dec2 % 2)
	{
	case 1:
	  switch (type)
	    {
	    case 'T':
	      std::cout << orb + 1 << " ";
	      break;
	    case 'D':
	      std::cout << orb << " ";
	      break;
	    }
	  orb--;
	  break;
	case 0:
	  orb--;
	  break;
	}
      dec2=dec2/2;
    } while (orb >= 0);
}

void basis::tParameter()
{
  if (n1 == 0 || n2 == 0)
    {
      N = boost::math::gcd(n1 + n2, nOrb);
      p = (n1 + n2) / N;
      q = nOrb / N;
    }
  else
    {
      N = boost::math::gcd(n1 + n2, nOrb);
      p = (n1 + n2) / N;
      q = nOrb / N;
    }
}
