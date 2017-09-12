//
// Created by David Madden on 9/7/17.
//

#include "server.h"

int sock;
int portBind;

void Server::connectToSocket() {
	/**
	 * PF_INET for TCP/IP sockets
	 * SOCK_STREAM is TCP
	 * 0 is for Internet protocol
	 */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
}

void Server::bindToPort() {
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	//TODO change 8080 to some random, free port number above 1024
	address.sin_port = htons(8080);

	if(bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}