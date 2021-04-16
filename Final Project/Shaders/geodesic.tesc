//  Geodesic Tesselation Control Shader

#version 400

//  Tesselation control parameters
float distance = 0;
//  Triangles out
layout(vertices = 3) out;
//  Coordinates in out out
in  vec3 vPosition[];
out vec3 tcPosition[];

void main()
{
   //  Coordinate passthrough
   tcPosition[gl_InvocationID] = vPosition[gl_InvocationID];
   //  Only the first vertex per patch needs to set the patch parameters

   float LOD = 1;
   if (distance >= 1)
      LOD = 50;
   else if (distance >= -1)
      LOD = 40;
   else if (distance >= -2)
      LOD = 30;
   else if (distance >= -4)
      LOD = 20;
   else if (distance >= -6)
      LOD = 15;
   else if (distance >= -8)
      LOD = 10;
   else if (distance >= -10)
      LOD = 7;
   else if (distance >= -15)
      LOD = 6;
   else if (distance >= -20)
      LOD = 5;
   else if (distance >= -30)
      LOD = 4;
   else if (distance >= -50)
      LOD = 3;
   else if (distance >= -80)
      LOD = 2;
   else if (distance >= -140)
      LOD = 1;

   LOD = 6;

//LOD = 1;

   if (gl_InvocationID == 0)
   {
      gl_TessLevelInner[0] = LOD;
      gl_TessLevelOuter[0] = LOD;
      gl_TessLevelOuter[1] = LOD;
      gl_TessLevelOuter[2] = LOD;
   }
}
