#include "Bot.hpp"
#include "Server.hpp"
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Bot::Bot(int port) : _port(port)
{
	struct sockaddr_in addr;

	this->_socket = socket(PF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(this->_port);
	if (connect(this->_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		std::cerr << "bot connect fail" << std::endl;
		return;
	}
	std::cout << "Bot start" << std::endl;
	this->on();
}

Bot::~Bot()
{
}

void Bot::on()
{
	std::vector<char> buffer(MAX_BUF_LENGTH);

	listen(this->_socket, 42); // TODO : 42 est une valeur a changer
	//int rec = recv(this->_socket, &buffer[0], buffer.size(), 0);
	//std::cout << "value : " << rec << std::endl;
	//std::cout << "buff : " << buffer[0] << std::endl;
}

void Bot::send(const std::string & channel, const std::string & msg)
{
	(void) channel;
	(void) msg;
}

void Bot::close()
{
	::close(this->_socket);
}
