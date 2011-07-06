#ifndef __AVMT_CLIENT_H__
#define __AVMT_CLIENT_H__

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

int main(int argc, char *argv[]);
int client_default(char *clnt_msg); 
int client (char *serv_ip, unsigned short serv_port, char *clnt_msg);
void receive(int sock, char *rcvd_msg, unsigned int msg_len);
void tcp_error(char *errorMessage);

#endif /* __AVMT_CLIENT_H__ */
