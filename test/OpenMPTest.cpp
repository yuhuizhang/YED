#include <iostream>
using namespace std;
 
#include <omp.h>
 
int main(int argc, char *argv[])
{
  int th_id, nthreads;
#pragma omp parallel private(th_id) shared(nthreads)
  {
    th_id = omp_get_thread_num();
#pragma omp critical
    {
      cout << "Hello World from thread " << th_id << '\n';
    }
#pragma omp barrier
 
#pragma omp master
    {
      nthreads = omp_get_num_threads();
      cout << "There are " << nthreads << " threads" << '\n';
    }
  }

  int s = 0;
#pragma omp parallel for private(th_id)
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < i * 100000; j++)
	continue;
      s += i;
      th_id = omp_get_thread_num();
      cout << "i = " << i << ", s = " << s <<endl;
      cout << "H " << th_id << '\n';
    }

  return 0;
}
