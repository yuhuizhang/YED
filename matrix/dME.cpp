#include "matrix.h"
#include <cmath> // pow
#include <iostream>

int matrix::dOffME(int position, int deci, int pB1[], int antipB1[], int oB1[], int pB2[], int antipB2[], int oB2[], char typ, int* rowTemp, double* ATemp)
{
  using namespace std;
  int m1, m2, m3, m4;
  int sign, subSize = 1;
  int rNo = 1;
  // spin up and up
  if (n1 != 0 && n2 != 0) // this is added bacause if there is just one component of electrons, I want it run in the spin "down and down" section.
    for (int i1 = 0; i1 < n1; i1++)
      {
	m1 = pB1[i1];
	for (int i2 = i1 + 1; i2 < n1; i2++)
	  {
	    m2 = pB1[i2];
	    for (int i3 = 0; i3 < nOrb - n1; i3++)
	      {
		m3 = antipB1[i3];
		m4 = m1 + m2 - m3;
		if (m4 > m3 && m4 < nOrb && oB1[m4] == 0)
		  {
		    int newDeci = deci + (long) (pow(2.0, 2 * nOrb - 1 - m3) + pow(2.0, 2 * nOrb - 1 - m4) + 0.5) - (long) (pow(2.0, 2 * nOrb - 1 - m1) + pow(2.0, 2 * nOrb - 1 - m2) + 0.5);
		    int newPosition = binarySearchBToS(newDeci, 0, dim - 1, bases);
		    if (newPosition > position && typ == 'O')
		      {
			sign = 1;
			for (int m = m1 + 1; m < m2; m++)
			  if (oB1[m] == 1) 
			    sign *= -1;
			for (int m = m3 + 1; m < m4; m++)
			  if (m != m1 && m != m2 && oB1[m] == 1)
			    sign *= -1;
			ATemp[subSize] = sign * (itrA[m1 * nOrb * nOrb + m2 * nOrb + m3] - itrA[m1 * nOrb * nOrb + m2 * nOrb + m4]);
			rowTemp[subSize] = newPosition;
			subSize++;
			rNo++;
		      }
		    else if (newPosition > position && typ == 'C')
		      {
			basisSctNo[position]++;
			rNo++;
		      }
		    else
		      continue;
		  }
		else 
		  continue;
	      }
	  }
      }

  // spin down and down or single component part
  for (int i1 = 0; i1 < n2; i1++)
    {
      m1 = pB2[i1];
      for (int i2 = i1 + 1; i2 < n2; i2++)
	{
	  m2 = pB2[i2];
	  for (int i3 = 0; i3 < nOrb - n2; i3++)
	    {
	      m3 = antipB2[i3];
	      m4 = m1 + m2 - m3;
	      if (m4 > m3 && m4 < nOrb && oB2[m4] == 0)
		{
		  int newDeci = deci + (long) (pow(2.0, nOrb - 1 - m3) + pow(2.0, nOrb - 1 - m4) + 0.5) - (long) (pow(2.0, nOrb - 1 - m1) + pow(2.0, nOrb - 1 - m2) + 0.5);
		  int newPosition = binarySearchBToS(newDeci, 0, dim - 1, bases);
		  if (newPosition > position && typ == 'O')
		    {
		      sign = 1;
		      for (int m = m1 + 1; m < m2; m++)
			if (oB2[m] == 1) 
			  sign *= -1;
		      for (int m = m3 + 1; m < m4; m++)
			if (m != m1 && m != m2 && oB2[m] == 1)
			  sign *= -1;
		      ATemp[subSize] = sign * (itrA[m1 * nOrb * nOrb + m2 * nOrb + m3] - itrA[m1 * nOrb * nOrb + m2 * nOrb + m4]);
		      rowTemp[subSize] = newPosition;
		      subSize++;
		      rNo++;
		    }
		  else if (newPosition > position && typ == 'C')
		    {
		      basisSctNo[position]++;
		      rNo++;
		    }
		  else
		    continue;

		}
	      else 
		continue;
	    }
	}
    }
  // spin up and down
  if (n1 != 0 && n2 != 0)
    for (int i1 = 0; i1 < n1; i1++)
      {
	m1 = pB1[i1];
	for (int i2 = 0; i2 < n2; i2++)
	  {
	    m2 = pB2[i2];
	    for (int i3 = 0; i3 < nOrb - n1; i3++)
	      {
		m3 = antipB1[i3];
		m4 = m1 + m2 - m3;
		if (m4 >= 0 && m4 < nOrb && oB2[m4] == 0)
		  {
		    int newDeci = deci + (long) (pow(2.0, 2 * nOrb - 1 - m3) + pow(2.0, nOrb - 1 - m4) + 0.5) - (long) (pow(2.0, 2 * nOrb - 1 - m1) + pow(2.0, nOrb - 1 - m2) + 0.5);
		    int newPosition = binarySearchBToS(newDeci, 0, dim - 1, bases);
		    if (newPosition > position && typ == 'O')
		      {
			sign = 1;
			sign *= (int)(pow(-1.0, i1) + 0.5);
			sign *= (int)(pow(-1.0, i2) + 0.5);
			for (int m = 0; m < m3; m++)
			  if (m != m1 && oB1[m] == 1)
			    sign *= -1;
			for (int m = 0; m < m4; m++)
			  if (m != m2 && oB2[m] == 1)
			    sign *= -1;
			ATemp[subSize] = sign * itrR[m1 * nOrb * nOrb + m2 * nOrb + m3];
			rowTemp[subSize] = newPosition;
			subSize++;
			rNo++;
		      }
		    else if (newPosition > position && typ == 'C')
		      {
			basisSctNo[position]++;
			rNo++;
		      }
		    else
		      continue;
		  }
		else 
		  continue;
	      }
	  }
      }
  return rNo;
}
