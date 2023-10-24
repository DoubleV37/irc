/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/22 15:04:45 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"
#include "../utils/CmdUtils.hpp"
#include <cstddef>
#include <string>

Join::Join() : ACommand( "join", "/join <channel>", false )
{
}

Join::~Join()
{
}

bool Join::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
    (void)channel;
	if (args.empty() || args.size() > 2)
        return false;

    std::vector<Channel *> *channels = CmdUtils::getChannelsOf(args[0], server);

    for (std::vector<Channel *>::iterator it = channels->begin(); it != channels->end(); ++it)
    {
        if (*it == NULL)
        {
            Channel *newChannel = new Channel();
            newChannel->addUser(user, 1);
            user->addChannel(newChannel);
            server->addChannel(newChannel);
        }
        else
        {
            ((Channel *) *it)->addUser(user, 0);
            user->addChannel(*it);
        }
    }
    delete channels;
    return true;
}
