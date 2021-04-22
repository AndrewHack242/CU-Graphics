#pragma once

#include "Object.h"

class Pillar : public Object
{
public:
    Pillar(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    unsigned int vao;
    int N;
};