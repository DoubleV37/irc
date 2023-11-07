/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/07 13:07:56 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

Topic::Topic() : ACommand( "TOPIC", "/topic <topic>", true )
{
}

Topic::~Topic()
{
}

bool Topic::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)channel;

	if (args.size() == 0)
	{
		server->sendMessageError(user->getFd(), "461", "Not enough parameters");
		return false;
	}

    Channel* channelTarget = server->getChannelByName(args[0]);

	if (args.size() == 1 && channelTarget != NULL)
	{
		if (channelTarget->getTopic() == "")
			server->sendMessage(user->getFd(), ": 331 " + user->getNickname() + " " + channelTarget->getName() + " :No topic is set\r\n");
		else
			server->sendMessage(user->getFd(), ": 332 " + user->getNickname() + " " + channelTarget->getName() + " :" + channelTarget->getTopic() + "\r\n");
		return true;
	}

    if (channelTarget == NULL)
    {
		server->sendMessageError(user->getFd(), "403", "No such channel");
        return false;
    }
    if (channelTarget->hasTopicProtection() && !channelTarget->isOp(user))
    {
        server->sendMessageError(user->getFd(), "482", "You're not channel operator");
        return false;
    }

	channelTarget->setTopic(args[1]);
	server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " TOPIC " + channelTarget->getName() + " :" + args[1] + "\r\n");
    return true;
}
