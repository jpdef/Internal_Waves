// $Id: main.cpp,v 1.13 2014-05-08 18:32:56-07 - - $

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cmath>
using namespace std;

#include "strat_wv.h"
#include "window.h"


void mesh::init_mesh(double interval, int _N){
	h = interval; N = _N;
	v_field = (point**)calloc(N,sizeof(point *));
  v_field_prev = (point**)calloc(N,sizeof(point *));
	for(int i = 0; i < N; ++i){
		v_field[i] = (point*)calloc(N,sizeof(point));
    v_field_prev[i] = (point*)calloc(N,sizeof(point));
	}

}

void mesh::set_mesh(double k, double omega, double t, fn_db m){
    for(int i =0; i < N ; ++i){
      for(int j = 0; j<N; ++j){
      v_field[i][j].x_pos = i*h;
      v_field[i][j].z_pos = j*h;
      v_field[i][j].u = 0.0;
      v_field[i][j].w = 0.0;
      v_field[i][j].k = k;
      v_field[i][j].omega = omega;
      v_field[i][j].t = t;
      v_field[i][j].m = m;
    }
  }
}


mesh::mesh(){
	v_field = nullptr;
	v_field_prev=nullptr;
  h = 0;
	N =0;  
}

mesh::~mesh(){
  for(int i = 0; i< N;++i){
      delete[] v_field[i];
  }
  delete[] v_field;
}

//Updating functions described as a ++ operator
mesh& mesh::operator++(){
  for(int i =0; i < N ; ++i){
    for(int j = 0; j<N; ++j){
      ++v_field[i][j];
    }
  }
  return *this;
      
}

point& point::operator++(){
     double m_value = m(z_pos);
     //double m_sq = ((pow(k,2))*(pow(N(z_pos),2)-pow(omega,2)))
     //               /pow(omega,2);
     double m_int = integrator();
     u = -(m_value/k) * sin(k*x_pos + m_int - omega*(t)*.01);
     w = (1.0/m_value)*cos(k*x_pos + m_int - omega*(t++)*.01);
     return *this;
}


const  point& mesh::get_point(int i,int j){
      return v_field[i][j];
}


double point::integrator(){
  double n = 50.0;
  double T_N = 0.0; //end return value
  double T_N_odd = 0.0;
  double T_N_even = 0.0;
  double h = (z_pos)/n;
  for(double i =1.0; i<n;i=i+2){//gurantees n function evaluations
    T_N_odd = T_N_odd + m(i*h);
    //printf("f(%f) = %f\n",a+i*h,m(a+i*h)); //debug print statement
  }
  for(double i =2.0; i<n;i=i+2){//gurantees n function evaluations
    T_N_even = T_N_even + m(i*h);
    //printf("f(%f) = %f\n",a+i*h,m(a+i*h)); //debug print statement
  }

  T_N = (h/3.0)*(4.0*T_N_odd + 2.0*T_N_even + m(0.0) + m(z_pos));
  return T_N;
}