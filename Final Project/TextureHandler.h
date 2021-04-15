#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <map>
#include <string>

#include "CSCIx239.h"
#include "glm.h"

namespace TextureHandler{
    unsigned int LoadTexture(std::string file, bool hasAlpha);
    unsigned int LoadBMPTexture(const char* file);
    unsigned int LoadBMPTexture32(const char* file);
}