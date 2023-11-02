/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:08 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/02 14:49:39 by gazzopar         ###   ########.fr       */
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
		return false;
	}

    User* userInvite = server->getUserByNickname(args[1]);
    Channel* channelTarget = server->getChannelByName(args[0]);

	if (channelTarget != NULL)
	{
        if (channelTarget->isFull())
        {
            user->send("The channel is full");
            return true;
        }
		channel->addUser(userInvite, 0);
		userInvite->addChannel(channel);
		return true;
	}
    return false;
}
