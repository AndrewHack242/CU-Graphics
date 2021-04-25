#include "LavaParticle.h"

void LavaParticle::VAOInit()
{
   unsigned int verts, faces;
           const int Faces[] =
       {
           0
           };
   const float Verts[] =
       {
          // X  Y  Z  W    R G B A  
            //  Face
            0,0,0,1,   1,1,0,1


           };
   N = sizeof(Faces) / sizeof(int);

   //  Position attribute
   /* unsigned int shader =  */ShaderHandler::useShader("LavaParticle");

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
    glEnableVertexAttribArray(2); // Color
    
    glVertexAttribPointer(0, 4, GL_FLOAT, 0, 16, (void *)0);  // Vertex
    glVertexAttribPointer(2, 4, GL_FLOAT, 0, 16, (void *)16); // Color

    glBindVertexArray(0);
    
   ShaderHandler::disableShaders();
}

LavaParticle::LavaParticle()
{

}

LavaParticle::LavaParticle(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, glm::vec3 initialv, glm::vec3 acceleration) : Object(pos, scale, rot)
{ 
    textures.push_back(TextureHandler::LoadTexture("Textures/particle.bmp",true));
    //ShaderHandler::LoadAttrShader("LavaParticle","Shaders/lavaparticle.vert","",Name);
    ShaderHandler::LoadShader("LavaParticle","Shaders/lavaparticle.vert","Shaders/lavaparticle.frag");
    vel = initialv;
    acc = acceleration;
    starttime = glfwGetTime();
    VAOInit();
}

void LavaParticle::drawObject()
{
    glPointSize(10);
    ErrCheck("particles0");
    //std::cout<< "test" << std::endl;
    ShaderHandler::useShader("LavaParticle");
    ErrCheck("particles0.5");
    ShaderHandler::updateParticle("LavaParticle", vel, acc,starttime);
    ErrCheck("particles1");
    
    //  Bind VAO and render
    glBindVertexArray(vao);
    ErrCheck("particles why");
    glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);
    ErrCheck("particles no you");
    glBindVertexArray(0);
    ErrCheck("particles fuck this");
    glBindTexture(GL_TEXTURE_2D, 0);
    ErrCheck("particles2");
    //glDisable(GL_TEXTURE_2D);
    ShaderHandler::disableShaders();
}