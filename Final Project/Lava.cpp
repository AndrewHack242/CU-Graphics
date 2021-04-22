#include "Lava.h"


void Lava::VAOInit()
{
     float w = 1;
   unsigned int verts, faces;
           const int Faces[] =
       {
           0,1,2, 3,0,2,
           2,4,3, 5,4,2,
           4,5,6, 7,4,6,
           6,0,7, 1,0,6,
           8,9,10, 8,10,11,
           12,14,13, 12,15,14
           };
   const float Verts[] =
       {
          // X  Y  Z  W    R G B A   s t
            //  Face
            +w,+1,+w,+1,   1,1,1,1,  1,1, //0
            +w,-1,+w,+1,   1,1,1,1,  0,1, //1
            +w,-1,-w,+1,   1,1,1,1,  1,0, //2
            +w,+1,-w,+1,   1,1,1,1,  0,0, //3
            -w,+1,-w,+1,   1,1,1,1,  1,1, //4
            -w,-1,-w,+1,   1,1,1,1,  0,1, //5
            -w,-1,+w,+1,   1,1,1,1,  1,0, //6
            -w,+1,+w,+1,   1,1,1,1,  0,0, //7

            +w,+1,+w,+1,   1,1,1,1,  1,1, //8
            +w,+1,-w,+1,   1,1,1,1,  0,1, //9
            -w,+1,-w,+1,   1,1,1,1,  1,0, //10
            -w,+1,+w,+1,   1,1,1,1,  0,0, //11

            +w,-1,+w,+1,   1,1,1,1,  1,1, //12
            +w,-1,-w,+1,   1,1,1,1,  0,1, //13
            -w,-1,-w,+1,   1,1,1,1,  1,0, //14
            -w,-1,+w,+1,   1,1,1,1,  0,0, //15


           };
   N = sizeof(Faces) / sizeof(int);

   //  Position attribute
   /* unsigned int shader =  */ShaderHandler::useShader("Lava");

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
    glEnableVertexAttribArray(2); // Color
    glEnableVertexAttribArray(3); // Textures
    
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, 40, (void *)0);  // Vertex
    //glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
    glVertexAttribPointer(2, 4, GL_FLOAT, 0, 40, (void *)16); // Color
    glVertexAttribPointer(3, 2, GL_FLOAT, 0, 40, (void *)32); // Textures
    
   ShaderHandler::disableShaders();
}

Lava::Lava(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot) : Object(pos, scale, rot)
{ 
    textures.push_back(TextureHandler::LoadTexture("Textures/crate.bmp",false)); //load the texture for this Lava
    ShaderHandler::LoadShader("Lava","Shaders/Lava.vert","Shaders/Lava.frag");
    VAOInit();
}

void Lava::drawObject()
{
    //std::cout<< "test" << std::endl;
    ShaderHandler::useShader("Lava");
    //std::cout<< "test" << std::endl;
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,textures[0]);

    //glPatchParameteri(GL_PATCH_VERTICES, 3);
    
    //  Bind VAO and render
   glBindVertexArray(vao);
   glDrawElements(GL_TRIANGLES, N, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
    ShaderHandler::disableShaders();
}