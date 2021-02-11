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
int mode = 1;          //  Shader
int move = 1;          //  Moving light
int zh = 0;            //  Light position
int th = 0, ph = 0;    //  View angles
int fov = 57;          //  Field of view (for perspective)
int tex = 0;           //  Texture
int obj = 0;           //  Object
float YL = 1.5;        //  Light elevation
float asp = 1;         //  Aspect ratio
float dim = 4;         //  Size of world
int shader[] = {0, 0}; //  Shaders
const char *text[] = {"OpenGL 2", "OpenGL 4"};

//
//  Companion Data
//
unsigned int companion_vbo = 0;
const int companion_size = 48;
const float companion_data[] = // Vertex data
    {
        //  X  Y  Z  W   Nx Ny Nz    R G B A   s t
        //  Front
        +1, +1, +1, +1, 0, 0, +1, 1, 0, 0, 1, 1, 1,
        -1, +1, +1, +1, 0, 0, +1, 1, 0, 0, 1, 0, 1,
        +1, -1, +1, +1, 0, 0, +1, 1, 0, 0, 1, 1, 0,
        -1, +1, +1, +1, 0, 0, +1, 1, 0, 0, 1, 0, 1,
        +1, -1, +1, +1, 0, 0, +1, 1, 0, 0, 1, 1, 0,
        -1, -1, +1, +1, 0, 0, +1, 1, 0, 0, 1, 0, 0,
        //  Back
        -1, -1, -1, +1, 0, 0, -1, 0, 0, 1, 1, 1, 0,
        +1, -1, -1, +1, 0, 0, -1, 0, 0, 1, 1, 0, 0,
        -1, +1, -1, +1, 0, 0, -1, 0, 0, 1, 1, 1, 1,
        +1, -1, -1, +1, 0, 0, -1, 0, 0, 1, 1, 0, 0,
        -1, +1, -1, +1, 0, 0, -1, 0, 0, 1, 1, 1, 1,
        +1, +1, -1, +1, 0, 0, -1, 0, 0, 1, 1, 0, 1,
        //  Right
        +1, +1, +1, +1, +1, 0, 0, 1, 1, 0, 1, 0, 1,
        +1, -1, +1, +1, +1, 0, 0, 1, 1, 0, 1, 0, 0,
        +1, +1, -1, +1, +1, 0, 0, 1, 1, 0, 1, 1, 1,
        +1, -1, +1, +1, +1, 0, 0, 1, 1, 0, 1, 0, 0,
        +1, +1, -1, +1, +1, 0, 0, 1, 1, 0, 1, 1, 1,
        +1, -1, -1, +1, +1, 0, 0, 1, 1, 0, 1, 1, 0,
        //  Left
        -1, +1, +1, +1, -1, 0, 0, 0, 1, 0, 1, 1, 1,
        -1, +1, -1, +1, -1, 0, 0, 0, 1, 0, 1, 0, 1,
        -1, -1, +1, +1, -1, 0, 0, 0, 1, 0, 1, 1, 0,
        -1, +1, -1, +1, -1, 0, 0, 0, 1, 0, 1, 0, 1,
        -1, -1, +1, +1, -1, 0, 0, 0, 1, 0, 1, 1, 0,
        -1, -1, -1, +1, -1, 0, 0, 0, 1, 0, 1, 0, 0,
        //  Top
        +1, +1, +1, +1, 0, +1, 0, 0, 1, 1, 1, 1, 0,
        +1, +1, -1, +1, 0, +1, 0, 0, 1, 1, 1, 1, 1,
        -1, +1, +1, +1, 0, +1, 0, 0, 1, 1, 1, 0, 0,
        +1, +1, -1, +1, 0, +1, 0, 0, 1, 1, 1, 1, 1,
        -1, +1, +1, +1, 0, +1, 0, 0, 1, 1, 1, 0, 0,
        -1, +1, -1, +1, 0, +1, 0, 0, 1, 1, 1, 0, 1,
        //  Bottom
        -1, -1, -1, +1, 0, -1, 0, 1, 0, 1, 1, 0, 0,
        +1, -1, -1, +1, 0, -1, 0, 1, 0, 1, 1, 1, 0,
        -1, -1, +1, +1, 0, -1, 0, 1, 0, 1, 1, 0, 1,
        +1, -1, -1, +1, 0, -1, 0, 1, 0, 1, 1, 1, 0,
        -1, -1, +1, +1, 0, -1, 0, 1, 0, 1, 1, 0, 1,
        +1, -1, +1, +1, 0, -1, 0, 1, 0, 1, 1, 1, 1,

        //Side panels
        //edge
        +0.20, +1.06, +1.01, +1, 0, 1, 1, 0, 0, 0, 1, 0.9, 0.4,
        -0.20, +1.06, +1.01, +1, 0, 1, 1, 0, 0, 0, 1, 0.1, 0.4,
        -0.20, +1.01, +1.06, +1, 0, 1, 1, 0, 0, 0, 1, 0.1, 0.6,
        +0.20, +1.01, +1.06, +1, 0, 1, 1, 0, 0, 0, 1, 0.9, 0.6,
        -0.20, +1.01, +1.06, +1, 0, 1, 1, 0, 0, 0, 1, 0.1, 0.6,
        +0.20, +1.06, +1.01, +1, 0, 1, 1, 0, 0, 0, 1, 0.9, 0.4,

        //side1

        //side2

        //corner seals
        +0.20, +1.06, +1.01, +1, 1, 0, 0, 0, 0, 0, 1, 0.9, 0.4,
        +0.20, +1.01, +1.06, +1, 1, 0, 0, 0, 0, 0, 1, 0.9, 0.6,
        +0.20, +1.01, +1.01, +1, 1, 0, 0, 0, 0, 0, 1, 0.991, 0.4,

        -0.20, +1.06, +1.01, +1, -1, 0, 0, 0, 0, 0, 1, 0.1, 0.4,
        -0.20, +1.01, +1.01, +1, -1, 0, 0, 0, 0, 0, 1, 0.009, 0.4,
        -0.20, +1.01, +1.06, +1, -1, 0, 0, 0, 0, 0, 1, 0.1, 0.6,

        //
};

