//
// Created by David Madden on 9/15/17.
//

#ifndef P1C_PACKET_H
#define P1C_PACKET_H
#define MAXSIZE 140
#define VERSION 457

struct Packet {
	char16_t version = htons(VERSION);
	char16_t msgLength;
	char msg[MAXSIZE];
};

#endif //P1C_PACKET_H
