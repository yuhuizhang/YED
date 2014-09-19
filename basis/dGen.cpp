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

