CROSS_COMPILE = arm-none-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc
CFLAGS = -static

server_src = server.c 
server_hdr = server.h
server_obj = server

client_src = client.c
client_hdr = client.h
client_obj = client

obj = $(server_obj) $(client_obj)

all: $(obj)

server: $(server_src) $(server_hdr)
	$(CC) $(CFLAGS) $^ -o $@

client: $(client_src) $(client_hdr)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(obj) *.o *~ *.swp

install:
	adb -s emulator-5554 push client /data/local/
