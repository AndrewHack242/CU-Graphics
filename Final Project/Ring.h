#pragma once

#include "Object.h"

class Ring : public Object
{
public:
    Ring(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

protected:
    virtual void drawObject();
    virtual void VBOInit();
};