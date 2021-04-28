
#version 400

in vec3 gFacetNormal;
in vec3 gTriDistance;
in vec3 gPatchDistance;
in vec2 TexCoord;
in vec4 fragpos;


uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;


uniform vec4 Global;
uniform vec4 Ambient;
uniform vec4 Diffuse;
uniform vec4 Specular;
uniform vec4 Position;
uniform vec4 LightColor;

const vec4 InnerLineColor = vec4(1, 1, 1, 1);
const bool DrawLines = true;

uniform sampler2D tex;

mat4 ModelViewMatrix;

vec4 phong()
{
   //  P is the vertex coordinate on body
   vec3 P = vec3(ViewMatrix * fragpos);
   //  N is the object normal at P
   vec3 N = normalize(gFacetNormal);
   //  L is the light vector
   vec3 L = normalize(vec3(ViewMatrix*Position) - P);

   //  Emission and ambient color
   vec4 color = ((Global+Ambient)*LightColor)*vec4(1.0);

   //  Diffuse light intensity is cosine of light and normal vectors
   float Id = dot(L,N);
   if (Id>0.0)
   {
      //  Add diffuse - material color from Color
      color += ((Id*Diffuse)*LightColor)*vec4(1.0);
      //  R is the reflected light vector R = 2(L.N)N - L
      vec3 R = reflect(-L, N);
      //  V is the view vector (eye at the origin)
      vec3 V = normalize(-P);
      //  Specular is cosine of reflected and view vectors
      //  Assert material specular color is white
      float Is = dot(R,V);
      if (Is>0.0) color += pow(Is,16.0)*Specular*LightColor;
   }

   //  Return sum of color components
   return color;
}

//  Output color
out vec4  FragColor;
 
void main()
{
   //construct Model-View Matrix
   ModelViewMatrix = ViewMatrix * ModelMatrix;

    vec4 color = vec4(0);
    
 
    //FragColor = vec4(color.xyz, 1.0);
    FragColor = 0.7*phong() * texture2D(tex,TexCoord);
}
