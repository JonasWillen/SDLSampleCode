# SDL_net sample code 
Some C-code examples  SDL_net 

- theMan: A figure in a empty space
- movingTheMan: A figure in empty space that you can move with the keyboard
- moveTheManWithMouse: A Figure in empty space that you can move with the mouse

## SDL_net 
- dnr: Demonstrate Hostname lookup try `./dnr www.kth.se`
- movingTheManWithUDP: Transmite the cordinates from the man to the upds.c server to be printed
- movingTwoMenWithUDP: Transmite the cordinates and communicate inbetween using the udpsMirror server
- movingTwoMenWithUDPandStruct: Transmite the cordinates using a Struct and communication inbetween using the udpsMirrorWithStruct server

## Server
- Server/updc: a smal text client
- Server/udps: a smal server just printf every thing its recives
- Server/updsMirror: a smal server that mirror each message retrived from two clients
- Server/updsMirrorWithStruct: a smal server that mirror each message retrived from two clients using structs

## TCP
- TCP/tcpc.c: a smal text client
- TCP/tcps.c: a smal text server
- TCP/tcpclient.c: a smal text client
- TCP/tcpserver.c: a smal text server
- TCP/tcpmulticlient.c: a chat client that works with tcpmultiserver
- TCP/tcpmultiserver.c: a smal singletread chat server 
