#include "Floor.h"


void Floor::VAOInit()
{
    unsigned int verts, faces;
           const int Faces[] =
       {
           0,2,1, 1,2,3 
           };
   const float Verts[] =
       {
          //  X  Y  Z  W   Nx Ny Nz    R G B A   s t
            //  Face
            +1, 0,+1,+1,   0, 0,+1,   1,1,1,1,  1,1, //0
            -1, 0,+1,+1,   0, 0,+1,   1,1,1,1,  0,1, //1
            +1, 0,-1,+1,   0, 0,+1,   1,1,1,1,  1,0, //2
            -1, 0,-1,+1,   0, 0,+1,   1,1,1,1,  0,0, //3
           };
   N = sizeof(Faces) / sizeof(int);

   //  Position attribute
   /* unsigned int shader =  */ShaderHandler::useShader("gl4");

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
    glEnableVertexAttribArray(1); // Normal
    glEnableVertexAttribArray(2); // Color
    glEnableVertexAttribArray(3); // Textures
    
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, 52, (void *)0);  // Vertex
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
    glVertexAttribPointer(2, 4, GL_FLOAT, 0, 52, (void *)28); // Color
    glVertexAttribPointer(3, 2, GL_FLOAT, 0, 52, (void *)44); // Textures

    ErrCheck("VBOInit:5");
   ShaderHandler::disableShaders();
}

Floor::Floor(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, std::string tex, bool hasAlpha) : Object(pos, scale, rot)
{
    textures.push_back(TextureHandler::LoadTexture(tex,hasAlpha)); //load the texture for this Floor
    ShaderHandler::LoadShader("gl4","Shaders/gl4.vert","Shaders/gl4.frag");
    VAOInit();
}

void Floor::drawObject()
{
    ShaderHandler::useShader("gl4");
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,textures[0]);
    
    //  Bind VAO and render
   glBindVertexArray(vao);
   glDrawElements(GL_TRIANGLES, N, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
    ShaderHandler::disableShaders();
}