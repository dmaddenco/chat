//
// Created by David Madden on 9/7/17.
//

#ifndef P1C_CLIENT_H
#define P1C_CLIENT_H

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <regex>
using std::regex;
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <netinet/in.h>

class Client {
public:
	bool checkIp(string ip);
	bool checkPort(string port);
	void establishConnection(string ip, string port);
	void printWelcome();
};

#endif //P1C_CLIENT_H
