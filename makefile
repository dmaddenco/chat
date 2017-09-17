all: chat

chat: client/*.cpp server/*.cpp help/*.cpp *.cpp client/*.h server/*.h help/*.h packet/*.h
	g++ -I. -Wall -std=c++11 client/*.cpp server/*.cpp help/*.cpp *.cpp -g -o chat
clean:
	rm -rf *.o *.tar chat*
tar:
	tar -cvf client/client.cpp client/client.h help/help.cpp help/help.h packet/packet.h server/server.cpp server/server.h main.cpp makefile README.txt