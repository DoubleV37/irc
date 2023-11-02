/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/02 10:58:33 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Who.hpp"

Who::Who() : ACommand( "WHO", "/who <channel>", false )
{
    
}

Who::~Who()
{ 
    
}

bool Who::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    
    std::string parameter;
    (void)channel;

    channel = server->getChannelByName(args[0]);
    if (channel == NULL)
    {
        server->sendMessage(user->getFd(), ": 403 " + user->getNickname() + " " + args[0] + " :No such channel\r\n");
        return false;
    }
    server->sendMessage(user->getFd(), ": 353 " + user->getNickname() + " = " + channel->getName() + " :" + channel->getUsersList() + "\r\n");
    server->sendMessage(user->getFd(), ": 366 " + user->getNickname() + " " + channel->getName() + " :End of /NAMES list.\r\n");
    return true;
}
