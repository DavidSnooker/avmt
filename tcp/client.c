#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define RCV_BUF_SIZE 32
#define ECHO_MODE 0 

int main(int argc, char *argv[]);
int client (char *serv_ip, unsigned short serv_port, char *clnt_msg);
void receive(int sock, char *rcvd_msg, unsigned int msg_len);
void tcp_error(char *errorMessage);

int main(int argc, char *argv[]) {
	if (argc != 4) {
       fprintf(stderr, "Usage: %s <Server IP> <Port> <Message>\n",
               argv[0]);
       exit(1);
    }
	char *serv_ip = argv[1];
	unsigned short serv_port = atoi(argv[2]);
    char *clnt_msg = argv[3];
	client(serv_ip, serv_port, clnt_msg);
}

int client (char *serv_ip, unsigned short serv_port, char *clnt_msg) {
    int sock;
	struct sockaddr_in serv_addr;
    char rcvd_msg[RCV_BUF_SIZE];
    unsigned int msg_len;

	/* create socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        tcp_error("socket() failed");

    /* construct serv_addr */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(serv_ip);
    serv_addr.sin_port = htons(serv_port);

    /* connect */
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        tcp_error("connect() failed");

    msg_len = strlen(clnt_msg);

    /* send */
    if (send(sock, clnt_msg, msg_len, 0) != msg_len)
        tcp_error("send() sent a different number of bytes than expected");

    /* receive */
	if (ECHO_MODE)
		receive(sock, rcvd_msg, msg_len);

	/* close */
	close(sock);
    exit(0);
}

void receive(int sock, char *rcvd_msg, unsigned int msg_len) {
    int bytes_rcvd, total_bytes_rcvd = 0; 
    printf("received: ");
	while (total_bytes_rcvd < msg_len) {
        if ((bytes_rcvd = recv(sock, rcvd_msg, RCV_BUF_SIZE - 1, 0)) <= 0)
            tcp_error("recv() failed or connection closed prematurely");
        total_bytes_rcvd += bytes_rcvd;
        rcvd_msg[bytes_rcvd] = '\0';
        printf("%s", rcvd_msg);
    }
    printf("\n");
}

void tcp_error(char *err_msg) {
    perror(err_msg);
    exit(1);
}
