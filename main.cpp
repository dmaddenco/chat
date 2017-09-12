#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include <string>
using std::string;

#include "server.h"
#include "client.h"
#include "help.h"

string setPort(char* flags[]) {
	string flag = flags[1];
	if (flag == ("-p")) {
		return flags[2];
	}
	flag = flags[3];
	if (flag == ("-p")) {
		return flags[4];
	}
	return 0;
}

string setServerIp(char* flags[]) {
	string flag = flags[1];
	if (flag == ("-s")) {
		return flags[2];
	}
	flag = flags[3];
	if (flag == ("-s")) {
		return flags[4];
	}
	return 0;
}

int main(int argc, char* argv[]) {
	Help help;
	string port;
	string servIp;

	if (argc == 1) {
		//TODO Create server
		cout << "Server" << endl;
	} else if (argc == 5) {
		//TODO Create client
		port = setPort(argv);
		servIp = setServerIp(argv);
	} else if (argc == 2) {
		string flag = argv[1];

		if (flag.compare("-h") == 0){
			help.message();
		}

	} else {
		help.error();
	}
}