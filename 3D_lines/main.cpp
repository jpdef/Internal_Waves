// $Id: main.cpp,v 1.13 2014-05-08 18:32:56-07 - - $

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cmath>
using namespace std;
#define PI  3.14159265359

#include "window.h"

double sine(double x){
	return sin(2.0*PI*x);
}

int main(){
    window::main();
    
    return 0;
}

