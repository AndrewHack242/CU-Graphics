#include "CSCIx239.h"

//
//  Projection matrix
//
void Projection(float fov,float asp,float dim)
{
   //  Set projection matrix
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //  Perspective transformation
   if (fov)
      gluPerspective(fov,asp,dim/16,16*dim);
   //  Orthogonal transformation
   else
      glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);
   //  Reset modelview
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

//
//  View Matrix
//
void View(float th,float ph,float fov,float dim, float x, float y, float z)
{
   //  Set ModelView matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //  Perspective - set eye position
   if (fov)
   {
      float Ex = Cos(th)*Cos(ph);
      float Ey =         Sin(ph);
      float Ez = Sin(th)*Cos(ph);
      gluLookAt(x,y,z , x + Ex,y + Ey,z + Ez , 0,1,0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
}
