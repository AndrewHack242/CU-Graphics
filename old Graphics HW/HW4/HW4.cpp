/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 */

#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <iostream>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265
#endif

//borrowed from ex8
#define Cos(x) (cos((x)*3.1415927 / 180))
#define Sin(x) (sin((x)*3.1415927 / 180))

static GLint win = 0;
static GLdouble asp;

/*
 *  Function to print any errors encountered
 *  BORROWED FROM ex5.c, modified slightly for c++
 */
void ErrCheck(std::string where)
{
   int err = glGetError();
   if (err)
   {
      fprintf(stderr, "ERROR: %s", gluErrorString(err));
   }
}

/* Borrowed from the gears example program*/
#define LEN 8192 //  Maximum amount of text
void Print(const char *format, ...)
{
   char buf[LEN];  // Text storage
   char *ch = buf; // Text pointer
   //  Create text to be display
   va_list args;
   va_start(args, format);
   vsnprintf(buf, LEN, format, args);
   va_end(args);
   //  Display text string
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

//return by reference - normalizes a vector (mostly needed for movement)
void normalize(GLdouble &lax, GLdouble &lay, GLdouble &laz)
{
   GLdouble sum = pow(lax, 2) + pow(lay, 2) + pow(laz, 2);
   sum = sqrt(sum);

   lax /= sum;
   lay /= sum;
   laz /= sum;
}

//function to return by reference the cross product of two vectors
void cross(GLdouble a1, GLdouble a2, GLdouble a3, GLdouble b1, GLdouble b2, GLdouble b3, GLdouble &r1, GLdouble &r2, GLdouble &r3)
{
   r1 = (a2 * b3) - (a3 * b2);
   r2 = (a3 * b1) - (a1 * b3);
   r3 = (a1 * b2) - (a2 * b1);
}

//like vertex, but for elevated 2d planes
//inspired by Vertex in ex8, but entirely written by me
static void circleVertex(GLdouble ang, GLdouble height)
{
   glVertex3d(Cos(ang), height, Sin(ang));
}

class Companion
{
private:
   GLdouble size;             //size of the cube
   GLdouble x, y, z;          //translation coordinates for cube center
   GLdouble rotx, roty, rotz; //rotation of cube

public:
   Companion() //default constructor
   {
   }

   Companion(GLdouble tx, GLdouble ty, GLdouble tz, GLdouble s, GLdouble rx, GLdouble ry, GLdouble rz)
   {
      x = tx;
      y = ty;
      z = tz;
      size = s;
      rotx = rx;
      roty = ry;
      rotz = rz;
   }

   //borrowed from ex8 with slight edits
   void cube()
   {

      //  Cube
      glBegin(GL_QUADS);
      //  Front
      glVertex3f(-1, -1, 1);
      glVertex3f(+1, -1, 1);
      glVertex3f(+1, +1, 1);
      glVertex3f(-1, +1, 1);
      //  Back
      glVertex3f(+1, -1, -1);
      glVertex3f(-1, -1, -1);
      glVertex3f(-1, +1, -1);
      glVertex3f(+1, +1, -1);
      //  Right
      glVertex3f(+1, -1, +1);
      glVertex3f(+1, -1, -1);
      glVertex3f(+1, +1, -1);
      glVertex3f(+1, +1, +1);
      //  Left
      glVertex3f(-1, -1, -1);
      glVertex3f(-1, -1, +1);
      glVertex3f(-1, +1, +1);
      glVertex3f(-1, +1, -1);
      //  Top
      glVertex3f(-1, +1, +1);
      glVertex3f(+1, +1, +1);
      glVertex3f(+1, +1, -1);
      glVertex3f(-1, +1, -1);
      //  Bottom
      glVertex3f(-1, -1, -1);
      glVertex3f(+1, -1, -1);
      glVertex3f(+1, -1, +1);
      glVertex3f(-1, -1, +1);
      //  End
      glEnd();
   }

   void sidePanel()
   {
      glColor3f(0.2, 0.2, 0.9);
      glBegin(GL_QUADS);
      //corner
      glVertex3f(+0.2, +1.06, +1.01);
      glVertex3f(-0.2, +1.06, +1.01);
      glVertex3f(-0.2, +1.01, +1.06);
      glVertex3f(+0.2, +1.01, +1.06);
      //side 1
      glVertex3f(-0.2, +1.06, +1.01);
      glVertex3f(+0.2, +1.06, +1.01);
      glVertex3f(+0.2, +1.06, +0.85);
      glVertex3f(-0.2, +1.06, +0.85);

      glVertex3f(-0.2, +1.06, +1.01);
      glVertex3f(-0.2, +1, +1.01);
      glVertex3f(-0.2, +1, +0.85);
      glVertex3f(-0.2, +1.06, +0.85);

      glVertex3f(+0.2, +1.06, +1.01);
      glVertex3f(+0.2, +1.06, +0.85);
      glVertex3f(+0.2, +1, +0.85);
      glVertex3f(+0.2, +1, +1.01);

      glVertex3f(+0.2, +1.06, +0.85);
      glVertex3f(-0.2, +1.06, +0.85);
      glVertex3f(-0.2, +1, +0.85);
      glVertex3f(+0.2, +1, +0.85);
      //side 2
      glVertex3f(-0.2, +1.01, +1.06);
      glVertex3f(+0.2, +1.01, +1.06);
      glVertex3f(+0.2, +0.85, +1.06);
      glVertex3f(-0.2, +0.85, +1.06);

      glVertex3f(-0.2, +1.01, +1.06);
      glVertex3f(-0.2, +1.01, +1);
      glVertex3f(-0.2, +0.85, +1);
      glVertex3f(-0.2, +0.85, +1.06);

      glVertex3f(+0.2, +1.01, +1.06);
      glVertex3f(+0.2, +0.85, +1.06);
      glVertex3f(+0.2, +0.85, +1);
      glVertex3f(+0.2, +1.01, +1);

      glVertex3f(+0.2, +0.85, +1.06);
      glVertex3f(-0.2, +0.85, +1.06);
      glVertex3f(-0.2, +0.85, +1);
      glVertex3f(+0.2, +0.85, +1);

      glEnd();

      //seal the corner with triangles
      glBegin(GL_TRIANGLES);
      glVertex3f(+0.2, +1.06, +1.01);
      glVertex3f(+0.2, +1.01, +1.06);
      glVertex3f(+0.2, +1.01, +1.01);

      glVertex3f(-0.2, +1.06, +1.01);
      glVertex3f(-0.2, +1.01, +1.01);
      glVertex3f(-0.2, +1.01, +1.06);

      glEnd();
   }

   void cornerPanel()
   {
      glColor3f(0.2, 0.2, 0.9);
      glBegin(GL_TRIANGLES);
      //corner
      glVertex3f(+1.06, +1.01, +1.01);
      glVertex3f(+1.01, +1.06, +1.01);
      glVertex3f(+1.01, +1.01, +1.06);

      glEnd();

      glBegin(GL_QUADS);
      //strips
      glVertex3f(+1.01, +1.06, +1.01);
      glVertex3f(+1.01, +1.01, +1.06);
      glVertex3f(+0.3, +1.01, +1.06);
      glVertex3f(+0.3, +1.06, +1.01);

      glVertex3f(+1.06, +1.01, +1.01);
      glVertex3f(+1.01, +1.01, +1.06);
      glVertex3f(+1.01, +0.3, +1.06);
      glVertex3f(+1.06, +0.3, +1.01);

      glVertex3f(+1.01, +1.06, +1.01);
      glVertex3f(+1.06, +1.01, +1.01);
      glVertex3f(+1.06, +1.01, +0.3);
      glVertex3f(+1.01, +1.06, +0.3);
      glEnd();

      glColor3f(0.1882, 0.7176, 0);

      glBegin(GL_TRIANGLES);
      //corner plates
      glVertex3f(+0.3, +1.01, +1.06);
      glVertex3f(+1.01, +0.3, +1.06);
      glVertex3f(+1.01, +1.01, +1.06);

      glVertex3f(+1.06, +0.3, +1.01);
      glVertex3f(+1.06, +1.01, +0.3);
      glVertex3f(+1.06, +1.01, +1.01);

      glVertex3f(+0.3, +1.06, +1.01);
      glVertex3f(+1.01, +1.06, +0.3);
      glVertex3f(+1.01, +1.06, +1.01);
      //strip end-caps

      glColor3f(0.2, 0.2, 0.9);
      glVertex3f(+0.3, +1.01, +1.06);
      glVertex3f(+0.3, +1.06, +1.01);
      glVertex3f(+0.3, +1.00, +1.00);

      glVertex3f(+1.01, +0.3, +1.06);
      glVertex3f(+1.06, +0.3, +1.01);
      glVertex3f(+1.00, +0.3, +1.00);

      glVertex3f(+1.06, +1.01, +0.3);
      glVertex3f(+1.01, +1.06, +0.3);
      glVertex3f(+1.00, +1.00, +0.3);

      glEnd();

      glBegin(GL_QUADS);
      //inner cover pieces
      glVertex3f(+0.3, +1.01, +1.06);
      glVertex3f(+1.01, +0.3, +1.06);
      glVertex3f(+1.01, +0.3, +1.00);
      glVertex3f(+0.3, +1.01, +1.00);

      glVertex3f(+1.06, +0.3, +1.01);
      glVertex3f(+1.06, +1.01, +0.3);
      glVertex3f(+1.00, +1.01, +0.3);
      glVertex3f(+1.00, +0.3, +1.01);

      glVertex3f(+0.3, +1.06, +1.01);
      glVertex3f(+1.01, +1.06, +0.3);
      glVertex3f(+1.01, +1.00, +0.3);
      glVertex3f(+0.3, +1.00, +1.01);

      glEnd();
   }

   //draws a cylinder with a given radius and height at the specified resolution
   void cylinder(GLint angleChange, GLdouble radius, GLdouble height)
   {
      glPushMatrix();
      glScaled(radius, height, radius);

      glBegin(GL_TRIANGLE_FAN);

      glVertex3f(0, 1, 0); //set center point for top circle

      for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
      {
         circleVertex(ang, 1);
         circleVertex(ang + angleChange, 1);
      }
      glEnd();

      glBegin(GL_TRIANGLE_FAN);

      glVertex3f(0, -1, 0); //set center point for top circle

      for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
      {
         circleVertex(ang, -1);
         circleVertex(ang + angleChange, -1);
      }
      glEnd();

      //connect top circle to bottom circle
      glBegin(GL_QUADS);
      for (int ang = 0; ang <= 360; ang += angleChange)
      {
         circleVertex(ang, 1);
         circleVertex(ang + angleChange, 1);
         circleVertex(ang + angleChange, -1);
         circleVertex(ang, -1);
      }
      glEnd();

      glPopMatrix();
   }

   void display()
   {

      //  Save transformation
      glPushMatrix();
      //  Offset
      glTranslated(x, y, z);
      glRotated(rotx, 1, 0, 0);
      glRotated(roty, 0, 1, 0);
      glRotated(rotz, 0, 0, 1);
      glScaled(size, size, size);

      glColor3f(0.427, 0.522, 0.569);

      cube();

      //side panels (need 12)

      //top
      glPushMatrix();
      sidePanel();
      glRotated(90, 0, 1, 0);
      sidePanel();
      glRotated(90, 0, 1, 0);
      sidePanel();
      glRotated(90, 0, 1, 0);
      sidePanel();
      glPopMatrix();

      //bottom
      glPushMatrix();
      glRotated(90, 1, 0, 0);
      sidePanel();
      glRotated(90, 0, 0, 1);
      sidePanel();
      glRotated(90, 0, 0, 1);
      sidePanel();
      glRotated(90, 0, 0, 1);
      sidePanel();
      glPopMatrix();

      //middle
      glPushMatrix();
      glRotated(90, 0, 0, 1);
      sidePanel();
      glRotated(90, 1, 0, 0);
      sidePanel();
      glRotated(90, 1, 0, 0);
      sidePanel();
      glRotated(90, 1, 0, 0);
      sidePanel();
      glPopMatrix();

      //corners (8)

      //top
      glPushMatrix();
      cornerPanel();
      glRotated(90, 0, 1, 0);
      cornerPanel();
      glRotated(90, 0, 1, 0);
      cornerPanel();
      glRotated(90, 0, 1, 0);
      cornerPanel();
      glPopMatrix();

      //bottom
      glPushMatrix();
      glRotated(180, 1, 0, 0);
      cornerPanel();
      glRotated(90, 0, 1, 0);
      cornerPanel();
      glRotated(90, 0, 1, 0);
      cornerPanel();
      glRotated(90, 0, 1, 0);
      cornerPanel();
      glPopMatrix();

      //fun with cylinders (the ones in the center of each side)
      glColor3f(1, 1, 1);

      glPushMatrix();

      glTranslated(0, 1.025, 0);
      glColor3f(1, 1, 1);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(90, 1, 0, 0);
      glTranslated(0, 1.025, 0);
      glColor3f(0.72549, 0, 0);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(180, 1, 0, 0);
      glTranslated(0, 1.025, 0);
      glColor3f(1, 0.83529, 0);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(270, 1, 0, 0);
      glTranslated(0, 1.025, 0);
      glColor3f(1, 0.349, 0);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(90, 0, 0, 1);
      glTranslated(0, 1.025, 0);
      glColor3f(0, 0.2705, 0.6784);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(270, 0, 0, 1);
      glTranslated(0, 1.025, 0);
      glColor3f(0, 0.6078, 0.2823);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();

      //  Undo transformations
      glPopMatrix();
   }
};

//camera class to handle all perspective things
class Camera
{
private:
   GLfloat x = 0, y = 0, z = 0;
   GLfloat view_rotx = 0, view_roty = 0, view_rotz = 0;
   bool ortho = false, fp = false;
   GLdouble fov = 55, dim = 20;

public:
   Camera()
   {
   }

   Camera(GLdouble xt, GLdouble yt, GLdouble zt, GLdouble rotx, GLdouble roty, GLdouble rotz)
   {
      x = xt;
      y = yt;
      z = zt;
      view_rotx = rotx;
      view_roty = roty;
      view_rotz = rotz;
   }

   //implements the camera positioning to the scene
   void display()
   {
      //  Tell OpenGL we want to manipulate the projection matrix
      glMatrixMode(GL_PROJECTION);
      //  Undo previous transformations
      glLoadIdentity();

      //  Perspective transformation
      if (!ortho || fp)
         gluPerspective(fov, asp, dim / 4, 4 * dim);
      //  Orthogonal projection
      else
         glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);
      //  Switch to manipulating the model matrix
      glMatrixMode(GL_MODELVIEW);
      //  Undo previous transformations
      //glLoadIdentity();

      //assistance from learnopengl.com/Getting-started/Camera
      if (fp)
      {
         GLdouble lax = Sin(view_roty) * Cos(view_rotx);//calculate where to look at
         GLdouble lay = Sin(view_rotx);
         GLdouble laz = Cos(view_roty) * Cos(view_rotx);

         normalize(lax, lay, laz);

         GLdouble rx = 0; //calculate the right vector
         GLdouble ry = 0;
         GLdouble rz = 0;
         cross(lax, lay, laz, 0, 1, 0, rx, ry, rz);
         normalize(rx, ry, rz);

         if (!(abs(view_rotx) >= 90 && abs(view_rotx) < 270)) //fixing random flip, don't really understand why it happens
      {
         rx *= -1;
         ry *= -1;
         rz *= -1;
      }

         GLdouble ux = 0;//use right and front vector to find top vector
         GLdouble uy = 0;
         GLdouble uz = 0;
         cross(lax, lay, laz, rx, ry, rz, ux, uy, uz);
         normalize(ux, uy, uz);

         //lookat camera pos,camera front + camerapos, camera up
         gluLookAt(x, y, z, lax + x, lay + y, laz + z, ux, uy, uz);
      }
      //borrowed from ex9
      //perspective - set eye position
      else if (!ortho)
      {
         x = -2 * dim * Sin(view_roty) * Cos(view_rotx);
         y = +2 * dim * Sin(view_rotx);
         z = +2 * dim * Cos(view_roty) * Cos(view_rotx);
         gluLookAt(x, y, z, 0, 0, 0, 0, Cos(view_rotx), 0);
      }

      //  Orthogonal - set world orientation
      else
      {
         glRotatef(view_rotx, 1, 0, 0);
         glRotatef(view_roty, 0, 1, 0);
      }
      //  borrowed from ex9
      //  Display parameters
      glWindowPos2i(5, 5);
      Print("Angle: %d,%d  Dim: %.1f FOV: %.0f Projection: %s FP: %s", abs((int)view_roty % 360), (int)view_rotx % 360, dim, fov, (fp || !ortho) ? "Perpective" : "Orthogonal", fp ? "True" : "False");
   }

   //take rotate arguments from key presses
   void rotate(GLdouble xrot, GLdouble yrot, GLdouble zrot)
   {
      view_rotx += xrot;
      view_roty += yrot;
      view_rotz += zrot;
   }

   //move the cam
   void move(GLdouble xm, GLdouble ym, GLdouble zm)
   {
      GLdouble lax = Sin(view_roty) * Cos(view_rotx); //looking vector
      GLdouble lay = Sin(view_rotx);
      GLdouble laz = Cos(view_roty) * Cos(view_rotx);

      normalize(lax, lay, laz);

      x += xm * lax;
      y += xm * lay;
      z += xm * laz;//forward motion

      GLdouble rx = 0; //right vector
      GLdouble ry = 0;
      GLdouble rz = 0;
      cross(lax, lay, laz, 0, 1, 0, rx, ry, rz);
      normalize(rx, ry, rz);
      if (!(abs(view_rotx) >= 90 && abs(view_rotx) < 270))
      {
         rx *= -1;
         ry *= -1;
         rz *= -1;
      }

      x += zm * rx;
      y += zm * ry;
      z += zm * rz;//side motion

      GLdouble ux = 0;//up vector
      GLdouble uy = 0;
      GLdouble uz = 0;
      cross(lax, lay, laz, rx, ry, rz, ux, uy, uz);
      normalize(ux, uy, uz);

      x += ym * ux;// up and down motion (uses up from camera perspective)
      y += ym * uy;
      z += ym * uz;
   }

   //change dimensions of space
   void changeDim(GLdouble d)
   {
      dim += d;
      if(dim <5)
         dim = 5;
   }

   //swap between perspective and orthogonal
   void swapPerspective()
   {
      ortho = !ortho;
   }

   //swap between first person and not
   void swapFP()
   {
      rotate(2 * -view_rotx, ((view_roty - 90) * -1) + 90 - view_roty, 0); //fix the perspective to try to line up the two modes as closely as possible
      fp = !fp;
   }
};

