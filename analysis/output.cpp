#include<iostream>
#include<iomanip>
#include<fstream>
#include "analysis.h"

void analysis::output()
{
  using namespace std;
  std::ofstream fout;
  cout << outputName << endl;
  fout.open(outputName.c_str());
  for (int i = 0; i < wn; i++)
    {
      fout << setiosflags(ios::fixed) << setprecision(6) << phD[i].e << " ";
      fout << setiosflags(ios::fixed) << setprecision(6) << phD[i].e - phD[0].e << " ";
      fout << phD[i].deg << " ";
      for (int j = 1; j <= phD[i].degUniq; j++)
	{
	  fout << phD[i].repst[2 * j - 2] << " ";
	  fout << phD[i].repst[2 * j - 1] << " ";
	  fout << setiosflags(ios::fixed) << setprecision(3) << phD[i].repK[2 * j - 2] << " ";
	  fout << setiosflags(ios::fixed) << setprecision(3) << phD[i].repK[2 * j - 1] << " ";
	}
      fout << endl;
    }	
  fout.close();
}
