//
// Created by David Madden on 9/7/17.
//

#ifndef P1C_CLIENT_H
#define P1C_CLIENT_H

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

class Client {
public:
	bool checkIp(string ip);
	bool checkPort(string port);
	void establishConnection(string ip, string port);
	void printWelcome();
	void printMessage(char msg[]);
	string getMessage();
	bool checkMessageSize(string msg);
	void msgError();
};

#endif //P1C_CLIENT_H