//
//  Initialize companion VBO
//
void InitCompanion()
{
   //  Get buffer name
   glGenBuffers(1, &companion_vbo);
   //  Bind VBO
   glBindBuffer(GL_ARRAY_BUFFER, companion_vbo);
   //  Copy icosahedron to VBO
   glBufferData(GL_ARRAY_BUFFER, sizeof(companion_data), companion_data, GL_STATIC_DRAW);
   //  Release VBO
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//
//  Refresh display
//
void display(GLFWwindow *window)
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Eye position for perspective
   float Ex = -2 * dim * Sin(th) * Cos(ph);
   float Ey = +2 * dim * Sin(ph);
   float Ez = +2 * dim * Cos(th) * Cos(ph);

   //  Lighting parameters
   glm::vec4 global = {0.1, 0.1, 0.1, 1.0};
   glm::vec4 ambient = {0.3, 0.3, 0.3, 1.0};
   glm::vec4 diffuse = {0.8, 0.8, 0.8, 1.0};
   glm::vec4 specular = {1.0, 1.0, 1.0, 1.0};
   glm::vec4 position = {(float)(3 * Cos(zh)), YL, (float)(3 * Sin(zh)), 1.0};

   //  Draw light position as white ball using fixed pipeline
   glColor3f(1, 1, 1);
   View(th, ph, fov, dim);
   Sphere(position[0], position[1], position[2], 0.1, 0, 8, 0);

   //  Enable shader
   glUseProgram(shader[mode]);

   //  Set light property uniforms
   int id = glGetUniformLocation(shader[mode], "fov");
   glUniform1f(id, fov);
   id = glGetUniformLocation(shader[mode], "Global");
   glUniform4fv(id, 1, &global[0]);
   id = glGetUniformLocation(shader[mode], "Ambient");
   glUniform4fv(id, 1, &ambient[0]);
   id = glGetUniformLocation(shader[mode], "Diffuse");
   glUniform4fv(id, 1, &diffuse[0]);
   id = glGetUniformLocation(shader[mode], "Specular");
   glUniform4fv(id, 1, &specular[0]);
   id = glGetUniformLocation(shader[mode], "Position");
   glUniform4fv(id, 1, &position[0]);
   //  OpenGL 4
   //  Create Projection matrix
   glm::mat4 proj(1.0f);
   if (fov)
      proj = glm::perspective((float)fov, asp, dim / 16, 16 * dim); //mat4perspective(proj , fov,asp,dim/16,16*dim);
   else
      proj = glm::ortho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);
   //  Create View matrix
   glm::mat4 view(1.0f);
   if (fov)
      view = glm::lookAt(glm::vec3(Ex, Ey, Ez), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, (float)Cos(ph), 0.0f));
   else
   {
      view = glm::rotate(view, glm::radians((float)ph), glm::vec3(1.0f, 0.0f, 0.0f));
      view = glm::rotate(view, glm::radians((float)th), glm::vec3(0.0f, 1.0f, 0.0f));
   }
   //  Create ModelView matrix
   glm::mat4 modelview(1.0f);
   modelview = view;
   //modelview = glm::translate(modelview, glm::vec3(0, 0, 0.5));
   //  Get Normal matrix
   glm::mat3 normal(modelview);
   normal = glm::inverseTranspose(normal);

   //  Set Projection, View, Modelview and Normal Matrix
   id = glGetUniformLocation(shader[mode], "ProjectionMatrix");
   glUniformMatrix4fv(id, 1, 0, &proj[0][0]);
   id = glGetUniformLocation(shader[mode], "ViewMatrix");
   glUniformMatrix4fv(id, 1, 0, &view[0][0]);
   id = glGetUniformLocation(shader[mode], "ModelViewMatrix");
   glUniformMatrix4fv(id, 1, 0, &modelview[0][0]);
   id = glGetUniformLocation(shader[mode], "NormalMatrix");
   glUniformMatrix3fv(id, 1, 0, &normal[0][0]);

   //draw cube
   Companion c;
   c.display(modelview);

   //  Fixed pipeline
   glUseProgram(0);

   //  Draw axes using fixed pipeline (white)
   Axes(2);

   //  Display parameters
   glColor3f(1, 1, 1);
   glWindowPos2i(5, 5);
   Print("Angle=%d,%d  Dim=%.1f Projection=%s Mode=%s", th, ph, dim, fov > 0 ? "Perpective" : "Orthogonal", text[mode]);
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

   //  Exit on ESC
   if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window, 1);
   //  Reset view angle and location
   else if (key == GLFW_KEY_0)
      th = ph = 0;
   //  Switch shaders
   else if (key == GLFW_KEY_M)
      mode = 1 - mode;
   //  Light movement
   else if (key == GLFW_KEY_S)
      move = 1 - move;
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
   //  Switch objects
   else if (key == GLFW_KEY_O)
      obj = 1 - obj;
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
   GLFWwindow *window = InitWindow("OpenGL Versions", 1, 600, 600, &reshape, &key);

   //  Load shaders
   shader[0] = CreateShaderProg("gl2.vert", "gl2.frag");
   shader[1] = CreateShaderProg("gl4.vert", "gl4.frag");
   //  Load textures
   tex = LoadTexBMP("pi.bmp");
   //  Load cube into VBO
   InitCube();

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
