#include "textureHolder.h"

static textureHolder *instance = nullptr;

void textureHolder::init()
{
    texfloor = LoadTexBMP32("textures/concrete_modular_ceiling1.bmp",false);
    texconcrete = LoadTexBMP32("textures/concrete_modular_wall5.bmp", true);
    texcube = LoadTexBMP32("textures/metalwall1_med.bmp", false);
    texmetal = LoadTexBMP32("textures/metal_detail_01.bmp", true);
    texwood = LoadTexBMP32("textures/woodpanel_002.bmp", true);
    texedge = LoadTexBMP32("textures/underground_wall_metal004d.bmp", true);
}

textureHolder::textureHolder()
{

}

textureHolder* textureHolder::getInstance()
    {
        if (instance == nullptr)
            instance = new textureHolder();
        return instance;
    }

unsigned int textureHolder::getMetal()
{
    return texmetal;
}

unsigned int textureHolder::getConcrete()
{
    return texconcrete;
}

unsigned int textureHolder::getCube()
{
    return texcube;
}

unsigned int textureHolder::getFloor()
{
    return texfloor;
}

unsigned int textureHolder::getWood()
{
    return texwood;
}

unsigned int textureHolder::getEdge()
{
    return texedge;
}