// ----------Function Name: dFCoulomb(); vmIntegrand(); vm(); cgc(); dItr(): ----------
// Location: interaction/dItr.cpp
// Function: generate the interaction in disk geometry
// ----------Function Name: tF(); tItr(): ----------
// Location: interaction/tItr.cpp
// Function: generate the interaction in torus geometry
// ----------Function Name: itrGen(): ----------
// Location: interaction/itrGen.cpp
// Function: generate the function
#ifndef INTERACTION_H_
#define INTERACTION_H_

#include <gsl/gsl_math.h> // pi
#include <complex>
#include <gsl/gsl_integration.h>
#include <cmath> // exp(); pow(); sqrt()

double dFCoulomb(double k);
double vmIntegrand(double k, void* params);

class interaction
{
  friend class matrix;
private:
  int nOrb;
  int LLn; // Landau level no.
  double param[4]; // parameters of the interaction; like [a, b, c1, c2]
  char type[3];  //interaction type like "DC"
  double* itr;
  std::complex<double>* itrC;
  // for pseudo-potential method in disk
  double vm(int m);
  double cgc(int m1, int m2, int m);
  double dItr(int m1, int m2, int m3);
  // for interactions in torus
  double tF(double qx, double qy);
  std::complex<double> tItr(int m1, int m2, int m3);
public:
  interaction(int nOrb_, int LLn_, double param_[], char type_[]);
  void itrGen();
  void print();
  void itrPrint(int m1, int m2, int m3);
};

#endif
