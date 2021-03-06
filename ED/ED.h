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

#ifndef ED_H_
#define ED_H_

#include <complex>
#include <string>
#include "../matrix/matrix.h"

class matrix;

class ED
{
private:
  long dim;
  long size;
  //  long sizeC;
  double* A;
  std::complex<double>* AC;
  int* row;
  int* pcol;
  char type[2];
  int s, t;

  int wn;
  double *EigValR;
  double *EigVecR;
  std::complex<double> *EigValC;
  std::complex<double> *EigVecC;
  double* EigValue;
public:
  ED(matrix m_, int wn_);
  void arpackpp();
  void terminalOP();
  void terminalVectorOP();
  void fileOP(std::string name);
};

#endif
