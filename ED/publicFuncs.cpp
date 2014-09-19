#include "ED.h"
#include "areig.h"
#include <iostream>
#include <complex>
#include <iomanip>
#include <string>
#include <algorithm> // sort()
#include <fstream>
#include "matrix/matrix.h"

ED::ED(matrix m_, int wn_)
{
  using namespace std;
  dim = m_.dim;
  size = m_.size;
  type[0] = m_.type[0];
  type[1] = m_.type[1];
  //  sizeC = 0;
  row = m_.row;
  pcol = m_.pcol;
  switch (type[0])
    {
    case 'D':
      A = m_.A;
      break;
    case 'T':
      AC = m_.AC;
      break;
    }
  s = m_.s;
  t = m_.t;
  wn = wn_;
}

void ED::arpackpp()
{
  using namespace std;
  // show the matrix (CSC)
  // cout << "dim = " << dim << ", size = " << size << endl;
  // for (int i = 0; i <= dim; i++)
  //   cout << pcol[i] << " ";
  // cout << endl;
  // for (long j = 0; j < size ; j++)
  //   cout << row[j] << " " << AC[j] << " ";
  // cout << endl;

  // show the matrix
  /*
  cout << "!!!!!!!!!" << endl;
  for (int i = 0; i <= dim; i++)
    cout << pcol[i] << " ";
  cout << endl;
  int i = 0;
  for (long j = 0; j < size ; j++)
    {
      if (j == pcol[i] && row[j - 1] != i - 1)
	{
	  i++;
	  cout << endl;
	}
      cout << row[j] << " " << AC[j] << " ";
    }
  cout << endl;
  */
  switch (type[0])
    {
    case 'D':
      EigValR = new double[wn];
      EigVecR = new double[wn * dim];
      cout << "Before ED check: dim = " << dim << ", size = " << size << endl;
      AREig(EigValR, EigVecR, dim, size, A, row, pcol, 'L', wn, "SM");
      EigValue = new double[wn];
      for (int i = 0; i < wn; i++)
	{
	  EigValue[i] = EigValR[i];
	}
      break;
    case 'T':
      EigValC = new std::complex<double>[wn];
      EigVecC = new std::complex<double>[wn * dim];
      cout << "Before ED check: dim = " << dim << ", size = " << size << endl;
      AREig(EigValC, EigVecC, dim, size, AC, row, pcol, wn, "SM", 0, 0.0, 10000 * wn);
      EigValue = new double[wn];
      for (int i = 0; i < wn; i++)
	EigValue[i] = std::real(EigValC[i]);
      std::sort(EigValue, EigValue + wn);
      break;
    }
}

void ED::terminalOP()
{
  using namespace std;
  cout << "The lowest energies are:" << endl;
  for (int i = 0; i < wn; i++)
    cout << i << ": " << setiosflags(ios::fixed) << setprecision(8) << EigValue[i] - 100 << endl;
}

void ED::terminalVectorOP()
{
  using namespace std;
  cout << "The lowest eigenvectors are" << endl;
  for (int i = 0; i < wn; i++)
    {
      cout << "the no. " << i << ": ";
      for (int j = 0; j < dim; j++)
	cout << setiosflags(ios::fixed) << setprecision(8) << EigVecR[i * dim + j] << " ";
      cout << endl;
    }
}

void ED::fileOP(std::string name)
{
  using namespace std;
  ofstream fout;
  fout.open(name.c_str());
  for (int i = 0; i < wn; i++)
    fout << setiosflags(ios::fixed) << setprecision(8) << EigValue[i] - 100 << endl;
  fout.close();
}
