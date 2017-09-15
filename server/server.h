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
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
using std::cin;

class Server {
public:
	void establishConnection();
	void printWelcome(sockaddr_in address);
	void printConnection();
	void printMessage(char msg[]);
	string getMessage();
	bool checkMessageSize(string msg);
	void msgError();
};

#endif //P1C_SERVER_H
