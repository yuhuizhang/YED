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
#include <iostream>

void analysis::compare()
{
  using namespace std;
  double epsilon = 0.000001;
  int sign, degNo;
  if (record[0][0][0] > -epsilon)
    sign = 1;
  else 
    sign = -1;
  cout << "sign = " << sign << "; but not guaranteed." << endl;

  for (int i = 0; i < wn; i++)
    {
      arE[i] = 100.0; // just set a very large no.
      ar[i][0] = 0;
      int si = N / 2, ti;
      for (int s = si; s <= N; s++)
	{
	  if (ratioFlag == 1)
	    ti = s;
	  else if (ratioFlag == 0)
	    ti = N / 2;
	  for (int t = ti; t <= N; t++)
	    {
	      //cout << "t: " << t << ", s: " << s << endl;
	      int sc = s - si;
	      int tc = t - ti;
	      for (int j = 0; j < wn; j++)
		{ 
		  if (i == 0 && (long)((record[sc][tc][j] + sign * epsilon/10) / epsilon) < (long)((arE[i] + sign * epsilon/10) / epsilon)) 
		    {
		      arE[i] = record[sc][tc][j];
		      ar[i][0] = 1;
		      ar[i][1] = s;
		      ar[i][2] = t;
		      continue;
		    }
		  else if ((long)((record[sc][tc][j] + sign * epsilon/10) / epsilon) < (long)((arE[i] + sign * epsilon/10) / epsilon) && (long)((record[sc][tc][j] + sign * epsilon/10) / epsilon) > (long)((arE[i - 1] + sign * epsilon/10) / epsilon))
		    {
		      arE[i] = record[sc][tc][j];
		      ar[i][0] = 1;
		      ar[i][1] = s;
		      ar[i][2] = t;
		      continue;
		    }
		  else if ((long)((record[sc][tc][j] + sign * epsilon/10) / epsilon) == (long)((arE[i] + sign * epsilon/10) / epsilon))
		    {
		      ar[i][0]++;
		      degNo = ar[i][0];
		      ar[i][2 * degNo - 1] = s;
		      ar[i][2 * degNo] = t;
		      //		      cout << "s = " << s << ", t = " << t << endl;
		      //		      cout << "record: " << (long)((record[sc][tc][j] + sign * epsilon/10) / epsilon) << ", " << record[sc][tc][j] << endl;
		      //		      cout << "record: " << (long)((arE[i] + sign * epsilon/10) / epsilon) << ", " << arE[i] << endl;
		      continue;
		    }
		  else if ((long)((record[sc][tc][j] + sign * epsilon/10) / epsilon) > (long)((arE[i] + sign * epsilon/10) / epsilon))
		    continue;
		  else
		    continue;
		}
	    }
	}
    }
  cout << arE[0] << endl;
}
