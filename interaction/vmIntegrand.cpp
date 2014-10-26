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
#include <gsl/gsl_sf_laguerre.h>
#include <gsl/gsl_math.h> // const pi
#include <iostream>

// Fourier tranfromation of different interactions in disk
double dFCoulomb(double k) {return 2 * M_PI / k;}

double vmIntegrand(double k, void* params)
{
  using namespace std;
  int n = *(int *) params, // means 0th Landau level
    m = *((int *) params + 1);
    double ln = gsl_sf_laguerre_n(n, 0, k*k/2),
    lm = gsl_sf_laguerre_n(m, 0, k*k),
    e = exp(-k * k);
  return (1/(2*M_PI)) * k * ln * ln * lm * e * dFCoulomb(k);
}

