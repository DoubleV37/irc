/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/31 15:02:29 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"
#include "../utils/CmdUtils.hpp"
#include <cstddef>
#include <string>
#include "../ACommand.hpp"

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
            Channel *channelTarget = (Channel *)*it;
            if (channelTarget->isFull())
            {
                user->send(channelTarget->getName() + " is Full.");
                continue;
            }
            ((Channel *) *it)->addUser(user, 0);
            user->addChannel(*it);
        }
    }
    delete channels;
    return true;
}
