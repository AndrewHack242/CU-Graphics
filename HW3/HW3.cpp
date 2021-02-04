/*
 *  Procedural Textures
 *  Demonstrates the use of shaders to generate textures
 *
 *  Key bindings:
 *  m          Toggle shaders
 *  o          Change objects
 *  xXyYzZ     Change location or zoom
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx239.h"
#include "companion.h"
int mode = 1;              //  Shader
int move = 1;              //  Moving light
int zh = 0;                //  Light position
int th = 0, ph = 0;        //  View angles
int fov = 57;              //  Field of view (for perspective)
int tex = 0;               //  Texture
int obj = 0;               //  Object
float asp = 1;             //  Aspect ratio
float dim = 3.0;           //  Size of world
float X = 0, Y = 0, Z = 1; //  Location of Object
#define MODE 4
int shader[] = {0, 0, 0, 0, 0, 0}; //  Shaders
const char *text[] = {"None", "Hexagons", "Tiny Hexagons", "Candy Cane", "Bricks"};

//
//  Refresh display
//
void display(GLFWwindow *window)
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set view
   View(th, ph, fov, dim);
   //  Enable lighting
   Lighting(3 * Cos(zh), 1.5, 3 * Sin(zh), 0.3, 0.5, 0.8);

   //  Select shader
   glUseProgram(shader[mode]);
   //  Set dimensions for shader 3
   if (mode > 0)
   {
      //  Time
      float t = glfwGetTime();
      int id = glGetUniformLocation(shader[mode], "time");
      glUniform1f(id, t);
      //  Location
      id = glGetUniformLocation(shader[mode], "loc");
      glUniform3f(id, X, Y, 1 / Z);
   }
   //  Draw scene
   switch (obj)
   {
   case 0:
      TexturedCube(tex);
      break;
   case 1: //  Draw companions to scene
   {
      Companion amigo = Companion(0, 0, 0, 1, 0, 0, 0);
      Companion amigo2 = Companion(0, 1.6, 0, 0.5, 0, 60, 0);
      Companion amigo3 = Companion(2, -0.6, 1, 0.4, 0, 0, 90);
      Companion amigo4 = Companion(-4, -0.6, 0, 0.5, 90, 0, 0);
      Companion amigo5 = Companion(0, 10, 0, 0.5, 45, 45, 0);

      amigo.display();
      amigo2.display();
      amigo3.display();
      amigo4.display();
      amigo5.display();
      break;
   }
   case 2:
      TexturedIcosahedron(tex);
      break;
   default:
      TexturedTeapot(8, tex);
      break;
   }
   //  Revert to fixed pipeline
   glUseProgram(0);
   glDisable(GL_LIGHTING);

   //  Display parameters
   glColor3f(1, 1, 1);
   glWindowPos2i(5, 5);
   Print("Angle=%d,%d FPS=%d Dim=%.1f Projection=%s Mode=%s",th,ph,FramesPerSecond(),dim,fov>0?"Perpective":"Orthogonal",text[mode]);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glfwSwapBuffers(window);
}

//
//  Key pressed callback
//
void key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
   //  Discard key releases (keeps PRESS and REPEAT)
   if (action == GLFW_RELEASE)
      return;

   //  Check for shift
   int shift = (mods & GLFW_MOD_SHIFT);

   //  Exit on ESC
   if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window, 1);
   //  Change location
   else if (key == GLFW_KEY_X)
      X += shift ? +0.05 / Z : -0.05 / Z;
   else if (key == GLFW_KEY_Y)
      Y += shift ? +0.05 / Z : -0.05 / Z;
   //  Change zoom
   else if (key == GLFW_KEY_Z && !shift)
      Z *= 2.0;
   else if (key == GLFW_KEY_Z && shift && Z > 1)
      Z *= 0.5;
   //  Reset view angle and location
   else if (key == GLFW_KEY_0)
      X = Y = Z = th = ph = 0;
   //  Switch shaders
   else if (key == GLFW_KEY_M)
      mode = shift ? (mode + MODE - 1) % MODE : (mode + 1) % MODE;
   //  Light movement
   else if (key == GLFW_KEY_S)
      move = 1 - move;
   //  Switch objects
   else if (key == GLFW_KEY_O)
      obj = shift ? (obj + 3) % 4 : (obj + 1) % 4;
   //  Switch between perspective/orthogonal
   else if (key == GLFW_KEY_P)
      fov = fov ? 0 : 57;
   //  Increase/decrease asimuth
   else if (key == GLFW_KEY_RIGHT)
      th += 5;
   else if (key == GLFW_KEY_LEFT)
      th -= 5;
   //  Increase/decrease elevation
   else if (key == GLFW_KEY_UP)
      ph += 5;
   else if (key == GLFW_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLFW_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLFW_KEY_PAGE_UP && dim > 1)
      dim -= 0.1;

   //  Wrap angles
   th %= 360;
   ph %= 360;
   //  Update projection
   Projection(fov, asp, dim);
}

//
//  Window resized callback
//
void reshape(GLFWwindow *window, int width, int height)
{
   //  Get framebuffer dimensions (makes Apple work right)
   glfwGetFramebufferSize(window, &width, &height);
   //  Ratio of the width to the height of the window
   asp = (height > 0) ? (double)width / height : 1;
   //  Set the viewport to the entire window
   glViewport(0, 0, width, height);
   //  Set projection
   Projection(fov, asp, dim);
}

//
//  Main program with GLFW event loop
//
int main(int argc, char *argv[])
{
   //  Initialize GLFW
   GLFWwindow *window = InitWindow("HW3: Andrew Hack", 0, 900, 900, &reshape, &key);

   //  Load shaders
   shader[1] = CreateShaderProg("Shaders/model.vert", "Shaders/hexagons.frag");
   shader[2] = CreateShaderProg("Shaders/model.vert", "Shaders/tinyhex.frag");
   shader[3] = CreateShaderProg("Shaders/model.vert", "Shaders/candycane.frag");
   //  Load textures
   tex = LoadTexBMP("pi.bmp");

   //  Event loop
   ErrCheck("init");
   while (!glfwWindowShouldClose(window))
   {
      //  Light animation
      if (move)
         zh = fmod(90 * glfwGetTime(), 360);
      //  Display
      display(window);
      //  Process any events
      glfwPollEvents();
   }
   //  Shut down GLFW
   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;
}
