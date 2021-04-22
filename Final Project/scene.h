#pragma once

#include "CSCIx239.h"
#include "glm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Object.h"
//#include "Camera.h"

#include "surface.h"
#include "Ring.h"
#include "Pillar.h"
#include "Lava.h"
#include "Floor.h"

class Scene
{
public:
    Scene();
    Scene(std::string worldfile);

    void loadWorldFile(std::string worldfile);
    glm::vec3 GetVectorFromString(std::string str);
    void LoadObject(std::string objLine);
    void reload();

    void drawScene();

    void rotateCam(glm::vec3 rot);

    void moveCam(glm::vec3 mov);

protected:
    //Camera camera;
    std::string filename;
    std::vector<Object *> objects;
};