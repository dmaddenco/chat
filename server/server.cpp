//
// Created by David Madden on 9/7/17.
//

#include "server.h"
#define MAXPENDING 5

int servSock;
int portBind;

void Server::connectToSocket() {
	/**
	 * PF_INET for TCP/IP sockets
	 * SOCK_STREAM is TCP
	 * 0 is for Internet protocol
	 */
	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock < 0) {
		perror("socket fail");
		exit(EXIT_FAILURE);
	}
}

void Server::bindToPort() {
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//TODO change 8080 to some random, free port number above 1024
	servAddr.sin_port = htons(8080);

	if(bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}

void Server::listenToPort() {
	if (listen(servSock, MAXPENDING) < 0) {
		perror("listen fail");
		exit(EXIT_FAILURE);
	}
}

void Server::establishConnection() {
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//TODO change 8080 to some random, free port number above 1024
	servAddr.sin_port = htons(8080);
	/**
	 * PF_INET for TCP/IP sockets
	 * SOCK_STREAM is TCP
	 * 0 is for Internet protocol
	 */
	servSock = socket(PF_INET, SOCK_STREAM, 0);

	if (servSock < 0) {
		perror("socket fail");
		exit(EXIT_FAILURE);
	}

	if(bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	printWelcome(servAddr);

	if (listen(servSock, MAXPENDING) < 0) {
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	sockaddr_in newSockAddr;
	socklen_t newSockAddrSize = sizeof(newSockAddr);

	int newServSock = accept(servSock, (sockaddr *)&newSockAddr, &newSockAddrSize);

	if (newServSock < 0) {
		perror("new socket fail");
		exit(EXIT_FAILURE);
	}


//	struct sockaddr_storage their_addr;
//	socklen_t addr_size;
//
//	addr_size = sizeof their_addr;
//	int connection = accept(servSock, (sockaddr *)&their_addr, &addr_size);
//	if (connection < 0) {
//		perror("connection failed");
//		exit(EXIT_FAILURE);
//	}
//	char s[INET6_ADDRSTRLEN];
//	while(1) {  // main accept() loop
//		socklen_t sin_size = sizeof their_addr;
//		int new_fd = accept(servSock, (struct sockaddr *) &their_addr, &sin_size);
//		if (new_fd == -1) {
//			perror("accept");
//			continue;
//		}
//
//		inet_ntop(their_addr.ss_family, ((struct sockaddr *) &their_addr), s, sizeof s);
//		printf("server: got connection from %s\n", s);
//
//		if (send(new_fd, "Hello, world!", 13, 0) == -1) {
//			perror("send");
//			exit(EXIT_FAILURE);
//		}
//		close(new_fd);
//		close(new_fd);  // parent doesn't need this
//	}
}

void Server::printWelcome(sockaddr_in servAddr) {
	cout << "Welcome to Chat!" << endl;
	cout << "Waiting on connection on" << endl;
	cout << servAddr.sin_addr.s_addr << " port " << servAddr.sin_port << endl;
}