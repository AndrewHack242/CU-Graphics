#include "VBOHandler.h"

namespace VBOHandler
{
    namespace
    {
        std::map<std::string, unsigned int> textures; //holds all loaded textures so that they only need to be loaded once
    } // namespace

    unsigned int LoadVBO(std::string file, bool hasAlpha);

}