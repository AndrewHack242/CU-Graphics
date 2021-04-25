//  Confetti Cannon
//  derived from Orange Book
#version 400

uniform float time;
uniform float starttime;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

uniform vec3 velocity;
uniform vec3 acceleration;

//  Vertex attributes (input)
layout(location = 0) in vec4 Vertex;
layout(location = 2) in vec4 Color;

out vec4 color;

void main(void)
{
      //construct Model-View Matrix
   mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
   //  Transform particle location
   vec4 pos = Vertex + (time * vec4(velocity,0.0)) + (0.5 * vec4(acceleration,0.0) * pow(time-starttime,2));
   color = Color;
   gl_Position = ProjectionMatrix * ModelViewMatrix * pos;
}
