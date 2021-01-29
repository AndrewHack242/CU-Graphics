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
      fprintf(stderr,"ERROR: %s",gluErrorString(err));
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

//simple coordinate class that can be used to hold the vertices of the attractor
class Coord
{
private:
   GLdouble x, y, z;

public:
   void setCoord(GLdouble x1, GLdouble y1, GLdouble z1)
   {
      x = x1;
      y = y1;
      z = z1;
   }

   GLdouble getX()
   {
      return x;
   }
   GLdouble getY()
   {
      return y;
   }
   GLdouble getZ()
   {
      return z;
   }
};

class Lorenz
{
private:
   /*  Lorenz Parameters  */
   bool overtime = true;
   int starttime = glutGet(GLUT_ELAPSED_TIME);
   GLdouble s = 3.4;
   GLdouble r = 37.3;
   GLdouble b = 2.1;
   Coord coord[50000]; //stores the lorenz until it is generated with different parameters

public:
   //swaps between draw and draw over time
   void swapMode()
   {
      overtime = !overtime;
      starttime = glutGet(GLUT_ELAPSED_TIME);
   }

   //generates a new attractor
   void generateLorenz()
   {
      GLdouble x = 1;
      GLdouble y = 1;
      GLdouble z = 1;
      coord[0].setCoord(x, y, z);
      for (GLint i = 1; i < 50000; i++)
      {
         doLorenz(i, x, y, z);
         coord[i].setCoord(x, y, z);
      }
   }

   //used to modify the lorenz values
   void editS(GLdouble s1)
   {
      s += s1;
      generateLorenz();
      starttime = glutGet(GLUT_ELAPSED_TIME);
   }
   void editB(GLdouble b1)
   {
      b += b1;
      generateLorenz();
      starttime = glutGet(GLUT_ELAPSED_TIME);
   }
   void editR(GLdouble r1)
   {
      r += r1;
      generateLorenz();
      starttime = glutGet(GLUT_ELAPSED_TIME);
   }

   //getters
   GLdouble getS()
   {
      return s;
   }
   GLdouble getR()
   {
      return r;
   }
   GLdouble getB()
   {
      return b;
   }

   //an individual calculation of the attractor, returns using pass by reference.
   void doLorenz(GLint &i, GLdouble &x, GLdouble &y, GLdouble &z)
   {
      GLdouble dt = 0.001;
      GLdouble dx = s * (y - x);
      GLdouble dy = x * (r - z) - y;
      GLdouble dz = x * y - b * z;
      x += dt * dx;
      y += dt * dy;
      z += dt * dz;
   }

   //display the attractor
   void display()
   {
      glPushMatrix();
      glBegin(GL_LINE_STRIP); //draw line strip to connect all points
      /* this for loop has 2 modes, draw all of it at once, and draw it over time.
         the over time will add a new vertex each millisecond until it is done      */
      for (GLint i = 0; i < 50000 && (!overtime || i < (GLint)glutGet(GLUT_ELAPSED_TIME) - starttime); i++)
      {
         if (i < 25000) //pretty color gradient
         {
            glColor3d(1.0 - i * 1.0 / 25000, 0, i * 1.0 / 25000);
         }
         else if (i < 50000) //pretty color gradient part 2
         {
            glColor3d(0, (i - 25000) * 1.0 / 25000, 1.0 - (i - 25000) * 1.0 / 25000);
         }

         glVertex3d(coord[i].getX(), coord[i].getY(), coord[i].getZ()); //set next vertex
      }
      glEnd();
      glPopMatrix();
   }
};

class Window
{
private:
   GLdouble scale = 0.1;
   Lorenz l;
   GLfloat view_rotx = 20.0, view_roty = 60.0, view_rotz = 0.0;

public:
   //make the lorenz and do the initial generation
   Window()
   {
      l = Lorenz();
      l.generateLorenz();
   }

   //used to adjust the scale of the window by the key presses
   void adjScale(GLdouble adj)
   {
      scale += adj;
      if (scale < 0.01)
      {
         scale = 0.01;
      }
      else if (scale >0.2)
      {
         scale = 0.2;
      }
   }

   //returns a pointer to the attractor
   Lorenz *getLorenz()
   {
      return &l;
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

      glColor3d(1.0, 1.0, 1.0);

      glBegin(GL_LINES);
      glVertex3d(0, 0, 0);
      glVertex3d(100, 0, 0);
      glVertex3d(0, 0, 0);
      glVertex3d(0, 100, 0);
      glVertex3d(0, 0, 0);
      glVertex3d(0, 0, 100);
      glEnd();

      l.display();

      //code borrowed from ex7
      glColor3d(1.0, 1.0, 1.0);
      glRasterPos3d(100,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,100,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,100);
      Print("Z");

      glPopMatrix();

      glColor3d(1.0, 1.0, 1.0);
      glWindowPos2i(5, 5);
      Print("S: %.2f | R: %.2f | B: %.2f", l.getS(), l.getR(), l.getB());
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
static void
reshape(int width, int height)
{
   GLfloat h = (GLdouble)height / (GLdouble)width;

   glViewport(0, 0, (GLint)width, (GLint)height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.0, 1.0, -h, h, 5.0, 60.0);
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
   case 'q':
      window.getLorenz()->editS(0.1);
      break;
   case 'a':
      window.getLorenz()->editS(-0.1);
      break;
   case 'w':
      window.getLorenz()->editR(0.1);
      break;
   case 's':
      window.getLorenz()->editR(-0.1);
      break;
   case 'e':
      window.getLorenz()->editB(0.1);
      break;
   case 'd':
      window.getLorenz()->editB(-0.1);
      break;
   case 'x':
      window.getLorenz()->swapMode();
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
/*funciton borrrowed from gears example*/
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
   //  Sanity check
   ErrCheck("display");
   //  Make scene visible
   window.display();
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
   glutInitWindowSize(500, 500);
   win = glutCreateWindow("HOMEWORK 2: Andrew Hack");
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
