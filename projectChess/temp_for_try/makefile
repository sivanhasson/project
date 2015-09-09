all: try

clean:
	-rm try.o try

try: try.o
	gcc  -o try try.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs`

try.o: try.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm try.c `sdl-config --cflags`
