// Rule 110
#version 120

uniform float dX;
uniform float dY;
uniform sampler2D img;

//  Get cell value (stored in a)
bool cell(vec2 d)
{
   return texture2D(img,gl_TexCoord[0].st+d).a > 0.5;
}

//  Evaluate cell
void main()
{
   float color = 0;
   vec2 left = vec2(-dX, -dY);
   vec2 middle = vec2(0, -dY);
   vec2 right = vec2(dX, -dY);

   int sum = int(cell(left)) + int(cell(middle)) + int(cell(right));
   if(sum == 2)
   {
      color = 1;
   }
   else if(!cell(left) && cell(middle) && !cell(right))
   {
      color = 1;
   }
   else if(cell(left) && !cell(middle) && !cell(right))
   {
      color = 1;
   }
   else if(cell(vec2(0,0)))
   {
      color = 1;
   }

    

   gl_FragColor = vec4(color, 0, 0, color);
}