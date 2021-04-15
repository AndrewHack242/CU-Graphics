#version 330 core

//  Transformation matrices
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;

//  Vertex attributes (input)
layout(location = 0) in vec4 Vertex;


void main()
{
   gl_Position = ProjectionMatrix * ModelViewMatrix * Vertex;
}
