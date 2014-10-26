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
#include <cmath> // sqrt(); cos(); sin()
#include <complex>
#include <boost/math/special_functions/binomial.hpp>
#include <iostream>

int matrix::tOffME(int position, long deci, int pB1[], int antipB1[], int oB1[], int pB2[], int antipB2[], int oB2[], char typ, int* rowTemp, std::complex<double>* ACTemp)
{
  using namespace std;
  int m1, m2, m3, m4;
  int phase;
  std::complex<double> meM;
  //*** for type[1] = 'C' ***
  int rNo = 1;
  using namespace boost::math;
  int pseudoRow[(int)((binomial_coefficient<double>(n1, 2) * (nOrb - n1) 
		       + binomial_coefficient<double>(n2, 2) * (nOrb - n2)
		       + n1 * n2 * (nOrb - n1)))];
  pseudoRow[0] = position;

  // spin up and up
  for (int i1 = 0; i1 < n1; i1++)
    { 
      m1 = pB1[i1];
      for (int i2 = i1 + 1; i2 < n1; i2++)
	{
	  m2 = pB1[i2];
	  for (int i3 = 0; i3 < nOrb - n1; i3++)
	    {
	      m3 = antipB1[i3];
	      for (int diffRangeNo = 0; diffRangeNo <= 1; diffRangeNo++)
		{
		  m4 = (m1 + m2) % nOrb + diffRangeNo * nOrb - m3;
		  if (m4 > m3 && m4 < nOrb && oB1[m4] == 0)
		    {
		      /*
		      if (typ == 'O')
			cout << "m1" << m1 << "m2" << m2 << "m3" << m3 << "m4" << m4 << endl;
		      */
		      long newDeci = deci + (long) (pow(2.0, 2 * nOrb - 1 - m3) + pow(2.0, 2 * nOrb - 1 - m4) + 0.5) - (long) (pow(2.0, 2 * nOrb - 1 - m1) + pow(2.0, 2 * nOrb - 1 - m2) + 0.5);
		      long newStateDeci = newDeci;
		      phase = tLocateME(newStateDeci); // this also give the right newDeci
		      /*
		      if (typ == 'O')
			{
			  cout << "newStateDeci: " << newStateDeci << ", dim = " << dim << endl;
			  cout << bases[0] << " -> " << bases[dim - 1] << endl;
			}
		      */
		      int newPosition = binarySearchBToS(newStateDeci, 0, dim - 1, bases);
		      /*
		      if (typ == 'O')
			cout << "newPosition" << newPosition << endl;
		      */

		      if ((newPosition >= position && typ == 'O' && matrixType == 'l') ||
			  (newPosition != -1 && typ == 'O' && matrixType == 'w'))
			{
			  int sign = sgnChange(m1, m2, m3, m4, n1, n2, i1, i2, oB1, oB2, newStateDeci, newDeci, 'U');
			  //			  cout << phase << " " << sign << " " << position << " " << newPosition << endl;
			  meM = tScatteredValue(m1, m2, m3, m4, phase, sign, position, newPosition, 'S');
			  tStoreValueTemp(meM, position, newPosition, rowTemp, ACTemp, rNo);
			}

		      else if ((newPosition >= position && typ == 'C' && matrixType == 'l') ||
			       (newPosition != -1 && typ == 'C' && matrixType == 'w'))
			{
			  if (tNewJudge(position, newPosition, rNo, pseudoRow) == 1)
			    basisSctNo[position]++;
			}

		      else
			continue;
		    }
		  else 
		    continue;
		}
	    }
	}
    }

  // spin down and down
  for (int i1 = 0; i1 < n2; i1++)
    {
      m1 = pB2[i1];
      for (int i2 = i1 + 1; i2 < n2; i2++)
	{
	  m2 = pB2[i2];
	  for (int i3 = 0; i3 < nOrb - n2; i3++)
	    {
	      m3 = antipB2[i3];
	      for (int diffRangeNo = 0; diffRangeNo <= 1; diffRangeNo++)
		{
		  m4 = (m1 + m2) % nOrb + diffRangeNo * nOrb - m3;
		  if (m4 > m3 && m4 < nOrb && oB2[m4] == 0)
		    {
		      long newDeci = deci + (long) (pow(2.0, nOrb - 1 - m3) + pow(2.0, nOrb - 1 - m4) + 0.5) - (long) (pow(2.0, nOrb - 1 - m1) + pow(2.0, nOrb - 1 - m2) + 0.5);
		      long newStateDeci = newDeci;
		      phase = tLocateME(newStateDeci); // this also give the right newDeci
		      int newPosition = binarySearchBToS(newStateDeci, 0, dim - 1, bases);
		      if ((newPosition >= position && typ == 'O' && matrixType == 'l') ||
			  (newPosition != -1 && typ == 'O' && matrixType == 'w'))
			{
			  int sign = sgnChange(m1, m2, m3, m4, n1, n2, i1, i2, oB1, oB2, newStateDeci, newDeci, 'D');
			  meM = tScatteredValue(m1, m2, m3, m4, phase, sign, position, newPosition, 'S');
			  tStoreValueTemp(meM, position, newPosition, rowTemp, ACTemp, rNo);
			}

		      else if ((newPosition >= position && typ == 'C' && matrixType == 'l') ||
			       (newPosition != -1 && typ == 'C' && matrixType == 'w'))
			{
			  if (tNewJudge(position, newPosition, rNo, pseudoRow) == 1)
			    basisSctNo[position]++;
			}

		      else
			continue;
		    }
		  else 
		    continue;
		}
	    }
	}
    }

  // spin up and down
  for (int i1 = 0; i1 < n1; i1++)
    {
      m1 = pB1[i1];
      for (int i2 = 0; i2 < n2; i2++)
	{
	  m2 = pB2[i2];
	  for (int i3 = 0; i3 < nOrb - n1; i3++)
	    {
	      m3 = antipB1[i3];
	      for (int diffRangeNo = 0; diffRangeNo <= 1; diffRangeNo++)
		{
		  m4 = (m1 + m2) % nOrb + diffRangeNo * nOrb - m3;
		  //cout << "m1: " << m1 << ", m2: " << m2 << ", m3: " << m3 << ", m4: " << m4 << endl;
		  if (0 <= m4 && m4 < nOrb && oB2[m4] == 0)
		    {
		      long newDeci = deci + (long) (pow(2.0, 2 * nOrb - 1 - m3) + pow(2.0, nOrb - 1 - m4) + 0.5) - (long) (pow(2.0, 2 * nOrb - 1 - m1) + pow(2.0, nOrb - 1 - m2) + 0.5);
		      long newStateDeci = newDeci;
		      phase = tLocateME(newStateDeci); // this also give the right newDeci
		      int newPosition = binarySearchBToS(newStateDeci, 0, dim - 1, bases);
		      if ((newPosition >= position && typ == 'O' && matrixType == 'l') ||
			  (newPosition != -1 && typ == 'O' && matrixType == 'w'))
			{
			  int sign = sgnChange(m1, m2, m3, m4, n1, n2, i1, i2, oB1, oB2, newStateDeci, newDeci, 'B');
			  meM = tScatteredValue(m1, m2, m3, m4, phase, sign, position, newPosition, 'B');
			  tStoreValueTemp(meM, position, newPosition, rowTemp, ACTemp, rNo);
			}

		      else if ((newPosition >= position && typ == 'C' && matrixType == 'l') ||
			       (newPosition != -1 && typ == 'C' && matrixType == 'w'))
			{
			  if (tNewJudge(position, newPosition, rNo, pseudoRow) == 1)
			    basisSctNo[position]++;
			}

		      else
			continue;
		    }
		  else 
		    continue;
		}
	    }
	}
    }
  return rNo;
}
