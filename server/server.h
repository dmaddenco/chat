//
// Created by David Madden on 9/7/17.
//

#ifndef P1C_SERVER_H
#define P1C_SERVER_H

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <netinet/in.h>
#include <sys/socket.h>

class Server {
public:
	void connectToSocket();
	void bindToPort();
	void listenToPort();
	void establishConnection();
	void printWelcome(sockaddr_in address);
};

#endif //P1C_SERVER_H
