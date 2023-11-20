/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:08 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/20 14:07:48 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"
#include <cstddef>

/**
 * NAME : INVITE
 * USAGE : /invite <channel> <user>
 */
Invite::Invite() : ACommand( "INVITE", true )
{

}

Invite::~Invite() {

}

bool Invite::execute( std::vector<std::string> args, User* user, Server* server ) {
	if (args.size() != 2 || args[0].empty() || args[1].empty())
	{
		server->sendMessageError(user->getFd(), "461", "Not enough parameters");
		return false;
	}

    User* userInvite = server->getUserByNickname(args[0]);
    Channel* channelTarget = server->getChannelByName(args[1]);

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
		channelTarget->addUserInvited(userInvite->getNickname());
		server->sendMessage(userInvite->getFd(), ":" + user->getNickname() + " INVITE " + userInvite->getNickname() + " " + args[1] + "\r\n");
		return true;
	}
	else if (channelTarget == NULL && userInvite != NULL)
	{
		server->sendMessage(userInvite->getFd(), "INVITE " + userInvite->getNickname() + " " + args[1] + "\r\n");
		return true;
	}
	server->sendMessageError(user->getFd(), "401", "No such nick");
    return false;
}
