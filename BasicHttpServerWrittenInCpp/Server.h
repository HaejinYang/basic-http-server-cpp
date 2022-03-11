#pragma once

#include <string>
#include <WS2tcpip.h>
#include <Windows.h>

class Server
{
public:
	bool Start(std::wstring listenIP, unsigned short port);
private:
	bool initialize(std::wstring listenIP, unsigned short port);
	void run();
private:
	unsigned short mPort;
	std::wstring mListenIP;
	SOCKET mListenSocket;
};
