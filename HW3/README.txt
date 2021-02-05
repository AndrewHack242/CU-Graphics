Andrew Hack, HW3

Time spent: 5 hours

compiling: make
running: ./hw3

----KEYBINDS

arrows: rotate around scene

p: swap between perspective and orthogonal

m/shift+m: toggle shaders

z/shift+z: zoom

o/shift+o: change objects

page up & page down: change dimensions of space

esc: exit program


----CODE REUSE:
Code began as a re-use from HW2

----Observations
I think my computer is just too powerful, different shaders were giving different results, but modifying a shader to use ifs 
instead of a mix or dividing over and over instead of doing it once seemingly did nothing to the fps.

-spawning 1000 objects always seems to give 77 fps with a shader, but the default pipeline gives less.

This leads me to believe that my fragment shader is having a miniscule impact, in fact it seemed to gain frames when I increased the resolution of the window.
The majority of the limiting on all of the shaders seems to be coming from the vertex shader, seeing as adding more objects really impacts the performance.

Honestly, the things I have seen working on this make so little sense to me that I'm beginning to think that there is some windows setting that is messing with me.
An alternate idea is that I am somehow cpu capped, though I find this unlikely.

----OTHER NOTES:
