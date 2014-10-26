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

//
// ----------Function Name: orbBToDeci: ----------
// Location: basis/basisInfo.cpp
// Function: translate the orbital basis to a decimal number.
// Return: the decimal number

#ifndef BASIS_H_
#define BASIS_H_

class basis
{
  friend class matrix;
private:
  int n1, n2, nOrb, qn, s;
  char type;
  long* bases;
  long* bCompare;
  int* tStSetNo;
  long dim;
  int p, q, N;  // parameters for torus geometry
  int pBToDeci(int b[], int n);
  int pBToQN(int b[], int n);
  void constr(int n, long b[], int qn[]);
  void deciToOBShow(long dec);
  void deciToPBShow(long dec);
  void deciToOB(long dec, int oB1[], int oB2[]);
  void deciToOB(long dec, int oB[]);
  int dGen();
  void tParameter();
  int sTBasisJudge(long b);
  int biTBasisJudge(long b);
  int tGen();
public:
  basis(int n1_, int n2_, int nOrb_, int qn_, int s_, char type_);
  int bGen();
  void print();
};

#endif


