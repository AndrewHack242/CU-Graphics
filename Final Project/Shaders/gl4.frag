#version 400 core

//  Transformation matrices
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

uniform vec3 camPos;

//  Light propeties
uniform float fov;
uniform vec4 Global;
uniform vec4 Ambient;
uniform vec4 Diffuse;
uniform vec4 Specular;
uniform vec4 Position;
uniform vec4 LightColor;

//  Input from previous shader
in vec4 FrontColor;
in vec2 Texcoord;
in vec4 fragpos;
in vec3 norm;

//  Fragment color
layout (location=0) out vec4 Fragcolor;

//  Texture
uniform sampler2D tex;


in mat4 ModelViewMatrix;
mat3 NormalMatrix;


vec4 phong()
{
   //  N is the object normal at P
   vec3 N = normalize(NormalMatrix * normalize(norm));
   //  L is the light vector
   vec3 L = normalize(vec3(Position - fragpos));

   vec3 viewDir = normalize(camPos - vec3(fragpos));
   vec3 reflectDir = reflect(-L, norm);  


   //  Emission and ambient color
   vec4 color = ((Global+Ambient)*LightColor)*vec4(1.0);
   //diffuse
   color = color + (max(dot(norm, L), 0.0) * LightColor);
   //specular
   color = color + (Specular * pow(max(dot(viewDir, reflectDir), 0.0), 32) * LightColor);

   //  Return sum of color components
   return color;
}

void main()
{
   vec4 FrontColor;
   //construct Normal Matrix
   NormalMatrix = mat3(transpose(inverse(ModelViewMatrix)));
   //  Pass colors to fragment shader (will be interpolated)
   FrontColor = phong();
   //get da color
   Fragcolor = 0.7*FrontColor*texture2D(tex,Texcoord);
}
