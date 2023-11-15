#include "Bot.hpp"
#include "Server.hpp"
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Bot::Bot(int port) : _port(port)
{
}

Bot::~Bot()
{
}

void Bot::run()
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

void Bot::on()
{
	std::string msg;
	std::vector<char> buffer(MAX_BUF_LENGTH);
	listen(this->_socket, 42); // TODO : 42 est une valeur a changer
	
	std::string connect_cmd = "PASS pass\r\nNICK bot\r\nUSER bot\r\n";
	::send(this->_socket, connect_cmd.c_str(), connect_cmd.size(), 0);
	
	this->exec("JOIN", "#bot", "");
	this->exec("TOPIC", "#bot", "ceci est un topic");

	for (;;)
	{
		recv(this->_socket, &buffer[0], buffer.size(), 0);
		msg = this->compact(buffer);
		if (msg.find("!quoi") != std::string::npos)
		{
			this->send("#bot", "feur");
		}
	}
}

void Bot::exec(const std::string & cmd, const std::string & channel, const std::string & arg)
{
	std::string buf = cmd + " " + channel;
	if (!arg.empty())
	{
		buf.append(" " + arg);
	}
	buf.append("\r\n");
	::send(this->_socket, buf.c_str(), buf.size(), 0);
}

std::string Bot::compact(const std::vector<char> & vector) const
{
	std::string str = "";

	for (size_t i = 0; i < vector.size(); i++)
	{
		str += vector[i];
	}
	return str;
}

void Bot::send(const std::string & channel, const std::string & content)
{
	this->exec("PRIVMSG", channel, content);
}

void Bot::close()
{
	::close(this->_socket);
}
