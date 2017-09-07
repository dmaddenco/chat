#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include <string>
using std::string;

#include "server.h"
#include "client.h"
#include "help.h"

int main(int argc, char* argv[]) {
	Help help;
	if (argc == 1) {
		//TODO Create server
		cout << "Server" << endl;
	} else if (argc == 5) {
		//TODO Create client
		cout << "Client" << endl;
	} else if (argc == 2) {
		string flag = argv[1];
		if (flag.compare("-h") == 0){
			help.message();
		}
	} else {
		help.error();
	}
}