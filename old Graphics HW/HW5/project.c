/*
 *  Set projection
 */
#include "CSCIx229.h"
#include <stdbool.h>

void Project(double fov,double asp,double dim, bool ortho)
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (!ortho)
      gluPerspective(fov,asp,dim/16,16*dim);
   //  Orthogonal transformation
   else
      glOrtho(-asp*dim,asp*dim,-dim,+dim,-2*dim,+2*dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   //glLoadIdentity(); //removing because of the different use in my program
}

