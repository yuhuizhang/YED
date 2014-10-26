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

#ifndef MATRIX_H_
#define MATRIX_H_

#include <complex>
#include "../basis/basis.h"
#include "../interaction/interaction.h"

// forward declaration, since class matrix is the friend class of class basis and interaction
class basis;
class interaction;

class matrix
{
  friend class ED;
private:
  // asked variables
  char type[2];
  char matrixType;
  int n1, n2, nOrb;
  int q, N, s, t;
  long dim;
  // asked data
  long* bases;
  int* tStSetNo;
  // interactions
  double* itrA, * itrR;
  std::complex<double>* itrAC, * itrRC;
  // express the matrix (general)
  int* pcol;
  // 1D array CSC format
  double* A;
  std::complex<double>* AC;
  int* row;
  // 2D array format
  double** A2;
  int** row2;
  // for parallel programming
  int* basisSctNo;

  long size;
  void deciToPOB(long dec, int pB1[], int antipB1[], int oB1[], int pB2[], int antipB2[], int oB2[], int n1, int n2);
  void deciToPOS(long dec, int pB[], int antipB[], int oB[], int n);
  //  void deciToPB(int dec, int pB1[], int antiPB1[], int pB2[], int antiPB2[], int n1, int n2);
  long estimateSize();
  long countSize();
  int mAdd(int m1, int m2){
    switch (type[0])
      {
      case 'D':
	return m1 + m2;
      case 'T':
	return (m1 + m2) % nOrb;	  
      }
  }
  bool nZMEJuedge(int m1, int m2, int m3, int m4) {
    switch (type[0])
      {
      case 'D':
	return m1 + m2 == m3 + m4;
      case 'T':
	return (m1 + m2) % nOrb == (m3 + m4) % nOrb;
      }
  }
  int binarySearchBToS(long key, int imin, int imax, long array[]);
  int binarySearchSToB(int key, int imin, int imax, int array[]);
  int dOffME(int position, int deci, int pB1[], int antiPB1[], int oB1[], int pB2[], int antiPfB2[], int oB2[], char typ, int* rowTemp = NULL, double* ATemp = NULL);
  void diaMED(int position, long deci, int pB1[], int pB2[], int rowTemp[], double ATemp[]);
  void diaMET(int position, long deci, int pB1[], int pB2[], int rowTemp[], std::complex<double> ACTemp[]);
  //  int tLocatseMES(int& deci);
  int tLocateME(long& deci);
  int sgnChange(int m1, int m2, int m3, int m4, int n, int oB[], long newStateDeci, long newDeci);
  int sgnChange(int m1, int m2, int m3, int m4, int n1, int n2, int i1, int i2, int oB1[], int oB2[], long newStateDeci, long newDeci, char type);
  std::complex<double> tScatteredValue(int m1, int m2, int m3, int m4, int phase, int sign, int position, int newPosition, char t);
  void dStoreValue(int position, int rowTemp[], double ATemp[], int rNo);
  int tStoreValueTemp(std::complex<double> meM, int position, int newPosition, int rowTemp[], std::complex<double> ACTemp[], int& rNo);
  void tStoreValue(int position, int rowTemp[], std::complex<double> ACTemp[], int rNo);
  int tNewJudge(int position, int newPosition, int& superSize, int pseudoRow[]);
  int tOffME(int position, long deci, int pB1[], int antiPB1[], int oB1[], int pB2[], int antiPB2[], int oB2[], char type, int* rowTemp = NULL, std::complex<double>* ACTemp = NULL);
public:
  matrix(basis b_, interaction itrA_, interaction itrR_, char matrixType_, char sizeCountType_, int t_, int s_);
  void mGen();
  void print();
};

#endif
