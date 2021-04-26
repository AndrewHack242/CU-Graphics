#include "Pillar.h"


void Pillar::VAOInit()
{
     float w = 0.5;
   unsigned int verts, faces;
           const int Faces[] =
       {
           0,2,1, 3,2,0,
           8,9,10, 11,8,10,
           4,6,5, 7,6,4,
           12,13,14, 15,12,14,
           };
   const float Verts[] =
       {
          // X  Y  Z  W    R G B A   s t
            //  Face
            +w,+1,+w,+1,   1,1,1,1,  5,3, //0
            +w,-1,+w,+1,   1,1,1,1,  0,3, //1

            +w,-1,-w,+1,   1,1,1,1,  5,0, //2
            +w,+1,-w,+1,   1,1,1,1,  0,0, //3

            -w,+1,-w,+1,   1,1,1,1,  5,3, //4
            -w,-1,-w,+1,   1,1,1,1,  0,3, //5   

            -w,-1,+w,+1,   1,1,1,1,  5,0, //6
            -w,+1,+w,+1,   1,1,1,1,  0,0, //7

            

            +w,-1,-w,+1,   1,1,1,1,  0,0, //8
            +w,+1,-w,+1,   1,1,1,1,  5,0, //9

            -w,+1,-w,+1,   1,1,1,1,  0,3, //10
            -w,-1,-w,+1,   1,1,1,1,  5,3, //11

            -w,-1,+w,+1,   1,1,1,1,  0,0, //12 -6
            -w,+1,+w,+1,   1,1,1,1,  5,0, //13

            +w,+1,+w,+1,   1,1,1,1,  0,3, //14 -0
            +w,-1,+w,+1,   1,1,1,1,  5,3, //15
           };
   N = sizeof(Faces) / sizeof(int);

   //  Position attribute
   /* unsigned int shader =  */ShaderHandler::useShader("pillar");

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
    //glEnableVertexAttribArray(1); // Normal
    //glEnableVertexAttribArray(2); // Color
    glEnableVertexAttribArray(3); // Textures
    
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, 40, (void *)0);  // Vertex
    //glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
    //glVertexAttribPointer(2, 4, GL_FLOAT, 0, 40, (void *)16); // Color
    glVertexAttribPointer(3, 2, GL_FLOAT, 0, 40, (void *)32); // Textures

   ShaderHandler::disableShaders();
}

Pillar::Pillar(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot) : Object(pos, scale, rot)
{ //TODO: add texture
    textures.push_back(TextureHandler::LoadTexture("Textures/stone.bmp",false)); //load the texture for this Pillar
    ShaderHandler::LoadTesShader("pillar","Shaders/pillar.vert","Shaders/pillar.tesc","Shaders/pillar.tese","Shaders/pillar.geom","Shaders/pillar.frag");
    VAOInit();
}

void Pillar::drawObject()
{
    ShaderHandler::useShader("pillar");
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,textures[0]);

    glPatchParameteri(GL_PATCH_VERTICES, 3);
    
    //  Bind VAO and render
   glBindVertexArray(vao);
   glDrawElements(GL_PATCHES, N, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
    ShaderHandler::disableShaders();
}