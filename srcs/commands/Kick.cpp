/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:10 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/07 13:57:37 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"
#include <cstddef>

Kick::Kick() : ACommand( "KICK", "/kick <channel> <user> [message]", true )
{
}

Kick::~Kick()
{
}

bool Kick::execute( std::vector<std::string> args, User* user, Server* server )
{
    (void)user;

	if (args.size() < 2)
	{
		server->sendMessageError(user->getFd(), "461", "Not enough parameters");
		return false;
	}
	std::string reasons;
	if (args.size() > 2)
	{
		for (size_t i = 2; i < args.size(); i++)
		{
			reasons += args[i];
			if (i + 1 < args.size())
				reasons += " ";
		}
	}

	Channel* channelTarget = server->getChannelByName(args[0]);
    User* userTarget = server->getUserByNickname(args[1]);

    if (channelTarget == NULL)
    {
		server->sendMessageError(user->getFd(), "403", "No such channel");
        return false;
    }
	if (userTarget == NULL)
	{
		server->sendMessageError(user->getFd(), "401", "No such nick");
		return false;
	}
	if (!channelTarget->containsUser(user))
	{
		server->sendMessageError(user->getFd(), "442", "You're not on that channel");
		return false;
	}
	if (!channelTarget->isOp(user))
	{
		server->sendMessageError(user->getFd(), "482", "You're not channel operator");
		return false;
	}
	if (channelTarget->containsUser(userTarget))
	{
		if (reasons.empty())
			server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " KICK " + channelTarget->getName() + " " + userTarget->getNickname() + "\r\n");
		else
			server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " KICK " + channelTarget->getName() + " " + userTarget->getNickname() + " :" + reasons + "\r\n");
		channelTarget->removeUser(userTarget);
		userTarget->removeChannel(channelTarget->getName());
    	return true;
	}
	server->sendMessageError(user->getFd(), "441", "User not in channel");
	return false;
}
