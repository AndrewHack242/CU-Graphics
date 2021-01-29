#include "camera.h"

Camera::Camera()
{
}

Camera::Camera(GLdouble xt, GLdouble yt, GLdouble zt, GLdouble rotx, GLdouble roty, GLdouble rotz)
{
    x = xt;
    y = yt;
    z = zt;
    view_rotx = rotx;
    view_roty = roty;
    view_rotz = rotz;
}

void Camera::display()
{
    Project(fov, asp, dim, ortho);

    //assistance from learnopengl.com/Getting-started/Camera
    if (fp)
    {
        GLdouble lax = Sin(view_roty) * Cos(view_rotx); //calculate where to look at
        GLdouble lay = Sin(view_rotx);
        GLdouble laz = Cos(view_roty) * Cos(view_rotx);

        normalize(lax, lay, laz);

        GLdouble rx = 0; //calculate the right vector
        GLdouble ry = 0;
        GLdouble rz = 0;
        cross(lax, lay, laz, 0, 1, 0, rx, ry, rz);
        normalize(rx, ry, rz);

        if (!(abs(view_rotx) > 90 && abs(view_rotx) <= 270)) //fixing random flip, don't really understand why it happens
        {
            rx *= -1;
            ry *= -1;
            rz *= -1;
        }

        GLdouble ux = 0; //use right and front vector to find top vector
        GLdouble uy = 0;
        GLdouble uz = 0;
        cross(lax, lay, laz, rx, ry, rz, ux, uy, uz);
        normalize(ux, uy, uz);

        //lookat camera pos,camera front + camerapos, camera up
        gluLookAt(x, y, z, lax + x, lay + y, laz + z, ux, uy, uz);
    }
    //borrowed from ex9
    //perspective - set eye position
    else if (!ortho)
    {
        x = -2 * dim * Sin(view_roty) * Cos(view_rotx);
        y = +2 * dim * Sin(view_rotx);
        z = +2 * dim * Cos(view_roty) * Cos(view_rotx);
        gluLookAt(x, y, z, 0, 0, 0, 0, Cos(view_rotx), 0);
    }

    //  Orthogonal - set world orientation
    else
    {
        glRotatef(view_rotx, 1, 0, 0);
        glRotatef(view_roty, 0, 1, 0);
    }
    //  borrowed from ex9
    //  Display parameters
    glWindowPos2i(5, 5);
    Print("Angle: %d,%d  Dim: %.1f FOV: %.0f Projection: %s FP: %s", abs((int)view_roty % 360), (int)view_rotx % 360, dim, fov, (fp || !ortho) ? "Perpective" : "Orthogonal", fp ? "True" : "False");
}

void Camera::rotate(GLdouble xrot, GLdouble yrot, GLdouble zrot)
{
    view_rotx += xrot;
    view_roty += yrot;
    view_rotz += zrot;
}

void Camera::move(GLdouble xm, GLdouble ym, GLdouble zm)
{
    GLdouble lax = Sin(view_roty) * Cos(view_rotx); //looking vector
    GLdouble lay = Sin(view_rotx);
    GLdouble laz = Cos(view_roty) * Cos(view_rotx);

    normalize(lax, lay, laz);

    x += xm * lax;
    y += xm * lay;
    z += xm * laz; //forward motion

    GLdouble rx = 0; //right vector
    GLdouble ry = 0;
    GLdouble rz = 0;
    cross(lax, lay, laz, 0, 1, 0, rx, ry, rz);
    normalize(rx, ry, rz);
    if (!(abs(view_rotx) > 90 && abs(view_rotx) <= 270))
    {
        rx *= -1;
        ry *= -1;
        rz *= -1;
    }

    x += zm * rx;
    y += zm * ry;
    z += zm * rz; //side motion

    GLdouble ux = 0; //up vector
    GLdouble uy = 0;
    GLdouble uz = 0;
    cross(lax, lay, laz, rx, ry, rz, ux, uy, uz);
    normalize(ux, uy, uz);

    x += ym * ux; // up and down motion (uses up from camera perspective)
    y += ym * uy;
    z += ym * uz;
}

void Camera::changeDim(GLdouble d)
{
    dim += d;
    if (dim < 5)
        dim = 5;
}

void Camera::swapPerspective()
{
    ortho = !ortho;
}

void Camera::swapFP()
{
    rotate(2 * -view_rotx, ((view_roty - 90) * -1) + 90 - view_roty, 0); //fix the perspective to try to line up the two modes as closely as possible
    fp = !fp;
}

void Camera::setASP(GLdouble a)
{
    asp = a;
}