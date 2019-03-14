LIBDIR = -L/usr/X11R6/lib
CC = gcc
CFLAGS = $(COMPILERFLAGS)
LIBRARIES = -lX11 -lXmu -lglut -lGL -lGLU -lm

sphereworld : sphereworld.o framemath.o vectormath.o torus.o matrixmath.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $? $(LIBRARIES)

framemath.o : ../../glTools/framemath.c matrixmath.o
	$(CC) $(CFLAGS) -c $<

vectormath.o : ../../glTools/vectormath.c
	$(CC) $(CFLAGS) -c $<

matrixmath.o : ../../glTools/matrixmath.c
	$(CC) $(CFLAGS) -c $<

torus.o : ../../glTools/torus.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
