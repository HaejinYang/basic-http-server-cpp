#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include "HttpParser.h"
#include "Server.h"

bool Server::Start(std::wstring listenIP, unsigned short port)
{
	if (initialize(listenIP, port) == false)
	{
		return false;
	}

	run();

	return true;
}

bool Server::initialize(std::wstring listenIP, unsigned short port)
{
	mListenIP = listenIP;
	mPort = port;

	WSADATA wsa;
	int wsa_startup_result = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (wsa_startup_result != 0)
	{
		int error = WSAGetLastError();
		wprintf(L"Failed WSAStartup. code : %d", error);

		return false;
	}

	SOCKADDR_IN server_address;
	memset(&server_address, 0, sizeof server_address);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(mPort);
	int inet_pton_result = InetPton(AF_INET, mListenIP.c_str(), &server_address.sin_addr);
	if (inet_pton_result != 1)
	{
		if (inet_pton_result == 0)
		{
			wprintf(L"Failed InetPton. invalid IP string");
		}
		else
		{
			int error = WSAGetLastError();
			wprintf(L"Failed InetPton. code : %d", error);
		}

		return false;
	}

	mListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mListenSocket == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		wprintf(L"Failed socket. code : %d", error);

		return false;
	}

	int bind_result = bind(mListenSocket, (struct sockaddr*)&server_address, sizeof server_address);
	if (bind_result != 0)
	{
		int error = WSAGetLastError();
		wprintf(L"Failed bind. code : %d", error);

		return false;
	}

	int listen_result = listen(mListenSocket, SOMAXCONN);
	if (listen_result != 0)
	{
		int error = WSAGetLastError();
		wprintf(L"Failed listen. code : %d", error);

		return false;
	}

	return true;
}

void Server::run()
{
	while (true)
	{
		SOCKADDR_IN client_address;
		memset(&client_address, 0, sizeof client_address);
		int client_address_size = sizeof client_address;
		SOCKET connected_socket = accept(mListenSocket, (struct sockaddr*)&client_address, &client_address_size);
		if (connected_socket == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			wprintf(L"Failed accept. code : %d", error);

			continue;
		}

		char buf[1024];
		int result = recv(connected_socket, buf, sizeof buf, 0);
		
		HttpParser parser;
		parser.Parse(buf, result);
		parser.PrintAllLines();
		std::cout << parser.GetPath() << std::endl;


		const char* body = "<html><body><p>Hello world</p></body></html>";
		const char* header = "HTTP/1.1 200 OK\nContent-Length: 45\nContent-Type: text/html\n\n";

		send(connected_socket, header, static_cast<int>(strlen(header)), 0);
		send(connected_socket, body, static_cast<int>(strlen(body)), 0);

		Sleep(10);
		closesocket(connected_socket);
	}
}