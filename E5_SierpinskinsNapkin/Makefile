CFLAGS = -c -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib/ -lSDL2 

HelloWorld: main.o
	gcc -o HelloWorld $(LDFLAGS) main.o 
main.o: main.c
	gcc $(CFLAGS) main.c
oneline:
	gcc -o HelloWorld -I/opt/homebrew/include/SDL2  -L/opt/homebrew/lib/ -lSDL2 main.c
clean:
	rm *.o
	rm HelloWorld
