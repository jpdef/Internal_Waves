#include <iostream>

using namespace std;

#include <GL/freeglut.h>
#include <cassert>
#include <cmath>
#include "window.h"
#include "strat_wv.h"

int window::width = 640;
int window::height = 480;
mesh window::g_mesh ;
int window::count = 0;
void window::close(){
     exit(0);
}


void window::display(){
   cout << ++count <<"th interation "<< endl;
   double scale_length = g_mesh.scale();
   double scaling_x = window::height/scale_length;
   double scaling_z = window::width/scale_length;
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0f,0.0f,0.0f);
   glLineWidth(4.0f);
   for(int i = 0; i< g_mesh.size(); ++i){
    for(int j=0; j<g_mesh.size(); ++j){
      glBegin (GL_LINES);
       GLfloat x = scaling_x*g_mesh.get_point(i,j).x_pos;
       GLfloat z = scaling_x*g_mesh.get_point(i,j).z_pos;
       glVertex2f(x,z);
       double theta = atan(g_mesh.get_point(i,j).w/g_mesh.get_point(i,j).u);
       glVertex2f(GLfloat(x+10*cos(theta)*scale_length), GLfloat(z+10*sin(theta)*scale_length)) ;
      glEnd();
      if(i == 8 && j == 8)
      cout << i << "," << j <<
      " = " << "{"<< x<< " , "<< z << "} " <<
        "{" << x + cos(theta) <<" , " <<z + sin(theta)<< "}"<< 
      endl;

    }
   }
   glEnd();
   glutSwapBuffers();
}

void window::idle(){
  cout << "updated" << endl;
  ++g_mesh;
  glutPostRedisplay();
}

void window::reshape (int width, int height) {
     window::width = width;
     window::height = height;
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D (0, window::width, 0, window::height);
     glMatrixMode (GL_MODELVIEW);
     glViewport (0, 0, window::width, window::height);
     glClearColor (0.25, 0.25, 0.25, 1.0);
     glutPostRedisplay();
}


void window::main(){
     static int argc = 0;
     glutInit(&argc,nullptr);
     glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
     glutInitWindowSize (window::width, window::height);
     glutInitWindowPosition (128, 128);
     glutCreateWindow ("test");
     glutCloseFunc (window::close);
     glutIdleFunc(window::idle);
     glutDisplayFunc (window::display);
     glutReshapeFunc (window::reshape);
     glutMainLoop();
}
