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

#include <gsl/gsl_math.h> // pi
#include <iostream>
#include "analysis.h"

void analysis::newForm()
{
  for (int i = 0; i < wn; i++)
    {
      phD[i].e = arE[i];
      phD[i].degUniq = ar[i][0];
      int degNo = phD[i].degUniq;
      phD[i].deg = 0;
      for (int j = 1; j <= degNo; j++)
	{
	  int s = ar[i][2 * j - 1];
	  int t = ar[i][2 * j];
	  phD[i].repst[2 * j - 2] = s;
	  phD[i].repst[2 * j - 1] = t;

	  double kx = sqrt(2 * M_PI / ratio / nOrb) * (s - s0);
	  double ky = sqrt(2 * M_PI * ratio / nOrb) * (t - t0);
	  phD[i].repK[2 * j - 2] = kx;
	  phD[i].repK[2 * j - 1] = ky;
	  switch (ratioFlag)
	    {
	    case 1: 
	      phD[i].deg += degFunR1(s, t);
	      break;
	    case 0:
	      phD[i].deg += degFunRG(s, t);
	      break;
	    default: 
	      std::cout << "error: ratioFlag's value is wrong!";
	      break;
	    }
	}
    }
}

int analysis::degFunR1(int s, int t)
{
  if ((t == N && s == N) || 
      (t == N/2 && s == N/2))
    return 1;
  else if (s == N/2 && t == N)
    return 2;
  else if ((s == N/2 && N/2 < t && t < N) || 
	   (t == N && N/2 < s && s < N) || 
	   (t != N && t != N/2 && s == t))
    return 4;
  else 
    return 8;
}

int analysis::degFunRG(int s, int t)
{
  if ((t == N && s == N) || 
      (t == N/2 && s == N/2) ||
      (t == N/2 && s == N) ||
      (t == N && s == N/2))
    return 1;
  else if ((s == N/2 && N/2 < t && t < N) ||
	   (t == N/2 && N/2 < s && s < N) ||
	   (s == N && N/2 < t && t < N) ||
	   (t == N && N/2 < s && s < N))
    return 2;
  else if (N/2 < s && s < N && N/2 < t && t < N)
    return 4;
  else 
    return 1000;
}

