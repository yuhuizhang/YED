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

#include "analysis.h"

void analysis::parametersGen()
{
  int n = n1 + n2;
  for(N = n; N >= 1; N--)
    if(n % N == 0 && nOrb % N == 0)
      break;
  p = n / N;
  q = nOrb / N;

  int pow = p * q * (n - 1);
  if (pow % 2 == 0)
    {
      t0 = N; s0 = N;
    }
  else 
    {
      t0 = N / 2; s0 = N / 2;
    }
  stNo = N / 2 + 1;
}
