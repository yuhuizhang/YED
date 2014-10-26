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

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

int main()
{
  using namespace std;
  int dim = 26;
  int sign[26] = {1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, -1, -1, 1, -1, -1, 1, -1, -1, -1, 1, -1};
  int size = (dim * dim - dim) / 2 + dim;
  double m1[size], m2[size];
  ifstream fin;
  fin.open("mm");
  for (int i = 0; i < size; i++)
    fin >> m1[i];
  for (int i = 0; i < size; i++)
    fin >> m2[i];
  fin.close();

  int s = 0;
  for (int j = 0; j < dim; j++)
    {
      cout << setw(3) << j << ": ";
      for (int i = j; i < dim; i++)
	{
	  //m1[s] *= sign[i] * sign[j];
	  if (abs(m1[s]) < 0.00000001)
	    cout << "0  ";
	  else if (abs(m1[s] - m2[s]) < 0.0000001)
	    cout << "+  "; // << m1[s] << " " << m2[s] << " ";
	  else 
	    cout << "-  "; // << m1[s] << " " << m2[s] << " ";
	  s++;
	}
      cout << endl;
    }

}
