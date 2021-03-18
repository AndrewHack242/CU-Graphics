/*
 *  Geodesic Sphere
 *  This program requires OpenGL 4.0 or above
 *
 *  Demonstrate a tesselation shader by drawing a sphere
 *  from an icosahedron.
 *
 *  Based on The Little Grashopper tutorial
 *  http://prideout.net/blog/?p=48
 *
 *  Key bindings:
 *  +/-        Increase/decrease inner and outer
 *  i/I        Increase/decrease inner
 *  o/O        Increase/decrease outer
 *  r          Reset inner/outer levels
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx239.h"
int th = 0;      //  Azimuth of view angle
int ph = 0;      //  Elevation of view angle
int zh = 0;      //  Light angle
int shader[2];   //  Shader
int N;           //  Number of faces
int RingN;
int Inner = 3;   //  Tesselation inner level
int Outer = 2;   //  Tesselation outer level
float asp = 1;   //  Screen aspect ratio
float dim = 2;   //  World dimension
float elv = -10; //  Light elevation
int lines = 0;
int mode = 0;
int fov = 57;
float distance = 0;
unsigned int vao; //  Icosahedron VAO
unsigned int pointvao;
unsigned int ringvao;
int ring = 1;
int oof = 0;
int ringshader[2];
int oofshader = 0;
float lod = 1.00;

//
//  Refresh display
//
void display(GLFWwindow *window)
{

   float Ex = -2 * dim * Sin(th) * Cos(ph);
   float Ey = +2 * dim * Sin(ph);
   float Ez = +2 * dim * Cos(th) * Cos(ph);
   //  Create Projection matrix
   float project[16];
   mat4identity(project);
   if (fov)
      mat4perspective(project, fov, asp, dim / 16, 100 * dim);
   else
      mat4ortho(project, -dim * asp, +dim * asp, -dim, +dim, -dim, +100 * dim);
   //  Create View matrix
   float view[16];
   mat4identity(view);
   if (fov)
      mat4lookAt(view, Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
   else
   {
      mat4rotate(view, ph, 1, 0, 0);
      mat4rotate(view, th, 0, 1, 0);
   }
   //  Create ModelView matrix
   float modelview[16];
   mat4identity(modelview);
   mat4translate(modelview, 0, 0, distance);
   mat4multMatrix(modelview, view);
   //  Get Normal matrix
   float normal[9];
   mat4normalMatrix(modelview, normal);

   if(oof)
   {
      glUseProgram(oofshader);
   //  Set transformation matrixes
   int id = glGetUniformLocation(oofshader, "Projection");
   glUniformMatrix4fv(id, 1, 0, project);
   id = glGetUniformLocation(oofshader, "Modelview");
   glUniformMatrix4fv(id, 1, 0, modelview);
   id = glGetUniformLocation(oofshader, "NormalMatrix");
   glUniformMatrix3fv(id, 1, 0, normal);
   id = glGetUniformLocation(oofshader, "LOD");
   glUniform1f(id, lod);

   // Render the scene
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_PROGRAM_POINT_SIZE);
   //glEnable(GL_CULL_FACE);
   glClearColor(0.1, 0.1, 0.1, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //draw the ring
   //  Bind VAO and render
   glBindVertexArray(pointvao);
   glDrawArrays(GL_POINTS, 0, 3);
   glUseProgram(0);
   }
   else if(ring)
   {
//  Set shader
   glUseProgram(ringshader[mode]);

   //  Lighting parameters
   int id = glGetUniformLocation(ringshader[mode], "LightDir");
   glUniform3f(id, Cos(zh), 0.1 * elv, Sin(zh));

   //  Set transformation matrixes
   id = glGetUniformLocation(ringshader[mode], "Projection");
   glUniformMatrix4fv(id, 1, 0, project);
   id = glGetUniformLocation(ringshader[mode], "Modelview");
   glUniformMatrix4fv(id, 1, 0, modelview);
   id = glGetUniformLocation(ringshader[mode], "NormalMatrix");
   glUniformMatrix3fv(id, 1, 0, normal);
   id = glGetUniformLocation(ringshader[mode], "lines");
   glUniform1i(id, lines);

   //  Controls for tesselation level
   id = glGetUniformLocation(ringshader[mode], "distance");
   glUniform1f(id, distance);

   // Render the scene
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_CULL_FACE);
   glClearColor(0.1, 0.1, 0.1, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPatchParameteri(GL_PATCH_VERTICES, 3);

   //  Bind VAO and render
   glBindVertexArray(ringvao);
   glDrawElements(GL_PATCHES, RingN, GL_UNSIGNED_INT, 0);

   //  Unset shader
   glUseProgram(0);
   }
   else
   {
   //  Set shader
   glUseProgram(shader[mode]);

   //  Lighting parameters
   int id = glGetUniformLocation(shader[mode], "LightDir");
   glUniform3f(id, Cos(zh), 0.1 * elv, Sin(zh));

   //  Set transformation matrixes
   id = glGetUniformLocation(shader[mode], "Projection");
   glUniformMatrix4fv(id, 1, 0, project);
   id = glGetUniformLocation(shader[mode], "Modelview");
   glUniformMatrix4fv(id, 1, 0, modelview);
   id = glGetUniformLocation(shader[mode], "NormalMatrix");
   glUniformMatrix3fv(id, 1, 0, normal);
   id = glGetUniformLocation(shader[mode], "lines");
   glUniform1i(id, lines);

   //  Controls for tesselation level
   id = glGetUniformLocation(shader[mode], "distance");
   glUniform1f(id, distance);

   // Render the scene
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_CULL_FACE);
   glClearColor(0.1, 0.1, 0.1, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPatchParameteri(GL_PATCH_VERTICES, 3);

   //  Bind VAO and render
   glBindVertexArray(vao);
   glDrawElements(GL_PATCHES, N, GL_UNSIGNED_INT, 0);

   //  Unset shader
   glUseProgram(0);
   }

   //  Display parameters
   glColor3f(1, 1, 1);
   glWindowPos2i(5, 5);
   Print("FPS=%d Angle=%d,%d Projection=%s distance=%0.1f",
         FramesPerSecond(), th, ph, fov ? "Perspective" : "Ortho", distance);
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
   //  Toggle movement
   else if (key == GLFW_KEY_W)
      distance -= 0.5;
   else if (key == GLFW_KEY_S)
      distance += 0.5;
   //  Move light
   else if (key == GLFW_KEY_LEFT_BRACKET && !shift)
      zh += 5;
   else if (key == GLFW_KEY_RIGHT_BRACKET && !shift)
      zh -= 5;
   //  Move light
   else if (key == GLFW_KEY_LEFT_BRACKET && shift)
      elv++;
   else if (key == GLFW_KEY_RIGHT_BRACKET && shift)
      elv--;
   //toggle lines
   else if (key == GLFW_KEY_L)
   {
      lines = lines ? 0 : 1;
   }
   else if (key == GLFW_KEY_PERIOD)
      lod+=0.5;
   else if (key == GLFW_KEY_COMMA)
      lod-=0.5;
   //toggle lighting mode
   else if (key == GLFW_KEY_M)
   {
      mode = mode ? 0 : 1;
   }
   else if (key == GLFW_KEY_O)
   {
      ring = ring ? 0 : 1;
   }
   else if (key == GLFW_KEY_F)
   {
      oof = oof ? 0 : 1;
   }
   else if (key == GLFW_KEY_P)
      fov = fov ? 0 : 57;
   //  Right arrow key - increase angle by 5 degrees
   else if (key == GLFW_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLFW_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLFW_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLFW_KEY_DOWN)
      ph -= 5;

   //  Limit tessalation level
   if (Inner < 1)
      Inner = 1;
   if (Outer < 1)
      Outer = 1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   if (lod < 1)
      lod = 1;
   if(ring)
      mode = 0;
}

//
//  Window resized callback
//
void reshape(GLFWwindow *window, int width, int height)
{
   //  Get framebuffer dimensions (makes Apple work right)
   glfwGetFramebufferSize(window, &width, &height);
   //  Ratio of the width to the height of the window
   asp = (height > 0) ? width / (double)height : 1;
   //  Set the viewport to the entire window
   glViewport(0, 0, width, height);
}

//
//  Create Shader Program
//
void CreateShaderProgTess(int *prog)
{
   //  Create program

   prog[0] = glCreateProgram();
   //  Compile shaders
   CreateShader(prog[0], GL_VERTEX_SHADER, "geodesic.vert");
   CreateShader(prog[0], GL_TESS_CONTROL_SHADER, "geodesic.tesc");
   CreateShader(prog[0], GL_TESS_EVALUATION_SHADER, "geodesic.tese");
   CreateShader(prog[0], GL_GEOMETRY_SHADER, "geodesic.geom");
   CreateShader(prog[0], GL_FRAGMENT_SHADER, "geodesic.frag");
   //  Link program
   glLinkProgram(prog[0]);
   //  Check for errors
   PrintProgramLog(prog[0]);

   prog[1] = glCreateProgram();
   //  Compile shaders
   CreateShader(prog[1], GL_VERTEX_SHADER, "geodesic.vert");
   CreateShader(prog[1], GL_TESS_CONTROL_SHADER, "geodesic.tesc");
   CreateShader(prog[1], GL_TESS_EVALUATION_SHADER, "geodesic.tese");
   CreateShader(prog[1], GL_GEOMETRY_SHADER, "smoothlight.geom");
   CreateShader(prog[1], GL_FRAGMENT_SHADER, "geodesic.frag");
   //  Link program
   glLinkProgram(prog[1]);

   ringshader[0] = glCreateProgram();
   //  Compile shaders
   CreateShader(ringshader[0], GL_VERTEX_SHADER, "geodesic.vert");
   CreateShader(ringshader[0], GL_TESS_CONTROL_SHADER, "geodesic.tesc");
   CreateShader(ringshader[0], GL_TESS_EVALUATION_SHADER, "ring.tese");
   CreateShader(ringshader[0], GL_GEOMETRY_SHADER, "geodesic.geom");
   CreateShader(ringshader[0], GL_FRAGMENT_SHADER, "geodesic.frag");
   //  Link program
   glLinkProgram(ringshader[0]);

   ringshader[1] = glCreateProgram();
   //  Compile shaders
   CreateShader(ringshader[1], GL_VERTEX_SHADER, "geodesic.vert");
   CreateShader(ringshader[1], GL_TESS_CONTROL_SHADER, "geodesic.tesc");
   CreateShader(ringshader[1], GL_TESS_EVALUATION_SHADER, "ring.tese");
   CreateShader(ringshader[1], GL_GEOMETRY_SHADER, "smoothlight.geom");
   CreateShader(ringshader[1], GL_FRAGMENT_SHADER, "geodesic.frag");
   //  Link program
   glLinkProgram(ringshader[1]);

   //  Check for errors
   PrintProgramLog(prog[1]);
}

//
//  Icosahedron data
//    We don't need normals because we known this is an inscribed
//    icosahedron so the normals are the same as for a sphere.
//
static void CreateIcosahedron()
{
   unsigned int verts, faces;
   const int Faces[] =
       {
           2, 1, 0, 3, 2, 0, 4, 3, 0, 5, 4, 0, 1, 5, 0,
           11, 6, 7, 11, 7, 8, 11, 8, 9, 11, 9, 10, 11, 10, 6,
           1, 2, 6, 2, 3, 7, 3, 4, 8, 4, 5, 9, 5, 1, 10,
           2, 7, 6, 3, 8, 7, 4, 9, 8, 5, 10, 9, 1, 6, 10};
   const float Verts[] =
       {
           0.000, 0.000, 1.000,
           0.894, 0.000, 0.447,
           0.276, 0.851, 0.447,
           -0.724, 0.526, 0.447,
           -0.724, -0.526, 0.447,
           0.276, -0.851, 0.447,
           0.724, 0.526, -0.447,
           -0.276, 0.851, -0.447,
           -0.894, 0.000, -0.447,
           -0.276, -0.851, -0.447,
           0.724, -0.526, -0.447,
           0.000, 0.000, -1.000};
   N = sizeof(Faces) / sizeof(int);

   //  Position attribute
   glUseProgram(shader[mode]);
   int loc = glGetAttribLocation(shader[mode], "Position");

   // Create the VAO:
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   // Create the VBO for facet indices
   glGenBuffers(1, &faces);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces), Faces, GL_STATIC_DRAW);

   // Create the VBO for coordinates
   glGenBuffers(1, &verts);
   glBindBuffer(GL_ARRAY_BUFFER, verts);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
   // Enable Position as vertex array
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

   glUseProgram(0);
}

static void CreatePoint()
{
   unsigned int verts;

   const float Verts[] =
   {
      0,0,0
   };

   // Create the VAO:
   glGenVertexArrays(1, &pointvao);
   glBindVertexArray(pointvao);

   // Create the VBO for coordinates
   glGenBuffers(1, &verts);
   glBindBuffer(GL_ARRAY_BUFFER, verts);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);

   // Enable Position as vertex array
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
}

static void CreateRing()
{
   unsigned int verts, faces;
   const int Faces[] =
       {
           0,2,4,    4,2,6,    2,1,6,     6,1,5,      1,3,5,      5,3,7,      3,0,7,    7,0,4,  //1
           4,6,8,    8,6,10,    6,5,10,     10,5,9,      5,7,9,      9,7,11,      7,4,11,    11,4,8,  //2
           8,10,12,    12,10,14,    10,9,14,     14,9,13,      9,11,13,     13,11,15,      11,8,15,    15,8,12,  //3
           12,14,16,    16,14,18,    14,13,18,     18,13,17,      13,15,17,      17,15,19,      15,12,19,    19,12,16,  //4
           16,18,20,    20,18,22,    18,17,22,     22,17,21,      17,19,21,      21,19,23,      19,16,23,    23,16,20,  //5
           20,22,24,    24,22,26,    22,21,26,     26,21,25,      21,23,25,      25,23,27,      23,20,27,    27,20,24,  //6
           24,26,28,    28,26,30,    26,25,30,     30,25,29,      25,27,29,      29,27,31,      27,24,31,    31,24,28,  //7
           28,30,0,    0,30,2,    30,29,2,     2,29,1,      29,31,1,     1,31,3,      31,28,3,    3,28,0,  //8
           };
   const float Verts[] =
       {
          //1
           Cos(0), Sin(0), 0.000, //1 //arrays start at 0 *facepalm*
           0.4*Cos(0), 0.4*Sin(0), 0.000, //2
           0.7*Cos(0), 0.7*Sin(0), 0.3, //3
           0.7*Cos(0), 0.7*Sin(0),-0.3, //4

         //2
           Cos(45), Sin(45), 0.000, //5
           0.4*Cos(45), 0.4*Sin(45), 0.000, //6
           0.7*Cos(45), 0.7*Sin(45), 0.3, //7
           0.7*Cos(45), 0.7*Sin(45),-0.3, //8

         //3
           Cos(90), Sin(90), 0.000, //9
           0.4*Cos(90), 0.4*Sin(90), 0.000, //0
           0.7*Cos(90), 0.7*Sin(90), 0.3, //11
           0.7*Cos(90), 0.7*Sin(90),-0.3, //12

         //4
           Cos(135), Sin(135), 0.000, //13
           0.4*Cos(135), 0.4*Sin(135), 0.000, //14
           0.7*Cos(135), 0.7*Sin(135), 0.3, //15
           0.7*Cos(135), 0.7*Sin(135),-0.3, //16

         //5
           Cos(180), Sin(180), 0.000, //17
           0.4*Cos(180), 0.4*Sin(180), 0.000, //18
           0.7*Cos(180), 0.7*Sin(180), 0.3, //19
           0.7*Cos(180), 0.7*Sin(180),-0.3, //20
           
         //6
           Cos(225), Sin(225), 0.000, //21
           0.4*Cos(225), 0.4*Sin(225), 0.000, //22
           0.7*Cos(225), 0.7*Sin(225), 0.3, //23
           0.7*Cos(225), 0.7*Sin(225),-0.3, //24

         //7
           Cos(270), Sin(270), 0.000, //25
           0.4*Cos(270), 0.4*Sin(270), 0.000, //26
           0.7*Cos(270), 0.7*Sin(270), 0.3, //27
           0.7*Cos(270), 0.7*Sin(270),-0.3, //28

         //8
           Cos(315), Sin(315), 0.000, //29
           0.4*Cos(315), 0.4*Sin(315), 0.000, //30
           0.7*Cos(315), 0.7*Sin(315), 0.3, //31
           0.7*Cos(315), 0.7*Sin(315),-0.3, //32
           };
   RingN = sizeof(Faces) / sizeof(int);

   //  Position attribute
   glUseProgram(ringshader[mode]);
   int loc = glGetAttribLocation(ringshader[mode], "Position");

   // Create the VAO:
   glGenVertexArrays(1, &ringvao);
   glBindVertexArray(ringvao);

   // Create the VBO for facet indices
   glGenBuffers(1, &faces);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces), Faces, GL_STATIC_DRAW);

   // Create the VBO for coordinates
   glGenBuffers(1, &verts);
   glBindBuffer(GL_ARRAY_BUFFER, verts);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
   // Enable Position as vertex array
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

   glUseProgram(0);
}
//
//  Main program with GLFW event loop
//
int main(int argc, char *argv[])
{
   //  Initialize GLFW
   GLFWwindow *window = InitWindow("Andrew Hack HW9", 0, 1920, 1000, &reshape, &key);
   oofshader = CreateShaderProgGeom("ring.vert","ring.geom","ring.frag");
   //  Shader program
   CreateShaderProgTess(shader);
   CreateIcosahedron();
   CreatePoint();
   CreateRing();

   //  Event loop
   ErrCheck("init");
   while (!glfwWindowShouldClose(window))
   {
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
