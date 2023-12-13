#include "f1.h"

#include <iostream>
#include <chrono>

int main() {
  using namespace std;
  using namespace std::chrono;
  // increase to experience superior run time of adjoint
  const int N=231224; // required to be even
  // code to be executed in integer arithmetic
  using T=char;
  // size of x equal to size of gradient
  T x[N];
  // vanishing inputs up to entry N-10
  for (int i=0;i<N-10;++i) x[i]=0;
  // custom input values x[N-10] ... x[N-1]
  T xv[]={101,77,114,114,32,121,109,88,115,97};
  for (int i=N-10;i<N;++i) x[i]=xv[i-(N-10)];
  // Season's Greetings ...
  cout << "AD wishes ";
  // start time measurement
  auto begin=system_clock::now();
  // compute gradient in tangent ...
  dfdx_t1<N>(x);
  // ... or adjoint mode
  // dfdx_a1<N>(x);
  // finish time measurement
  auto end=system_clock::now();
  // report run time
  cout << "! (taking "
    << duration_cast<seconds>(end-begin).count()
    << "s)" << endl;
  return 0;
}
