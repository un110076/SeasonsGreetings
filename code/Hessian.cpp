#include "f2.h"

#include <iostream>
#include <chrono>

int main() {
  using namespace std;
  using namespace std::chrono;
  // increase to compare run times of various approaches
  const int N=240101;
  // code to be executed in integer arithmetic
  using T=char;
  // size of x yields squared number of Hessian entries
  T x[N];
  // vanishing inputs up to entry N-10
  for (int i=0;i<N-10;++i) x[i]=0;
  // custom input values x[N-10] ... x[N-1]
  T xv[]={72,97,112,112,121,32,50,48,50,52};
  for (int i=N-10;i<N;++i) x[i]=xv[i-(N-10)];
  // Season's Greetings ...
  cout << "AD wishes ";
  // start time measurement
  auto begin=system_clock::now();
  // compute diagonal of the Hessian in tangent ...
  ddfdxx_t1_t2_sparse<N>(x);
  // ... or adjoint mode 
  // ddfdxx_a1_t2_compressed<N>(x);
  // finish time measurement
  auto end=system_clock::now();
  // report run time 
  cout << "! (taking " 
    << duration_cast<seconds>(end-begin).count()
    << "s)" << endl;
  return 0;
}
