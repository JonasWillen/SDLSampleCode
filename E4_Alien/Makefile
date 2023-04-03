# A simple Makefile for compiling small SDL projects

theGame: main.o spaceman.o Alien.o world.o
	gcc -o theGame main.o spaceman.o Alien.o world.o -L/opt/homebrew/lib/ -lSDL2 -lSDL2_image
main.o: main.c
	gcc -c main.c -I/opt/homebrew/include/SDL2
spaceman.o: spaceman.c
	gcc -c spaceman.c
world.o: world.c
	gcc -c world.c
Alien.o: alien.c
	gcc -c Alien.c
clean: 
	rm *.o
	rm theGame