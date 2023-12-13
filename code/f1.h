// naumann@stce.rwth-aachen.de

#pragma once

#include <iostream>

template<int N, typename T>
void f(T x[], T &y) {
  y=0;
  for (int i=0;i<N;i+=2) {
    y+=x[i]*x[i+1];
  }
}

// tangent version of f
template<int N, typename T>
void f_t1(T x[], T x_t1[], T &y_t1) {
  y_t1=0;
  for (int i=0;i<N;i+=2) {
    // product rule
    y_t1+=x_t1[i]*x[i+1]+x[i]*x_t1[i+1];
  }
}

// adjoint version of f
template<int N, typename T>
void f_a1(T x[], T y_a1, T x_a1[]) {
  for (int i=N-2;i>=0;i-=2) {
    // adjoint product rule
    x_a1[i]=y_a1*x[i+1];
    x_a1[i+1]=y_a1*x[i];
  }
}

// gradient in tangent mode
template<int N, typename T>
void dfdx_t1(T x[]) {
  // declare tangent variables
  T x_t1[N], y_t1;
  // prepare for Cartesian basis vectors e_i
  for (int i=0;i<N;++i) x_t1[i]=0;
  for (int i=0;i<N;++i) {
    // set tangent of input equal to e_i
    x_t1[i]=1;
    // call tangent of f
    f_t1<N>(x,x_t1,y_t1);
    // print tangent of output
    std::cout << y_t1;
    // prepare for next Cartesian basis vector
    x_t1[i]=0;
  }
}

// gradient in adjoint mode
template<int N, typename T>
void dfdx_a1(T x[]) {
  // declare adjoint variables
  T x_a1[N]; T y_a1; 
  // set adjoint of output equal to one
  y_a1=1;
  // call adjoint of f
  f_a1<N>(x,y_a1,x_a1);
  // print adjoint of input
  for (int i=0;i<N;++i) std::cout << x_a1[i];
}
