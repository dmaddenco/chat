//
// Created by David Madden on 9/7/17.
//

#ifndef P1C_SERVER_H
#define P1C_SERVER_H
#define MAXPENDING 5
#define PORT 5000
#define MAXSIZE 140
#define VERSION 457

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>

#include "packet/packet.h"

class Server {
public:
	void establishConnection();
	void printWelcome(sockaddr_in address);
	void printConnection();
	void printMessage(char msg[]);
	string getMessage();
	bool checkMessageSize(string msg);
	void msgError();
	bool checkPacket(Packet packet);
	void printPacketError();
};

#endif //P1C_SERVER_H
