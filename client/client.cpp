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
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(ip.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(EXIT_FAILURE);
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
							 p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		exit(EXIT_FAILURE);
	}

	inet_ntop(p->ai_family, ((struct sockaddr *)p->ai_addr), s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure

	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv");
		exit(EXIT_FAILURE);
	}

	buf[numbytes] = '\0';

	printf("client: received '%s'\n",buf);

	close(sockfd);

	printWelcome();

}

void Client::printWelcome() {
	cout << "Connected to a friend! You send first." << endl;
}