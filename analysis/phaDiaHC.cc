#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<algorithm>
#include<sstream>
using namespace std;

#define PI 3.141592653589793238462643

string nameFileTool(string, int);
string nameFileTool(string, double);
int degFunR1(int, int, int);
int degFunRG(int, int, int);

int main()
{
  //* input parameters
  int N = 6, NDown = 3, stno = 12; 
  double v0 = 0, v1 = 1, vI0, vI1, vI0I = -8, vI0F = -3, vI1I = 1, vI1F = 1;
  double step = 0.2;
  int ratioFlag = 0; // 1 is ratio=1; 0 is other ratios
  double ratio;
  cout << "ratio is: ";
  cin >> ratio;
  cout << endl;

  int wn = 20;
  string nickName = "HC";
  double epsilon = 0.00000001;
  int sign = -1;
  //* generate basic parameters 
  int nDiv, p, q;
  for(nDiv = N; nDiv >= 1; nDiv--)
    if(N % nDiv == 0 && stno % nDiv == 0)
      break;
  p = N / nDiv;
  q = stno / nDiv;

  int tI = nDiv, tF, sI = nDiv, sF, t0, s0, tsNo;
  int pow = p * q * (N - 1);
  if (pow % 2 == 0)
    {
      t0 = nDiv; s0 = nDiv;
    }
  else 
    {
      t0 = nDiv / 2; s0 = nDiv / 2;
    }
  tsNo = nDiv / 2 + 1;

  //* Input
  string oname = "IND/", tname, name;
  oname += nameFileTool("N", N);
  oname += nameFileTool("O", stno);
  oname += nickName;
  oname += nameFileTool("R", ratio);
  tname = oname;
  tname += "e/";
  int vI0No = (vI0F - vI0I + step/10) / step + 1, vI1No = (vI1F - vI1I + step/10) / step + 1;
  double record[tsNo][tsNo][vI0No][vI1No][wn];
  int t, s;

  ifstream in;
  int i, j, tc, sc, v0c, v1c, ti;
  for (s = nDiv/2; s <= nDiv; s++)
    {
      if (ratioFlag == 0)
	ti = nDiv/2;
      else
	ti = s;
      for (t = ti; t <= nDiv; t++)
	{
	  cout << "t: " << t << ", s: " << s << endl;
	  for (vI0 = vI0I; vI0 < vI0F + step/10; vI0 += step)
	    for (vI1 = vI1I; vI1 < vI1F + step/10; vI1 += step)
	      {
		name = tname;
		name += nameFileTool("t", t);
		name += nameFileTool("s", s);
		name += "/";
		name += nameFileTool("u", N - NDown);
		name += nameFileTool("d", NDown);
		name += nameFileTool("V0_", v0);
		name += nameFileTool("V1_", v1);
		name += nameFileTool("VI0_", vI0);
		name += nameFileTool("VI1_", vI1);

		in.open(name.c_str());
		tc = t - ti;
		sc = s - nDiv/2;
		v0c = (vI0 - vI0I + step/10) / step;
		v1c = (vI1 - vI1I + step/10) / step;
		for (i = 0; i < wn; i++)
		  {
		    in >> record[tc][sc][v0c][v1c][i];
		    //cout << wn - 1 - i << ": " << record[tc][sc][v0c][v1c][wn - 1 - i] << endl;
		  }
		in.close();
	      }
	}
    }
  //* energy levels for each vI0, vI1
  //** compare and obtain low levels, record as ar[v0][v1][wn][1 + all (t, s)] and arE[v0][v1][wn]
  int degNo, ar[vI0No][vI1No][wn][1 + nDiv * nDiv];
  double arE[vI0No][vI1No][wn];
  for (vI0 = vI0I; vI0 < vI0F + step/10; vI0 += step)
    for (vI1 = vI1I; vI1 < vI1F + step/10; vI1 += step)
      {
	v0c = (vI0 - vI0I + step/10) / step;
	v1c = (vI1 - vI1I + step/10) / step;
	for (i = 0; i < wn; i++)
	  {
	    //cout << "i: " << i << endl;
	    arE[v0c][v1c][i] = 100.0; // just set a very large no.
	    ar[v0c][v1c][i][0] = 0;
	    for (s = nDiv/2; s <= nDiv; s++)
	      {
		if (ratioFlag == 0)
		  ti = nDiv/2;
		else
		  ti = s;
		for (t = ti; t <= nDiv; t++)
		  {
		    //cout << "t: " << t << ", s: " << s << endl;
		    tc = t - ti;
		    sc = s - nDiv/2;
		    for (j = 0; j < wn; j++)
		      { 
			//cout << "j = " << j << endl;
			//cout << record[tc][sc][v0c][v1c][j] << ", " << (int)(record[tc][sc][v0c][v1c][j] / epsilon) << endl;
			//cout << arE[v0c][v1c][i] << ", " << (int)(arE[v0c][v1c][i] / epsilon) << endl;
			//cout << endl;
			if (i == 0 && (long)((record[tc][sc][v0c][v1c][j] + sign*epsilon/10) / epsilon) < (long)((arE[v0c][v1c][i] + sign*epsilon/10) / epsilon)) 
			  {
			    arE[v0c][v1c][i] = record[tc][sc][v0c][v1c][j];
			    ar[v0c][v1c][i][0] = 1;
			    ar[v0c][v1c][i][1] = t;
			    ar[v0c][v1c][i][2] = s;
			    continue;
			  }
			else if ((long)((record[tc][sc][v0c][v1c][j] + sign*epsilon/10) / epsilon) < (long)((arE[v0c][v1c][i] + sign*epsilon/10) / epsilon) && (long)((record[tc][sc][v0c][v1c][j] + sign*epsilon/10) / epsilon) > (long)((arE[v0c][v1c][i - 1] + sign*epsilon/10) / epsilon))
			  {
			    arE[v0c][v1c][i] = record[tc][sc][v0c][v1c][j];
			    ar[v0c][v1c][i][0] = 1;
			    ar[v0c][v1c][i][1] = t;
			    ar[v0c][v1c][i][2] = s;
			    continue;
			  }
			else if ((long)((record[tc][sc][v0c][v1c][j] + sign*epsilon/10) / epsilon) == (long)((arE[v0c][v1c][i] + sign*epsilon/10) / epsilon))
			  {
			    ar[v0c][v1c][i][0]++;
			    degNo = ar[v0c][v1c][i][0];
			    ar[v0c][v1c][i][2 * degNo - 1] = t;
			    ar[v0c][v1c][i][2 * degNo] = s;
			    continue;
			  }
			else if ((long)((record[tc][sc][v0c][v1c][j] + sign*epsilon/10) / epsilon) > (long)((arE[v0c][v1c][i] + sign*epsilon/10) / epsilon))
			  continue;
			else
			  continue;
		      }
		  }
	      }
	    //cout << arE[v0c][v1c][i] << endl;
	  }
      }

  //* write the energy levels in a better form (transform to kx, ky representation)
  double kx, ky;
  struct eLevel
  {
    double e;
    int deg;
    int degUniq;
    int repts[20];
    double repK[20];
  };
  eLevel phD[vI0No][vI1No][wn];
  for (vI0 = vI0I; vI0 < vI0F + epsilon; vI0 += step)
    for (vI1 = vI1I; vI1 < vI1F + epsilon; vI1 += step)
      {
	v0c = (vI0 - vI0I + step/10) / step;
	v1c = (vI1 - vI1I + step/10) / step;
	for (i = 0; i < wn; i++)
	  {
	    phD[v0c][v1c][i].e = arE[v0c][v1c][i];
	    phD[v0c][v1c][i].degUniq = ar[v0c][v1c][i][0];
	    degNo = phD[v0c][v1c][i].degUniq;
	    phD[v0c][v1c][i].deg = 0;
	    for (j = 1; j <= degNo; j++)
	      {
		t = ar[v0c][v1c][i][2 * j - 1];
		s = ar[v0c][v1c][i][2 * j];
		phD[v0c][v1c][i].repts[2 * j - 2] = s;
		phD[v0c][v1c][i].repts[2 * j - 1] = t;
		kx = sqrt(2 * PI / stno / ratio) * (s - s0);
		ky = sqrt(2 * PI / stno / ratio) * ratio * (t - t0);
		phD[v0c][v1c][i].repK[2 * j - 2] = kx;
		phD[v0c][v1c][i].repK[2 * j - 1] = ky;
		if (ratioFlag == 0)
		  phD[v0c][v1c][i].deg += degFunRG(s, t, nDiv);
		else
		  phD[v0c][v1c][i].deg += degFunR1(s, t, nDiv);
	      }
	  }
      }

  //* output
  ofstream Fout;
  string onameF = "phD/", nameF;
  onameF += nameFileTool("N", N);
  onameF += nameFileTool("O", stno);
  onameF += nameFileTool("u", N - NDown);
  onameF += nameFileTool("d", NDown);
  onameF += nickName;
  onameF += nameFileTool ("R", ratio);
  onameF += "/";
  for (vI0 = vI0I; vI0 < vI0F + step/10; vI0 += step)
    for (vI1 = vI1I; vI1 < vI1F + step/10; vI1 += step)
      {
	//cout << "vI0: " << vI0 << ", vI1: " << vI1 << endl;
	v0c = (vI0 - vI0I + step/10) / step;
	v1c = (vI1 - vI1I + step/10) / step;
	nameF = onameF;
	nameF += nameFileTool("V0_", v0);
	nameF += nameFileTool("V1_", v1);
	nameF += nameFileTool("VI0_", vI0);
	nameF += nameFileTool("VI1_", vI1);
	cout << nameF << endl;
	Fout.open(nameF.c_str());
	for (i = 0; i < wn; i++)
	  {
	    Fout << setiosflags(ios::fixed) << setprecision(8) << phD[v0c][v1c][i].e << " ";
	    Fout << phD[v0c][v1c][i].deg << " ";
	    for (j = 1; j <= phD[v0c][v1c][i].degUniq; j++)
	      {
		Fout << phD[v0c][v1c][i].repts[2 * j - 2] << " ";
		Fout << phD[v0c][v1c][i].repts[2 * j - 1] << " ";
		Fout << phD[v0c][v1c][i].repK[2 * j - 2] << " ";
		Fout << phD[v0c][v1c][i].repK[2 * j - 1] << " ";
	      }
	    Fout << endl;
	  }	
	Fout.close();
      }

  //* show the phase diagram
  //*********show in the terminal****************
  for (vI0 = vI0I; vI0 < vI0F + step/10; vI0 += step)
    { 
      cout << "vI0: " << setw(4) << setiosflags(ios::fixed) << setprecision(2) << vI0 << "||";
      for (vI1 = vI1I; vI1 < vI1F + step/10; vI1 += step)
	{
	  v0c = (vI0 - vI0I + step/10) / step;
	  v1c = (vI1 - vI1I + step/10) / step;
	  // cout << "(" << vI0 << ", " << vI1 << "): ";
	  cout << setw(1) << phD[v0c][v1c][0].deg;
	  cout << ", " << setw(1) << phD[v0c][v1c][1].deg;
	  cout << ", " << setw(1) << phD[v0c][v1c][2].deg;
	  cout << ", " << setw(1) << phD[v0c][v1c][3].deg;
	  //cout << setw(1) << phD[v0c][v1c][0].deg + phD[v0c][v1c][1].deg + phD[v0c][v1c][2].deg + phD[v0c][v1c][3].deg;
	  //cout  << ", " << setw(6) << setiosflags(ios::fixed) << setprecision(3) << phD[v0c][v1c][0].e;
	  //cout  << ", " << setw(5) << setiosflags(ios::fixed) << setprecision(3) << phD[v0c][v1c][4].e - phD[v0c][v1c][3].e;
	  cout << " | ";
	}
      cout << endl;
    }

  //*********show in the file****************
  ofstream fout;
  fout.open("phD/latexOutput");
  fout << "$V_{0(inter)}\V_{1(inter)}$" << " ";
  for (vI0 = vI0I; vI0 < vI0F + epsilon; vI0 += step)
    {
      fout << " & " << "$" << vI0 << "$";
    }
  fout << "\\ \hline" << endl;
  for (vI1 = vI1F; vI1 > vI1I - epsilon; vI1 -= step)
    { 
      fout << " $" << vI1 << "$ " << " & ";
      for (vI0 = vI0I; vI0 < vI0F + epsilon; vI0 += step)
p	{
	  v0c = (vI0 - vI0I + step/10) / step;
	  v1c = (vI1 - vI1I + step/10) / step;
	  for (i = 0; i < 4; i++)
	    {
	      fout << "$" << phD[v0c][v1c][i].deg << "$";
	      if (i != 3)
		fout << ", ";
	    }
	  if ((int)(vI0 / epsilon) != (int)(vI0F / epsilon))
	    fout << " & ";
	}
      fout << "\\\hline" << endl; 
    }
  fout.close();
}