class Window
{
private:
   Companion testcube, cube1, cube2, cube3;
   Camera cam;

public:
   //make the lorenz and do the initial generation
   Window()
   {
      testcube = Companion(0, 0, 0, 3, 0, 0, 0);
      cube1 = Companion(0, 5.3, 0, 2, 0, 0, 180);
      cube2 = Companion(0, -0.5, 6.05, 2, -60, 0, 0);
      cube3 = Companion(-6, -1, -6, 2, 0, 57, 0);
      cam = Camera(0, 0, 0, 60, 60, 0);
   }

   
   //functions to pass commands to the camera
   void rotate(GLdouble xrot, GLdouble yrot, GLdouble zrot)
   {
      cam.rotate(xrot, yrot, zrot);
   }

   
   void move(GLdouble xm, GLdouble ym, GLdouble zm)
   {
      cam.move(xm, ym, zm); 
   }

   void changeDim(GLdouble d)
   {
      cam.changeDim(d);
   }

   void swapPerspective()
   {
      cam.swapPerspective();
   }

   void swapFP()
   {
      cam.swapFP();
   }

   //deals with rotation, displays axes, and calls the attractor display,
   //as well as shows the attractor variables
   void display()
   {
      glPushMatrix();
      cam.display(); //do the camera stuffs

      glColor3d(1.0, 1.0, 1.0);

      testcube.display();
      cube1.display();
      cube2.display();
      cube3.display();

      glPopMatrix();
   }
};

