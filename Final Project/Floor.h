#pragma once

#include "Object.h"

class Floor : public Object
{
public:
    Floor(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, std::string tex, bool hasAlpha);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    unsigned int vao;
    int N;
};