CC = gcc
CFLAGS = -Wall
LDFLAGS = -lcurses

all: echo-client echo-server
	@echo Compilation complete

echo-client: echo-client.o
	$(CC) $(CFLAGS) echo-client.o -o echo-client $(LDFLAGS)

echo-server: echo-server.o
	$(CC) $(CFLAGS) echo-server.o -o echo-server

echo-client.o: echo-client.c
	$(CC) $(CFLAGS) -c echo-client.c

echo-server.o: echo-server.c
	$(CC) $(CFLAGS) -c echo-server.c

clean:
	rm -f *.o echo-client echo-server
	@echo Clean complete
