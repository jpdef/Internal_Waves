#ifndef __CHEV_H__
#define __CHEV_H__

#include <memory>
#include <vector>
#include <fftw3.h>

using namespace std;
using fn_db = std::function<double(const double)>;

class chev{
  private:
      int size;
      double* phys_space;
      double* spectral_space;
      fftw_plan forw;
      fftw_plan inv;
      double** D;
      pair<float,int>* gl_order;
   public:
     void initialize(fn_db fn , int N);
     void deriv(); 
     void inverse_transform(); 
     void transform(); 
     void print_phys(); 
     void print_spec(); 
     void sort_cosine();
      
};


#endif
