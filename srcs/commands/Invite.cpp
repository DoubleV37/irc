/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:08 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/06 13:08:36 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"
#include <cstddef>

Invite::Invite() : ACommand( "INVITE", "/invite <channel> <user>", true )
{

}

Invite::~Invite() {

}

bool Invite::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)channel;

    if (!user->isLog())
	{
		server->sendMessageError(user->getFd(), "451", "You have not registered");
		return false;
	}
	if (args.size() < 2)
	{
		server->sendMessageError(user->getFd(), "461", "Not enough parameters");
		return false;
	}

    User* userInvite = server->getUserByNickname(args[1]);
    Channel* channelTarget = server->getChannelByName(args[0]);

	if (channelTarget != NULL && userInvite != NULL)
	{
		if (channelTarget->containsUser(userInvite))
		{
			server->sendMessageError(user->getFd(), "443", "User is already on channel");
			return false;
		}
		else if (!channelTarget->isOp(user))
		{
			server->sendMessageError(user->getFd(), "482", "You're not channel operator");
			return false;
		}
		channelTarget->addUserInvited(userInvite);
		server->sendMessage(userInvite->getFd(), ":" + user->getNickname() + " INVITE " + userInvite->getNickname() + " " + args[0]);
		return true;
	}
	else if (channelTarget == NULL && userInvite != NULL)
	{
		server->sendMessage(userInvite->getFd(), "INVITE " + userInvite->getNickname() + " " + args[0]);
		return true;
	}
	server->sendMessageError(user->getFd(), "401", "No such nick");
    return false;
}
