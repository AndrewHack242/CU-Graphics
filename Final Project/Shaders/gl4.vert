#version 400 core

//  Transformation matrices
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

//  Vertex attributes (input)
layout(location = 0) in vec4 Vertex;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec4 Color;
layout(location = 3) in vec2 Texture;

//  Output to next shader
out vec4 FrontColor;
out vec2 Texcoord;
out vec4 fragpos;
out vec4 vert;
out vec3 norm;


out mat4 ModelViewMatrix;


void main()
{	
   //construct Model-View Matrix
   ModelViewMatrix = ViewMatrix * ModelMatrix;

   Texcoord = Texture;
   fragpos = ModelMatrix * Vertex;
   norm = Normal;
   vert = Vertex;
   //  Set transformed vertex location
   gl_Position =  ProjectionMatrix * ModelViewMatrix * Vertex;
}
