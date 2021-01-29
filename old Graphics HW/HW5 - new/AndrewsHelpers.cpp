#include "AndrewsHelpers.h"

void normalize(GLdouble &lax, GLdouble &lay, GLdouble &laz)
{
   GLdouble sum = pow(lax, 2) + pow(lay, 2) + pow(laz, 2);
   sum = sqrt(sum);

   lax /= sum;
   lay /= sum;
   laz /= sum;
}

void cross(GLdouble a1, GLdouble a2, GLdouble a3, GLdouble b1, GLdouble b2, GLdouble b3, GLdouble &r1, GLdouble &r2, GLdouble &r3)
{
   r1 = (a2 * b3) - (a3 * b2);
   r2 = (a3 * b1) - (a1 * b3);
   r3 = (a1 * b2) - (a2 * b1);
}

void circleVertex(GLdouble ang, GLdouble height)
{
   glNormal3f(0, height, 0);
   glVertex3d(Cos(ang), height, Sin(ang));
}

void cyliVertex(GLdouble ang, GLdouble height)
{
   glNormal3f(Cos(ang), 0, Sin(ang));
   glVertex3d(Cos(ang), height, Sin(ang));
}

void ballVertex(double th, double ph)
{
   double x = Sin(th) * Cos(ph);
   double y = Cos(th) * Cos(ph);
   double z = Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x, y, z);
   glVertex3d(x, y, z);
}
