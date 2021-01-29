#include "companion.h"

Companion::Companion()
{
}

Companion::Companion(GLdouble tx, GLdouble ty, GLdouble tz, GLdouble s, GLdouble rx, GLdouble ry, GLdouble rz)
{
    x = tx;
    y = ty;
    z = tz;
    size = s;
    rotx = rx;
    roty = ry;
    rotz = rz;
}

void Companion::rotate(GLdouble x, GLdouble y, GLdouble z)
{
    rotx = fmod(rotx + x,360);
    roty = fmod(roty + y,360);
    rotz = fmod(rotz + z,360);
}

void Companion::cube()
{

    //  Cube
    glBegin(GL_QUADS);
    //  Front
    glNormal3f(0, 0, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(+1, -1, 1);
    glVertex3f(+1, +1, 1);
    glVertex3f(-1, +1, 1);
    //  Back
    glNormal3f(0, 0, -1);
    glVertex3f(+1, -1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, +1, -1);
    glVertex3f(+1, +1, -1);
    //  Right
    glNormal3f(1, 0, 0);
    glVertex3f(+1, -1, +1);
    glVertex3f(+1, -1, -1);
    glVertex3f(+1, +1, -1);
    glVertex3f(+1, +1, +1);
    //  Left
    glNormal3f(-1, 0, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, +1);
    glVertex3f(-1, +1, +1);
    glVertex3f(-1, +1, -1);
    //  Top
    glNormal3f(0, 1, 0);
    glVertex3f(-1, +1, +1);
    glVertex3f(+1, +1, +1);
    glVertex3f(+1, +1, -1);
    glVertex3f(-1, +1, -1);
    //  Bottom
    glNormal3f(0, -1, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(+1, -1, -1);
    glVertex3f(+1, -1, +1);
    glVertex3f(-1, -1, +1);
    //  End
    glEnd();
}

void Companion::sidePanel()
{
    glColor3f(0.2, 0.2, 0.9);
    glBegin(GL_QUADS);
    //corner
    glNormal3f(0, 1, 1);
    glVertex3f(+0.2, +1.06, +1.01);
    glVertex3f(-0.2, +1.06, +1.01);
    glVertex3f(-0.2, +1.01, +1.06);
    glVertex3f(+0.2, +1.01, +1.06);
    //side 1
    glNormal3f(0, +1.06, 0);
    glVertex3f(-0.2, +1.06, +1.01);
    glVertex3f(+0.2, +1.06, +1.01);
    glVertex3f(+0.2, +1.06, +0.85);
    glVertex3f(-0.2, +1.06, +0.85);

    glNormal3f(+0.2, 0, 0);
    glVertex3f(+0.2, +1.06, +1.01);
    glVertex3f(+0.2, +1.06, +0.85);
    glVertex3f(+0.2, +1, +0.85);
    glVertex3f(+0.2, +1, +1.01);

    glNormal3f(-0.2, 0, 0);
    glVertex3f(-0.2, +1.06, +1.01);
    glVertex3f(-0.2, +1, +1.01);
    glVertex3f(-0.2, +1, +0.85);
    glVertex3f(-0.2, +1.06, +0.85);

    glNormal3f(0, 0, -0.85);
    glVertex3f(+0.2, +1.06, +0.85);
    glVertex3f(-0.2, +1.06, +0.85);
    glVertex3f(-0.2, +1, +0.85);
    glVertex3f(+0.2, +1, +0.85);
    //side 2
    glNormal3f(0, 0, +1.06);
    glVertex3f(-0.2, +1.01, +1.06);
    glVertex3f(+0.2, +1.01, +1.06);
    glVertex3f(+0.2, +0.85, +1.06);
    glVertex3f(-0.2, +0.85, +1.06);

    glNormal3f(-0.2, 0, 0);
    glVertex3f(-0.2, +1.01, +1.06);
    glVertex3f(-0.2, +1.01, +1);
    glVertex3f(-0.2, +0.85, +1);
    glVertex3f(-0.2, +0.85, +1.06);

    glNormal3f(+0.2, 0, 0);
    glVertex3f(+0.2, +1.01, +1.06);
    glVertex3f(+0.2, +0.85, +1.06);
    glVertex3f(+0.2, +0.85, +1);
    glVertex3f(+0.2, +1.01, +1);

    glNormal3f(0, -0.85, 0);
    glVertex3f(+0.2, +0.85, +1.06);
    glVertex3f(-0.2, +0.85, +1.06);
    glVertex3f(-0.2, +0.85, +1);
    glVertex3f(+0.2, +0.85, +1);

    glEnd();

    //seal the corner with triangles
    glBegin(GL_TRIANGLES);
    glNormal3f(+0.2, 0, 0);
    glVertex3f(+0.2, +1.06, +1.01);
    glVertex3f(+0.2, +1.01, +1.06);
    glVertex3f(+0.2, +1.01, +1.01);

    glNormal3f(-0.2, 0, 0);
    glVertex3f(-0.2, +1.06, +1.01);
    glVertex3f(-0.2, +1.01, +1.01);
    glVertex3f(-0.2, +1.01, +1.06);

    glEnd();
}

void Companion::cornerPanel()
{
    glColor3f(0.2, 0.2, 0.9);
    glBegin(GL_TRIANGLES);
    //corner
    glNormal3f(1, 1, 1);
    glVertex3f(+1.06, +1.01, +1.01);
    glVertex3f(+1.01, +1.06, +1.01);
    glVertex3f(+1.01, +1.01, +1.06);

    glEnd();

    glBegin(GL_QUADS);
    //strips
    glNormal3f(0, 1, 1);
    glVertex3f(+1.01, +1.06, +1.01);
    glVertex3f(+1.01, +1.01, +1.06);
    glVertex3f(+0.3, +1.01, +1.06);
    glVertex3f(+0.3, +1.06, +1.01);

    glNormal3f(1, 0, 1);
    glVertex3f(+1.06, +1.01, +1.01);
    glVertex3f(+1.01, +1.01, +1.06);
    glVertex3f(+1.01, +0.3, +1.06);
    glVertex3f(+1.06, +0.3, +1.01);

    glNormal3f(1, 1, 0);
    glVertex3f(+1.01, +1.06, +1.01);
    glVertex3f(+1.06, +1.01, +1.01);
    glVertex3f(+1.06, +1.01, +0.3);
    glVertex3f(+1.01, +1.06, +0.3);
    glEnd();

    glColor3f(0.1882, 0.7176, 0);

    glBegin(GL_TRIANGLES);
    //corner plates
    glNormal3f(0, 0, +1.06);
    glVertex3f(+0.3, +1.01, +1.06);
    glVertex3f(+1.01, +0.3, +1.06);
    glVertex3f(+1.01, +1.01, +1.06);

    glNormal3f(+1.06, 0, 0);
    glVertex3f(+1.06, +0.3, +1.01);
    glVertex3f(+1.06, +1.01, +0.3);
    glVertex3f(+1.06, +1.01, +1.01);

    glNormal3f(0, +1.06, 0);
    glVertex3f(+0.3, +1.06, +1.01);
    glVertex3f(+1.01, +1.06, +0.3);
    glVertex3f(+1.01, +1.06, +1.01);
    //strip end-caps

    glColor3f(0.2, 0.2, 0.9);
    glNormal3f(-0.3, 0, 0);
    glVertex3f(+0.3, +1.01, +1.06);
    glVertex3f(+0.3, +1.06, +1.01);
    glVertex3f(+0.3, +1.00, +1.00);

    glNormal3f(0, -0.3, 0);
    glVertex3f(+1.01, +0.3, +1.06);
    glVertex3f(+1.06, +0.3, +1.01);
    glVertex3f(+1.00, +0.3, +1.00);

    glNormal3f(0, 0, -0.3);
    glVertex3f(+1.06, +1.01, +0.3);
    glVertex3f(+1.01, +1.06, +0.3);
    glVertex3f(+1.00, +1.00, +0.3);

    glEnd();

    glBegin(GL_QUADS);
    //inner cover pieces
    glNormal3f(-1, -1, 0);
    glVertex3f(+0.3, +1.01, +1.06);
    glVertex3f(+1.01, +0.3, +1.06);
    glVertex3f(+1.01, +0.3, +1.00);
    glVertex3f(+0.3, +1.01, +1.00);

    glNormal3f(0, -1, -1);
    glVertex3f(+1.06, +0.3, +1.01);
    glVertex3f(+1.06, +1.01, +0.3);
    glVertex3f(+1.00, +1.01, +0.3);
    glVertex3f(+1.00, +0.3, +1.01);

    glNormal3f(-1, 0, -1);
    glVertex3f(+0.3, +1.06, +1.01);
    glVertex3f(+1.01, +1.06, +0.3);
    glVertex3f(+1.01, +1.00, +0.3);
    glVertex3f(+0.3, +1.00, +1.01);

    glEnd();
}

void Companion::cylinder(GLint angleChange, GLdouble radius, GLdouble height)
{
    glPushMatrix();
    glScaled(radius, height, radius);

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, 1, 0);
    glVertex3f(0, 1, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        circleVertex(ang, 1);
        circleVertex(ang + angleChange, 1);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, -1, 0);
    glVertex3f(0, -1, 0); //set center point for top circle

    for (int ang = 0; ang <= 360; ang += angleChange) //draw circle in chunks
    {
        circleVertex(ang, -1);
        circleVertex(ang + angleChange, -1);
    }
    glEnd();

    //connect top circle to bottom circle
    glBegin(GL_QUADS);
    for (int ang = 0; ang <= 360; ang += angleChange)
    {
        cyliVertex(ang, 1);
        cyliVertex(ang + angleChange, 1);
        cyliVertex(ang + angleChange, -1);
        cyliVertex(ang, -1);
    }
    glEnd();

    glPopMatrix();
}

void Companion::display()
{

    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x, y, z);
    glRotated(rotx, 1, 0, 0);
    glRotated(roty, 0, 1, 0);
    glRotated(rotz, 0, 0, 1);
    glScaled(size, size, size);

    glColor3f(0.427, 0.522, 0.569);

    cube();

    //side panels (need 12)

    //top
    glPushMatrix();
    sidePanel();
    glRotated(90, 0, 1, 0);
    sidePanel();
    glRotated(90, 0, 1, 0);
    sidePanel();
    glRotated(90, 0, 1, 0);
    sidePanel();
    glPopMatrix();

    //bottom
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    sidePanel();
    glRotated(90, 0, 0, 1);
    sidePanel();
    glRotated(90, 0, 0, 1);
    sidePanel();
    glRotated(90, 0, 0, 1);
    sidePanel();
    glPopMatrix();

    //middle
    glPushMatrix();
    glRotated(90, 0, 0, 1);
    sidePanel();
    glRotated(90, 1, 0, 0);
    sidePanel();
    glRotated(90, 1, 0, 0);
    sidePanel();
    glRotated(90, 1, 0, 0);
    sidePanel();
    glPopMatrix();

    //corners (8)

    //top
    glPushMatrix();
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glPopMatrix();

    //bottom
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glRotated(90, 0, 1, 0);
    cornerPanel();
    glPopMatrix();

    //fun with cylinders (the ones in the center of each side)
    glColor3f(1, 1, 1);

    glPushMatrix();

    glTranslated(0, 1.025, 0);
    glColor3f(1, 1, 1);
    cylinder(5, 0.5, 0.05);

    glPopMatrix();
    glPushMatrix();

    glRotated(90, 1, 0, 0);
    glTranslated(0, 1.025, 0);
    glColor3f(0.72549, 0, 0);
    cylinder(5, 0.5, 0.05);

    glPopMatrix();
    glPushMatrix();

    glRotated(180, 1, 0, 0);
    glTranslated(0, 1.025, 0);
    glColor3f(1, 0.83529, 0);
    cylinder(5, 0.5, 0.05);

    glPopMatrix();
    glPushMatrix();

    glRotated(270, 1, 0, 0);
    glTranslated(0, 1.025, 0);
    glColor3f(1, 0.349, 0);
    cylinder(5, 0.5, 0.05);

    glPopMatrix();
    glPushMatrix();

    glRotated(90, 0, 0, 1);
    glTranslated(0, 1.025, 0);
    glColor3f(0, 0.2705, 0.6784);
    cylinder(5, 0.5, 0.05);

    glPopMatrix();
    glPushMatrix();

    glRotated(270, 0, 0, 1);
    glTranslated(0, 1.025, 0);
    glColor3f(0, 0.6078, 0.2823);
    cylinder(5, 0.5, 0.05);

    glPopMatrix();

    //  Undo transformations
    glPopMatrix();
}