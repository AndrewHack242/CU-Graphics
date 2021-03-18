//began as example from learnopengl.com
#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 256) out;


uniform mat4 Projection;
uniform mat4 Modelview;

uniform float LOD; //1 = 45 deg circle, 90 deg tube

out vec3 fColor;

void build_ring(vec4 position)
{    
    /*fColor = gs_in[0].color; // gs_in[0] since there's only one input vertex
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); // 1:bottom-left   
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0); // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0); // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0); // 4:top-right
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0); // 5:top
    fColor = vec3(1.0, 1.0, 1.0);
    EmitVertex();*/
   fColor = vec3(0,0,1.0);

   mat4 per = Projection * Modelview;

   float rounddeg = 45/LOD;
   float thickdeg = 90/LOD;
   for(float r = 0; r < 360; r += rounddeg)
   {
      vec3 roundpoint = vec3(0.7 * cos(radians(r)),0.7 * sin(radians(r)),position.z);
      vec3 nextroundpoint = vec3(0.7 * cos(radians(r + rounddeg)),0.7 * sin(radians(r + rounddeg)),position.z);
      for(float t = 0; t < 360; t += thickdeg)
      {
          gl_Position = per* vec4(roundpoint + vec3(0.0,0.3 * cos(radians(t)),0.3 * sin(radians(t))),1.0); //1
         EmitVertex();
         gl_Position = per* vec4(nextroundpoint + vec3(0.0,0.3 * cos(radians(t)),0.3 * sin(radians(t))),1.0); //2
         EmitVertex();  

      }
      gl_Position = per* vec4(roundpoint + vec3(0.0,0.3 * cos(0),0.3 * sin(0)), 1.0); //finish the loop
      EmitVertex();
      gl_Position = per* vec4(nextroundpoint + vec3(0.0,0.3 * cos(0),0.3 * sin(0)), 1.0);
      EmitVertex();

      EndPrimitive();
   }

    /* gl_Position = per* (position + vec4(1.0,1.0,1.0,1.0));
    EmitVertex();
    gl_Position = per* (position + vec4(-1.0,-1.0,-1.0,1.0));
    EmitVertex();
    gl_Position = per* (position + vec4(-1.0,1.0,-1.0,1.0));
    EmitVertex();
    EndPrimitive(); */
}

void main() {    
    build_ring(gl_in[0].gl_Position);
}