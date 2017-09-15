//
// Created by David Madden on 9/7/17.
//

#include "server.h"
//#define MAXPENDING 5
//#define PORT 5000
//#define MAXSIZE 140
//#define VERSION 457

int servSock;

void Server::establishConnection() {
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//port number can be hard coded, PORT=5000
	servAddr.sin_port = htons(PORT);
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

	if (listen(servSock, MAXPENDING) < 0) {
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	printWelcome(servAddr);

	sockaddr_in newSockAddr;
	socklen_t newSockAddrSize = sizeof(newSockAddr);

	int newServSock = accept(servSock, (sockaddr *)&newSockAddr, &newSockAddrSize);

	if (newServSock < 0) {
		perror("new socket fail");
		exit(EXIT_FAILURE);
	}

	printConnection();

	while(true) {
		Packet svrPacket;

		char msg[MAXSIZE];
		memset(&msg, 0, sizeof(msg));	//clear the buffer

//		recv(newServSock, (char*)&msg, sizeof(msg), 0);
		recv(newServSock, &svrPacket, sizeof(svrPacket), 0);

//		printMessage(msg);
		if (checkPacket(svrPacket)) {
			printMessage(svrPacket.msg);
		} else {
			printPacketError();
		}

		string data = getMessage();

		while (!checkMessageSize(data)) {
			msgError();
			data = getMessage();
		}

		svrPacket.msgLength = htons(data.length());
		strcpy(svrPacket.msg, data.c_str());

		memset(&msg, 0, sizeof(msg));	//clear the buffer
//		strcpy(msg, data.c_str());

		//send the message to client
//		send(newServSock, (char*)&msg, strlen(msg), 0);
		send(newServSock, &svrPacket, sizeof(svrPacket), 0);
	}
	//TODO signal handler
	close(newServSock);
	close(servSock);
}

void Server::printWelcome(sockaddr_in servAddr) {
	struct hostent *he;
	struct in_addr **addr_list;
	char hostname[128];

	gethostname(hostname, sizeof hostname);
	he = gethostbyname(hostname);
	addr_list = (struct in_addr **)he->h_addr_list;

	cout << "Welcome to Chat!" << endl;
	cout << "Waiting on connection on" << endl;
	cout << inet_ntoa(*addr_list[0]) << " port " << ntohs(servAddr.sin_port) << endl;
}

void Server::printConnection() {
	cout << "Found a friend! You receive first." << endl;
}

void Server::printMessage(char *msg) {
	cout << "Friend: " << msg << endl;
}

string Server::getMessage() {
	cout << "You: ";
	string data;
	getline(cin, data);
	return data;
}

bool Server::checkMessageSize(string msg) {
	if (msg.length() > MAXSIZE) {
		return false;
	}
	return true;
}

void Server::msgError() {
	cout << "Error: Input too long." << endl;
}

bool Server::checkPacket(Packet packet) {
	if (ntohs(packet.version) != VERSION) {
		return false;
	}
	if (ntohs(packet.msgLength) != strlen(packet.msg)) {
		return false;
	}
	return true;
}

void Server::printPacketError() {
	cout << "Malformed packet." << endl;
}