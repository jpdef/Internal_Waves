#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <memory>
#include <vector>

using namespace std;


class window{
   private:
      static int width;
      static int height;
      static int count;
      static float angleCube;
   private:
      static void close();
      static void display();
      static void idle();
      static void reshape(int width, int height);
   public:
      static void main();

};


#endif
