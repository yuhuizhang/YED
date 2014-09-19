#include "analysis.h"
#include <fstream>

void analysis::input()
{
  using namespace std;
  std::ifstream fin;
  int si = N / 2, ti;
  for (int s = si; s <= N; s++)
    {
      if (ratioFlag == 1)
	ti = s;
      else if (ratioFlag == 0)
	ti = N / 2;
      for (int t = ti; t <= N; t++)
	{
	  std::string name = inputName1;
	  name += nameFileTool("s", s);
	  name += nameFileTool("t", t);
	  name += "/";
	  name += inputName2;
	  fin.open(name.c_str());
	  int sc = s - si;
	  int tc = t - ti;
	  for (int i = 0; i < wn; i++)
	    fin >> record[sc][tc][i];
	  fin.close();
	}
    }
}
