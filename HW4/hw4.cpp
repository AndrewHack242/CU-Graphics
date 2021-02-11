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
#include "CSCIx239.h"
int mode=0;    //  Shader
int move=1;    //  Moving light
int zh=0;      //  Light position
int th=0,ph=0; //  View angles
int fov=57;    //  Field of view (for perspective)
int tex=0;     //  Texture
int obj=0;     //  Object
float YL=1.5;  //  Light elevation
float asp=1;   //  Aspect ratio
float dim=4;   //  Size of world
int shader[] = {0,0};  //  Shaders
const char* text[] = {"OpenGL 2","OpenGL 4"};

//
//  Cube Data
//
unsigned int cube_vbo=0;
const int cube_size=36;
const float cube_data[] =  // Vertex data
{
//  X  Y  Z  W   Nx Ny Nz    R G B A   s t
   //  Front
   +1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  1,1,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  1,0,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  1,0,
   -1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  0,0,
   //  Back                        
   -1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  1,0,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  1,1,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  1,1,
   +1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  0,1,
   //  Right                       
   +1,+1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,1,
   +1,-1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,0,
   //  Left                        
   -1,+1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,1,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,0,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,0,
   -1,-1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,0,
   //  Top                         
   +1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  1,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  0,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  0,0,
   -1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  0,1,
   //  Bottom                      
   -1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  0,0,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  0,1,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  0,1,
   +1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  1,1,
   };

//
//  Initialize cube VBO
//
void InitCube()
{
   //  Get buffer name
   glGenBuffers(1,&cube_vbo);
   //  Bind VBO
   glBindBuffer(GL_ARRAY_BUFFER,cube_vbo);
   //  Copy icosahedron to VBO
   glBufferData(GL_ARRAY_BUFFER,sizeof(cube_data),cube_data,GL_STATIC_DRAW);
   //  Release VBO
   glBindBuffer(GL_ARRAY_BUFFER,0);
}