string nameFileTool(string p, int pn)
{
  string output = p;
  string temp;
  ostringstream convert;
  convert << pn;
  temp = convert.str();
  output += temp;
  convert.str("");
  return output;
}

string nameFileTool(string p, double number)
{
  string output = p;
  ostringstream strs;
  strs << number;
  string n = strs.str();
  output += n;
  return output;
}

int degFunRG(int s, int t, int nDiv)
{
  if ((t == nDiv && s == nDiv) || 
      (t == nDiv/2 && s == nDiv/2) ||
      (t == nDiv/2 && s == nDiv) ||
      (t == nDiv && s == nDiv/2))
    return 1;
  else if ((s == nDiv/2 && nDiv/2 < t && t < nDiv) ||
	   (t == nDiv/2 && nDiv/2 < s && s < nDiv) ||
	   (s == nDiv && nDiv/2 < t && t < nDiv) ||
	   (t == nDiv && nDiv/2 < s && s < nDiv))
    return 2;
  else if (nDiv/2 < s && s < nDiv && nDiv/2 < t && t < nDiv)
    return 4;
  else 
    return 1000;
}

int degFunR1(int s, int t, int nDiv)
{
  if ((t == nDiv && s == nDiv) || 
      (t == nDiv/2 && s == nDiv/2))
    return 1;
  else if (s == nDiv/2 && t == nDiv)
    return 2;
  else if ((s == nDiv/2 && nDiv/2 < t && t < nDiv) || 
	   (t == nDiv && nDiv/2 < s && s < nDiv) || 
	   (t != nDiv && t != nDiv/2 && s == t))
    return 4;

  else 
    return 8;
}
