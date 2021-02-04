Andrew Hack, HW2

Time spent: 3 hours

compiling: make
running: ./hw2

----KEYBINDS

arrows: rotate around scene

p: swap between perspective and orthogonal

m/shift+m: toggle shaders

z/shift+z: zoom

o/shift+o: change objects

page up & page down: change dimensions of space

esc: exit program


----CODE REUSE:
Code is very similar to your ex3, started as a copy. Added my own companion cubes as 
an additional object choice, and made the required shaders.


----OTHER NOTES:
I created 3 procedrual textures using shaders.

1) a texture with slowly moving hexagons. These Hexagons are rendered through a tequnique 
	similar to your bricks tequnique, and yet quite a bit more detail is required to make 
	the hexagon shapes.
2) a smaller version of the hexagon texture that plays better with the zoom feature.
3) The first procedrual texture that I made while making sure I understood what I was doing.
	Simple stripe effect that moves on the y-axis.