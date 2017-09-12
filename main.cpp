//
// Created by David Madden on 9/7/17.
//

//program is run via: "$ ./chat -p 3790 -s 192.168.47.232"

#include "server/server.h"
#include "client/client.h"
#include "help/help.h"

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
	Client client;
	string port;
	string servIp;

	if (argc == 1) {
		//TODO Create server
		cout << "Server" << endl;
	} else if (argc == 5) {
		//TODO Create client
		port = setPort(argv);
		servIp = setServerIp(argv);

		if (!client.checkIp(servIp) || !client.checkPort(port)){
			help.error();
		}

	} else if (argc == 2) {
		string flag = argv[1];

		if (flag.compare("-h") == 0){
			help.message();
		}

	} else {
		help.error();
	}
}