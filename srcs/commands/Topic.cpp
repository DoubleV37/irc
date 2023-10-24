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

Topic::Topic() : ACommand( "topic", "/topic <topic>" )
{
}

Topic::~Topic()
{   
}

bool Topic::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    (void)user;
    (void)server;
	if (args.size() != 1)
	{
		return false;
	}
	channel->setTopic(args[0]);
    return true;
}
