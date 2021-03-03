/*
 *  Image processing
 *  Demonstrates post-processing of an image
 *
 *  Key bindings:
 *  m          Toggle shader
 *  o          Change objects
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx239.h"
int tex;
int mode=3;    //  Shader
int N=1;       //  Number of passes
int th=0,ph=0; //  View angles
int fov=57;    //  Field of view (for perspective)
float asp=1;   //  Aspect ratio
float dim=3;   //  Size of world
int obj;       //  Cruiser object
int toon;      //  Toon shader
unsigned int depthbuf[4];  //  Depth buffer
unsigned int img[5];      //  Image textures
unsigned int framebuf[5]; //  Frame buffers
#define MODE 4
int shader[MODE] = {0};   //  Shader programs
const char* text[] = {"No Shader","Anti-Aliasing (MSAA) w/ copy","Anti-Aliasing (SSAA)","MSAA + SSAA"};

//
//  Refresh display
//
void display(GLFWwindow* window)
{
   int width, height;
   glfwGetFramebufferSize(window,&width,&height);
   //  Send all output to frame buffer 0
   glViewport(0,0, width,height);
   glEnable(GL_MULTISAMPLE);
   if (mode == 2) //use framebuffer of 2x
   {
      glBindFramebuffer(GL_FRAMEBUFFER,framebuf[2]);
      glViewport(0,0, 2*width,2*height);
   }
   else if (mode == 1)
   {
      glBindFramebuffer(GL_FRAMEBUFFER,framebuf[3]);
   }
   else if(mode == 3)
   {
      glBindFramebuffer(GL_FRAMEBUFFER,framebuf[4]);
      glViewport(0,0,2*width,2*height);
   }
   else if (mode)
   {
      glBindFramebuffer(GL_FRAMEBUFFER,framebuf[0]);
   }
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Set projection and view
   Projection(fov,asp,dim);
   View(th,ph,fov,dim);


   //  
   Cube(-1.3,1.3,0 , 1,1,1 , 0,0 , tex);
   //  Teapot
   glUseProgram(toon);
   float zh = fmod(90*glfwGetTime(),360);
   float lpos[4] = {2*Cos(zh),2,2*Sin(zh),1};
   glLightfv(GL_LIGHT0,GL_POSITION,lpos);
   Teapot(1,1,0 , 0.5 , 90,0 , 4,0);
   glUseProgram(0);
   //  Icosahedron
   Icosahedron(-1,-1,0,0.7 , 0,0 , 0);
   //  Cruiser
   glPushMatrix();
   glColor3f(1,1,1);
   glTranslated(1,-1,0);
   glScaled(0.5,0.5,0.5);
   glCallList(obj);
   glPopMatrix();

   //  Draw axes using fixed pipeline (white)
   if(mode == 2 || mode == 3)
   {
      glLineWidth(2);
   }
   else
      glLineWidth(1);
   Axes(2);

   //  Ping-Pong between framebuffers
   if (mode)
   {
      //  Enable shader
      glUseProgram(shader[mode]);
      //  Set screen resolution uniforms
      int id,width,height;
      glfwGetWindowSize(window,&width,&height);
      id = glGetUniformLocation(shader[mode],"dX");
      glUniform1f(id,1.0/width);
      id = glGetUniformLocation(shader[mode],"dY");
      glUniform1f(id,1.0/height);
      //  Identity projection
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      //  Disable depth test & Enable textures
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_TEXTURE_2D);
      //  Copy entire screen
      for (int i=0;i<N;i++)
      {
         //  Output to alternate framebuffers
         //  Final output is to screen
         if(mode == 2 || mode == 1 || mode == 3)
            glBindFramebuffer(GL_FRAMEBUFFER,0);
         else
            glBindFramebuffer(GL_FRAMEBUFFER,i==N-1?0:framebuf[(i+1)%2]);
         //  Clear the screen
         glClear(GL_COLOR_BUFFER_BIT);
         //  Input image is from the last framebuffer
         if(mode == 2)
            glBindTexture(GL_TEXTURE_2D,img[2]);
         else if (mode == 1)
         {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuf[3]);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuf[0]);
            glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D,img[0]);
            glBindFramebuffer(GL_FRAMEBUFFER,0);
         }
         else if (mode == 3)
         {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuf[4]);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuf[2]);
            glBlitFramebuffer(0, 0, 2*width, 2*height, 0, 0, 2*width, 2*height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D,img[2]);
            glBindFramebuffer(GL_FRAMEBUFFER,0);
         }
         else
            glBindTexture(GL_TEXTURE_2D,img[i%2]);
         //  Redraw the screen
         glBegin(GL_QUADS);
         glTexCoord2f(0,0); glVertex2f(-1,-1);
         glTexCoord2f(0,1); glVertex2f(-1,+1);
         glTexCoord2f(1,1); glVertex2f(+1,+1);
         glTexCoord2f(1,0); glVertex2f(+1,-1);
         glEnd();
      }
      //  Disable textures and shaders
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_MULTISAMPLE);
      glUseProgram(0);
   }

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

   //  Check for shift
   int shift = (mods & GLFW_MOD_SHIFT);

   //  Exit on ESC
   if (key == GLFW_KEY_ESCAPE)
     glfwSetWindowShouldClose(window,1);
   //  Switch shaders
   else if (key==GLFW_KEY_M)
   {
      mode = shift ? (mode+MODE-1)%MODE : (mode+1)%MODE;
      if(mode == 2)
         N = 1;
   }
   //  Number of passes
   else if ((key==GLFW_KEY_KP_SUBTRACT || key==GLFW_KEY_MINUS) && N>1)
   {
      N --;
      if(mode == 2)
         N = 1;
   }
   else if (key==GLFW_KEY_KP_ADD || key==GLFW_KEY_EQUAL)
   {
      N++;
      if(mode == 2)
         N = 1;
   }
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
   else if(key == '1')
      mode = 0;
   else if(key == '2')
      mode = 1;
   else if(key == '3')
      mode = 2;
   else if(key == '4')
      mode = 3;
   //  Wrap angles
   th %= 360;
   ph %= 360;
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
   //
   //  Allocate a frame buffer
   //  Typically the same size as the screen (W,H) but can be larger or smaller
   //
   //  Delete old frame buffer, depth buffer and texture
   if (depthbuf[0])
   {
      glDeleteRenderbuffers(4,depthbuf);
      glDeleteTextures(5,img);
      glDeleteFramebuffers(5,framebuf);
   }
   //  Allocate two textures, two frame buffer objects and a depth buffer
   glGenFramebuffers(5,framebuf);   
   glGenTextures(5,img);
   glGenRenderbuffers(4,depthbuf);   
   //  Allocate and size texture
   for (int k=0;k<2;k++)
   {
      glBindTexture(GL_TEXTURE_2D,img[k]);
      glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
      //  Bind frame buffer to texture
      glBindFramebuffer(GL_FRAMEBUFFER,framebuf[k]);
      glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,img[k],0);
      //  Bind depth buffer to frame buffer 0
      if (k==0)
      {
         glBindRenderbuffer(GL_RENDERBUFFER,depthbuf[0]);
         glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,width,height);
         glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,depthbuf[0]);
      }
   }

   //SSAA
   glBindTexture(GL_TEXTURE_2D,img[2]);
   glTexImage2D(GL_TEXTURE_2D,0,3,width*2,height*2,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
   //  Bind frame buffer to texture
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf[2]);
   glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,img[2],0);
   //  Bind depth buffer to frame buffer 0
   glBindRenderbuffer(GL_RENDERBUFFER,depthbuf[1]);
   glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,width*2,height*2);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,depthbuf[1]);
   //  Switch back to regular display buffer
   glBindFramebuffer(GL_FRAMEBUFFER,0);

   //MSAA
   glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,img[3]);
   glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4, GL_RGB, width, height, GL_TRUE);

   //  Bind frame buffer to texture
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf[3]);
   glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE,img[3],0);
   //  Bind depth buffer to frame buffer 0
   glBindRenderbuffer(GL_RENDERBUFFER,depthbuf[2]);
   glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4,GL_DEPTH24_STENCIL8,width,height);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,depthbuf[2]);

   if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
   {
      printf("BAD\n");
   }

   //MSAA x SSAA
   glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,img[4]);
   glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4, GL_RGB, width*2, height*2, GL_TRUE);

   //  Bind frame buffer to texture
   glBindFramebuffer(GL_FRAMEBUFFER,framebuf[4]);
   glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE,img[4],0);
   //  Bind depth buffer to frame buffer 0
   glBindRenderbuffer(GL_RENDERBUFFER,depthbuf[3]);
   glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4,GL_DEPTH24_STENCIL8,width*2,height*2);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,depthbuf[3]);

   if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
   {
      printf("BAD\n");
   }
   

   //  Switch back to regular display buffer
   glBindFramebuffer(GL_FRAMEBUFFER,0);

   ErrCheck("Framebuffer");
}

//
//  Main program with GLFW event loop
//
int main(int argc,char* argv[])
{
   //  Initialize GLFW
   glfwWindowHint(GLFW_SAMPLES, 4);
   GLFWwindow* window = InitWindow("Image Processing",1,600,600,&reshape,&key);

   //  Load shaders
   shader[1] = CreateShaderProg(NULL,"shaders/copy.frag"); //MSAA
   shader[2] = CreateShaderProg(NULL,"shaders/test.frag"); //SSAA
   shader[3] = CreateShaderProg(NULL,"shaders/test.frag"); //BOTH
   
   //  Toon shader for teapot
   toon = CreateShaderProg("shaders/toon.vert","shaders/toon.frag");
   //  Load object
   obj = LoadOBJ("cruiser.obj");

   tex = LoadTexBMP32("cubetex.bmp", false);

   //  Event loop
   ErrCheck("init");
   while(!glfwWindowShouldClose(window))
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
