#pragma once

#include "CSCIx239.h"


//>move these later<
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

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

    //draws a cylinder with a given radius and height at the specified resolution
    void cylinder(GLint angleChange, GLdouble radius, GLdouble height);

    void display(glm::mat4 modelview);
};

extern unsigned int cube_vbo;
extern const int cube_size;
extern const float cube_data[];

void InitCube();