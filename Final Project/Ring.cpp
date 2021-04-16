#include "Ring.h"

unsigned int ringvao;
int RingN;
static void CreateRing()
{
   unsigned int verts, faces;
   const int Faces[] =
       {
           0,2,4,    4,2,6,    2,1,6,     6,1,5,      1,3,5,      5,3,7,      3,0,7,    7,0,4,  //1
           4,6,8,    8,6,10,    6,5,10,     10,5,9,      5,7,9,      9,7,11,      7,4,11,    11,4,8,  //2
           8,10,12,    12,10,14,    10,9,14,     14,9,13,      9,11,13,     13,11,15,      11,8,15,    15,8,12,  //3
           12,14,16,    16,14,18,    14,13,18,     18,13,17,      13,15,17,      17,15,19,      15,12,19,    19,12,16,  //4
           16,18,20,    20,18,22,    18,17,22,     22,17,21,      17,19,21,      21,19,23,      19,16,23,    23,16,20,  //5
           20,22,24,    24,22,26,    22,21,26,     26,21,25,      21,23,25,      25,23,27,      23,20,27,    27,20,24,  //6
           24,26,28,    28,26,30,    26,25,30,     30,25,29,      25,27,29,      29,27,31,      27,24,31,    31,24,28,  //7
           28,30,0,    0,30,2,    30,29,2,     2,29,1,      29,31,1,     1,31,3,      31,28,3,    3,28,0,  //8
           };
   const float Verts[] =
       {
          //1
           Cos(0), Sin(0), 0.000, //1 //arrays start at 0 *facepalm*
           0.4*Cos(0), 0.4*Sin(0), 0.000, //2
           0.7*Cos(0), 0.7*Sin(0), 0.3, //3
           0.7*Cos(0), 0.7*Sin(0),-0.3, //4

         //2
           Cos(45), Sin(45), 0.000, //5
           0.4*Cos(45), 0.4*Sin(45), 0.000, //6
           0.7*Cos(45), 0.7*Sin(45), 0.3, //7
           0.7*Cos(45), 0.7*Sin(45),-0.3, //8

         //3
           Cos(90), Sin(90), 0.000, //9
           0.4*Cos(90), 0.4*Sin(90), 0.000, //0
           0.7*Cos(90), 0.7*Sin(90), 0.3, //11
           0.7*Cos(90), 0.7*Sin(90),-0.3, //12

         //4
           Cos(135), Sin(135), 0.000, //13
           0.4*Cos(135), 0.4*Sin(135), 0.000, //14
           0.7*Cos(135), 0.7*Sin(135), 0.3, //15
           0.7*Cos(135), 0.7*Sin(135),-0.3, //16

         //5
           Cos(180), Sin(180), 0.000, //17
           0.4*Cos(180), 0.4*Sin(180), 0.000, //18
           0.7*Cos(180), 0.7*Sin(180), 0.3, //19
           0.7*Cos(180), 0.7*Sin(180),-0.3, //20
           
         //6
           Cos(225), Sin(225), 0.000, //21
           0.4*Cos(225), 0.4*Sin(225), 0.000, //22
           0.7*Cos(225), 0.7*Sin(225), 0.3, //23
           0.7*Cos(225), 0.7*Sin(225),-0.3, //24

         //7
           Cos(270), Sin(270), 0.000, //25
           0.4*Cos(270), 0.4*Sin(270), 0.000, //26
           0.7*Cos(270), 0.7*Sin(270), 0.3, //27
           0.7*Cos(270), 0.7*Sin(270),-0.3, //28

         //8
           Cos(315), Sin(315), 0.000, //29
           0.4*Cos(315), 0.4*Sin(315), 0.000, //30
           0.7*Cos(315), 0.7*Sin(315), 0.3, //31
           0.7*Cos(315), 0.7*Sin(315),-0.3, //32
           };
   RingN = sizeof(Faces) / sizeof(int);

    ErrCheck("VBOInit:1");
   //  Position attribute
   unsigned int shader = ShaderHandler::useShader("ring");
    ErrCheck("VBOInit:1.5");
   int loc = glGetAttribLocation(shader, "Position");

    ErrCheck("VBOInit:2");
   // Create the VAO:
   glGenVertexArrays(1, &ringvao);
   glBindVertexArray(ringvao);

   // Create the VBO for facet indices
   glGenBuffers(1, &faces);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces), Faces, GL_STATIC_DRAW);

    ErrCheck("VBOInit:3");
   // Create the VBO for coordinates
   glGenBuffers(1, &verts);
   glBindBuffer(GL_ARRAY_BUFFER, verts);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
   
    ErrCheck("VBOInit:4");
   // Enable Position as vertex array
   glEnableVertexAttribArray(loc);
   glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    ErrCheck("VBOInit:5");
   ShaderHandler::disableShaders();
}


void Ring::VBOInit()
{
    CreateRing();
    ErrCheck("VBOInit");
}

Ring::Ring(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot) : Object(pos, scale, rot)
{
    ShaderHandler::LoadTesShader("ring","Shaders/geodesic.vert", "Shaders/geodesic.tesc", "Shaders/ring.tese", "Shaders/geodesic.geom", "Shaders/geodesic.frag");
    VBOInit();
}

void Ring::drawObject()
{
  
        //std::cout << "shadercheck" << std::endl;
    ShaderHandler::useShader("ring");
        //std::cout << "/shadercheck" << std::endl;

    glPatchParameteri(GL_PATCH_VERTICES, 3);

   //  Bind VAO and render
   glBindVertexArray(ringvao);
   glDrawElements(GL_PATCHES, RingN, GL_UNSIGNED_INT, 0);

    ShaderHandler::disableShaders();
}