#pragma once

#include "CSCIx229.h"
#include <iostream>

//return by reference - normalizes a vector (mostly needed for movement)
void normalize(GLdouble &lax, GLdouble &lay, GLdouble &laz);

//function to return by reference the cross product of two vectors
void cross(GLdouble a1, GLdouble a2, GLdouble a3, GLdouble b1, GLdouble b2, GLdouble b3, GLdouble &r1, GLdouble &r2, GLdouble &r3);

//like vertex, but for elevated 2d planes
//inspired by Vertex in ex8, but entirely written by me
void circleVertex(GLdouble ang, GLdouble height);

//does normals different than circleVertex so I can make a cylinder
void cyliVertex(GLdouble ang, GLdouble height);

/*
 *  Draw vertex in polar coordinates with normal
 * from ex13
 */
void ballVertex(double th, double ph);
