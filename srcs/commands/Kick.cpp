/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:10 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/21 11:12:09 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"
#include <cstddef>

Kick::Kick() : ACommand( "kick", "/kick <channel> <user> [message]", true )
{
}

Kick::~Kick()
{
}

bool Kick::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
    (void)user;
	if (args.size() < 2)
	{
		return false;
	}

	Channel* channelTarget = server->getChannelByName(args[0]);
    User* userTarget = server->getUserByUsername(args[1]);

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
