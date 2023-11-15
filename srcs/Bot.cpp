#include "Bot.hpp"
#include "Server.hpp"
#include <bits/types/siginfo_t.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Bot::Bot()
{
	this->_port = 0;
}

Bot::Bot(int port, std::string password, std::string name)
{
	this->_port = port;
	this->_password = password;
	this->_name = name;
}

Bot::~Bot()
{
}

Bot &Bot::operator=(const Bot &copy)
{
	if (this == &copy)
		return *this;
	this->_socket = copy._socket;
	this->_port = copy._port;
	this->_password = copy._password;
	this->_name = copy._name;
	return *this;
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
	::listen(this->_socket, 42); // TODO : 42 est une valeur a changer
	
	std::string connect_cmd = "";
	std::string name = !this->_name.empty() ? this->_name : "bot";

	if (!this->_password.empty())
	{
		connect_cmd.append("PASS " + this->_password + "\r\n");
	}
	connect_cmd.append("NICK " + name + "\r\nUSER " + name + "\r\n");

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
