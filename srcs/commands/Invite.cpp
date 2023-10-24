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

Invite::Invite() : ACommand( "invite", "/invite <user>", true )
{
    
}

Invite::~Invite() {
    
}

bool Invite::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    (void)user;
	if (args.size() != 1)
	{
		return false;
	}
	User* userInvite = server->getUserByUsername(args[0]);
	if (userInvite != NULL)
	{
		channel->addUser(userInvite, 0);
		userInvite->addChannel(channel);
		return true;
	}
    return false;
}
