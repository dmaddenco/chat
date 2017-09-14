//
// Created by David Madden on 9/7/17.
//

#include "client.h"

bool Client::checkIp(string ip) {
	regex r("\\d{1,3}(\\.\\d{1,3}){3})");
	if (!regex_match(ip,r)) {
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

}