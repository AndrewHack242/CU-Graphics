#pragma once

#include "Object.h"
#include "LavaParticle.h"

#define PCount 5

class Lava : public Object
{
public:
    Lava(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    void InitPart(void);
    void DrawPart(void);

    unsigned int vao;
    int N;

    LavaParticle p[PCount];
};