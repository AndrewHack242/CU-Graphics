#pragma once
#include "CSCIx239.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <map>
#include <string>

namespace VBOHandler{
    unsigned int LoadVBO(std::string file, bool hasAlpha);
}