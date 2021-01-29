#include "light.h"

Light::Light()
{
}

Light::Light(GLint amb, GLint diff, GLint spec, GLfloat dist)
{
    ambient = amb;
    diffuse = diff;
    specular = spec;
    distance = dist;
    on = true;
    moving = true;
    zh = 0;
    y = 8;

    emission = 0;
    shiny = 1;
}

void Light::toggleMove()
{
    moving = !moving;
}

//move light up and down
void Light::moveUp(GLfloat up)
{
    y += up;
}

void Light::move(GLfloat d)
{
    zh += d;
}

void Light:: toggle()
{
    on = !on;
}

//mostly borrowed from ex13
void Light::display()
{
    if (on)
    {
        if (moving)
        {
            double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
            zh = fmod(90 * t, 360.0);
        }
        //  Translate intensity to color vectors
        GLfloat Ambient[] = {(float)0.01 * ambient, (float)0.01 * ambient, (float)0.01 * ambient, 1.0};
        GLfloat Diffuse[] = {(float)0.01 * diffuse, (float)0.01 * diffuse, (float)0.01 * diffuse, 1.0};
        GLfloat Specular[] = {(float)0.01 * specular, (float)0.01 * specular, (float)0.01 * specular, 1.0};
        //  Light position
        GLfloat Position[] = {distance * (float)Cos(zh), y, distance * (float)Sin(zh), 1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1, 1, 1);
        ball(10, Position[0], Position[1], Position[2], 1, emission, shiny);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        //  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
        glLightfv(GL_LIGHT0, GL_POSITION, Position);
    }
    else
        glDisable(GL_LIGHTING);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 * from ex13 with slight edits
 */
void Light::ball(GLint inc, double x, double y, double z, double r, GLint emission, GLfloat shiny)
{
    GLint th, ph;
    GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat Emission[] = {0.0, 0.0, (float)0.01 * emission, 1.0};
    //  Save transformation
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x, y, z);
    glScaled(r, r, r);
    //  White ball
    glColor3f(1, 1, 1);
    glMaterialf(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
    glMaterialfv(GL_FRONT, GL_EMISSION, Emission);
    //  Bands of latitude
    for (ph = -90; ph < 90; ph += inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (th = 0; th <= 360; th += 2 * inc)
        {
            ballVertex(th, ph);
            ballVertex(th, ph + inc);
        }
        glEnd();
    }
    //  Undo transofrmations
    glPopMatrix();
}
