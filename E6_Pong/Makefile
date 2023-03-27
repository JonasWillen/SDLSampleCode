# based on https://austinmorlan.com/posts/pong_clone/
CFLAGS = -c -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib/ -lSDL2 -lSDL2_ttf

Pong: main.o application.o vec2.o ball.o paddle.o playerScore.o
	gcc -o pong $(LDFLAGS) main.o application.o ball.o vec2.o paddle.o playerScore.o
main.o: main.c
	gcc $(CFLAGS) main.c
applicaiton.o: application.c 
	gcc $(CFLAGS) application.c 
ball.o: ball.c
	gcc $(CFLAGS) ball.c 
vec2.o: vec2.c
	gcc $(CFLAGS) vec2.c 
paddle.o: paddle.c
	gcc $(CFLAGS) paddle.c
playerScore.o: playerScore.c
	gcc $(CFLAGS) playerScore.c


clean:
	rm *.o pong

		
