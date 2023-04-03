
CFLAGS = -c -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib/ -lSDL2 -lSDL2_ttf

Pong: main.o application.o ball.o
	gcc -o redAndBlue $(LDFLAGS) main.o application.o ball.o  
main.o: main.c
	gcc $(CFLAGS) main.c
applicaiton.o: application.c
	gcc $(CFLAGS) application.c
ball.o: ball.c
	gcc $(CFLAGS) ball.c	
clean:
	rm *.o
	rm redAndBlue
