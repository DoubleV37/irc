#include "Bot.hpp"
#include "Server.hpp"
#include <bits/types/siginfo_t.h>
#include <cstdlib>
#include <ctime>
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
	this->exit = false;
}

Bot::Bot(int port, std::string password, std::string name)
{
	this->_port = port;
	this->_password = password;
	this->_name = name;
	this->exit = false;
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

	// création socket du bot
	this->_socket = socket(PF_INET, SOCK_STREAM, 0);
	// parametrage de l'adresse à laquelle le bot va se lier
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(this->_port);
	// on cast parce que connect attend un sockaddr et pas un addr
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
	::listen(this->_socket, 1); // TODO : 42 est une valeur a changer

	std::string connect_cmd = "";
	std::string name = !this->_name.empty() ? this->_name : "bot";
	std::string yodaQuotes[7] = { "No! Try not. Do. Or do not. There is no try", "Size matters not. Look at me. Judge me by my size, do you? Hmm? And well you should not. For my ally is the Force, and a powerful ally it is. Life creates it, makes it grow. Its energy surrounds us and binds us. Luminous beings are we, not this crude matter. You must feel the Force around you. Here, between you, me, the tree, the rock—everywhere, yes. Even between the land and the ship.", "Fear is the path to the dark side. Fear leads to anger. Anger leads to hate. Hate leads to suffering.", "Great warrior. Hmm. Wars not make one great.", "You must unlearn what you have learned.", "Once you start down the dark path, forever will it dominate your destiny. Consume you, it will.", "Smaller in number are we, but larger in mind." };
	std::string sarQuotes[4] = { "Si la vérité blesse, c'est la faute de la vérité.", "Quelle indignité... et nous sommes sur le service public !", "Patrick à éternué dans le cluster, c'est une honte !", "Vous en avez assez hein ? Vous en avez assez de cette bande de racailles ? Et bien on va vous en débarasser" };

	if (!this->_password.empty())
	{
		connect_cmd.append("PASS " + this->_password + "\r\n");
	}
	connect_cmd.append("NICK " + name + "\r\nUSER " + name + "\r\n");

	// :: devant parce qu'appartient aux libc, dans ce cas socket.c,
	// qu'on ne veut pas confondre avec une autre du même nom
	::send(this->_socket, connect_cmd.c_str(), connect_cmd.size(), 0);

	this->exec("JOIN", "#bot", "");
	this->exec("TOPIC", "#bot", "ceci est un topic");

	srand(time(0));

	while (!this->exit)
	{
		recv(this->_socket, &buffer[0], buffer.size(), 0);
		msg = this->compact(buffer);
		if (msg == "!quoi\r" || msg == "!quoi")
		{
			this->send("#bot", rand() % 2 ? "feur" : "quoicoubeh");
		}
		if (msg == "!yoda\r")
		{
			this->send("#bot", yodaQuotes[rand() % 7]);
		}
		if (msg == "!sarko\r")
		{
			this->send("#bot", sarQuotes[rand() % 4]);
		}
	}
}

void Bot::exec(const std::string & cmd, const std::string & channel, const std::string & arg)
{
	std::string buf = cmd;
	if (!channel.empty())
	{
		buf.append(" " + channel);
	}
	if (!arg.empty())
	{
		buf.append(" " + arg);
	}
	buf.append("\r\n");
	::send(this->_socket, buf.c_str(), buf.size(), 0);
}

std::string Bot::compact(std::vector<char> & vector) const
{
	std::string str = "";
	int find = 0;

	for (size_t i = 0; i < vector.size(); ++i)
	{
		if (vector[i] == '\n')
			break;
		if (find >= 2)
			str += vector[i];
		if (vector[i] == ':')
			find++;
		vector[i] = '\0';
	}
	return str;
}

void Bot::send(const std::string & channel, const std::string & content)
{
	this->exec("PRIVMSG", channel, content);
}

void Bot::close()
{
	this->exec("QUIT", "", "");
	::close(this->_socket);
	this->exit = true;
}
