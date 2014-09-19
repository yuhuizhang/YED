#include "analysis.h"

void analysis::parametersGen()
{
  int n = n1 + n2;
  for(N = n; N >= 1; N--)
    if(n % N == 0 && nOrb % N == 0)
      break;
  p = n / N;
  q = nOrb / N;

  int pow = p * q * (n - 1);
  if (pow % 2 == 0)
    {
      t0 = N; s0 = N;
    }
  else 
    {
      t0 = N / 2; s0 = N / 2;
    }
  stNo = N / 2 + 1;
}
