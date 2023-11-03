/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:15 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/03 18:22:04 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"
#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

Mode::Mode() : ACommand( "MODE", "/mode <channel> <+ | -> <mode> [params]", true )
{
}

Mode::~Mode()
{
}

bool Mode::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
    (void)channel;

    if (!user->isLog())
	{
		server->sendMessageError(user->getFd(), "451", "You have not registered");
		return false;
	}
    if (args.size() < 1)
    {
        return false;
    }

    Channel *channelTarget = server->getChannelByName(args[0]);

    if (channelTarget == NULL)
    {
		server->sendMessageError(user->getFd(), "403", args[0] + " :No such channel");
        return false;
    }
	if (args.size() == 1)
	{
		server->sendMessageChannel(channelTarget, channelTarget->getModes());
		return true;
	}
	if (!channelTarget->isOp(user))
	{
		server->sendMessageError(user->getFd(), "482", args[0] + " :You're not channel operator");
		return true;
	}

	int ac = 0;
	int totalErrorFlag = 0;

	for (size_t i = 0; i < args[1].size(); i++)
	{
		if (i == 0 && args[1][0] != '+' && args[1][0] != '-')
			return false;
		else if (i == 0)
			continue;
		
		if (args[1][i] == 'i')
		{
			channelTarget->setPrivate(args[1][0] == '+');
		}
		else if (args[1][i] == 'l')
		{
			channelTarget->setLimit(args[1][0] == '+' ? std::atoi(args[2 + ac].c_str()) : 0);
			ac++;
		}
		else if (args[1][i] == 't')
		{
			channelTarget->setTopicProtection(args[1][0] == '+');
		}
		else if (args[1][i] == 'k')
		{
			channelTarget->setPassword(args[1][0] == '+' ? args[2 + ac] : "");
			ac++;
		}
		else if (args[1][i] == 'o')
		{
			User *userTarget = server->getUserByNickname(args[2 + ac]);
			args[1][0] == '+' ? channelTarget->setOp(userTarget) : channelTarget->deOp(userTarget);
			ac++;
		}
		else
		{
			totalErrorFlag++;
		}
	}
    return true;
}
