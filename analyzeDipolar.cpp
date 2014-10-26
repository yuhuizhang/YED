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

#include "./analysis/analysis.h"
#include <iostream>
#include <string>
#include <sstream>

std::string nameFileTool(std::string, int);
std::string nameFileTool(std::string, double);

int main()
{
  int n1 = 5, n2 = 5,
    nOrb = 20, wn = 35;
  double ratio = 1,
    ratioFlag = 1; // 1 is ratio = 1; 0 is other ratios
  std::string inputName1 = "rawData/dipolar/N10/";

  double dI = 0, dF = 4.5, dStep = 0.1;
  for (double i = dI; i < dF + dStep / 10; i += dStep)
    {
      double d = i;
      std::string inputName2 = nameFileTool("r", ratio);
      inputName2 += nameFileTool("d", d);
      std::string outputName = nameFileTool("data/dipolar/N10/r1d", d);
      std::cout << inputName1 << "; " << outputName << std::endl;
      analysis a(n1, n2, nOrb, ratio, ratioFlag, wn, inputName1, inputName2, outputName);
      a.analyze();
    }
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
