#include "Message.hpp"
#include <string>

/**
 * NAME : PRIVMSG
 * USAGE : /privmsg <user | channel> <message>
 */
Message::Message() : ACommand( "PRIVMSG", true )
{
}

Message::~Message()
{
}

void	Message::sendBroadcastMessage(Server *server, Channel *channel, std::string message, User *origin_user)
{
	std::map<User*, int> users = channel->getUsers();
	for (std::map<User*, int>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (it->first != origin_user)
		{
			server->sendMessage(it->first->getFd(), message);
		}
	}
}

bool Message::execute(std::vector<std::string> args, User *user, Server *server)
{
	std::string message = "";

	if (args.size() < 2)
	{
		server->sendMessage(user->getFd(), "Usage: PRIVMSG <user | channel> <message> \r\n");
		return false;
	}

	for (size_t i = 1; i < args.size(); i++)
	{
		message.append(args.at(i));
		if (i != args.size() - 1)
			message.append(" ");
	}
    if (server->getChannelByName(args[0]) != NULL && server->getChannelByName(args[0])->containsUser(user))
    {
		sendBroadcastMessage(server, server->getChannelByName(args[0]), ":" + user->getNickname() + " PRIVMSG " + args[0] + " :" + message + "\r\n", user);
    }
    else if (server->getUserByNickname(args[0]) != NULL)
    {
		std::cout << "Sending message to " << args[0] << std::endl;
		std::cout << "Message: " << message << std::endl;
		server->sendMessageBetweenUsers(user->getFd(), args[0], message);
    }
    else
    {
		server->sendMessageError(user->getFd(), "401", args[0] + " :No such nick/channel");
        return false;
    }
	return true;
}
