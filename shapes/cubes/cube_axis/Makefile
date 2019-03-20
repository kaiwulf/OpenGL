LIBDIR = -L/usr/include/X11/
CC = gcc
CFLAGS = $(COMPILERFLAGS)
LIBRARIES = -lX11 -lXmu -lglut -lGL -lGLU -lm

cube_axis : cube_axis.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $? $(LIBRARIES)

cube_axis_move : cube_axis_move.o framemath.o vectormath.o matrixmath.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $? $(LIBRARIES)

framemath.o : ../../../glTools/framemath.c matrixmath.o
	$(CC) $(CFLAGS) -c $<

vectormath.o : ../../../glTools/vectormath.c
	$(CC) $(CFLAGS) -c $<

matrixmath.o : ../../../glTools/matrixmath.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
