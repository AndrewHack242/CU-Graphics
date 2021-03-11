//  Confetti Cannon
//  derived from Orange Book
#version 120

uniform   float time;  //  Time
attribute float Start; //  Start time
attribute float Initang; //init angle
uniform float length;
float initdist = 4;
float wrap = 480;
float gap = 0;

void main(void)
{
   //  Particle location
   vec4 vert = gl_Vertex;
   //  Time offset mod 5
   float t = mod(time-Start,length);

   float ang = radians(Initang + (wrap*(t/length)));
   float alpha = (1-gap)-(t/length);
   float dist = initdist * (1-(t/length));
      gl_FrontColor = vec4(gl_Color.xyz,alpha);
   vert = vec4(dist*sin(ang),0,dist*cos(ang),1);

   //  Transform particle location
   gl_Position = gl_ModelViewProjectionMatrix*vert;
}
