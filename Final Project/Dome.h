#pragma once

#include "Object.h"

class Dome : public Object
{
public:
    Dome(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    unsigned int vao, vao2;
    int N, N2;
};