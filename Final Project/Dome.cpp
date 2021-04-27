#include "Dome.h"


void Dome::VAOInit()
{
     float w = 1;
   unsigned int verts, faces;
           const int Faces[] =
       {
           0,1,4, 1,2,4, 2,3,4, 3,0,4

           };
   const float Verts[] =
       {
          // X  Y  Z  W    R G B A   s t
            //  Face

            +w, 0,-w,+1,   1,1,1,1,  0.5f*s.x*3,0, //0
            -w, 0,-w,+1,   1,1,1,1,  0,0.5f*s.z*3, //1
            -w, 0,+w,+1,   1,1,1,1,  0.5f* s.x*3,1*s.z*3, //2 fix the textures
            +w, 0,+w,+1,   1,1,1,1,  1*s.x*3,0.5f*s.z*3, //3

             0,+1, 0,+1,   1,1,1,1,  0.5f*s.x*3,0.5f *s.z*3, //4
           };
   N = sizeof(Faces) / sizeof(int);

   //  Position attribute
   ShaderHandler::useShader("Dome");

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
   

    glEnableVertexAttribArray(0); // Vertex
    glEnableVertexAttribArray(3); // Textures
    
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, 40, (void *)0);  // Vertex
    glVertexAttribPointer(3, 2, GL_FLOAT, 0, 40, (void *)32); // Textures

   ShaderHandler::disableShaders();

   unsigned int verts2, faces2;
           const int Faces2[] =
       {
           0,1,2, 1,3,2 
           };
   const float Verts2[] =
       {
          //  X  Y  Z  W   Nx Ny Nz   R G B A   s t
            //  Face
            +1, 0,+1,+1,   0,-1, 0,   1,1,1,1,  0,0, //0
            -1, 0,+1,+1,   0,-1, 0,   1,1,1,1,  s.x,0, //1
            +1, 0,-1,+1,   0,-1, 0,   1,1,1,1,  0,s.z, //2
            -1, 0,-1,+1,   0,-1, 0,   1,1,1,1,  s.x,s.z, //3
           };
   N2 = sizeof(Faces2) / sizeof(int);

   //  Position attribute
   /* unsigned int shader =  */ShaderHandler::useShader("Domegl4");

   // Create the VAO:
   glGenVertexArrays(1, &vao2);
   glBindVertexArray(vao2);

   // Create the VBO for facet indices
   glGenBuffers(1, &faces2);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces2);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces2), Faces2, GL_STATIC_DRAW);

   // Create the VBO for coordinates
   glGenBuffers(1, &verts2);
   glBindBuffer(GL_ARRAY_BUFFER, verts2);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Verts2), Verts2, GL_STATIC_DRAW);
   

    glEnableVertexAttribArray(0); // Vertex
    glEnableVertexAttribArray(1); // Normal
    glEnableVertexAttribArray(2); // Color
    glEnableVertexAttribArray(3); // Textures
    
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, 52, (void *)0);  // Vertex
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
    glVertexAttribPointer(2, 4, GL_FLOAT, 0, 52, (void *)28); // Color
    glVertexAttribPointer(3, 2, GL_FLOAT, 0, 52, (void *)44); // Textures

   ShaderHandler::disableShaders();
}

Dome::Dome(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot) : Object(pos, scale, rot)
{
    textures.push_back(TextureHandler::LoadTexture("Textures/stone.bmp",false)); //load the texture for this Dome
    textures.push_back(TextureHandler::LoadTexture("Textures/diorite.bmp",false)); //load the texture for this Dome
    ShaderHandler::LoadTesShader("Dome","Shaders/Dome.vert","Shaders/Dome.tesc","Shaders/Dome.tese","Shaders/Dome.geom","Shaders/Dome.frag");
    ShaderHandler::LoadShader("Domegl4","Shaders/gl4.vert","Shaders/Domegl4.frag");
    VAOInit();
}

void Dome::drawObject()
{
    ShaderHandler::useShader("Dome");
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,textures[1]);

    glPatchParameteri(GL_PATCH_VERTICES, 3);
    
    //  Bind VAO and render
   glBindVertexArray(vao);
   glDrawElements(GL_PATCHES, N, GL_UNSIGNED_INT, 0);

   glBindTexture(GL_TEXTURE_2D,textures[0]);
   glBindVertexArray(vao2);
   ShaderHandler::useShader("Domegl4");
   glDrawElements(GL_TRIANGLES, N, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
    ShaderHandler::disableShaders();
    ErrCheck("Dome");
}