#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <memory>
#include <vector>

using namespace std;

#include "strat_wv.h"

class window{
   private:
      static int width;
      static int height;
      static int count;
      static mesh g_mesh;
   private:
      static void close();
      static void display();
      static  void idle();
      static void reshape(int height, int width);
   public:
      static void main();
      static void init_mesh( double h, int N){
          window::g_mesh.init_mesh(h,N);
     }
     static void set_mesh( double k, double omega, double t, fn_db m){
          window::g_mesh.set_mesh(k,omega,t,m);
     }

};


#endif
