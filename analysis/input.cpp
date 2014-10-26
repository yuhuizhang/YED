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
#include <fstream>

void analysis::input()
{
  using namespace std;
  std::ifstream fin;
  int si = N / 2, ti;
  for (int s = si; s <= N; s++)
    {
      if (ratioFlag == 1)
	ti = s;
      else if (ratioFlag == 0)
	ti = N / 2;
      for (int t = ti; t <= N; t++)
	{
	  std::string name = inputName1;
	  name += nameFileTool("s", s);
	  name += nameFileTool("t", t);
	  name += "/";
	  name += inputName2;
	  fin.open(name.c_str());
	  int sc = s - si;
	  int tc = t - ti;
	  for (int i = 0; i < wn; i++)
	    fin >> record[sc][tc][i];
	  fin.close();
	}
    }
}
