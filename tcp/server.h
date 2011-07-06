#ifndef __AVMT_SERVER_H__
#define __AVMT_SERVER_H__

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

int main(int argc, char *argv[]);
int server_default(); 
int server(unsigned short serv_port);
void handle_client(int clnt_sock);
void echo(int clnt_sock, char *rcvd_msg, int msg_size); 
void tcp_error(char *err_msg);

#endif /* __AVMT_SERVER_H__ */
