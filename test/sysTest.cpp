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
#include <climits>
// use limits.h for older systems
int main()
{
using namespace std;
int n_int = INT_MAX;
// initialize n_int to max int value
short n_short = SHRT_MAX;
// symbols defined in climits file
long n_long = LONG_MAX;
long long n_llong = LLONG_MAX;
// sizeof operator yields size of type or of variable
cout << "int is " << sizeof (int) << " bytes." << endl;
cout << "short is " << sizeof n_short << " bytes." << endl;
cout << "long is " << sizeof n_long << " bytes." << endl;
cout << "long long is " << sizeof n_llong << " bytes." << endl;
cout << endl;
cout << "Maximum values:" << endl;
cout << "int: " << n_int << endl;
cout << "short: " << n_short << endl;
cout << "long: " << n_long << endl;
cout << "long long: " << n_llong << endl << endl;
cout << "Minimum int value = " << INT_MIN << endl;
cout << "Bits per byte = " << CHAR_BIT << endl;
return 0;
}
