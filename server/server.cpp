//
// Created by David Madden on 9/7/17.
//

#include "server.h"
#define MAXPENDING 5

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
		perror("socket fail");
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

void Server::listenToPort() {
	if (listen(sock, MAXPENDING) < 0) {
		perror("listen fail");
		exit(EXIT_FAILURE);
	}
}

void Server::establishConnection() {
	//TODO Clean up
	/**
	 * PF_INET for TCP/IP sockets
	 * SOCK_STREAM is TCP
	 * 0 is for Internet protocol
	 */
	sock = socket(PF_INET, SOCK_STREAM, 0);

	if (sock < 0) {
		perror("socket fail");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	//TODO change 8080 to some random, free port number above 1024
	address.sin_port = htons(8080);

	if(bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(sock, MAXPENDING) < 0) {
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	printWelcome(address);

	struct sockaddr_storage their_addr;
	socklen_t addr_size;

	addr_size = sizeof their_addr;
	int connection = accept(sock, (sockaddr *)&their_addr, &addr_size);
	if (connection < 0) {
		perror("connection failed");
		exit(EXIT_FAILURE);
	}
}

void Server::printWelcome(sockaddr_in address) {
	cout << "Welcome to Chat!" << endl;
	cout << "Waiting on connection on" << endl;
	cout << address.sin_addr.s_addr << " port " << address.sin_port << endl;
}