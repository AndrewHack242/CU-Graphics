#ifndef Companion_h
#define Companion_h

#include "CSCIx239.h"

class Companion
{
private:
    GLdouble size;             //size of the cube
    GLdouble x, y, z;          //translation coordinates for cube center
    GLdouble rotx, roty, rotz; //rotation of cube

public:
    Companion(); //default constructor

    Companion(GLdouble tx, GLdouble ty, GLdouble tz, GLdouble s, GLdouble rx, GLdouble ry, GLdouble rz);

    //borrowed from ex8 with slight edits
    void cube();

    void sidePanel();

    void cornerPanel();

    void rotate(GLdouble x, GLdouble y, GLdouble z);

    void display();
};
#endif