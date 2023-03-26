CFLAGS = -c -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib/ -lSDL2 -lSDL2_ttf

HelloWorld: main.o
	gcc -o HelloWorld $(LDFLAGS) main.o 
main.o: main.c
	gcc $(CFLAGS) main.c
