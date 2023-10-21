/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/21 11:06:59 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"
#include <cstddef>

Join::Join() : ACommand( "join", "/join <channel>" )
{
    
}

Join::~Join()
{
    
}

bool Join::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
	(void)channel;
	if (args.size() != 1)
	{
		return false;
	}
	Channel* joinChannel = server->getChannelByName(args[0]);
	if (joinChannel != NULL)
	{
		joinChannel->addUser(user, 0);
	}
	else
	{
		joinChannel = new Channel();
		joinChannel->addUser(user, 1);
	}
	user->addChannel(joinChannel);
	return true;
}
