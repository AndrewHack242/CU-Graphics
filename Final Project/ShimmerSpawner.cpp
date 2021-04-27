#include "ShimmerSpawner.h"

void ShimmerSpawner::VAOInit()
{
     
}

void ShimmerSpawner::InitPart(void)
{
    for (int i = 0; i < SPCount; i++)
    {
        float rx,ry,rz;
        rx = ((rand() %((int)s.x * 2000)) / 1000.0) - s.x; //gets a point somewhere in the ShimmerSpawner pool
        ry = -0.3;
        rz = ((rand() %((int)s.z * 2000)) / 1000.0) - s.z;

        glm::vec3 tmp = glm::vec3(rx,ry,rz);
        tmp = RotateY(tmp, rot.y);
        sp[i] = ShimmerParticle(pos + tmp, glm::vec3(1), glm::vec3(0), glm::vec3(0,1,0), glm::vec3(0,0,0));
    }
}

void ShimmerSpawner::DrawPart(void)
{
    for (int i = 0; i < SPCount; i++)
    {
        if(sp[i].checkLife())
        {
            float rx,ry,rz;
            rx = ((rand() %((int)s.x * 2000)) / 1000.0) - s.x; //gets a point somewhere in the ShimmerSpawner pool
            ry = -0.3;
            rz = ((rand() %((int)s.z * 2000)) / 1000.0) - s.z;

            glm::vec3 tmp = glm::vec3(rx,ry,rz);
            tmp = RotateY(tmp, rot.y);
            sp[i].respawn(pos + tmp);
        }
        sp[i].draw();
    }
}

ShimmerSpawner::ShimmerSpawner(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot) : Object(pos, scale, rot)
{ 
    SPCount = s.x * s.z * 20;
    sp = new ShimmerParticle[SPCount];
    InitPart();
    VAOInit();
}
ShimmerSpawner::~ShimmerSpawner()
{
    delete[] sp;
}

void ShimmerSpawner::drawObject()
{
    
    DrawPart();
    glBindTexture(GL_TEXTURE_2D, 0);
    ErrCheck("shimmer particles");

    glDisable(GL_TEXTURE_2D);
    ShaderHandler::disableShaders();
}