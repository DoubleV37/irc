#include "Message.hpp"
#include <string>

Message::Message() : ACommand( "PRIVMSG", "PRIVMSG <user | channel> <message>", false )
{
}

Message::~Message()
{
}

bool Message::execute(std::vector<std::string> args, User *user, Channel *channel, Server *server)
{
	std::string message = "";

	(void)channel;

	for (size_t i = 0; i < args.size(); i++)
	{
		std::cout << "arg[" << i << "] = " << args[i] << std::endl;
	}
	if (args.size() < 2)
	{
		server->sendMessage(user->getFd(), "Usage: PRIVMSG <user | channel> <message> \r\n");
		return false;
	}

	for (size_t i = 1; i < args.size(); i++)
	{
		message.append(args.at(i));
	}
    if (server->getChannelByName(args[0]) != NULL)
    {
        server->getChannelByName(args[0])->broadcast(message);
    }
    else if (server->getUserByNickname(args[0]) != NULL)
    {
		std::cout << "Sending message to " << args[0] << std::endl;
		std::cout << "Message: " << message << std::endl;
		server->sendMessageBetweenUsers(user->getFd(), args[0], message);
        // server->getUserByUsername(args[0])->send(message);
    }
    else
    {
		server->sendMessageError(user->getFd(), "401", args[0] + " :No such nick/channel");
        return false;
    }
	return true;
}
