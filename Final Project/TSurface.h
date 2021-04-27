#pragma once

#include "Object.h"

class TSurface : public Object
{
public:
    TSurface(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, std::string tex, bool hasAlpha);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    unsigned int vao;
    int N;
};