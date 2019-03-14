LIBDIR = -L/usr/include/X11/
CC = gcc
CFLAGS = $(COMPILERFLAGS)
LIBRARIES = -lX11 -lXmu -lglut -lGL -lGLU -lm

cube_axis : cube_axis.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $? $(LIBRARIES)

clean:
	rm -f *.o
