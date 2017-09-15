//
// Created by David Madden on 9/7/17.
//

#include "client.h"
#define MAXDATASIZE 100

bool Client::checkIp(string ip) {
//	regex r("\\d{1,3}(\\.\\d{1,3}){3})");
//	if (!regex_match(ip,r)) {
//		return false;
//	}
	struct sockaddr_in sa;
	if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 1) {
		return false;
	}
	return true;
}

bool Client::checkPort(string port) {
	for (int i = 0; i < (int) port.length(); ++i) {
		if (!isdigit(port[i])) {
			return false;
		}
	}
	int p = stoi(port);
	if (p > 65535 || p < 1024) {
		return false;
	}
	return true;
}

void Client::establishConnection(string ip, string port){
	//TODO Clean up
	struct hostent* host = gethostbyname(ip.c_str());
	sockaddr_in sendSockAddr;
	sendSockAddr.sin_family = AF_INET;
	sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
	sendSockAddr.sin_port = htons(stoi(port));

	int clientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(clientSock, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr)) < 0) {
		perror("connect fail");
		exit(EXIT_FAILURE);
	}

	printWelcome();

	int bytesRead, bytesWritten = 0;

	while(1) {
		char msg[1500];
		cout << "You: ";
		string data;
		getline(cin, data);
		memset(&msg, 0, sizeof(msg));//clear the buffer
		strcpy(msg, data.c_str());
		if(data == "exit")
		{
			send(clientSock, (char*)&msg, strlen(msg), 0);
			break;
		}
		bytesWritten += send(clientSock, (char*)&msg, strlen(msg), 0);

		memset(&msg, 0, sizeof(msg));//clear the buffer
		bytesRead += recv(clientSock, (char*)&msg, sizeof(msg), 0);

		cout << "Friend: " << msg << endl;
	}
	close(clientSock);
}

void Client::printWelcome() {
	cout << "Connected to a friend! You send first." << endl;
}