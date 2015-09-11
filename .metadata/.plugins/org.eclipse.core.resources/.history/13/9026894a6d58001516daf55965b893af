all: GUI

clean:
	-rm GUI.o GUI

GUI: GUI.o
	gcc  -o GUI GUI.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs`

GUI.o: GUI.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm GUI.c `sdl-config --cflags`
