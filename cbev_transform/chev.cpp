#include <cassert>
#include <cmath>
#include <unistd.h>
#include <algorithm>

#include <fstream>
#include <iostream>
#include "chev.h"

using namespace std;
using fn_db = std::function<double(const double)>;


#define PI  3.14159265359

void chev::initialize(fn_db fn ,int N){
      
      
      //differentiation matrix
      D = (double**) malloc(N*sizeof(double*));
   
      for(int i=0;i<N;++i)
          D[i] = (double*)calloc(N,sizeof(double));
     
      double c = 1; 
      for(int i=0;i<N;++i){
           for(int j=i+1;j<N;j+=2){
              D[i][j] = c*j;
            }
            c = 2;
      }

      phys_space = (double*) fftw_malloc(N*sizeof(double));
      spectral_space  = (double*) fftw_malloc(N*sizeof(double));
      forw = fftw_plan_r2r_1d(N,phys_space,spectral_space,FFTW_REDFT10,FFTW_ESTIMATE);
      inv = fftw_plan_r2r_1d(N,spectral_space,phys_space,FFTW_REDFT01,FFTW_ESTIMATE);
      size = N;
      
      //sorted gl_lobatto points
      sort_cosine();     
      
      
      for(int i = 0; i< N ; ++i){
         double chev_extr = cos(PI*(i + 0.5)/N); 
         phys_space[i] = fn(chev_extr);
         spectral_space[i] = 0.0;
         spectral_space[i] = 0.0;
       }

}


void chev::deriv(){
     double sum = 0.0;
      for(int i = 0; i< size ; ++i){
          for(int j = 0; j< size ; ++j){
            sum +=  spectral_space[j]* D[i][j];
          }
          spectral_space[i] =sum;
          sum = 0;
      }
}


void chev::transform(){
     fftw_execute(forw);
      for(int i = 0; i< size ; ++i){
         spectral_space[i]/=double(size);
      }
}


void chev::inverse_transform(){
     fftw_execute(inv);

}

void chev::print_phys(){
     for(int i = 0; i< size ; ++i){
        cout << phys_space[gl_order[i].second]<< " , \n";
     }
     cout << endl;
}
bool compare( const pair<float,int>& i , 
                    const pair<float,int>& j){
         return i.first < j.first;
}

void chev::sort_cosine(){
     
     gl_order =
     (pair<float,int>*)malloc(size*sizeof(pair<float,int>));
     
     for(int i = 0; i< size ; ++i){
         gl_order[i].first = cos(PI*(i + 0.5)/double(size));
         gl_order[i].second = i;
     }
     sort(gl_order,gl_order + size ,compare);
}


void chev::print_spec(){
     for(int i = 0; i< size ; ++i){
        cout << spectral_space[i]<< " , \n";
     }
     cout << endl;
}
