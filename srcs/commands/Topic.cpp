/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/31 18:36:45 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

Topic::Topic() : ACommand( "TOPIC", "/topic <topic>", false )
{
}

Topic::~Topic()
{   
}

bool Topic::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    (void)channel;
	if (args.size() < 2)
	{
		return false;
	}
    Channel* channelTarget = server->getChannelByName(args[0]);

    if (channelTarget == NULL)
    {
        return false;
    }
    if (channelTarget->hasTopicProtection() && !channelTarget->isOp(user))
    {
        user->send("you need to be op to make this order in this channel");
        return true;
    }

	channelTarget->setTopic(args[1]);
    return true;
}
