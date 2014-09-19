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


