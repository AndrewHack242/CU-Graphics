#pragma once

#include "Object.h"

#define PCount 5

class LavaParticle : public Object
{
public:
    LavaParticle();
    LavaParticle(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, glm::vec3 initialv, glm::vec3 acceleration);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    glm::vec3 vel, acc;
    float starttime;
    unsigned int vao;
    int N;
};