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
