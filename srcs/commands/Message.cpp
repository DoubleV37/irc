#include "Message.hpp"
#include <string>

Message::Message() : ACommand( "message", "/message <user> <message>", false )
{
}

Message::~Message()
{
}

bool Message::execute(std::vector<std::string> args, User *user, Channel *channel, Server *server)
{
	std::string message = "";

	(void)channel;
	(void)server;
	if (args.size() < 2)
	{
		return false;
	}
	for (size_t i = 0; i < args.size(); i++)
	{
		message.append(args.at(i));
	}
	user->send(message);
	return true;
}
