//  tiny hexagon fragment shader
//  derived from brick example which was
//  Derived from Orange Book Chapter 6 by Charles Gruenwald
#version 120

//  Hardwire brick dimensions and color
const vec3 BrickColor  = vec3(1.0,0.3,0.2);
const vec3 MortarColor = vec3(0.39,0.051,0.49);
const float a   = 0.02; //short = 1.732 (sqrt(3)) * a * 0.5 || long = a
const float shorta = 1.732 * a;
const float border = 0.04;

const float calca = 1.0/6.0;


const vec2 unit = vec2(2*shorta,6*a);
const float vertborder = border * unit[0] / unit[1];

//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
uniform float time;

void main()
{
   //  Divide by brick size for unit coordinates
   vec2 position = ModelPos / unit;
   //  Scroll bricks at 0.5 hexagons per second
   position.y += 0.5*time;
   //  Don't care about the integer part
   position = fract(position);
   //  make the hexagon outline in seperate color with sharp divide
   //right side
   vec2 use1a1 = step(position,vec2(1,1 - calca));
   vec2 use1a2 = step(-position,-vec2(1 - (border/2),3*calca - 0.01)); //invert for greater than

   //right top
   vec2 use2a1 = step(position,vec2(1.0, -(2*calca)*position.x + 1 + calca + vertborder/4)); //y=mx+b
   vec2 use2a2 = step(-position,-vec2(0.5, -(2*calca)*position.x + 1 + calca - 3*vertborder/4));

   //right bottom
   vec2 use3a1 = step(position,vec2(1.0, 2*calca*position.x -calca + 2*calca + vertborder/4));
   vec2 use3a2 = step(-position,-vec2(0.5, 2*calca*position.x -calca + 2*calca -3*vertborder/4));
   
   //left
   vec2 use4a1 = step(position,vec2(border/2,1 - calca));
   vec2 use4a2 = step(-position,-vec2(0,3*calca - 0.01));
   
   //left top
   vec2 use5a1 = step(position,vec2(0.5, 2*calca*position.x + 1-calca + vertborder/4));
   vec2 use5a2 = step(-position,-vec2(0.0, 2*calca*position.x + 1-calca- 3*vertborder/4));
   
   //left bottom
   vec2 use6a1 = step(position,vec2(0.5, (-2*calca)*position.x + 3*calca + vertborder/4));
   vec2 use6a2 = step(-position,-vec2(0.0, (-2*calca)*position.x + 3*calca - 3*vertborder/4));

   //bottom
   vec2 use7a1 = step(position,vec2(0.5+border/2,2*calca));
   vec2 use7a2 = step(-position,-vec2(0.5-border/2,0));
   
   //top
   vec2 use8a1 = step(position,vec2(0.5+border/2,1));
   vec2 use8a2 = step(-position,-vec2(0.5-border/2,1-0.01));


   //  Interpolate color (0 or 1 gives sharp transition)
   vec3 color  = mix(BrickColor, MortarColor, 
      (use1a1.x * use1a1.y * use1a2.x * use1a2.y)
    + (use2a1.x * use2a1.y * use2a2.x * use2a2.y * (1- (use1a1.x * use1a1.y * use1a2.x * use1a2.y)))
    + (use3a1.x * use3a1.y * use3a2.x * use3a2.y * (1- (use1a1.x * use1a1.y * use1a2.x * use1a2.y)))
    + (use4a1.x * use4a1.y * use4a2.x * use4a2.y)
    + (use5a1.x * use5a1.y * use5a2.x * use5a2.y * (1- (use4a1.x * use4a1.y * use4a2.x * use4a2.y)))
    + (use6a1.x * use6a1.y * use6a2.x * use6a2.y * (1- (use4a1.x * use4a1.y * use4a2.x * use4a2.y)))
    + (use7a1.x * use7a1.y * use7a2.x * use7a2.y * (1 - (use6a1.x * use6a1.y * use6a2.x * use6a2.y)) * (1 - (use3a1.x * use3a1.y * use3a2.x * use3a2.y)))
    + (use8a1.x * use8a1.y * use8a2.x * use8a2.y * (1 - (use5a1.x * use5a1.y * use5a2.x * use5a2.y)) * (1 - (use2a1.x * use2a1.y * use2a2.x * use2a2.y)))
    ); //check if pixel is in any of the zones. extended parts with 1- at the beginning are for preventing overlaps that mess with the color.
   //  Adjust color intensity for lighting (interpolated from vertex shader values)
   color *= LightIntensity;
   //  Pad color with alpha
   gl_FragColor = vec4(color,1.0);
}
