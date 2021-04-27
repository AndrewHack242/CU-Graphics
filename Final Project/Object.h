#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <math.h>
#include <vector>
#include "CSCIx239.h"
#include "glm.h"
#include "TextureHandler.h"
#include "ShaderHandler.h"

glm::vec3 RotateY(glm::vec3 dis, float deg);
class Object
{
public:
    Object();
    Object(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

    glm::vec3 getPos() { return pos; }
    glm::vec3 getScale() { return s; }
    glm::vec3 getRot() { return rot; }

    void draw();

    void updatePos(glm::vec3 newpos);

protected:
    virtual void drawObject();
    virtual void VAOInit();

    std::vector<unsigned int> textures;
    glm::vec3 pos, s, rot;
};

#endif