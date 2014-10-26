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
#include <string>
#include <iostream>

analysis::analysis(int n1_, int n2_, int nOrb_, double ratio_, int ratioFlag_, int wn_, std::string inputName1_, std::string inputName2_, std::string outputName_)
{
  n1 = n1_;
  n2 = n2_;
  nOrb = nOrb_;
  ratio = ratio_;
  ratioFlag = ratioFlag_;
  wn = wn_;
  inputName1 = inputName1_;
  inputName2 = inputName2_;
  outputName = outputName_;
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

  record = new double **[stNo];
  for (int i = 0; i < stNo; i++)
    {
      record[i] = new double *[stNo];
      for (int j = 0; j < stNo; j++)
	record[i][j] = new double[wn];
    }
  ar = new int *[wn];
  for (int i = 0; i < wn; i++)
    ar[i] = new int[1 + N * N];
  arE = new double[wn];
  phD = new eLevel[wn];
}

analysis::~analysis()
{
  for (int i = 0; i < stNo; i++)
    {
      for (int j = 0; j < stNo; j++)
	delete[] record[i][j];
      delete[] record[i];
    }
  delete[] record;

  for (int i = 0; i < wn; i++)
    delete[] ar[i];
  delete[] ar;
  delete[] arE;
  delete[] phD;
}

void analysis::analyze()
{
  using namespace std;
  input();
  compare();
  newForm(); 
  output();
}
