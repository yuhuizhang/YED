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
  const double timeDivider = 60.0 * 60;
  cout << "Feb. 4 version:" << endl;
  clock_t timeStart;
  timeStart = clock();
  cout << "start time: " << (double)(timeStart)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;
  int nOrb;
  cout << "Orbital number = ";
  cin >> nOrb;
  int s = 0; // this parameter is for torus, no use here
  // basis:
  int n1 = 0, n2, // if it just has one component, make n1 = 0
    qn,
    wn;
  cout << "Particle number = ";
  cin >> n2;
  cout << "Total angular momentum = ";
  cin >> qn;
  cout << "The number of lowest energies do you want = ";
  cin >> wn;
  char geometry = 'D';
  basis bases(n1, n2, nOrb, qn, s, geometry);
  bases.bGen();
  clock_t timeBasis;
  timeBasis = clock();
  cout << "basis finished time: " << (double)(timeBasis)/CLOCKS_PER_SEC/timeDivider << "hr" << endl;
  bases.print();
  // intra-layer interaction:
  double a = 0, b = 0, // for torus, no use here
    c0 = 0, c1 = 1,
    param[4] = {a, b, c0, c1};
  int LLn = 0;
  char type[3] = "DH"; // Position 1: D means disk. Position 2: C means Coulomb interaction; H means hard core
  interaction itrA(nOrb, LLn, param, type);
  itrA.itrGen();
  // inter-layer interaction:
  c0 = 0; c1 = 1;
  param[2] = c0; param[3] = c1;
  interaction itrR(nOrb, LLn, param, type);
  itrR.itrGen();
  // generate matrix
  int sizeCountType = 'C';
  char matrixType = 'l'; // w: whole; l: low part
  matrix m(bases, itrA, itrR, matrixType, sizeCountType, qn, s);
  m.mGen();
  m.print();
  // ED
  ED ed(m, wn);
  ed.arpackpp();
  ed.terminalOP();
  //  ed.terminalVectorOP();
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
