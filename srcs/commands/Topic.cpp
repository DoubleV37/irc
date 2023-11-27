/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/24 12:37:12 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"
#include <cctype>
#include <cstddef>

/**
 * NAME : TOPC
 * USAGE : /topic <topic>
 */
Topic::Topic() : ACommand( "TOPIC", true )
{
}

Topic::~Topic()
{
}

bool Topic::execute( std::vector<std::string> args, User* user, Server* server ) {
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
    if (channelTarget->containsUser(user) == false)
    {
        server->sendMessage(user->getFd(), ": 442 " + user->getNickname() + " " + args[0] + " :You're not on that channel\r\n");
        return false;
    }
    if (channelTarget->hasTopicProtection() && !channelTarget->isOp(user))
    {
        server->sendMessageError(user->getFd(), "482", "You're not channel operator");
        return false;
    }

	std:: string topic = "";

	for (size_t i = 1; i < args.size(); i++)
	{
		topic.append(args[i] + (i + 1 != args.size() ? " " : ""));
	}
	channelTarget->setTopic(topic);
	server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " TOPIC " + channelTarget->getName() + " :" + topic + "\r\n");
    return true;
}
