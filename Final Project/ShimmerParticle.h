#pragma once

#include "Object.h"

class ShimmerParticle : public Object
{
public:
    ShimmerParticle();
    ShimmerParticle(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, glm::vec3 initialv, glm::vec3 acceleration);

    bool checkLife();
    void respawn(glm::vec3 newpos);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    glm::vec3 vel, acc;
    float starttime;
    float timemod;
    unsigned int vao;
    int N;
};