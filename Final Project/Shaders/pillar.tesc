//  Geodesic Tesselation Control Shader

#version 400

//  Tesselation control parameters
float distance = 0;
//  Triangles out
layout(vertices = 3) out;
//  Coordinates in out out
in  vec3 vPosition[];
in vec2 TexCoord[];
out vec3 tcPosition[];
out vec2 tcTexCoord[];

void main()
{
   //  Coordinate passthrough
   tcPosition[gl_InvocationID] = vPosition[gl_InvocationID];
   tcTexCoord[gl_InvocationID] = TexCoord[gl_InvocationID];
   //  Only the first vertex per patch needs to set the patch parameters

   float innerLOD = 15;
   float outerLOD = 15;

//LOD = 1;

   if (gl_InvocationID == 0)
   {
      gl_TessLevelInner[0] = innerLOD;
      gl_TessLevelOuter[0] = innerLOD;
      gl_TessLevelOuter[1] = outerLOD;
      gl_TessLevelOuter[2] = outerLOD;
   }
}
