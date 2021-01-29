//  Basic fragment shader
#version 120

varying vec4 NDC;

void main()
{
   //get NDC and assign color based on it
   gl_FragColor = (1+ (NDC/NDC.w))*0.5;
}
