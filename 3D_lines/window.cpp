#include <iostream>

using namespace std;

#include <GL/freeglut.h>
#include <cassert>
#include <cmath>
#include "window.h"


#define PI  3.14159265359

int window::width = 640;
int window::height = 480;
int window::count = 0;
float window::angleCube = 0.0f; 
void window::close(){
     exit(0);
}

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
void window::display(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(0.0f, 0.0f, -2.0f);  // Move right and into the screen
   glRotatef(window::angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]
   GLfloat color = 5.0f;
   for(int i =0;i<100;i++){
      glBegin(GL_LINE_STRIP);
         GLfloat glfi = GLfloat(i);
         
         glColor3f(--color,color/2.0f,color/3.0f);
         for(int j =0; j<100;j++){
            GLfloat glfj = GLfloat(j);
            GLfloat y = GLfloat(sin(2*PI*glfj/glfi));
            glVertex3f(.1f*glfj,y,.1f*glfi);
         }
        glEnd();
        color +=  2.0f;

   }

   


glutSwapBuffers();
window::angleCube += 0.15f;


}

void window::idle(){
  glutPostRedisplay();
}

void window::reshape(int width, int height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
 
   // Set up orthographic projection view [NEW]
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      glOrtho(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0, 0.1, 100);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     glOrtho(-3.0, 3.0, -3.0 / aspect, 3.0 / aspect, 0.1, 100);
   }
}
void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(15, timer, 0); // next timer call milliseconds later
}

void window::main(){
     static int argc = 0;
     glutInit(&argc,nullptr);
     glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
     glutInitWindowSize (window::width, window::height);
     glutInitWindowPosition (300, 200);
     glutCreateWindow ("test");
     glutCloseFunc (window::close);
     //glutIdleFunc(window::idle);
     glutDisplayFunc (window::display);
     glutReshapeFunc (window::reshape);
     initGL();
     glutTimerFunc(0,timer,0);
     glutMainLoop();
}
