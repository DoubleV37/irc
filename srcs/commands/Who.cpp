/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/22 18:07:32 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Who.hpp"

/**
 * NAME : WHO
 * USAGE : /who <channel>
 */
Who::Who() : ACommand( "WHO", true )
{
}

Who::~Who()
{
}

bool Who::execute( std::vector<std::string> args, User* user, Server* server ) {
    std::string parameter;

	if (args.size() != 1)
	{
		server->sendMessageError(user->getFd(), "461", "WHO :Not enough or too many parameters");
		return false;
	}
    Channel *channel = server->getChannelByName(args[0]);
    if (channel == NULL)
    {
        server->sendMessage(user->getFd(), ": 403 " + user->getNickname() + " " + args[0] + " :No such channel\r\n");
        return false;
    }
    if (channel->containsUser(user) == false)
    {
        server->sendMessage(user->getFd(), ": 442 " + user->getNickname() + " " + args[0] + " :You're not on that channel\r\n");
        return false;
    }
    server->sendMessage(user->getFd(), ": 353 " + user->getNickname() + " = " + channel->getName() + " :" + channel->getUsersList() + "\r\n");
    server->sendMessage(user->getFd(), ": 366 " + user->getNickname() + " " + channel->getName() + " :End of /NAMES list.\r\n");
    return true;
}
