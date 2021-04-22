//  Lava fragment shader
//  Derived from Orange Book Chapter 6 by Charles Gruenwald
#version 120

//  Hardwire brick dimensions and color
const vec3 BrickColor  = vec3(1.0,0.3,0.2);
const vec3 MortarColor = vec3(0.85,0.86,0.84);
const vec2 BrickSize   = vec2(1,1);
const vec2 BrickPct    = vec2(0.90,0.85);

const vec3 minColor = vec3(0.776,0.227,0.027);
const vec3 maxColor = vec3(0.988,0.973,0.482);

//  Model coordinates from vertex shader
uniform float time;
in vec2  ModelPos;


//step(e,x) return 0 if x < e, else 1
//fract(x) x - x(floor), gets fractional part
//mix(x,y,a); interpolates betweenx and y using a to rate x*(1−a)+y*a .

//borrowed from https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83 with slight modification
#define M_PI 3.14159265358979323846

float rand(vec2 co){return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);}
float rand (vec2 co, float l) {return rand(vec2(rand(co), l));}
float rand (vec2 co, float l, float t) {return rand(vec2(rand(co, l), t));}

float perlin(vec2 p, float dim, float time) {
	vec2 pos = floor(p * dim);
	vec2 posx = pos + vec2(1.0, 0.0);
	vec2 posy = pos + vec2(0.0, 1.0);
	vec2 posxy = pos + vec2(1.0);
	
	float c = rand(pos, dim, time);
	float cx = rand(posx, dim, time);
	float cy = rand(posy, dim, time);
	float cxy = rand(posxy, dim, time);
	
	vec2 d = fract(p * dim);
	d = -0.5 * cos(d * M_PI) + 0.5;
	
	float ccx = mix(c, cx, d.x);
	float cycxy = mix(cy, cxy, d.x);
	float center = mix(ccx, cycxy, d.y);
	
	return center * 2.0 - 1.0;
}


void main()
{
   //  Divide by brick size for unit coordinates
   vec2 position = ModelPos;

   //slowmoving
   position.x += 0.15*time;

   float flux = 1.25+0.5*sin(time);

   //vec3 color = vec3(position.x, position.y, 0);
   vec3 color = mix(minColor,maxColor,perlin(position, 20, 0.0)*flux); 

   //  Pad color with alpha
   gl_FragColor = vec4(color,1.0);
}
