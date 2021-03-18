//  Geodesic Tesselation Evalution Shader

#version 400

//  Equilateral triangles in (CW order)
layout(triangles, equal_spacing, cw) in;
//  Modelview and projection matrices
uniform mat4 Projection;
uniform mat4 Modelview;
//  Coordinates in and out
in  vec3 tcPosition[];
out vec3 tePosition;
out vec3 tePatchDistance;

void main()
{
   //  Distance to edge of patch for interpolation
   tePatchDistance = gl_TessCoord;
   //  Calculate vertex as weighted average
   vec3 p = (gl_TessCoord.x * tcPosition[0]
          +  gl_TessCoord.y * tcPosition[1]
          +  gl_TessCoord.z * tcPosition[2]);
   //  Lengthen to unit radius
   //tePosition = normalize(p);

   //get angle of point for circle using arctan
   float ang = atan(p.y, p.x);
   // p in terms of circle center (p- 0.7*Cos(ang), p- 0.7*Sin(ang),p)
   vec3 adj = vec3(p.x - 0.7*cos(ang), p.y - 0.7 * sin(ang),p.z);
   //normalize the distance to 0.3 to point to make round
   tePosition = 0.3 * normalize(adj);
   //give point in terms of center of ring again
   tePosition = vec3(tePosition.x + 0.7*cos(ang), tePosition.y + 0.7 * sin(ang),tePosition.z);
   //  Project vertex
gl_Position = Projection * Modelview * vec4(tePosition, 1);
}
