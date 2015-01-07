
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <fftw3.h>


#include "chev.h"
#define PI  3.14159265359

using namespace std;
using fn_db = std::function<double(const double)>;

double N = 100;
double delta_x = .1;

double fn(double x){
    return pow(x,3);
}

double deriv(double x){
    return 3*x;
}

int main(){

chev ct;
ct.initialize(fn ,N);

//transform
    ct.transform();

//transform derivative
//   ct.print_spec();
   ct.deriv();
//   ct.print_spec();
//inverse transform
   ct.inverse_transform();

//compare
ct.print_phys();         
    return 0;
}

