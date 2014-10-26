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

std::string nameFileTool(std::string, int);
std::string nameFileTool(std::string, double);

int main()
{
  using namespace std;
  cout << "==============================================================" << endl;
  cout << "=========================== YED ==============================" << endl;
  cout << "==============================================================" << endl;
  int s = 4, t = 4;
  cout << "s = " << s << "; t = " << t << endl;
  // basis:
  int n1 = 3, n2 = 3,
    nOrb = 12, qn = t,
    wn = 20;
  char geometry = 'T';
  basis bases(n1, n2, nOrb, qn, s, geometry);
  bases.bGen();
  //  bases.print();
  //bases.debug();
  //cout << "==============================================";
  //bases.debugM();
  //cout << "==============================================";
  // intra-layer interaction:
  double a = sqrt(2.0 * M_PI * nOrb), b = sqrt(2.0 * M_PI * nOrb),
    c0 = 0, c1 = 1,
    param[4] = {a, b, c0, c1};
  int LLn = 0;
  char type[3] = "TH";
  interaction itrA(nOrb, LLn, param, type);
  itrA.itrGen();
  itrA.itrPrint(6, 4, 2);
  //itrA.itrPrint(0, 1, 3);
  //itrA.print();
  // inter-layer interaction:
  c1 = 1;
  double c0I = -8, c0F = 0, c0Step = 0.5;
  for (double i = c0I; i < c0F + c0Step / 10; i += c0Step)
    {
      c0 = i;
      cout << "c0 = " << c0 << endl;
      param[2] = c0; param[3] = c1;
      interaction itrR(nOrb, LLn, param, type);
      itrR.itrGen();
      // generate matrix
      int sizeCountType = 'C';
      char matrixType = 'w'; // w: whole; l: low part
      matrix m(bases, itrA, itrR, matrixType, sizeCountType, t, s);
      m.mGen();
      //  m.print();
      // ED
      ED ed(m, wn);
      ed.arpackpp();
      std::string name = "../rawData/TCTP";
      name += nameFileTool("N", n1 + n2);
      name += "/";
      name += nameFileTool("s", s);
      name += nameFileTool("t", t);
      name += "/";
      name += nameFileTool("v0", c0);
      std::cout << name << std::endl;
      ed.fileOP(name);
    }
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
