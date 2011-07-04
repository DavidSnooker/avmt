CROSS_COMPILE = arm-none-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc
CFLAGS = -static

server_src = server.c error.c handle_client.c
server_hdr = server.h error.h handle_client.h
server_obj = server

client_src = client.c error.c
client_hdr = client.h error.h
client_obj = client

obj = $(server_obj) $(client_obj)

all: $(obj)

server: $(server_src) 
	$(CC) $(CFLAGS) $^ -o $@

client: $(client_src) 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(obj) *.o *~ *.swp

install:
	adb -s emulator-5554 push client /data/
	adb -s emulator-5556 push server /data/
