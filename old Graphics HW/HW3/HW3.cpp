/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 */

#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
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

//like vertex, but for elevated 2d planes
//inspired by Vertex in ex8, but entirely written by me
static void circleVertex(GLdouble ang, GLdouble height)
{
   glVertex3d(Cos(ang), height, Sin(ang));
}

class Companion
{
private:
   GLdouble size; //size of the cube
   GLdouble x, y, z; //translation coordinates for cube center
   GLdouble rotx, roty, rotz; //rotation of cube

public:
   Companion() //default constructor
   {}

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
      glColor3f(0.2,0.2,0.9);
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
      glColor3f(0.2,0.2,0.9);
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
      
      glColor3f(0.1882,0.7176,0);

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

      glColor3f(0.2,0.2,0.9);
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

      for (int ang = 0; ang <= 360; ang += angleChange)//draw circle in chunks
      {
         circleVertex(ang, 1);
         circleVertex(ang + angleChange, 1);
      }
      glEnd();

      glBegin(GL_TRIANGLE_FAN);

      glVertex3f(0, -1, 0); //set center point for top circle

      for (int ang = 0; ang <= 360; ang += angleChange)//draw circle in chunks
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
      glColor3f(1,1,1);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(90, 1, 0, 0);
      glTranslated(0, 1.025, 0);
      glColor3f(0.72549,0,0);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(180, 1, 0, 0);
      glTranslated(0, 1.025, 0);
      glColor3f(1,0.83529,0);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(270, 1, 0, 0);
      glTranslated(0, 1.025, 0);
      glColor3f(1,0.349,0);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(90, 0, 0, 1);
      glTranslated(0, 1.025, 0);
      glColor3f(0,0.2705,0.6784);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();
      glPushMatrix();

      glRotated(270, 0, 0, 1);
      glTranslated(0, 1.025, 0);
      glColor3f(0,0.6078,0.2823);
      cylinder(5, 0.5, 0.05);

      glPopMatrix();

      //  Undo transformations
      glPopMatrix();
   }
};

class Window
{
private:
   Companion testcube, cube1, cube2, cube3;
   GLdouble scale = 0.1;
   GLfloat view_rotx = 20.0, view_roty = 60.0, view_rotz = 0.0;

public:
   //make the lorenz and do the initial generation
   Window()
   {
      testcube = Companion(0, 0, 0, 30, 0, 0, 0);
      cube1 = Companion(0, 53, 0, 20, 0, 0, 180);
      cube2 = Companion(0, -5, 60.5, 20, -60, 0, 0);
      cube3 = Companion(-60, -10, -60, 20, 0, 57, 0);
   }

   //used to adjust the scale of the window by the key presses
   void adjScale(GLdouble adj)
   {
      scale += adj;
      if (scale < 0.01)
      {
         scale = 0.01;
      }
      else if (scale > 0.2)
      {
         scale = 0.2;
      }
   }

   //deals with rotation, displays axes, and calls the attractor display,
   //as well as shows the attractor variables
   void display()
   {
      glPushMatrix();
      glRotatef(view_rotx, 1.0, 0.0, 0.0);
      glRotatef(view_roty, 0.0, 1.0, 0.0);
      glRotatef(view_rotz, 0.0, 0.0, 1.0);
      glScaled(scale, scale, scale);

      testcube.display();
      cube1.display();
      cube2.display();
      cube3.display();

      glPopMatrix();
   }

   //take rotate arguments from key presses
   void rotate(GLdouble xrot, GLdouble yrot, GLdouble zrot)
   {
      view_rotx += xrot;
      view_roty += yrot;
      view_rotz += zrot;
   }
};

static Window window;

/* new window size or exposure */
/*funciton borrrowed from gears example*/
//reworked to keep the vertical size of objects instead of horizontal
//this just lets the user see the scene better
static void
reshape(int width, int height)
{
   GLfloat w = (GLdouble)width / (GLdouble)height;

   glViewport(0, 0, (GLint)width, (GLint)height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-w, w, -1.0, 1.0, 5.0, 60.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslated(0.0, 0.0, -40.0);
}

/* change view angle, exit upon ESC */
/* ARGSUSED1 */
/*funciton borrrowed from gears example, but heavily modified*/
static void
key(unsigned char k, int x, int y)
{
   switch (k) //keys to adjust scale of window and to adjust the attractor, as well as end the program
   {
   case 'z':
      window.adjScale(0.01);
      break;
   case 'Z':
      window.adjScale(-0.01);
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
   win = glutCreateWindow("HOMEWORK 3: Andrew Hack");
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
