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

#include<iostream>
#include<iomanip>
#include<fstream>
#include "analysis.h"

void analysis::output()
{
  using namespace std;
  std::ofstream fout;
  cout << outputName << endl;
  fout.open(outputName.c_str());
  for (int i = 0; i < wn; i++)
    {
      fout << setiosflags(ios::fixed) << setprecision(6) << phD[i].e << " ";
      fout << setiosflags(ios::fixed) << setprecision(6) << phD[i].e - phD[0].e << " ";
      fout << phD[i].deg << " ";
      for (int j = 1; j <= phD[i].degUniq; j++)
	{
	  fout << phD[i].repst[2 * j - 2] << " ";
	  fout << phD[i].repst[2 * j - 1] << " ";
	  fout << setiosflags(ios::fixed) << setprecision(3) << phD[i].repK[2 * j - 2] << " ";
	  fout << setiosflags(ios::fixed) << setprecision(3) << phD[i].repK[2 * j - 1] << " ";
	}
      fout << endl;
    }	
  fout.close();
}
