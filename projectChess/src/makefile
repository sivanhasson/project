all: controllers

clean:
	-rm controllers.o controllers

controllers: controllers.o
	gcc  -o controllers controllers.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs`

controllers.o: controllers.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm controllers.c `sdl-config --cflags`
