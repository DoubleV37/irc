/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/21 17:47:36 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

Topic::Topic() : ACommand( "topic", "/topic <topic>", true )
{
}

Topic::~Topic()
{   
}

bool Topic::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    (void)user;
    (void)channel;
	if (args.size() < 2)
	{
		return false;
	}
    Channel* channelTarget = server->getChannelByName(args[0]);
	channelTarget->setTopic(args[1]);
    return true;
}
