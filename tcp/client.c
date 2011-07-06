#include "client.h"

#define RCV_BUF_SIZE 32
#define ECHO_MODE 1

/* default ip 10.0.2.2, port 7000 */
char *serv_ip = "10.0.2.2";
unsigned short serv_port = 7000;

int main(int argc, char *argv[]) {
	char *clnt_msg = NULL;

	if (argc < 2 || argc > 4) {
       fprintf(stderr, "Usage: %s [Server IP] [Port] <Message>\n",
               argv[0]);
       exit(1);
    }

	if (argc == 4) {
		serv_ip = argv[1];
		serv_port = atoi(argv[2]);
	    clnt_msg = argv[3];
	} else if (argc == 3) {
		serv_ip = argv[1];
	    clnt_msg = argv[2];
	} else if (argc == 2) {
		clnt_msg = argv[1];
	}

	client(serv_ip, serv_port, clnt_msg);
}

int client_default(char *clnt_msg) {
	client(serv_ip, serv_port, clnt_msg);
}

int client (char *serv_ip, unsigned short serv_port, char *clnt_msg) {
    int sock = 0;
	struct sockaddr_in serv_addr;
    char rcvd_msg[RCV_BUF_SIZE];
    unsigned int msg_len = 0;

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
    int bytes_rcvd = 0, total_bytes_rcvd = 0; 
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