static Window window;

/*
 *  GLUT calls this routine when the window is resized
 *  borrowed from ex9
 */
void reshape(int width, int height)
{
   //  Ratio of the width to the height of the window
   asp = (height > 0) ? (double)width / height : 1;
   //  Set the viewport to the entire window
   glViewport(0, 0, width, height);
   //  Set projection
   //Project();
}

/* change view angle, exit upon ESC */
/* ARGSUSED1 */
/*funciton borrrowed from gears example, but heavily modified*/
static void
key(unsigned char k, int x, int y)
{
   switch (k) //move the camera, as well as end the program
   {
   case 'w':
      window.move(1, 0, 0);
      break;
   case 'a':
      window.move(0, 0, 1);
      break;
   case 's':
      window.move(-1, 0, 0);
      break;
   case 'd':
      window.move(0, 0, -1);
      break;
   case ' ':
      window.move(0, 1, 0);
      break;
   case 'c':
      window.move(0, -1, 0);
      break;
   case 'q':
      window.swapPerspective();
      break;
   case 'f':
      window.swapFP();
      break;
   case 27: /* Escape */
      exit(0);
      break;
   default:
      return;
   }
   glutPostRedisplay();
}

/* change view angle */
/* ARGSUSED1 */
/*function borrowed from gears example*/
static void
special(int k, int x, int y)
{
   switch (k) //all of the navigation keys
   {
   case GLUT_KEY_UP:
      window.rotate(5.0, 0, 0);
      break;
   case GLUT_KEY_DOWN:
      window.rotate(-5.0, 0, 0);
      break;
   case GLUT_KEY_LEFT:
      window.rotate(0, 5.0, 0);
      break;
   case GLUT_KEY_RIGHT:
      window.rotate(0, -5.0, 0);
      break;
   case GLUT_KEY_PAGE_UP:
      window.changeDim(+0.1);
      break;
   case GLUT_KEY_PAGE_DOWN:
      window.changeDim(-0.1);
      break;
   default:
      return;
   }
   glutPostRedisplay();
}

/*
 * This function is called by GLUT when idle
 */
void idle()
{
   //  Request display update
   glutPostRedisplay();
}

/*
 * This function is called by GLUT to display the scene
 * Calls display function for window, which calls display function for lorenz attractor
 */
static void display()
{
   //  Clear screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //draw the window
   window.display();
   //  Sanity check
   ErrCheck("display");

   //  Make scene visible
   glFlush();
   glutSwapBuffers();
}

/*
 *  Main
 */
int main(int argc, char *argv[])
{
   //  Initialize GLUT
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glEnable(GL_DEPTH_TEST);
   //  Create window
   glutInitWindowPosition(0, 0);
   glutInitWindowSize(600, 600);
   win = glutCreateWindow("HOMEWORK 4: Andrew Hack");
   //  Register functions used to display scene
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(key);
   glutSpecialFunc(special);
   glutIdleFunc(idle);
   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
