#pragma once

#include "CSCIx229.h"
#include "AndrewsHelpers.h"

//class specifically for a spinny light
class Light
{
private:
    bool on, moving;
    int ambient, diffuse, specular;
    GLfloat distance, zh, y;

    GLint emission;
    GLfloat shiny;

public:
    Light();
    Light(GLint amb, GLint diff, GLint spec, GLfloat dist);

    void display();
    void toggleMove();
    void moveUp(GLfloat up);
    void move(GLfloat d);
    void toggle();

    void ball(GLint inc, double x, double y, double z, double r, GLint emission, GLfloat shiny);
};