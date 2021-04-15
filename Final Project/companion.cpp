#include "companion.h"

//
//  Cube Data
//
unsigned int cube_vbo = 0;
const int cube_size = 36;
const float cube_data[] = // Vertex data
{
//  X  Y  Z  W   Nx Ny Nz    R G B A   s t
   //  Front
   +1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  1,1,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  1,0,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  1,0,
   -1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  0,0,
   //  Back                        
   -1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  1,0,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  1,1,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  1,1,
   +1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  0,1,
   //  Right                       
   +1,+1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,1,
   +1,-1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,0,
   //  Left                        
   -1,+1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,1,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,0,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,0,
   -1,-1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,0,
   //  Top                         
   +1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  1,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  0,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  0,0,
   -1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  0,1,
   //  Bottom                      
   -1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  0,0,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  0,1,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  0,1,
   +1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  1,1,
   };
//
//  Initialize cube VBO
//
void InitCube()
{
    //  Get buffer name
    glGenBuffers(1, &cube_vbo);
    //  Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
    //  Copy icosahedron to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_data), cube_data, GL_STATIC_DRAW);
    //  Release VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


unsigned int side_vbo = 0;
const int side_size = 60;
const float side_data[] = // Vertex data
{
//Side panels
        //edge
        +0.20, +1.06, +1.01, +1,    0, 1, 1,    1, 1, 1, 1,     0.9, 0.4,
        -0.20, +1.06, +1.01, +1,    0, 1, 1,    1, 1, 1, 1,     0.1, 0.4,
        -0.20, +1.01, +1.06, +1,    0, 1, 1,    1, 1, 1, 1,     0.1, 0.6,
        +0.20, +1.01, +1.06, +1,    0, 1, 1,    1, 1, 1, 1,     0.9, 0.6,
        -0.20, +1.01, +1.06, +1,    0, 1, 1,    1, 1, 1, 1,     0.1, 0.6,
        +0.20, +1.06, +1.01, +1,    0, 1, 1,    1, 1, 1, 1,     0.9, 0.4,

        //side1
        -0.20, +1.06, +1.01, +1,    0, 1, 0,    1, 1, 1, 1,     0.1, 0.4,
        +0.20, +1.06, +1.01, +1,    0, 1, 0,    1, 1, 1, 1,     0.9, 0.4,
        +0.20, +1.06, +0.85, +1,    0, 1, 0,    1, 1, 1, 1,     0.9, 0.1,
        -0.20, +1.06, +0.85, +1,    0, 1, 0,    1, 1, 1, 1,     0.1, 0.1,
        +0.20, +1.06, +0.85, +1,    0, 1, 0,    1, 1, 1, 1,     0.9, 0.1,
        -0.20, +1.06, +1.01, +1,    0, 1, 0,    1, 1, 1, 1,     0.1, 0.4,

        +0.20, +1.06, +1.01, +1,    1, 0, 0,    1, 1, 1, 1,     0.9, 0.4,
        +0.20, +1.06, +0.85, +1,    1, 0, 0,    1, 1, 1, 1,     0.9, 0.1,
        +0.20, +1.00, +0.85, +1,    1, 0, 0,    1, 1, 1, 1,     1, 0.1,
        +0.20, +1.00, +1.01, +1,    1, 0, 0,    1, 1, 1, 1,     1, 0.4,
        +0.20, +1.00, +0.85, +1,    1, 0, 0,    1, 1, 1, 1,     1, 0.1,
        +0.20, +1.06, +1.01, +1,    1, 0, 0,    1, 1, 1, 1,     0.9, 0.4,
        
        -0.20, +1.06, +1.01, +1,    -1, 0, 0,    1, 1, 1, 1,     0.1, 0.4,
        -0.20, +1.00, +1.01, +1,    -1, 0, 0,    1, 1, 1, 1,     0.0, 0.4,
        -0.20, +1.00, +0.85, +1,    -1, 0, 0,    1, 1, 1, 1,     0.0, 0.1,
        -0.20, +1.06, +0.85, +1,    -1, 0, 0,    1, 1, 1, 1,     0.1, 0.1,
        -0.20, +1.00, +0.85, +1,    -1, 0, 0,    1, 1, 1, 1,     0.0, 0.1,
        -0.20, +1.06, +1.01, +1,    -1, 0, 0,    1, 1, 1, 1,     0.1, 0.4,

        +0.20, +1.06, +0.85, +1,    0, 0, -1,    1, 1, 1, 1,     0.9, 0.1,
        -0.20, +1.06, +0.85, +1,    0, 0, -1,    1, 1, 1, 1,     0.1, 0.1,
        -0.20, +1.00, +0.85, +1,    0, 0, -1,    1, 1, 1, 1,     0.1, 0.0,
        +0.20, +1.00, +0.85, +1,    0, 0, -1,    1, 1, 1, 1,     0.9, 0.0,
        -0.20, +1.00, +0.85, +1,    0, 0, -1,    1, 1, 1, 1,     0.1, 0.0,
        +0.20, +1.06, +0.85, +1,    0, 0, -1,    1, 1, 1, 1,     0.9, 0.1,

        //side2
        -0.20, +1.01, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0.1, 0.6,
        +0.20, +1.01, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0.9, 0.6,
        +0.20, +0.85, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0.9, 0.9,
        -0.20, +0.85, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0.1, 0.9,
        +0.20, +0.85, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0.9, 0.9,
        -0.20, +1.01, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0.1, 0.6,
        
        -0.20, +1.01, +1.06, +1,   -1, 0, 0,    1, 1, 1, 1,     0.1, 0.6,
        -0.20, +1.01, +1.00, +1,   -1, 0, 0,    1, 1, 1, 1,     0.0, 0.6,
        -0.20, +0.85, +1.00, +1,   -1, 0, 0,    1, 1, 1, 1,     0.0, 0.9,
        -0.20, +0.85, +1.06, +1,   -1, 0, 0,    1, 1, 1, 1,     0.1, 0.9,
        -0.20, +0.85, +1.00, +1,   -1, 0, 0,    1, 1, 1, 1,     0.0, 0.9,
        -0.20, +1.01, +1.06, +1,   -1, 0, 0,    1, 1, 1, 1,     0.1, 0.6,
        
        +0.20, +1.01, +1.06, +1,   +1, 0, 0,    1, 1, 1, 1,     0.9, 0.6,
        +0.20, +0.85, +1.06, +1,   +1, 0, 0,    1, 1, 1, 1,     0.9, 0.9,
        +0.20, +0.85, +1.00, +1,   +1, 0, 0,    1, 1, 1, 1,     1.0, 0.9,
        +0.20, +1.01, +1.00, +1,   +1, 0, 0,    1, 1, 1, 1,     1.0, 0.6,
        +0.20, +0.85, +1.00, +1,   +1, 0, 0,    1, 1, 1, 1,     1.0, 0.9,
        +0.20, +1.01, +1.06, +1,   +1, 0, 0,    1, 1, 1, 1,     0.9, 0.6,

        +0.20, +0.85, +1.06, +1,   0, -1, 0,    1, 1, 1, 1,     0.9, 0.9,
        -0.20, +0.85, +1.06, +1,   0, -1, 0,    1, 1, 1, 1,     0.1, 0.9,
        -0.20, +0.85, +1.00, +1,   0, -1, 0,    1, 1, 1, 1,     0.1, 1.0,
        +0.20, +0.85, +1.00, +1,   0, -1, 0,    1, 1, 1, 1,     0.9, 1.0,
        -0.20, +0.85, +1.00, +1,   0, -1, 0,    1, 1, 1, 1,     0.1, 1.0,
        +0.20, +0.85, +1.06, +1,   0, -1, 0,    1, 1, 1, 1,     0.9, 0.9,

        //corner seals
        +0.20, +1.06, +1.01, +1,    1, 0, 0,    1, 1, 1, 1,     0.9, 0.4,
        +0.20, +1.01, +1.06, +1,    1, 0, 0,    1, 1, 1, 1,     0.9, 0.6,
        +0.20, +1.01, +1.01, +1,    1, 0, 0,    1, 1, 1, 1,     0.991, 0.4,

        -0.20, +1.06, +1.01, +1,    -1, 0, 0,   1, 1, 1, 1,     0.1, 0.4,
        -0.20, +1.01, +1.01, +1,    -1, 0, 0,   1, 1, 1, 1,     0.009, 0.4,
        -0.20, +1.01, +1.06, +1,    -1, 0, 0,   1, 1, 1, 1,     0.1, 0.6,
};      
void InitSidePanels()
{
    //  Get buffer name
    glGenBuffers(1, &side_vbo);
    //  Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, side_vbo);
    //  Copy icosahedron to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(side_data), side_data, GL_STATIC_DRAW);
    //  Release VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int corner_vbo = 0;
const int corner_size = 48;
const float corner_data[] = // Vertex data
{
//Corner panels
        //corner
        +1.06, +1.01, +1.01, +1,    1, 1, 1,    1, 1, 1, 1,     0.3, 0.3,
        +1.01, +1.06, +1.01, +1,    1, 1, 1,    1, 1, 1, 1,     0.3, 0.6,
        +1.01, +1.01, +1.06, +1,    1, 1, 1,    1, 1, 1, 1,     0.6, 0.3,

        //strips
        +1.01, +1.06, +1.01, +1,    0, 1, 1,    1, 1, 1, 1,     0.9, 0.9,
        +1.01, +1.01, +1.06, +1,    0, 1, 1,    1, 1, 1, 1,     0.9, 0.1,
        +0.30, +1.01, +1.06, +1,    0, 1, 1,    1, 1, 1, 1,     0.1, 0.1,
        +0.30, +1.06, +1.01, +1,    0, 1, 1,    1, 1, 1, 1,     0.1, 0.9,
        +0.30, +1.01, +1.06, +1,    0, 1, 1,    1, 1, 1, 1,     0.1, 0.1,
        +1.01, +1.06, +1.01, +1,    0, 1, 1,    1, 1, 1, 1,     0.9, 0.9,
        
        +1.06, +1.01, +1.01, +1,    1, 0, 1,    1, 1, 1, 1,     0.9, 0.9,
        +1.01, +1.01, +1.06, +1,    1, 0, 1,    1, 1, 1, 1,     0.9, 0.1,
        +1.01, +0.30, +1.06, +1,    1, 0, 1,    1, 1, 1, 1,     0.1, 0.1,
        +1.06, +0.30, +1.01, +1,    1, 0, 1,    1, 1, 1, 1,     0.1, 0.9,
        +1.01, +0.30, +1.06, +1,    1, 0, 1,    1, 1, 1, 1,     0.1, 0.1,
        +1.06, +1.01, +1.01, +1,    1, 0, 1,    1, 1, 1, 1,     0.9, 0.9,

        +1.01, +1.06, +1.01, +1,    1, 1, 0,    1, 1, 1, 1,     0.9, 0.9,
        +1.06, +1.01, +1.01, +1,    1, 1, 0,    1, 1, 1, 1,     0.9, 0.1,
        +1.06, +1.01, +0.30, +1,    1, 1, 0,    1, 1, 1, 1,     0.1, 0.1,
        +1.01, +1.06, +0.30, +1,    1, 1, 0,    1, 1, 1, 1,     0.1, 0.9,
        +1.06, +1.01, +0.30, +1,    1, 1, 0,    1, 1, 1, 1,     0.1, 0.1,
        +1.01, +1.06, +1.01, +1,    1, 1, 0,    1, 1, 1, 1,     0.9, 0.9,

        //strip end caps
        +0.30, +1.01, +1.06, +1,   -1, 0, 0,    1, 1, 1, 1,     0.3, 0.3,
        +0.30, +1.06, +1.01, +1,   -1, 0, 0,    1, 1, 1, 1,     0.3, 0.6,
        +0.30, +1.00, +1.00, +1,   -1, 0, 0,    1, 1, 1, 1,     0.6, 0.3,
        
        +1.01, +0.30, +1.06, +1,    0,-1, 0,    1, 1, 1, 1,     0.3, 0.3,
        +1.06, +0.30, +1.01, +1,    0,-1, 0,    1, 1, 1, 1,     0.3, 0.6,
        +1.00, +0.30, +1.00, +1,    0,-1, 0,    1, 1, 1, 1,     0.6, 0.3,

        
        +1.06, +1.01, +0.30, +1,    0, 0,-1,    1, 1, 1, 1,     0.3, 0.3,
        +1.01, +1.06, +0.30, +1,    0, 0,-1,    1, 1, 1, 1,     0.3, 0.6,
        +1.00, +1.00, +0.30, +1,    0, 0,-1,    1, 1, 1, 1,     0.6, 0.3,

        //inner cover pieces
        +0.30, +1.01, +1.06, +1,   -1,-1, 0,    1, 1, 1, 1,     0.3, 0.3,
        +1.01, +0.30, +1.06, +1,   -1,-1, 0,    1, 1, 1, 1,     0.3, 0.7,
        +1.01, +0.30, +1.00, +1,   -1,-1, 0,    1, 1, 1, 1,     0.7, 0.7,
        +0.30, +1.01, +1.00, +1,   -1,-1, 0,    1, 1, 1, 1,     0.7, 0.3,
        +1.01, +0.30, +1.00, +1,   -1,-1, 0,    1, 1, 1, 1,     0.7, 0.7,
        +0.30, +1.01, +1.06, +1,   -1,-1, 0,    1, 1, 1, 1,     0.3, 0.3,

        +1.06, +0.30, +1.01, +1,    0,-1,-1,    1, 1, 1, 1,     0.3, 0.3,
        +1.06, +1.01, +0.30, +1,    0,-1,-1,    1, 1, 1, 1,     0.3, 0.7,
        +1.00, +1.01, +0.30, +1,    0,-1,-1,    1, 1, 1, 1,     0.7, 0.7,
        +1.00, +0.30, +1.01, +1,    0,-1,-1,    1, 1, 1, 1,     0.7, 0.3,
        +1.00, +1.01, +0.30, +1,    0,-1,-1,    1, 1, 1, 1,     0.7, 0.7,
        +1.06, +0.30, +1.01, +1,    0,-1,-1,    1, 1, 1, 1,     0.3, 0.3,

        +0.30, +1.06, +1.01, +1,    -1,0,-1,    1, 1, 1, 1,     0.3, 0.3,
        +1.01, +1.06, +0.30, +1,    -1,0,-1,    1, 1, 1, 1,     0.3, 0.7,
        +1.01, +1.00, +0.30, +1,    -1,0,-1,    1, 1, 1, 1,     0.7, 0.7,
        +0.30, +1.00, +1.01, +1,    -1,0,-1,    1, 1, 1, 1,     0.7, 0.3,
        +1.01, +1.00, +0.30, +1,    -1,0,-1,    1, 1, 1, 1,     0.7, 0.7,
        +0.30, +1.06, +1.01, +1,    -1,0,-1,    1, 1, 1, 1,     0.3, 0.3,

};      
void InitCornerPanels()
{
    //  Get buffer name
    glGenBuffers(1, &corner_vbo);
    //  Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, corner_vbo);
    //  Copy icosahedron to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(corner_data), corner_data, GL_STATIC_DRAW);
    //  Release VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int wood_vbo = 0;
const int wood_size = 9;
const float wood_data[] = // Vertex data
{
//Wood panels
        +0.30, +1.01, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0.1, 0.1,
        +1.01, +0.30, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0, 0.5,
        +1.01, +1.01, +1.06, +1,    0, 0, 1,    1, 1, 1, 1,     0.5, 0,

        +1.06, +0.30, +1.01, +1,    1, 0, 0,    1, 1, 1, 1,     0.1, 0.1,
        +1.06, +1.01, +0.30, +1,    1, 0, 0,    1, 1, 1, 1,     0, 0.5,
        +1.06, +1.01, +1.01, +1,    1, 0, 0,    1, 1, 1, 1,     0.5, 0,

        +0.30, +1.06, +1.01, +1,    0, 1, 0,    1, 1, 1, 1,     0.1, 0.1,
        +1.01, +1.06, +0.30, +1,    0, 1, 0,    1, 1, 1, 1,     0, 0.5,
        +1.01, +1.06, +1.01, +1,    0, 1, 0,    1, 1, 1, 1,     0.5, 0,

};      
void InitWoodPanels()
{
    //  Get buffer name
    glGenBuffers(1, &wood_vbo);
    //  Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, wood_vbo);
    //  Copy icosahedron to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(wood_data), wood_data, GL_STATIC_DRAW);
    //  Release VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int texwood, texedge;

void InitCompanion()
{
    InitCube();
    InitSidePanels();
    InitCornerPanels();
    InitWoodPanels();
    texwood = LoadTexBMP32("textures/woodpanel_002.bmp", true);
    texedge = LoadTexBMP32("textures/underground_wall_metal004d.bmp", true);
}

Companion::Companion()
{
    x = 0;
    y = 0;
    z = 0;
    size = 1;
    rotx = 0;
    roty = 0;
    rotz = 0;
}

Companion::Companion(GLdouble tx, GLdouble ty, GLdouble tz, GLdouble s, GLdouble rx, GLdouble ry, GLdouble rz)
{
    x = tx;
    y = ty;
    z = tz;
    size = s;
    rotx = rx;
    roty = ry;
    rotz = rz;
}

void Companion::sidePanel(int rx, int ry, int rz, glm::mat4 &modelview,  glm::mat3 &normal, int shader)
{
        modelview = glm::rotate(modelview, glm::radians((float)rx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)ry), glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)rz), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 tempnorm(normal);
        tempnorm = glm::rotate(tempnorm, glm::radians((float)rx), glm::vec3(1.0f, 0.0f, 0.0f));
        tempnorm = glm::rotate(tempnorm, glm::radians((float)ry), glm::vec3(0.0f, 1.0f, 0.0f));
        tempnorm = glm::rotate(tempnorm, glm::radians((float)rz), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat3 tempnorm2(tempnorm);
        int id = glGetUniformLocation(shader, "ModelViewMatrix");
        glUniformMatrix4fv(id, 1, 0, &modelview[0][0]);
        id = glGetUniformLocation(shader, "NormalMatrix");
        glUniformMatrix3fv(id, 1, 0, &tempnorm2[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, side_size);
        modelview = glm::rotate(modelview, glm::radians((float)-rz), glm::vec3(0.0f, 0.0f, 1.0f));
        modelview = glm::rotate(modelview, glm::radians((float)-ry), glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)-rx), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Companion::cornerPanel(int rx, int ry, int rz, glm::mat4 &modelview,  glm::mat3 &normal, int shader)
{
        modelview = glm::rotate(modelview, glm::radians((float)rx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)ry), glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)rz), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 tempnorm(normal);
        tempnorm = glm::rotate(tempnorm, glm::radians((float)rx), glm::vec3(1.0f, 0.0f, 0.0f));
        tempnorm = glm::rotate(tempnorm, glm::radians((float)ry), glm::vec3(0.0f, 1.0f, 0.0f));
        tempnorm = glm::rotate(tempnorm, glm::radians((float)rz), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat3 tempnorm2(tempnorm);
        int id = glGetUniformLocation(shader, "ModelViewMatrix");
        glUniformMatrix4fv(id, 1, 0, &modelview[0][0]);
        id = glGetUniformLocation(shader, "NormalMatrix");
        glUniformMatrix3fv(id, 1, 0, &tempnorm2[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, corner_size);
        modelview = glm::rotate(modelview, glm::radians((float)-rz), glm::vec3(0.0f, 0.0f, 1.0f));
        modelview = glm::rotate(modelview, glm::radians((float)-ry), glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)-rx), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Companion::woodPanel(int rx, int ry, int rz, glm::mat4 &modelview,  glm::mat3 &normal, int shader)
{
        modelview = glm::rotate(modelview, glm::radians((float)rx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)ry), glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)rz), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 tempnorm(normal);
        tempnorm = glm::rotate(tempnorm, glm::radians((float)rx), glm::vec3(1.0f, 0.0f, 0.0f));
        tempnorm = glm::rotate(tempnorm, glm::radians((float)ry), glm::vec3(0.0f, 1.0f, 0.0f));
        tempnorm = glm::rotate(tempnorm, glm::radians((float)rz), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat3 tempnorm2(tempnorm);
        int id = glGetUniformLocation(shader, "ModelViewMatrix");
        glUniformMatrix4fv(id, 1, 0, &modelview[0][0]);
        id = glGetUniformLocation(shader, "NormalMatrix");
        glUniformMatrix3fv(id, 1, 0, &tempnorm2[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, wood_size);
        modelview = glm::rotate(modelview, glm::radians((float)-rz), glm::vec3(0.0f, 0.0f, 1.0f));
        modelview = glm::rotate(modelview, glm::radians((float)-ry), glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)-rx), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Companion::display(int shader, glm::mat4 &proj, glm::mat4 &view, glm::mat4 &modelview, glm::mat3 &normal)
{
    glPushMatrix();
    {
        //transformations
        modelview = glm::translate(modelview, glm::vec3(x, y, z));
        modelview = glm::rotate(modelview, glm::radians((float)rotx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)roty), glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)rotz), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 tempnorm(normal);//FIX THE NORMALS
        tempnorm = glm::rotate(tempnorm, glm::radians((float)rotx), glm::vec3(1.0f, 0.0f, 0.0f));
        tempnorm = glm::rotate(tempnorm, glm::radians((float)roty), glm::vec3(0.0f, 1.0f, 0.0f));
        tempnorm = glm::rotate(tempnorm, glm::radians((float)rotz), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat3 tempnorm2(tempnorm);
        modelview = glm::scale(modelview, glm::vec3(size,size,size));

        //  Set Projection, View, Modelview and Normal Matrix
        int id = glGetUniformLocation(shader, "ProjectionMatrix");
        glUniformMatrix4fv(id, 1, 0, &proj[0][0]);
        id = glGetUniformLocation(shader, "ViewMatrix");
        glUniformMatrix4fv(id, 1, 0, &view[0][0]);
        id = glGetUniformLocation(shader, "ModelViewMatrix");
        glUniformMatrix4fv(id, 1, 0, &modelview[0][0]);
        id = glGetUniformLocation(shader, "NormalMatrix");
        glUniformMatrix3fv(id, 1, 0, &tempnorm2[0][0]);

        //  Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
        glBindTexture(GL_TEXTURE_2D, texedge);
        //  Set vertex attribute pointers
        glVertexAttribPointer(0, 4, GL_FLOAT, 0, 52, (void *)0);  // Vertex
        glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
        glVertexAttribPointer(2, 4, GL_FLOAT, 0, 52, (void *)28); // Color
        glVertexAttribPointer(3, 2, GL_FLOAT, 0, 52, (void *)44); // Textures

        //  Enable vertex arrays
        glEnableVertexAttribArray(0); // Vertex
        glEnableVertexAttribArray(1); // Normal
        glEnableVertexAttribArray(2); // Color
        glEnableVertexAttribArray(3); // Textures

        // Draw the cube
        glDrawArrays(GL_TRIANGLES, 0, cube_size);

        glBindBuffer(GL_ARRAY_BUFFER, side_vbo);
        glBindTexture(GL_TEXTURE_2D, texedge);

        glVertexAttribPointer(0, 4, GL_FLOAT, 0, 52, (void *)0);  // Vertex
        glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
        glVertexAttribPointer(2, 4, GL_FLOAT, 0, 52, (void *)28); // Color
        glVertexAttribPointer(3, 2, GL_FLOAT, 0, 52, (void *)44); // Textures

        //draw the side panels
        sidePanel(0,0,0,modelview, tempnorm2, shader);
        sidePanel(0,90,0,modelview, tempnorm2, shader);
        sidePanel(0,180,0,modelview, tempnorm2, shader);
        sidePanel(0,270,0,modelview, tempnorm2, shader);

        
        sidePanel(0,0,180,modelview, tempnorm2, shader);
        sidePanel(0,90,180,modelview, tempnorm2, shader);
        sidePanel(0,180,180,modelview, tempnorm2, shader);
        sidePanel(0,270,180,modelview, tempnorm2, shader);
        
        sidePanel(0,0,90,modelview, tempnorm2, shader);
        sidePanel(0,90,90,modelview, tempnorm2, shader);
        sidePanel(0,180,90,modelview, tempnorm2, shader);
        sidePanel(0,270,90,modelview, tempnorm2, shader);

        //draw the corner panels

        glBindBuffer(GL_ARRAY_BUFFER, corner_vbo);
        glBindTexture(GL_TEXTURE_2D, texedge);

        glVertexAttribPointer(0, 4, GL_FLOAT, 0, 52, (void *)0);  // Vertex
        glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
        glVertexAttribPointer(2, 4, GL_FLOAT, 0, 52, (void *)28); // Color
        glVertexAttribPointer(3, 2, GL_FLOAT, 0, 52, (void *)44); // Textures

        cornerPanel(0,0,0,modelview, tempnorm2, shader);
        cornerPanel(0,90,0,modelview, tempnorm2, shader);
        cornerPanel(0,180,0,modelview, tempnorm2, shader);
        cornerPanel(0,270,0,modelview, tempnorm2, shader);

        cornerPanel(0,0,180,modelview, tempnorm2, shader);
        cornerPanel(0,90,180,modelview, tempnorm2, shader);
        cornerPanel(0,180,180,modelview, tempnorm2, shader);
        cornerPanel(0,270,180,modelview, tempnorm2, shader);

        //draw the wood panels

        glBindBuffer(GL_ARRAY_BUFFER, wood_vbo);
        glBindTexture(GL_TEXTURE_2D, texwood);

        glVertexAttribPointer(0, 4, GL_FLOAT, 0, 52, (void *)0);  // Vertex
        glVertexAttribPointer(1, 3, GL_FLOAT, 0, 52, (void *)16); // Normal
        glVertexAttribPointer(2, 4, GL_FLOAT, 0, 52, (void *)28); // Color
        glVertexAttribPointer(3, 2, GL_FLOAT, 0, 52, (void *)44); // Textures

        woodPanel(0,0,0,modelview, tempnorm2, shader);
        woodPanel(0,90,0,modelview, tempnorm2, shader);
        woodPanel(0,180,0,modelview, tempnorm2, shader);
        woodPanel(0,270,0,modelview, tempnorm2, shader);

        woodPanel(0,0,180,modelview, tempnorm2, shader);
        woodPanel(0,90,180,modelview, tempnorm2, shader);
        woodPanel(0,180,180,modelview, tempnorm2, shader);
        woodPanel(0,270,180,modelview, tempnorm2, shader);

        //  Disable vertex arrays
        glDisableVertexAttribArray(0); // Vertex
        glDisableVertexAttribArray(1); // Normal
        glDisableVertexAttribArray(2); // Color
        glDisableVertexAttribArray(3); // Textures
        //  Release VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        modelview = glm::scale(modelview, glm::vec3(1/size,1/size,1/size));
        modelview = glm::rotate(modelview, glm::radians((float)-rotz), glm::vec3(0.0f, 0.0f, 1.0f));
        modelview = glm::rotate(modelview, glm::radians((float)-roty), glm::vec3(0.0f, 1.0f, 0.0f));
        modelview = glm::rotate(modelview, glm::radians((float)-rotx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelview = glm::translate(modelview, glm::vec3(-x, -y, -z));

    }
    glPopMatrix();
}