#pragma once

#include "Object.h"
#include "ShimmerParticle.h"


class ShimmerSpawner : public Object
{
public:
    ShimmerSpawner(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);
    ~ShimmerSpawner();

protected:
    virtual void drawObject();
    virtual void VAOInit();

    void InitPart(void);
    void DrawPart(void);

    unsigned int vao;
    int N;

    int PCount;
    int SPCount;
    
    ShimmerParticle *sp;
};