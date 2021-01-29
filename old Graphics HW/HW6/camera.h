#pragma once

#include "CSCIx229.h"
#include "AndrewsHelpers.h"

class Camera
{
private:
   GLfloat x = 0, y = 0, z = 0;
   GLfloat view_rotx = 0, view_roty = 0, view_rotz = 0;
   bool ortho = false, fp = true;
   GLdouble fov = 55, dim = 20;
   GLdouble asp;

public:
   Camera();

   Camera(GLdouble xt, GLdouble yt, GLdouble zt, GLdouble rotx, GLdouble roty, GLdouble rotz);

   //implements the camera positioning to the scene
   void display();

   //take rotate arguments from key presses
   void rotate(GLdouble xrot, GLdouble yrot, GLdouble zrot);

   //move the cam
   void move(GLdouble xm, GLdouble ym, GLdouble zm);

   //change dimensions of space
   void changeDim(GLdouble d);

   //swap between perspective and orthogonal
   void swapPerspective();

   //swap between first person and not
   void swapFP();

   void setASP(GLdouble a);
};