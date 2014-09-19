#include "interaction.h"
#include <gsl/gsl_sf_laguerre.h>
#include <cmath> // sqrt(); exp(); cos() and sin()
#include <complex>
#include <gsl/gsl_math.h> // const pi
#include <iostream>

double interaction::tF(double qx, double qy)
{
  double q2 = qx*qx + qy*qy;
  switch (type[1])
    {
    case 'H': return param[2] * 2.0 * gsl_sf_laguerre_n(0, 0, q2) + param[3] * 2.0 * gsl_sf_laguerre_n(1, 0, q2);
    case 'C': return 1 / sqrt(q2);
    case 'D': return -sqrt(q2) * exp(-param[2] * sqrt(q2));
    default : return 0;
    }
}


std::complex<double> interaction::tItr(int m1, int m2, int m3)
{
  using namespace std;
  double epsilon = 1e-13;
  int tt = m3 - m1, tau = m3 - m2;
  complex<double> result (0.0, 0.0), compare;
  double temp, qx, qy, a = param[0], b = param[1];
  int lim = 2 * nOrb - 2, t, s;
  do {
    compare = result;
    result = complex<double>(0.0, 0.0);
    lim += 2;
    for (t = -lim; t <= lim; t++)
      for (s = -lim; s <= lim; s++)
	{
	  if ((tt + 100 * nOrb) % nOrb == (t + 100 * nOrb) % nOrb) // if I don't add 100 * nOrb, the result may be a negative number
	    {
	      qx = 2.0 * M_PI * s / a;
	      qy = 2.0 * M_PI * t / b;
	      temp = tF(qx, qy) * exp(-(1.0/2)*(qx*qx + qy*qy));
	      real(result) += cos(-2.0 * M_PI * s * tau / nOrb) * temp;
	      imag(result) += sin(-2.0 * M_PI * s * tau / nOrb) * temp;
	    }
	  else 
	    continue;
	}
  } while(!((-epsilon < real(result) - real(compare) && real(result) - real(compare) < epsilon) && (-epsilon < imag(result) - imag(compare) && imag(result) - imag(compare) < epsilon)));
  result *= 2.0 * M_PI / (a * b);
  return result;
}










