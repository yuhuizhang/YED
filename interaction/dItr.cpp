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

#include "interaction.h"
#include <cmath> // exp(); pow(); sqrt()
#include <gsl/gsl_integration.h>
#include <algorithm> // max() and min()
#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <iostream>

double interaction::vm(int m)
{
  using namespace std;
  int n = LLn;
  gsl_function F;
  double result, error;
  int p[2];
  p[0] = n;
  p[1] = m;
  gsl_integration_workspace* w = gsl_integration_workspace_alloc(1000);
  F.function = &vmIntegrand;
  F.params = &p;
  gsl_integration_qagiu(&F, 0, 1e-13, 0, 1000, w, &result, &error);
  gsl_integration_workspace_free(w);
  return result;
}

double interaction::cgc(int m1, int m2, int m)
{
  if (m1 + m2 < m)
    return 0;
  using namespace boost::math;
  using namespace std;
  double result = 0;
  for (int n = std::max(0, m - m2); n <= std::min(m, m1); n++)
    result += pow(-1, m - n) * binomial_coefficient<double>(m1, n) * binomial_coefficient<double>(m2, m - n);
  result *= sqrt(factorial<double>(m1 + m2 - m) * factorial<double>(m) / (factorial<double>(m1) * factorial<double>(m2) * pow(2, m1 + m2)));
  return result;
}

double interaction::dItr(int m1, int m2, int m3)
{
  using namespace std;
  int m4 = m1 + m2 - m3;
  if (m4 < 0)
    return 0;
  double result = 0;
  switch (type[1])
    {
    case 'C':
      for (int m = 0; m <= m1 + m2; m++)
	result += cgc(m3, m4, m) * vm(m) * cgc(m1, m2, m);
      break;
    case 'H':
      for (int m = 0; m <= 1; m++)
	{
	  result += cgc(m3, m4, m) * param[2 + m] * cgc(m1, m2, m);
	}
      break;
    }
  return result;
}

