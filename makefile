all: chat

chat: client/*.cpp server/*.cpp help/*.cpp *.cpp client/*.h server/*.h help/*.h
	g++ -I. -Wall -std=c++11 client/*.cpp server/*.cpp help/*.cpp *.cpp -g -o chat
clean:
	rm -rf *.o *.tar chat*
tar:
	tar -cvf chat.tar client/*.cpp server/*.cpp help/*.cpp *.cpp client/*.h server/*.h help/*.h *.h makefile README.txt