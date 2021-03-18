//began as example from learnopengl.com
#version 400 core
layout (location = 0) in vec3 Vertex;

//  Transformation matrices
//uniform mat4 Projection;
//uniform mat4 Modelview;
//uniform mat3 NormalMatrix;



void main()
{
   //  Set transformed vertex location
   gl_Position =  vec4(Vertex,1.0);
}
