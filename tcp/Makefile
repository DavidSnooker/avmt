CROSS_COMPILE = arm-none-linux-gnueabi-
CC = gcc

CFLAGS = -I.
EXEC = server client
DEPS = server.h client.h error.h handle_client.h
SERVER_OBJ = server.o error.o handle_client.o
CLIENT_OBJ = client.o error.o
SERVER_SRC = server.c error.c handle_client.c
CLIENT_SRC = client.c error.c

arm: $(SERVER_SRC) $(CLIENT_SRC)
	$(CROSS_COMPILE)$(CC) -static $(SERVER_SRC) -o server
	$(CROSS_COMPILE)$(CC) -static $(CLIENT_SRC) -o client
	adb -s emulator-5554 push client /data/
	adb -s emulator-5556 push server /data/

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(EXEC)

server: $(SERVER_OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

client: $(CLIENT_OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(EXEC) *.o *~ *.swp

