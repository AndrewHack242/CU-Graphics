//  Geodesic Tesselation Evalution Shader

#version 400

//  Equilateral triangles in (CW order)
layout(triangles, equal_spacing, cw) in;
//  Modelview and projection matrices
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
//  Coordinates in and out
in  vec3 tcPosition[];
in  vec2 tcTexCoord[];
out vec3 teNormal;
out vec3 tePosition;
out vec3 tePatchDistance;
out vec2 teTexCoord;

float w = 0.5;

void main()
{
   teTexCoord = vec2(gl_TessCoord.x * tcTexCoord[0]
          +  gl_TessCoord.y * tcTexCoord[1]
          +  gl_TessCoord.z * tcTexCoord[2]);;
   //  Distance to edge of patch for interpolation
   tePatchDistance = gl_TessCoord;
   //  Calculate vertex as weighted average
   vec3 p = (gl_TessCoord.x * tcPosition[0]
          +  gl_TessCoord.y * tcPosition[1]
          +  gl_TessCoord.z * tcPosition[2]);
   //  Lengthen to unit radius
   
    //len = (w/2)(y^2) + (w/2)
    float len = (w/2)*pow(p.y,2) + (w/2);
    vec3 tmp = normalize(vec3(p.x,0.0f,p.z));
    tePosition = vec3(len* tmp.x,p.y,len * tmp.z);
    teNormal = normalize(vec3(tmp.x,-p.y*w,tmp.z));
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(tePosition, 1);
}
