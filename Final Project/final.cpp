/*
 *  Opengl 4
 *  Demonstrates OpenGL 4 syntax
 *
 *  Key bindings:
 *  m          Toggle shaders
 *  o          Change objects
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "companion.h"
#include "CSCIx239.h"
#include "scene.h"
#include "ShaderHandler.h"
int mode = 1;       //  Shader
int mov = 1;        //  Moving light
int zh = 0;         //  Light position
int th = 0, ph = 0; //  View angles
glm::vec3 pos;
int fov = 57;   //  Field of view (for perspective)
int tex = 0;    //  Texture
int obj = 0;    //  Object
float YL = 1.5; //  Light elevation
float asp = 1;  //  Aspect ratio
float dim = 4;  //  Size of world
const char *text[] = {"OpenGL 2", "OpenGL 4"};

Scene scene;

//
//  Refresh display
//
void display(GLFWwindow *window)
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //TODO: move lighting to its own handler FIX THE LIGHT SO THAT IT ISN'T DRAWN INCORRECTLY

   //  Lighting parameters
   glm::vec4 global = {0.1, 0.1, 0.1, 1.0};
   glm::vec4 ambient = {0.3, 0.3, 0.3, 1.0};
   glm::vec4 diffuse = {0.8, 0.8, 0.8, 1.0};
   glm::vec4 specular = {1.0, 1.0, 1.0, 1.0};
   glm::vec4 lightposition = {(float)(3 * Cos(zh)), YL, (float)(3 * Sin(zh)), 1.0};
   glm::vec4 lightcolor = {1.0, 0.0, 0.5, 1.0};

   //  Set light property uniforms
   ShaderHandler::updateLightInfo(global, ambient, diffuse, specular, lightposition, lightcolor);

   //  Draw light position as white ball using fixed pipeline
   glColor3f(1, 1, 1);
   View(th, ph, fov, dim, pos.x, pos.y, pos.z); //remove the default pipeline
   ColoredSphere(lightposition[0], lightposition[1], lightposition[2], 0.1, 0, 8, lightcolor.r, lightcolor.g, lightcolor.b, lightcolor.a);

   //  Create Projection matrix //TODO: create window class for this ish
   ShaderHandler::updateFOV(fov);
   glm::mat4 proj(1.0f);
   proj = glm::perspective(glm::radians((float)fov), asp, dim / 16, 16 * dim); //mat4perspective(proj , fov,asp,dim/16,16*dim);

   //TODO: move calculations to camera, scene

   //  Eye position for perspective
   glm::vec3 lapos;
   lapos.x = Cos(th) * Cos(ph);
   lapos.y = Sin(ph);
   lapos.z = Sin(th) * Cos(ph);
   lapos = glm::normalize(lapos);
   //  Create View matrix
   glm::mat4 view(1.0f);
   view = glm::lookAt(pos, pos + lapos, glm::vec3(0.0f, 1.0f, 0.0f));
   //model = glm::rotate(model, glm::radians((float)37), glm::vec3(0.0f, 1.0f, 0.0f));
   ShaderHandler::updateProjMatrix(proj);
   ShaderHandler::updateViewMatrix(view);

   //  Set Projection, View, Modelview and Normal Matrix now moved toShaderHandler

   scene.drawScene();
   //Companion c(0, 0, 0, 1, 0, 270, 0);
   //Companion c2(3, -.25, 2.5, 0.75, 0, 26, 0);
   //Companion c3(0, 1.455, 0, 0.4, 0, 45, 180);
   //Companion c4(1.85, 0, 0, 0.6, 0, 0, 60);
   //Companion c5(3, 1, 2.5, 0.5, 0, 94, 0);
   //c.display(shader[mode], proj, view, modelview, normal);
   //c2.display(shader[mode], proj, view, modelview, normal);
   //c3.display(shader[mode], proj, view, modelview, normal);
   //c4.display(shader[mode], proj, view, modelview, normal);
   //c5.display(shader[mode], proj, view, modelview, normal);

   //  Fixed pipeline

   //  Draw axes using fixed pipeline (white)
   //Axes(2);

   //  Display parameters
   glColor3f(1, 1, 1);
   glWindowPos2i(5, 5);
   Print("Angle=%d,%d  Dim=%.1f Projection=%s Mode=%s", th, ph, dim, fov > 0 ? "Perpective" : "Orthogonal", text[mode]);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glfwSwapBuffers(window);
}

void move(glm::vec3 movement)
{
   glm::vec3 lapos(0, 0, 0);
   lapos.x = Cos(th) * Cos(ph);
   lapos.y = Sin(ph);
   lapos.z = Sin(th) * Cos(ph);
   lapos = glm::normalize(lapos);

   pos = pos + (lapos * movement.x);

   glm::vec3 right(0, 0, 0);
   right = glm::cross(lapos, glm::vec3(0, 1, 0));
   right = glm::normalize(right);

   pos = pos + (right * movement.z);

   glm::vec3 up(0, 0, 0);
   up = glm::cross(lapos, right);
   up = glm::normalize(up);

   pos = pos + (up * -movement.y);
}

//
//  Key pressed callback
//
void key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
   //  Discard key releases (keeps PRESS and REPEAT)
   if (action == GLFW_RELEASE)
      return;

   //  Exit on ESC
   if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window, 1);
   //  Reset view angle and location
   else if (key == GLFW_KEY_0)
      th = ph = 0;
   //  Light movement
   else if (key == GLFW_KEY_L)
      mov = 1 - mov;
   //  Light elevation
   else if (key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_MINUS)
      YL -= 0.05;
   else if (key == GLFW_KEY_KP_ADD || key == GLFW_KEY_EQUAL)
      YL += 0.05;
   // Move light
   else if (key == GLFW_KEY_RIGHT_BRACKET)
      zh += 1;
   else if (key == GLFW_KEY_LEFT_BRACKET)
      zh -= 1;
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
   //  WASD/space/ctrl
   else if (key == GLFW_KEY_W)
      move(glm::vec3(1, 0, 0));
   else if (key == GLFW_KEY_A)
      move(glm::vec3(0, 0, -1));
   else if (key == GLFW_KEY_S)
      move(glm::vec3(-1, 0, 0));
   else if (key == GLFW_KEY_D)
      move(glm::vec3(0, 0, 1));
   else if (key == GLFW_KEY_SPACE)
      move(glm::vec3(0, 1, 0));
   else if (key == GLFW_KEY_LEFT_CONTROL)
      move(glm::vec3(0, -1, 0));
   //  PageUp key - increase dim
   else if (key == GLFW_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLFW_KEY_PAGE_UP && dim > 1)
      dim -= 0.1;
   //  refresh scene file
   else if (key == GLFW_KEY_R)
      scene.reload();
   //  Wrap angles
   th %= 360;
   if (ph > 85)
      ph = 85;
   if (ph < -85)
      ph = -85;
   //  Update projection
   Projection (fov, asp, dim);
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
   GLFWwindow *window = InitWindow("HW4: Andrew Hack", 1, 900, 900, &reshape, &key);
 
   //  Load cube into VBO
   InitCompanion();

   pos = glm::vec3(0, 0, 3);
   th = -90;
   ph = 0;
   scene = Scene("scene.txt");

   //  Event loop
   ErrCheck("init");
   while (!glfwWindowShouldClose(window))
   {
      //  Light animation
      if (mov)
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
