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
            0,0,0,1,   0.988,0.973,0.482,1


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
    float vx,vy,vz;
    vx = ((rand() % 1000)/ 2000.0) - 0.25;
    vy = ((rand() % 1000)/ 4000.0) - 0.125;
    vz = ((rand() % 1000)/ 2000.0) - 0.25;
    veladj = glm::vec3(vx,vy,vz);
    vel = initialv + veladj;
    acc = acceleration;
    starttime = glfwGetTime();
    timemod = (rand() % 2000) / 1000.0;
    VAOInit();
}

void LavaParticle::respawn(glm::vec3 newpos)
{
    updatePos(newpos);
    starttime = glfwGetTime();
    float vx,vy,vz;
    vx = ((rand() % 1000)/ 2000.0) - 0.25;
    vy = ((rand() % 1000)/ 4000.0) - 0.125;
    vz = ((rand() % 1000)/ 2000.0) - 0.25;
    vel = vel - veladj + glm::vec3(vx,vy,vz);
    veladj = glm::vec3(vx,vy,vz);
    timemod = (rand() % 2000) / 1000.0;
}

bool LavaParticle::checkLife()
{
    if((glfwGetTime() - starttime) >= (3 + timemod))
    {
        return true;
    }
    return false;
}

void LavaParticle::drawObject()
{
    glPointSize(4);
    //std::cout<< "test" << std::endl;
    ShaderHandler::useShader("LavaParticle");
    ShaderHandler::updateParticle("LavaParticle", vel, acc,starttime);
    
    //  Bind VAO and render
    glBindVertexArray(vao);
    glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_TEXTURE_2D);
    ShaderHandler::disableShaders();
}