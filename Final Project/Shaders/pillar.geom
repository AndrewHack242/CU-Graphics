//  Geodesic Geometry Shader

#version 400

//  Normal matrix
mat3 NormalMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

uniform float fov;
uniform vec4 Global;
uniform vec4 Ambient;
uniform vec4 Diffuse;
uniform vec4 Specular;
uniform vec4 Position;
uniform vec4 LightColor;

//  Triangles in and out
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
//  Coordinates and weights in and out
in  vec3 tePosition[3];
in  vec3 tePatchDistance[3];
in  vec2 teTexCoord[3];
in  vec3 teNormal[3];
out vec3 gFacetNormal;
out vec3 gPatchDistance;
out vec3 gTriDistance;
out vec2 TexCoord;
out vec4 fragpos;

void main()
{
   //construct Model-View Matrix
   mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
   //construct Normal Matrix
   NormalMatrix = mat3(transpose(inverse(ModelViewMatrix)));

   //  Transform normal

   //  First vertex
   gPatchDistance = tePatchDistance[0];
   gTriDistance = vec3(1, 0, 0);
   gl_Position = gl_in[0].gl_Position;
   TexCoord = teTexCoord[0];
   gFacetNormal = NormalMatrix * teNormal[0];
   fragpos = ModelMatrix * vec4(tePosition[0],1);
   EmitVertex();

   //  Second vertex
   gPatchDistance = tePatchDistance[1];
   gTriDistance = vec3(0, 1, 0);
   gl_Position = gl_in[1].gl_Position;
   TexCoord = teTexCoord[1];
   gFacetNormal = NormalMatrix * teNormal[1];
   fragpos = ModelMatrix * vec4(tePosition[1],1);
   EmitVertex();

   //  Third vertex
   gPatchDistance = tePatchDistance[2];
   gTriDistance = vec3(0, 0, 1);
   gl_Position = gl_in[2].gl_Position;
   TexCoord = teTexCoord[2];
   gFacetNormal = NormalMatrix * teNormal[2];
   fragpos = ModelMatrix * vec4(tePosition[2],1);
   EmitVertex();

   //  Done with triangle
   EndPrimitive();
}
