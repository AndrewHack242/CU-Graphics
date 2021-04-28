Andrew Hack, final submission

compiling: make
running: ./final

I made sure this compiles on linux, but my VM could not run GLSL 4, so I could not test it fully

-------------------------------------------------------------------------------------------------------

Controls:

-arrows: look around
-wasd: move
-space/ctrl: move up or down
-esc: close the window
-L: teleports the light to your current position (orbits around you)
-R: refreshes the scene file (not something you should need)

-------------------------------------------------------------------------------------------------------

-------Things to note and that I am proud of
-Tesselation: The pillars and domes make use of tesselation to get there smooth shapes.
The normals are calculated at each tesselated point.
The domes are simply normalizing the distance of each point, but the pillar uses a quadratic equation to calculate points and calculus to find the normals.
The specular lighting interacting with these objects is mesmerizing

-Procedural Textures: The lava uses a Procedural texture to produce its liquidy effect.

-Heat wave/blur effect: Above the lava there is a blur/wave effect meant to imitate waves above something that is very hot.
This functions by drawing a thin surface above the lava as well as a bunch of particles, but instead of drawing their color to the screen, they implement pixel manipulation via a stored texture of the screen.
After all objects are rendered, the screen is copied to a texture. From here a nearby pixel is selected via sin/cos functions and blurred, creating a blurred wavy effect.
The particles are 3D icosahedrons rendered off of a single point in the geometry shader. While this is not the most efficient way to do this, I wished to demonstrate a use of the geometry shader that did not involve tesselation.

-Particles: Lava particles popping off of the lava are utilized as more traditional, 2D particles

-------Shortcomings
-I got caught up on quite a few bugs during the creation of this project, and as a result had to cut a lot of what I had planned, namely the second scene.

-------Why I deserve an A
-I have demonstrated that I understand the subject material of the class, especially shaders, and have applied this knowledge to create specific desired effects in unique ways that expand upon what we learned in class.