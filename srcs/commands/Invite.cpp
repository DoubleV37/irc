/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:08 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/28 19:38:56 by doublev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"
#include <cstddef>

Invite::Invite() : ACommand( "invite", "/invite <channel> <user>", true )
{

}

Invite::~Invite() {

}

bool Invite::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    (void)user;
    (void)channel;
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
