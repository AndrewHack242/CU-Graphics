#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <map>
#include <iostream>

#include "CSCIx239.h"
#include "glm.h"

namespace ShaderHandler
{
    unsigned int LoadShader(std::string name, std::string vert, std::string frag);
    unsigned int LoadGeomShader(std::string name, std::string vert, std::string geom, std::string frag);
    unsigned int LoadTesShader(std::string name, std::string vert, std::string tesc, std::string tese, std::string geom, std::string frag);

    void updateProjMatrix(glm::mat4 proj);
    void updateViewMatrix(glm::mat4 view);
    void updateModelMatrix(glm::mat4 model);
    void updateLightInfo(glm::vec4 global, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec4 position, glm::vec4 lightcolor);
    void updateFOV(float fov);
    void updateTime(float time);

    void updatePixMan(int W,int H,float dX,float dY);
    void updateScreenTex();
    unsigned int getScreenTex();

    unsigned int getShader(std::string name);
    unsigned int useShader(std::string name);
    void disableShaders();

}