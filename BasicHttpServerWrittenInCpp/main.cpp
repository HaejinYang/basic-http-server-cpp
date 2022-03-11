#include <iostream>
#include "HttpParser.h"
#include "Server.h"

#define LISTEN_IP	L"0.0.0.0"
#define LISTEN_PORT	(50001)

int main(void)
{
	Server s;
	s.Start(LISTEN_IP, LISTEN_PORT);

	return 0;
}