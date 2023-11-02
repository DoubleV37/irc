/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:10 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/02 14:48:55 by gazzopar         ###   ########.fr       */
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

bool Kick::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
    (void)user;
    (void)channel;

	if (!user->isLog())
	{
		server->sendMessageError(user->getFd(), "451", "You have not registered");
		return false;
	}
	if (args.size() < 2)
	{
		return false;
	}

	Channel* channelTarget = server->getChannelByName(args[0]);
    User* userTarget = server->getUserByNickname(args[1]);

    if (channelTarget == NULL)
    {
        return false;
    }
	if (channelTarget->containsUser(userTarget))
	{
        channelTarget->removeUser(userTarget);
    	return true;
	}
	return false;
}
