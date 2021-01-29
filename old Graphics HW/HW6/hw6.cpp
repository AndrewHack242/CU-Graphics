/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 */

#include "CSCIx229.h"
#include "companion.h"
#include "camera.h"
#include "light.h"

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static GLint win = 0;

//camera class to handle all perspective things

class Scene
{
private:
   Companion testcube, cube1, cube2, cube3;
   Camera cam;
   Light light;
   bool spinon;
   textureHolder *texture;

public:
   //make the lorenz and do the initial generation
   Scene()
   {
      texture = textureHolder::getInstance();
      texture->init();

      testcube = Companion(0, 0, 0, 3, 0, 0, 0);
      cube1 = Companion(0, 8.3, 0, 2, 0, 0, 180);
      cube2 = Companion(0, -0.35, 6.05, 2, -60, 0, 0);
      cube3 = Companion(-6, -1, -6, 2, 0, 57, 0);
      cam = Camera(-20, 20, 20, -30, 135, 0);
      light = Light(10, 50, 0, 14);
      spinon = true;
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

   void setASP(GLdouble a)
   {
      cam.setASP(a);
   }

   void toggleLightMove()
   {
      light.toggleMove();
   }

   void moveLightUp(GLfloat up)
   {
      light.moveUp(up);
   }

   void moveLight(GLfloat d)
   {
      light.move(d);
   }

   void toggleLight()
   {
      light.toggle();
   }

   void toggleSpin()
   {
      spinon = !spinon;
   }

   //deals with rotation, displays axes, and calls the attractor display,
   //as well as shows the attractor variables
   void display()
   {
      glPushMatrix();

      cam.display(); //do the camera stuffs

      glColor3d(1.0, 1.0, 1.0);
      light.display();
      testcube.display();
      cube2.display();
      cube3.display();
      if (spinon)
         cube1.rotate(0.1, 0.15, 0.2);
      cube1.display();

      glEnable(GL_TEXTURE_2D);
      glColor3d(1.0, 1.0, 1.0);
      glPushMatrix();
      {
         glTranslated(0, -3.19, 0);
         glScalef(30, 30, 30);
         glBindTexture(GL_TEXTURE_2D, texture->getFloor());

         glBegin(GL_QUADS);
         glNormal3f(0, 1, 0);

         glTexCoord2f(0, 0);
         glVertex3f(-1, 0, -1);

         glTexCoord2f(4, 0);
         glVertex3f(+1, 0, -1);

         glTexCoord2f(4, 4);
         glVertex3f(+1, 0, +1);

         glTexCoord2f(0, 4);
         glVertex3f(-1, 0, +1);

         glEnd();
      }
      glPopMatrix();
      glDisable(GL_LIGHTING);
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();
      ErrCheck("scene");
   }
};

Scene *scene = nullptr;

/*
 *  GLUT calls this routine when the window is resized
 *  borrowed from ex9
 */
void reshape(int width, int height)
{
   //  Ratio of the width to the height of the scene
   scene->setASP((height > 0) ? (double)width / double(height) : 1);
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
      scene->move(1, 0, 0);
      break;
   case 'a':
      scene->move(0, 0, 1);
      break;
   case 's':
      scene->move(-1, 0, 0);
      break;
   case 'd':
      scene->move(0, 0, -1);
      break;
   case ' ':
      scene->move(0, 1, 0);
      break;
   case 'c':
      scene->move(0, -1, 0);
      break;
   case 'q':
      scene->swapPerspective();
      break;
   case 'f':
      scene->swapFP();
      break;
   case 'm':
      scene->toggleLightMove();
      break;
   case '1':
      scene->moveLightUp(-0.2);
      break;
   case '2':
      scene->moveLightUp(+0.2);
      break;
   case ',':
      scene->moveLight(-1);
      break;
   case '.':
      scene->moveLight(+1);
      break;
   case 'e':
      scene->toggleLight();
      break;
   case 'x':
      scene->toggleSpin();
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
      scene->rotate(5.0, 0, 0);
      break;
   case GLUT_KEY_DOWN:
      scene->rotate(-5.0, 0, 0);
      break;
   case GLUT_KEY_LEFT:
      scene->rotate(0, 5.0, 0);
      break;
   case GLUT_KEY_RIGHT:
      scene->rotate(0, -5.0, 0);
      break;
   case GLUT_KEY_PAGE_UP:
      scene->changeDim(+0.1);
      break;
   case GLUT_KEY_PAGE_DOWN:
      scene->changeDim(-0.1);
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

   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //draw the window
   scene->display();
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
   glutInitWindowSize(1280, 720);
   win = glutCreateWindow("HOMEWORK 6: Andrew Hack");
   //  Register functions used to display scene
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(key);
   glutSpecialFunc(special);
   glutIdleFunc(idle);

   scene = new Scene();
   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
