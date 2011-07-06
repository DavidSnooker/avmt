#include "server.h"

#define RCV_BUF_SIZE 32
#define MAX_PENDING 5
#define ECHO_MODE 1
#define DEFAULT_MODE 1

/* default port 7000 */
unsigned short serv_port = 7000;

int main(int argc, char *argv[]) {
	if (DEFAULT_MODE) {
		fprintf(stdout, "avmt server running on guest os at port %d\n", serv_port);
		server_default();
		exit(0);
	}

	if (argc < 1 || argc > 2) {
		fprintf(stderr, "Usage:  %s [Server Port]\n", argv[0]);
		exit(1);
	}
	
	if (argc == 2)
		serv_port = atoi(argv[1]);
	server(serv_port);
}

int server_default() {
	return server(serv_port);
}

int server(unsigned short serv_port) {
	int serv_sock = 0;
	int clnt_sock = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	unsigned int clnt_addr_len = 0;

	/* create socket */
	if ((serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		tcp_error("socket() failed");

	/* construct serv_addr */
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(serv_port);

	/* bind */
	if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		tcp_error("bind() failed");

	/* listen */
	if (listen(serv_sock, MAX_PENDING) < 0)
		tcp_error("listen() failed");

	while (1) {
		clnt_addr_len = sizeof(clnt_addr);

		/* accept */
		if ((clnt_sock = accept(serv_sock, 
			(struct sockaddr *) &clnt_addr, &clnt_addr_len)) < 0)
			tcp_error("accept() failed");

		/* clnt_sock is connected to a client! */
		printf("[from %s]\n", inet_ntoa(clnt_addr.sin_addr));

		handle_client(clnt_sock);
	}
	/* NOT REACHED */
}

void handle_client(int clnt_sock) {
	char rcvd_msg[RCV_BUF_SIZE];
	int msg_size = 0;

	/* receive */
	if ((msg_size = recv(clnt_sock, rcvd_msg, RCV_BUF_SIZE, 0)) < 0)
		tcp_error("recv() failed");

	/* handle */
	while (msg_size > 0) {
		rcvd_msg[msg_size] = '\0';
		printf("received: %s\n", (char *)&rcvd_msg);
		
		if (ECHO_MODE)
			echo(clnt_sock, rcvd_msg, msg_size);
		
		if ((msg_size = recv(clnt_sock, rcvd_msg, RCV_BUF_SIZE, 0)) < 0)
			tcp_error("recv() failed");
	}

	/* close */
	close(clnt_sock);
}

void echo(int clnt_sock, char *rcvd_msg, int msg_size) {
	if (send(clnt_sock, rcvd_msg, msg_size, 0) != msg_size)
		tcp_error("send() failed");
}

void tcp_error(char *err_msg) {
	perror(err_msg);
	exit(1);
}
