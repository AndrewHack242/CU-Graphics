# Example 01
EXE=hw5

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
hw5.o: hw5.cpp CSCIx229.h camera.h AndrewsHelpers.h companion.h light.h
light.o: light.c CSCIx229.h
camera.o: camera.h CSCIx229.h
companion.o: companion.h CSCIx229.h
AndrewsHelpers.o: AndrewsHelpers.h CSCIx229.h
fatal.o: fatal.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
print.o: print.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
object.o: object.c CSCIx229.h
project.o: project.c CSCIx229.h

#  Create archive
CSCIx229.a:fatal.o errcheck.o print.o loadtexbmp.o object.o project.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
hw5:hw5.o camera.o companion.o light.o AndrewsHelpers.o CSCIx229.a
	gcc -O3 -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
