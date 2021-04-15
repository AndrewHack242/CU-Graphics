#pragma once

#include "Object.h"

class Surface : public Object
{
public:
    Surface(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, std::string tex, bool hasAlpha);

protected:
    virtual void drawObject();
    virtual void VBOInit();
};