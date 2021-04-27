# Example 06
EXE=final

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lglfw3 -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DUSEGLEW
LIBS=-lglfw3 -lglew -framework Cocoa -framework OpenGL -framework IOKit
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglfw -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
final.o: final.cpp CSCIx239.h companion.h
scene.o: scene.cpp scene.h
Object.o: Object.cpp Object.h
TextureHandler.o: TextureHandler.cpp TextureHandler.h
ShaderHandler.o: ShaderHandler.cpp ShaderHandler.h
surface.o: surface.cpp surface.h
Ring.o: Ring.cpp Ring.h
Pillar.o: Pillar.cpp Pillar.h
Lava.o: Lava.cpp Lava.h
Floor.o: Floor.cpp Floor.h
Shimmer.o: Shimmer.cpp Shimmer.h
LavaParticle.o: LavaParticle.cpp LavaParticle.h
ShimmerParticle.o: ShimmerParticle.cpp ShimmerParticle.h
ShimmerSpawner.o: ShimmerSpawner.cpp ShimmerSpawner.h
Dome.o: Dome.cpp Dome.h
TSurface.o: TSurface.cpp TSurface.h



fatal.o: fatal.c CSCIx239.h
errcheck.o: errcheck.c CSCIx239.h
print.o: print.c CSCIx239.h
axes.o: axes.c CSCIx239.h
loadtexbmp.o: loadtexbmp.c CSCIx239.h
loadobj.o: loadobj.c CSCIx239.h
projection.o: projection.c CSCIx239.h
lighting.o: lighting.c CSCIx239.h
elapsed.o: elapsed.c CSCIx239.h
fps.o: fps.c CSCIx239.h
shader.o: shader.c CSCIx239.h
noise.o: noise.c CSCIx239.h
cube.o: cube.c CSCIx239.h
sphere.o: sphere.c CSCIx239.h
cylinder.o: cylinder.c CSCIx239.h
torus.o: torus.c CSCIx239.h
icosahedron.o: icosahedron.c CSCIx239.h
teapot.o: teapot.c CSCIx239.h
mat4.o: mat4.c CSCIx239.h
initwin.o: initwin.c CSCIx239.h

#  Create archive
CSCIx239.a:fatal.o errcheck.o print.o axes.o loadtexbmp.o loadobj.o projection.o lighting.o elapsed.o fps.o shader.o noise.o cube.o sphere.o cylinder.o torus.o icosahedron.o teapot.o mat4.o initwin.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
final:final.o scene.o Object.o TextureHandler.o ShaderHandler.o surface.o Floor.o Ring.o Pillar.o Lava.o Shimmer.o LavaParticle.o ShimmerParticle.o ShimmerSpawner.o Dome.o TSurface.o CSCIx239.a
	g++ -O3 -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
