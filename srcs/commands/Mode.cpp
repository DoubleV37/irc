/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:15 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 16:33:00 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

Mode::Mode() : ACommand( "mode", "/mode <channel> <+ | -> <mode> [params]", true )
{
}

Mode::~Mode()
{
}

bool Mode::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
    (void)channel;
    if (args.size() < 2)
    {
        return false;
    }

    Channel *channelTarget = server->getChannelByName(args[0]);

    if (channelTarget == NULL)
    {
        return false;
    }

    if (args[1] == "+i" || args[1] == "-i")
    {
        channelTarget->setPrivate(args[1] == "+i");
    }
    else if (args[1] == "+t" || args[1] == "-t")
    {
        channelTarget->setTopicProtection(args[1] == "+t");
    }
    else if (args[1] == "+k" || args[1] == "-k")
    {
        if (args.size() < 3)
        {
            user->send(args[1] + " needs a password");
            return true;
        }
        channelTarget->setPassword(args[1] == "+k" ? args[2] : "");
    }
    else if (args[1] == "+o" || args[1] == "-o")
    {
        if (args.size() < 3)
        {
            user->send(args[1] + " needs a user");
            return true;
        }
        User *userTarget = server->getUserByUsername(args[2]);
        args[1] == "+o" ? channelTarget->setOp(userTarget) : channelTarget->deOp(userTarget);
    }
    return true; 
}