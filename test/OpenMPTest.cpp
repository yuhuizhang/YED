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
using namespace std;
 
#include <omp.h>
 
int main(int argc, char *argv[])
{
  int th_id, nthreads;
#pragma omp parallel private(th_id) shared(nthreads)
  {
    th_id = omp_get_thread_num();
#pragma omp critical
    {
      cout << "Hello World from thread " << th_id << '\n';
    }
#pragma omp barrier
 
#pragma omp master
    {
      nthreads = omp_get_num_threads();
      cout << "There are " << nthreads << " threads" << '\n';
    }
  }

  int s = 0;
#pragma omp parallel for private(th_id)
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < i * 100000; j++)
	continue;
      s += i;
      th_id = omp_get_thread_num();
      cout << "i = " << i << ", s = " << s <<endl;
      cout << "H " << th_id << '\n';
    }

  return 0;
}
