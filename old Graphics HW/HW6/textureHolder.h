#pragma once
#include "AndrewsHelpers.h"

//singleton to hold textures so the don't need to be loaded multiple times
class textureHolder
{
    unsigned int texmetal, texconcrete, texcube, texfloor, texwood, texedge;

    // Private constructor so that no objects can be created.
    textureHolder();

public:
    static textureHolder *getInstance();

    void init();

    unsigned int getMetal();
    unsigned int getConcrete();
    unsigned int getCube();
    unsigned int getFloor();
    unsigned int getWood();
    unsigned int getEdge();
};