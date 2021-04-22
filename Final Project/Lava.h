#pragma once

#include "Object.h"

class Lava : public Object
{
public:
    Lava(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    unsigned int vao;
    int N;
};