//
//  Refresh display
//
void display(GLFWwindow* window)
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Eye position for perspective
   float Ex = -2*dim*Sin(th)*Cos(ph);
   float Ey = +2*dim        *Sin(ph);
   float Ez = +2*dim*Cos(th)*Cos(ph);

   //  Lighting parameters
   float global[]   = {0.1,0.1,0.1,1.0};
   float ambient[]  = {0.3,0.3,0.3,1.0};
   float diffuse[]  = {0.8,0.8,0.8,1.0};
   float specular[] = {1.0,1.0,1.0,1.0};
   float position[] = {3*Cos(zh),YL,3*Sin(zh),1.0};

   //  Draw light position as white ball using fixed pipeline
   glColor3f(1,1,1);
   View(th,ph,fov,dim);
   Sphere(position[0],position[1],position[2],0.1,0,8,0);

   //  Bind VBO
   glBindBuffer(GL_ARRAY_BUFFER,cube_vbo);
   //  Enable shader
   glUseProgram(shader[mode]);

   //  Set light property uniforms
   int id = glGetUniformLocation(shader[mode],"fov");
   glUniform1f(id,fov);
   id = glGetUniformLocation(shader[mode],"Global");
   glUniform4fv(id,1,global);
   id = glGetUniformLocation(shader[mode],"Ambient");
   glUniform4fv(id,1,ambient);
   id = glGetUniformLocation(shader[mode],"Diffuse");
   glUniform4fv(id,1,diffuse);
   id = glGetUniformLocation(shader[mode],"Specular");
   glUniform4fv(id,1,specular);
   id = glGetUniformLocation(shader[mode],"Position");
   glUniform4fv(id,1,position);

   //  OpenGL 2
   if (mode==0)
   {
      //  Set view
      glPushMatrix();
      glLoadIdentity();
      //  Perspective - set eye position
      if (fov)
         gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
      //  Orthogonal - set world orientation
      else
      {
         glRotatef(ph,1,0,0);
         glRotatef(th,0,1,0);
      }
      //  Set light position
      glLightfv(GL_LIGHT0,GL_POSITION,position);

      //  Set VBO pointers
      glVertexPointer(4,GL_FLOAT,52,(void*)0);
      glNormalPointer(GL_FLOAT,52,(void*)16);
      glColorPointer(4,GL_FLOAT,52,(void*)28);
      glTexCoordPointer(2,GL_FLOAT,52,(void*)44);
      //  Enable attribute pointers
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Draw the cube slightly offset
      glTranslated(0,0,0.5);
      glDrawArrays(GL_TRIANGLES,0,cube_size);

      //  Disable attribute pointers
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Undo transformations
      glPopMatrix();
   }
   //  OpenGL 4
   else
   {
      //  Create Projection matrix
      float proj[16];
      mat4identity(proj);
      if (fov)
         mat4perspective(proj , fov,asp,dim/16,16*dim);
      else
         mat4ortho(proj , -dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
      //  Create View matrix
      float view[16];
      mat4identity(view);
      if (fov)
         mat4lookAt(view , Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
      else
      {
         mat4rotate(view , ph,1,0,0);
         mat4rotate(view , th,0,1,0);
      }
      //  Create ModelView matrix
      float modelview[16];
      mat4copy(modelview , view);
      mat4translate(modelview , 0,0,0.5);
      //  Get Normal matrix
      float normal[9];
      mat4normalMatrix(modelview , normal);

      //  Set Projection, View, Modelview and Normal Matrix
      id = glGetUniformLocation(shader[mode],"ProjectionMatrix");
      glUniformMatrix4fv(id,1,0,proj);
      id = glGetUniformLocation(shader[mode],"ViewMatrix");
      glUniformMatrix4fv(id,1,0,view);
      id = glGetUniformLocation(shader[mode],"ModelViewMatrix");
      glUniformMatrix4fv(id,1,0,modelview);
      id = glGetUniformLocation(shader[mode],"NormalMatrix");
      glUniformMatrix3fv(id,1,0,normal);

      //  Set vertex attribute pointers
      glVertexAttribPointer(0,4,GL_FLOAT,0,52,(void*) 0); // Vertex
      glVertexAttribPointer(1,3,GL_FLOAT,0,52,(void*)16); // Normal
      glVertexAttribPointer(2,4,GL_FLOAT,0,52,(void*)28); // Color
      glVertexAttribPointer(3,2,GL_FLOAT,0,52,(void*)44); // Textures

      //  Enable vertex arrays
      glEnableVertexAttribArray(0); // Vertex
      glEnableVertexAttribArray(1); // Normal
      glEnableVertexAttribArray(2); // Color
      glEnableVertexAttribArray(3); // Textures

      // Draw the cube
      glDrawArrays(GL_TRIANGLES,0,cube_size);

      //  Disable vertex arrays
      glDisableVertexAttribArray(0); // Vertex
      glDisableVertexAttribArray(1); // Normal
      glDisableVertexAttribArray(2); // Color
      glDisableVertexAttribArray(3); // Textures
   }
   //  Release VBO
   glBindBuffer(GL_ARRAY_BUFFER,0);
   //  Fixed pipeline
   glUseProgram(0);

   //  Draw axes using fixed pipeline (white)
   Axes(2);

   //  Display parameters
   glColor3f(1,1,1);
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Projection=%s Mode=%s",th,ph,dim,fov>0?"Perpective":"Orthogonal",text[mode]);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glfwSwapBuffers(window);
}

//
//  Key pressed callback
//
void key(GLFWwindow* window,int key,int scancode,int action,int mods)
{
   //  Discard key releases (keeps PRESS and REPEAT)
   if (action==GLFW_RELEASE) return;

   //  Exit on ESC
   if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window,1);
   //  Reset view angle and location
   else if (key==GLFW_KEY_0)
      th = ph = 0;
   //  Switch shaders
   else if (key==GLFW_KEY_M)
      mode = 1-mode;
   //  Light movement
   else if (key==GLFW_KEY_S)
      move = 1-move;
   //  Light elevation
   else if (key==GLFW_KEY_KP_SUBTRACT || key==GLFW_KEY_MINUS)
      YL -= 0.05;
   else if (key==GLFW_KEY_KP_ADD || key==GLFW_KEY_EQUAL)
      YL += 0.05;
   // Move light
   else if (key==GLFW_KEY_RIGHT_BRACKET)
      zh += 1;
   else if (key==GLFW_KEY_LEFT_BRACKET)
      zh -= 1;
   //  Switch objects
   else if (key==GLFW_KEY_O)
      obj = 1-obj;
   //  Switch between perspective/orthogonal
   else if (key==GLFW_KEY_P)
      fov = fov ? 0 : 57;
   //  Increase/decrease asimuth
   else if (key==GLFW_KEY_RIGHT)
      th += 5;
   else if (key==GLFW_KEY_LEFT)
      th -= 5;
   //  Increase/decrease elevation
   else if (key==GLFW_KEY_UP)
      ph += 5;
   else if (key==GLFW_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key==GLFW_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key==GLFW_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Wrap angles
   th %= 360;
   ph %= 360;
   //  Update projection
   Projection(fov,asp,dim);
}

//
//  Window resized callback
//
void reshape(GLFWwindow* window,int width,int height)
{
   //  Get framebuffer dimensions (makes Apple work right)
   glfwGetFramebufferSize(window,&width,&height);
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Projection(fov,asp,dim);
}

//
//  Main program with GLFW event loop
//
int main(int argc,char* argv[])
{
   //  Initialize GLFW
   GLFWwindow* window = InitWindow("OpenGL Versions",1,600,600,&reshape,&key);

   //  Load shaders
   shader[0] = CreateShaderProg("gl2.vert","gl2.frag");
   shader[1] = CreateShaderProg("gl4.vert","gl4.frag");
   //  Load textures
   tex = LoadTexBMP("pi.bmp");
   //  Load cube into VBO
   InitCube();

   //  Event loop
   ErrCheck("init");
   while(!glfwWindowShouldClose(window))
   {
      //  Light animation
      if (move) zh = fmod(90*glfwGetTime(),360);
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
