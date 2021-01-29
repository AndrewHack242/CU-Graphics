//  Basic vertex shader
#version 120

varying vec4 NDC;

void main()
{
   //  Transform
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   NDC = gl_Position;
}
