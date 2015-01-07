// $Id: main.cpp,v 1.13 2014-05-08 18:32:56-07 - - $

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cmath>
using namespace std;
#define PI  3.14159265359

#include "strat_wv.h"
#include "window.h"

double bouyancy_freq(double z){
	return 5.9*z;
}

int main(){
    /*with graphics*/
    window::init_mesh(.1,10);
    cout << "init_mesh worked" << endl;
    window::set_mesh((2*PI)/3.0,(2*PI)*.1,0.0,bouyancy_freq);
    cout << "set_mesh worked" << endl;
    window::main();
    
    return 0;
}

