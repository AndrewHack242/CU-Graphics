Andrew Hack, HW4

Time spent: 7 hours

compiling: make
running: ./hw4

----KEYBINDS

arrows: rotate around scene

p: swap between perspective and orthogonal

page up & page down: change dimensions of space

s: stops the light
+/-: light up and down
[]: move light

esc: exit program


----CODE REUSE:
Code began as ex06

----OTHER NOTES:
I changed over to using glm for most things since I am using c++.
This means that I am now using glm functions instead of yours for most things, as well as glm types (like mat4).
created a complex object (companion cube) as a VBO instead of using OpenGL 2 functions.
For a while, something was wrong with the normals. 
I realized later that it was due to rotating the modelview matrix without rotating the normal matrix to match.

If I had more time this week, I wanted to try to add the cylinders in a different way.
I wanted to try to create a function that generated an array that would be drawn as a cylinder.