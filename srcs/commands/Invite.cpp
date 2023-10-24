/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:08 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/24 15:03:19 by ltuffery         ###   ########.fr       */
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

    User* userInvite = server->getUserByUsername(args[1]);
    Channel* channelTarget = server->getChannelByName(args[0]);

	if (channelTarget != NULL)
	{
        if (channelTarget->hasLimit() && channelTarget->getLimit() >= channelTarget->getUsers().size())
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
