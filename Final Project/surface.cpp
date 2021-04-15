#include "surface.h"

//
//  face Data
//  TODO: move to VBOHandler
unsigned int face_vbo = 0;
const int face_size = 6;
const float face_data[] = // Vertex data
{
//  X  Y  Z  W   Nx Ny Nz    R G B A   s t
   //  Face
   +1,+1, 0,+1,   0, 0,+1,   1,1,1,1,  1,1,
   -1,+1, 0,+1,   0, 0,+1,   1,1,1,1,  0,1,
   +1,-1, 0,+1,   0, 0,+1,   1,1,1,1,  1,0,
   -1,+1, 0,+1,   0, 0,+1,   1,1,1,1,  0,1,
   +1,-1, 0,+1,   0, 0,+1,   1,1,1,1,  1,0,
   -1,-1, 0,+1,   0, 0,+1,   1,1,1,1,  0,0,
   };


void Surface::VBOInit()
{
    //  Get buffer name
    glGenBuffers(1, &face_vbo);
    //  Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, face_vbo);
    //  Copy icosahedron to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(face_data), face_data, GL_STATIC_DRAW);
    //  Release VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Surface::Surface(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, std::string tex, bool hasAlpha) : Object(pos, scale, rot)
{
    textures.push_back(TextureHandler::LoadTexture(tex,hasAlpha)); //load the texture for this surface
    VBOInit();
    ShaderHandler::LoadShader("gl4","Shaders/gl4.vert","Shaders/gl4.frag");
}

void Surface::drawObject()
{
    ShaderHandler::useShader("gl4");
    glEnable(GL_TEXTURE_2D);

    glBindBuffer(GL_ARRAY_BUFFER, face_vbo);

    glBindTexture(GL_TEXTURE_2D,textures[0]);
    
    //  Set vertex attribute pointers
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, 52, (void *)0);  // Vertex
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
    glVertexAttribPointer(2, 4, GL_FLOAT, 0, 52, (void *)28); // Color
    glVertexAttribPointer(3, 2, GL_FLOAT, 0, 52, (void *)44); // Textures

    //  Enable vertex arrays
    glEnableVertexAttribArray(0); // Vertex
    glEnableVertexAttribArray(1); // Normal
    glEnableVertexAttribArray(2); // Color
    glEnableVertexAttribArray(3); // Textures

    // Draw the face
    glDrawArrays(GL_TRIANGLES, 0, face_size);

    glBindBuffer(GL_ARRAY_BUFFER, face_vbo);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
    ShaderHandler::disableShaders();
}