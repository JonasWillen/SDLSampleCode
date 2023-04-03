CFLAGS = -c -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib/ -lSDL2 

redAndBlue: main.o application.o
	gcc -o redAndBlue $(LDFLAGS) main.o application.o 
main.o: main.o
	gcc $(CFLAGS) main.c
spaceman.o: application.o
	gcc $(CFLAGS) application.c
clean:
	rm *.o
	rm redAndBlue
