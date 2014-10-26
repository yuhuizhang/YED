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

#ifndef ANALYSIS_H_
#define ANALYSIS_H_
#include <string>

struct eLevel
{
  double e;
  int deg;
  int degUniq;
  int repst[20];
  double repK[20];
};

class analysis 
{
 private:
  int n1, n2, N, p, q, nOrb, wn;
  int s0, t0, stNo;
  double ratio;
  int ratioFlag; // 1 is ration = 1; 0 is other ratios
  std::string inputName1, inputName2, outputName;
  // inputName1 = rawData/TCTP/N6/
  // inputName2 = v0-0.5
  // outputName = data/TCTP/N6/v0-0.5
  double*** record;  
  int** ar;
  double* arE;
  eLevel* phD;

  std::string nameFileTool(std::string a, int n);
  std::string nameFileTool(std::string a, double n);
  void input();
  void compare();
  void newForm();
  int degFunRG(int s, int t);
  int degFunR1(int s, int t);
  void output();
 public:
  analysis(int n1_, int n2_, int nOrb_, double ratio_, int ratioFlag_, int wn_, std::string inputName1_, std::string inputName2_, std::string outputName_);
  ~analysis();
  void analyze();
};

#endif
