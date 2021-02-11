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
        +1,
        +1,
        +1,
        +1,
        0,
        0,
        +1,
        1,
        0,
        0,
        1,
        1,
        1,
        -1,
        +1,
        +1,
        +1,
        0,
        0,
        +1,
        1,
        0,
        0,
        1,
        0,
        1,
        +1,
        -1,
        +1,
        +1,
        0,
        0,
        +1,
        1,
        0,
        0,
        1,
        1,
        0,
        -1,
        +1,
        +1,
        +1,
        0,
        0,
        +1,
        1,
        0,
        0,
        1,
        0,
        1,
        +1,
        -1,
        +1,
        +1,
        0,
        0,
        +1,
        1,
        0,
        0,
        1,
        1,
        0,
        -1,
        -1,
        +1,
        +1,
        0,
        0,
        +1,
        1,
        0,
        0,
        1,
        0,
        0,
        //  Back
        -1,
        -1,
        -1,
        +1,
        0,
        0,
        -1,
        0,
        0,
        1,
        1,
        1,
        0,
        +1,
        -1,
        -1,
        +1,
        0,
        0,
        -1,
        0,
        0,
        1,
        1,
        0,
        0,
        -1,
        +1,
        -1,
        +1,
        0,
        0,
        -1,
        0,
        0,
        1,
        1,
        1,
        1,
        +1,
        -1,
        -1,
        +1,
        0,
        0,
        -1,
        0,
        0,
        1,
        1,
        0,
        0,
        -1,
        +1,
        -1,
        +1,
        0,
        0,
        -1,
        0,
        0,
        1,
        1,
        1,
        1,
        +1,
        +1,
        -1,
        +1,
        0,
        0,
        -1,
        0,
        0,
        1,
        1,
        0,
        1,
        //  Right
        +1,
        +1,
        +1,
        +1,
        +1,
        0,
        0,
        1,
        1,
        0,
        1,
        0,
        1,
        +1,
        -1,
        +1,
        +1,
        +1,
        0,
        0,
        1,
        1,
        0,
        1,
        0,
        0,
        +1,
        +1,
        -1,
        +1,
        +1,
        0,
        0,
        1,
        1,
        0,
        1,
        1,
        1,
        +1,
        -1,
        +1,
        +1,
        +1,
        0,
        0,
        1,
        1,
        0,
        1,
        0,
        0,
        +1,
        +1,
        -1,
        +1,
        +1,
        0,
        0,
        1,
        1,
        0,
        1,
        1,
        1,
        +1,
        -1,
        -1,
        +1,
        +1,
        0,
        0,
        1,
        1,
        0,
        1,
        1,
        0,
        //  Left
        -1,
        +1,
        +1,
        +1,
        -1,
        0,
        0,
        0,
        1,
        0,
        1,
        1,
        1,
        -1,
        +1,
        -1,
        +1,
        -1,
        0,
        0,
        0,
        1,
        0,
        1,
        0,
        1,
        -1,
        -1,
        +1,
        +1,
        -1,
        0,
        0,
        0,
        1,
        0,
        1,
        1,
        0,
        -1,
        +1,
        -1,
        +1,
        -1,
        0,
        0,
        0,
        1,
        0,
        1,
        0,
        1,
        -1,
        -1,
        +1,
        +1,
        -1,
        0,
        0,
        0,
        1,
        0,
        1,
        1,
        0,
        -1,
        -1,
        -1,
        +1,
        -1,
        0,
        0,
        0,
        1,
        0,
        1,
        0,
        0,
        //  Top
        +1,
        +1,
        +1,
        +1,
        0,
        +1,
        0,
        0,
        1,
        1,
        1,
        1,
        0,
        +1,
        +1,
        -1,
        +1,
        0,
        +1,
        0,
        0,
        1,
        1,
        1,
        1,
        1,
        -1,
        +1,
        +1,
        +1,
        0,
        +1,
        0,
        0,
        1,
        1,
        1,
        0,
        0,
        +1,
        +1,
        -1,
        +1,
        0,
        +1,
        0,
        0,
        1,
        1,
        1,
        1,
        1,
        -1,
        +1,
        +1,
        +1,
        0,
        +1,
        0,
        0,
        1,
        1,
        1,
        0,
        0,
        -1,
        +1,
        -1,
        +1,
        0,
        +1,
        0,
        0,
        1,
        1,
        1,
        0,
        1,
        //  Bottom
        -1,
        -1,
        -1,
        +1,
        0,
        -1,
        0,
        1,
        0,
        1,
        1,
        0,
        0,
        +1,
        -1,
        -1,
        +1,
        0,
        -1,
        0,
        1,
        0,
        1,
        1,
        1,
        0,
        -1,
        -1,
        +1,
        +1,
        0,
        -1,
        0,
        1,
        0,
        1,
        1,
        0,
        1,
        +1,
        -1,
        -1,
        +1,
        0,
        -1,
        0,
        1,
        0,
        1,
        1,
        1,
        0,
        -1,
        -1,
        +1,
        +1,
        0,
        -1,
        0,
        1,
        0,
        1,
        1,
        0,
        1,
        +1,
        -1,
        +1,
        +1,
        0,
        -1,
        0,
        1,
        0,
        1,
        1,
        1,
        1,
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

Companion::Companion()
{
    x = 0;
    y = 0;
    z = 0;
    size = 1;
    rotx = 45;
    roty = 0;
    rotz = 0;
}

void Companion::display(glm::mat4 modelview)
{
    glPushMatrix();
    {
        //transformations
        //modelview = glm::rotate(modelview, glm::radians((float)rotx), glm::vec3(1.0f,0.0f,0.0f));
        //  Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
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

        //  Disable vertex arrays
        glDisableVertexAttribArray(0); // Vertex
        glDisableVertexAttribArray(1); // Normal
        glDisableVertexAttribArray(2); // Color
        glDisableVertexAttribArray(3); // Textures
        //  Release VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glPopMatrix();
}