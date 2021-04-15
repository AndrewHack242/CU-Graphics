//  Candycane fragment shader
//  derived from brick example which was
//  Derived from Orange Book Chapter 6 by Charles Gruenwald
#version 120

//  Hardwire candycane dimensions and color
const vec3 StripeColor1  = vec3(1.0,1.0,1.0);
const vec3 StripeColor2 = vec3(0.85,0.0,0.0);
const vec2 StripeSize = vec2(1.0,0.4);
const vec2 Midpoint = vec2(1.1,0.5); //split each area into halves via horizontal line

//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
uniform float time;

void main()
{
   //  Divide by brick size for unit coordinates
   vec2 position = ModelPos/StripeSize;
   //  Stagger rows
   if (fract(0.5*position.y)>0.5) position.x += 0.5;
   //  Scroll bricks at 2.5 bricks per second
   position.y += 2.5*time;
   //  Don't care about the integer part
   position = fract(position);
   //  Snap to 0 or 1
   vec2 striper = step(position,Midpoint);
   //  Interpolate color (0 or 1 gives sharp transition)
   vec3 color  = mix(StripeColor1, StripeColor2, striper.x*striper.y);
   //  Adjust color intensity for lighting (interpolated from vertex shader values)
   color *= LightIntensity;
   //  Pad color with alpha
   gl_FragColor = vec4(color,1.0);
}
