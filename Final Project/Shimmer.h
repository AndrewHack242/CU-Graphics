#pragma once

#include "Object.h"

class Shimmer : public Object
{
public:
    Shimmer(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    unsigned int vao;
    int N;
};