//  Geodesic Geometry Shader

#version 400

//  Normal matrix
uniform mat3 NormalMatrix;
//  Triangles in and out
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
//  Coordinates and weights in and out
in  vec3 tePosition[3];
in  vec3 tePatchDistance[3];
out vec3 gFacetNormal;
out vec3 gPatchDistance;
out vec3 gTriDistance;

void main()
{
   //  Compute normal as cross product
   //  Since this is an inscribe sphere we know the normal,
   //  but instead use the cross product to clearly show facets
   //  Transform normal

   //  First vertex
   gFacetNormal = NormalMatrix * -tePosition[0];
   gPatchDistance = tePatchDistance[0];
   gTriDistance = vec3(1, 0, 0);
   gl_Position = gl_in[0].gl_Position;
   EmitVertex();

   //  Second vertex
   gFacetNormal = NormalMatrix * -tePosition[1];
   gPatchDistance = tePatchDistance[1];
   gTriDistance = vec3(0, 1, 0);
   gl_Position = gl_in[1].gl_Position;
   EmitVertex();

   //  Third vertex
   gFacetNormal = NormalMatrix * -tePosition[2];
   gPatchDistance = tePatchDistance[2];
   gTriDistance = vec3(0, 0, 1);
   gl_Position = gl_in[2].gl_Position;
   EmitVertex();

   //  Done with triangle
   EndPrimitive();
}
