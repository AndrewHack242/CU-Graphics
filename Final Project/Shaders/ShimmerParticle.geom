//
//  nBody geometry shader
//  Billboards point to quad
//

#version 150 compatibility
#extension GL_EXT_geometry_shader4 : enable
layout(points) in;
layout(triangle_strip,max_vertices=256) out;
float size = 0.1;


//  Transformation matrices
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

out vec4 Color;

mat4 ModelViewMatrix;

float gr = (1.0 + sqrt(5))/2;

void setPoint(vec3 pos)
{
   pos *= size;
   gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(pos,1);
   EmitVertex();
}

void createTriangle(vec3 pos1, vec3 pos2, vec3 pos3)
{
   setPoint(pos1);
   setPoint(pos2);
   setPoint(pos3);
   EndPrimitive();
}

void Icosahedron()
{
   /* vec2 delta = vec2(x,y);
   vec4 p = gl_PositionIn[0];
   p.x += dot(delta,ModelViewMatrix[0].xy);
   p.y += dot(delta,ModelViewMatrix[1].xy);
   p.z += dot(delta,ModelViewMatrix[2].xy);
   gl_Position = ProjectionMatrix * ModelViewMatrix * p;
   EmitVertex(); */
   //(x,y,z)

   //20 total triangles

   //top
   Color = vec4(1);
   createTriangle(vec3(+1,+gr,0),vec3(-1,+gr,0),vec3(0,+1,+gr));//1
   Color = vec4(1,0,1,1);
   createTriangle(vec3(-1,+gr,0),vec3(+1,+gr,0),vec3(0,+1,-gr));//2

   //bottom
   Color = vec4(1);
   createTriangle(vec3(-1,-gr,0),vec3(+1,-gr,0),vec3(0,-1,+gr));//3
   Color = vec4(1,0,1,1);
   createTriangle(vec3(+1,-gr,0),vec3(-1,-gr,0),vec3(0,-1,-gr));//4

   //sides
   Color = vec4(0,1,0,1);
   createTriangle(vec3(+1,+gr,0),vec3(+gr,0,+1),vec3(+gr,0,-1));//5
   Color = vec4(0,1,0,1);
   createTriangle(vec3(-1,+gr,0),vec3(-gr,0,-1),vec3(-gr,0,+1));//6

   
   Color = vec4(1);
   createTriangle(vec3(+1,-gr,0),vec3(+gr,0,-1),vec3(+gr,0,+1));//7
   Color = vec4(1,0,1,1);
   createTriangle(vec3(-1,-gr,0),vec3(-gr,0,+1),vec3(-gr,0,-1));//8


   Color = vec4(0,1,1,1);
   createTriangle(vec3(0,+1,+gr),vec3(0,-1,+gr),vec3(+gr, 0, +1));//9
   Color = vec4(1,1,0,1);
   createTriangle(vec3(0,-1,+gr),vec3(0,+1,+gr),vec3(-gr, 0, +1));//10


   Color = vec4(0,1,1,1);
   createTriangle(vec3(0,-1,-gr),vec3(0,+1,-gr),vec3(+gr, 0, -1));//11
   Color = vec4(1,1,0,1);
   createTriangle(vec3(0,+1,-gr),vec3(0,-1,-gr),vec3(-gr, 0, -1));//12

   
   Color = vec4(0.5,0.5,0.5,1);
   createTriangle(vec3(+1,+gr,0),vec3(0,+1,+gr),vec3(+gr,0,+1));//13
   Color = vec4(0.5,0.5,0.5,1);
   createTriangle(vec3(-1,-gr,0),vec3(-gr,0,-1),vec3(0,-1,-gr));//14

   
   Color = vec4(0.5,0,0,1);
   createTriangle(vec3(0,-1,+gr),vec3(+1,-gr,0),vec3(+gr,0,+1));//15
   Color = vec4(0.5,0,0,1);
   createTriangle(vec3(0,+1,-gr),vec3(-gr,0,-1),vec3(-1,+gr,0));//16

   
   Color = vec4(0,0,0.6,1);
   createTriangle(vec3(-1,+gr,0),vec3(-gr,0,+1),vec3(0,+1,+gr));//17
   Color = vec4(0,0,0.6,1);
   createTriangle(vec3(+gr,0,-1),vec3(+1,-gr,0),vec3(0,-1,-gr));//18

   
   Color = vec4(0.6,0,0.6,1);
   createTriangle(vec3(-gr,0,+1),vec3(-1,-gr,0),vec3(0,-1,+gr));//19
   Color = vec4(0.6,0,0.6,1);
   createTriangle(vec3(+1,+gr,0),vec3(+gr,0,-1),vec3(0,+1,-gr));//20
}

void main()
{
   ModelViewMatrix = ViewMatrix * ModelMatrix;
   //  Copy Color
   Color  = gl_FrontColorIn[0];
   Icosahedron();
   EndPrimitive();
}
