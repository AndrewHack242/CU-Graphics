//began as example from learnopengl.com
#version 400 core

in  vec4 Position;
//  Transformation matrices
uniform mat4 Projection;
uniform mat4 Modelview;
//uniform mat3 NormalMatrix;



void main()
{
   //  Set transformed vertex location
   gl_Position =  Projection * Modelview * Position;
}
