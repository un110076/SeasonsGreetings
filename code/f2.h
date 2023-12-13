// naumann@stce.rwth-aachen.de

#pragma once

#include <iostream>
#include <cmath>

template<int N, typename T>
void f(T x[], T &y) {
  y=0;
  for (int i=0;i<N;++i) {
    y+=pow(x[i],3);
  }
  y/=6;
}

// first-order tangent version of f
template<int N, typename T>
void f_t1(T x[], T x_t1[], T &y_t1) {
  // initially vanshing derivative of result
  y_t1=0;
  for (int i=0;i<N;++i) {
    // tangent of cubic function; factor 3 pulled out
    y_t1+=pow(x[i],2)*x_t1[i];
  }
  // factor 3 applied
  y_t1/=2;
}

// first-order adjoint version of f
template<int N, typename T>
void f_a1(T x[], T y_a1, T x_a1[]) {
  for (int i=N-1;i>=0;--i) {
    // adjoint of cubic function; factor 1/6 pulled in
    x_a1[i]=pow(x[i],2)/2*y_a1;
  }
}

// second-order tangent version of f
template<int N, typename T>
void f_t1_t2(T x[], T x_t1[], T x_t2[], T &y_t1_t2) {
  // initially vanshing derivative of result
  y_t1_t2=0;
  for (int i=0;i<N;++i) {
    // tangent of quadratic function; factor 1/2 applied
    y_t1_t2+=x[i]*x_t1[i]*x_t2[i];
  }
}

// second-order adjoint version of f
template<int N, typename T>
void f_a1_t2(T x[], T y_a1, T x_t2[], T x_a1_t2[]) {
  for (int i=0;i<N;++i) {
    // adjoint of quadratic function; factor 1/2 applied
    x_a1_t2[i]=x[i]*y_a1*x_t2[i];
  }
}

// Diagonal Hessian in second-order tangent mode 
template<int N, typename T>
void ddfdxx_t1_t2_sparse(T x[]) {
  // declare tangent variables
  T x_t1[N], x_t2[N], y_t1_t2;
  // prepare for Cartesian basis vectors e_i
  for (int i=0;i<N;++i) x_t1[i]=x_t2[i]=0;
  // loop over diagonal entries
  for (int i=0;i<N;++i) {
    // set both tangents of inputs equal to e_i
    x_t1[i]=x_t2[i]=1;
    // call second-order tangent f
    f_t1_t2<N>(x,x_t1,x_t2,y_t1_t2);
    // print i-th diagonal entry of Hessian
    std::cout << y_t1_t2; 
    // prepare for next Cartesian basis vector
    x_t1[i]=x_t2[i]=0;
  }
}

// Column-compressed Hessian in second-order adjoint mode 
template<int N, typename T>
void ddfdxx_a1_t2_compressed(T x[]) {
  // declare tangent and adjoint variables
  T x_t2[N], x_a1_t2[N], y_a1;
  // set all entries of tangent of input equal to one
  for (int i=0;i<N;++i) x_t2[i]=1;
  // set adjoint of output equal to one
  y_a1=1;
  // call second-order adjoint f
  f_a1_t2<N>(x,y_a1,x_t2,x_a1_t2);
  // print sum of all columns of Hessian
  for (int j=0;j<N;++j) std::cout << x_a1_t2[j]; 
}
