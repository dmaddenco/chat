//
// Created by David Madden on 9/7/17.
//

#include "help.h"

void Help::error(){
	cout << "Incorrect Number of Arguments" << endl;
}

void Help::message() {
	cout << "****************************************HELP****************************************" << endl;
	cout << "\tThis is a chat program, which includes a server and a client" << endl;
	cout << "\tTo invoke the server: $./chat" << endl;
	cout << "\tTo invoke the client: $./chat -p <port number> -s <IP address of friend>" << endl;
	cout << "\tTo see this message again: $./chat -h" << endl;
	cout << "************************************************************************************" << endl;
}