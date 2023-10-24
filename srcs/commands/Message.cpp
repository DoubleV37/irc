#include "Message.hpp"
#include <string>

Message::Message() : ACommand( "msg", "/msg <user | channel> <message>", false )
{
}

Message::~Message()
{
}

bool Message::execute(std::vector<std::string> args, User *user, Channel *channel, Server *server)
{
	std::string message = "";

	(void)channel;
    (void)user;
	if (args.size() < 2)
	{
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
    else if (server->getUserByUsername(args[0]) != NULL)
    {
        server->getUserByUsername(args[0])->send(message);
    }
    else
    {
        return false;
    }
	return true;
}
