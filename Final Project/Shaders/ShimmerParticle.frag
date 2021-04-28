//  Shimmer fragment shader

#version 430
#extension GL_EXT_gpu_shader4 : enable //enable bitwise operations

#define PI 3.1415926538

uniform float dX;
uniform float dY;
uniform sampler2D screenTex;
uniform vec2 resolution;

//  Model coordinates from vertex shader
uniform float time;

out vec4 FragColor;

const int r = 2;
float blurdiv = 1.0/((r*2 + 1)*(r*2 + 1));

//use int to pass offset data
//get current pixel with offset, blur with surrounding pixels - gl_FragCoord

vec4 pixel(float dx,float dy)
{
    vec2 pos = (gl_FragCoord.xy/ resolution) + vec2(dx*dX,dy*dY); //convert position to 1 scale
	return texture2D(screenTex,pos); //get pixel
}

vec4 blur(int dx, int dy)
{
	return pixel(dx * dX,dy * dY); //blurmap[dx + 2][dy + 2] * 
}

vec4 blurpixel(int dx,int dy)
{
	vec4 color = vec4(0,0,0,0);
	for (int x = -r; x <= +r; ++x)
	{
		for (int y = -r; y <= +r; ++y)
		{
		color += pixel(x + dx,y + dy)*blurdiv;
		}
	}
	return	color;
}

void main()
{
	float factor = 5;
	float mod1 = 5;
	float mod2 = 3;
	int x = 0, y = 0;
	x = int(factor * sin(mod1 * (gl_FragCoord.x/ resolution) * (sin(time * 0.9) + mod2) * PI)); //probably needs some tweaking, but good
	y = int(factor * sin(mod1 * (gl_FragCoord.y/ resolution) * (cos(time*0.75) + mod2) * PI));;
	vec4 color = blurpixel(x,y);

	FragColor = color;
}
