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

#include "./basis/basis.h"
#include "./interaction/interaction.h"
#include "./matrix/matrix.h"
#include "./ED/ED.h"
#include <cmath> // sqrt
#include <gsl/gsl_math.h> // pi
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

std::string nameFileTool(std::string, int);
std::string nameFileTool(std::string, double);


int main()
{
  using namespace std;
  cout << "==============================================================" << endl;
  cout << "=========================== YED ==============================" << endl;
  cout << "==============================================================" << endl;
  cout << "Feb. 2 Version." << endl;
  const double timeDivider = 60.0 * 60;

  clock_t timeStart;
  timeStart = clock();
  cout << "start time: " << (double)(timeStart)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;

  int s, t, n, nOrb;
  double v;
  double ratio;
  ifstream fin;
  fin.open("parameter");
  fin >> n;
  fin >> nOrb;
  fin >> s;
  fin >> t;
  fin >> v;
  fin >> ratio;
  fin.close();
  // basis:
  int n1 = n / 2, n2 = n / 2,
    qn = t,
    wn = 35;
  char geometry = 'T';
  basis bases(n1, n2, nOrb, qn, s, geometry);
  bases.bGen();

  clock_t timeBasis;
  timeBasis = clock();
  cout << "basis finished time: " << (double)(timeBasis)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;

  //  bases.print();
  //bases.debug();
  //cout << "==============================================";
  //bases.debugM();
  //cout << "==============================================";
  // intra-layer interaction:
  double a = sqrt(ratio * 2.0 * M_PI * nOrb), b = sqrt(2.0 * M_PI * nOrb / ratio),
    d = 0,
    param[4] = {a, b, d};
  int LLn = 0;
  char type[3] = "TD";
  interaction itrA(nOrb, LLn, param, type);
  itrA.itrGen();
  //itrA.itrPrint(0, 1, 3);
  //itrA.print();
  // inter-layer interaction:
  d = v;
  param[2] = d;
  interaction itrR(nOrb, LLn, param, type);
  itrR.itrGen();
  // generate matrix
  int sizeCountType = 'C';
  char matrixType = 'w'; // w: whole; l: low part
  matrix m(bases, itrA, itrR, matrixType, sizeCountType, t, s);
  m.mGen();

  clock_t timeMatrix;
  timeMatrix = clock();
  cout << "matrix finished time: " << (double)(timeMatrix)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;

  //  m.print();
  // ED
  ED ed(m, wn);
  ed.arpackpp();

  clock_t timeED;
  timeED = clock();
  cout << "ED finished time: " << (double)(timeED)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;

  std::string name = "../../rawData/dipolar";
  name += "/";
  name += nameFileTool("N", n1 + n2);
  name += "/";
  name += nameFileTool("s", s);
  name += nameFileTool("t", t);
  name += "/";
  name += nameFileTool("r", ratio);
  name += nameFileTool("d", d);
  // name in YEDCondor
  name = nameFileTool("r", ratio);
  name += nameFileTool("d", d);
  std::cout << name << std::endl;
  ed.fileOP(name);

  cout << "==============================================================" << endl;
  cout << "==============================================================" << endl;
}

std::string nameFileTool(std::string p, int pn)
{
  using namespace std;
  string output = p;
  string temp;
  ostringstream convert;
  convert << pn;
  temp = convert.str();
  output += temp;
  convert.str("");
  return output;
}

std::string nameFileTool(std::string p, double number)
{
  using namespace std;
  string output = p;
  ostringstream strs;
  strs << number;
  string n = strs.str();
  output += n;
  return output;
}
