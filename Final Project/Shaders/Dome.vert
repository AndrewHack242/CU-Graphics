//  Geodesic Vertex Shader
#version 400

//  Coordinates in and out
layout(location = 0) in vec4 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec4 Color;
layout(location = 3) in vec2 Texture;


out vec3 vPosition;
out vec2 TexCoord;

void main()
{
   //  Coordinate passthrough
   vPosition = Position.xyz / Position.w;
   TexCoord = Texture;
}
