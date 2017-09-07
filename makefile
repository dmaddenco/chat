all: chat

chat: *.cpp *.h
	g++ -I. -Wall -std=c++11 *.cpp -g -o chat
clean:
	rm -rf *.o *.tar chat*
tar:
	tar -cvf chat.tar *.cpp *.h makefile README.txt