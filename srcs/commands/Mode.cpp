/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:15 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/20 13:36:36 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"
#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

/**
 * NAME : MODE
 * USAGE : /mode <channel> <+ | -> <mode> [params]
 */
Mode::Mode() : ACommand( "MODE", true )
{
}

Mode::~Mode()
{
}

void Mode::inviteOnly(std::vector<std::string> &args, User* user, Server* server, Channel* channelTarget) {

	if (args[1][0] == '+')
	{
		channelTarget->setPrivate(true);
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " +i\r\n");
	}
	else
	{
		channelTarget->setPrivate(false);
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " -i\r\n");
	}
}

bool Mode::joinLimit(std::vector<std::string> &args, User* user, Server* server, Channel* channelTarget, size_t &ac) {

	if (args[1][0] == '+' && (args.size() < 3 + ac || args[2 + ac].size() == 0))
	{
		server->sendMessageError(user->getFd(), "461", "MODE :Not enough parameters");
		return false;
	}
	if (args[1][0] == '+' && args[2 + ac].size() > 0)
	{
		channelTarget->setLimit(std::atoi(args[2 + ac].c_str()));
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " +l " + args[2 + ac] + "\r\n");
	}
	else if (args[1][0] == '-')
	{
		channelTarget->setLimit(0);
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " -l\r\n");
	}
	return(true);
}

void Mode::topicLimit(std::vector<std::string> &args, User* user, Server* server, Channel* channelTarget) {

	if (args[1][0] == '+')
	{
		channelTarget->setTopicProtection(true);
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " +t\r\n");
	}
	else
	{
		channelTarget->setTopicProtection(false);
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " -t\r\n");
	}
}

bool Mode::channelPassword(std::vector<std::string> &args, User* user, Server* server, Channel* channelTarget, size_t &ac) {

	if (args[1][0] == '+' && (args.size() < 3 + ac || args[2 + ac].size() == 0))
	{
		server->sendMessageError(user->getFd(), "461", "MODE :Not enough parameters");
		return false;
	}
	if (args[1][0] == '+' && args[2 + ac].size() > 0)
	{
		channelTarget->setPassword(args[2 + ac]);
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " +k " + args[2 + ac] + "\r\n");
	}
	else if (args[1][0] == '-')
	{
		channelTarget->setPassword("");
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " -k\r\n");
	}
	return(true);
}

bool Mode::channelOp(std::vector<std::string> &args, User* user, Server* server, Channel* channelTarget, size_t &ac) {

	if (args.size() < 3 + ac || args[2 + ac].size() == 0)
	{
		server->sendMessageError(user->getFd(), "461", "MODE :Not enough parameters");
		return false;
	}
	User *userTarget = server->getUserByNickname(args[2 + ac]);
	if (userTarget == NULL)
	{
		server->sendMessageError(user->getFd(), "401", args[2 + ac] + " :No such nick/channel");
		return false;
	}
	if (!channelTarget->containsUser(userTarget))
	{
		server->sendMessageError(user->getFd(), "441", args[2 + ac] + " " + channelTarget->getName() + " :They aren't on that channel");
		return false;
	}
	if (args[1][0] == '+')
	{
		channelTarget->setOp(userTarget);
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " +o " + args[2 + ac] + "\r\n");
	}
	else
	{
		channelTarget->deOp(userTarget);
		server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " MODE " + channelTarget->getName() + " -o " + args[2 + ac] + "\r\n");
	}
	return(true);
}

bool Mode::execute( std::vector<std::string> args, User* user, Server* server )
{
    if (args.size() < 1)
    {
		server->sendMessageError(user->getFd(), "461", "MODE :Not enough parameters");
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
		server->sendMessage(user->getFd(), ": 324 " + user->getNickname() + " " + channelTarget->getName() + " " + channelTarget->getModes() + " \r\n");
		return true;
	}
	if (!channelTarget->containsUser(user))
	{
		server->sendMessageError(user->getFd(), "482", args[0] + " :You're not on that channel");
		return true;
	}
	if (!channelTarget->isOp(user))
	{
		server->sendMessageError(user->getFd(), "482", args[0] + " :You're not channel operator");
		return true;
	}

	size_t ac = 0;
	for (size_t i = 0; i < args[1].size(); i++)
	{
		if (i == 0 && args[1][0] != '+' && args[1][0] != '-')
		{
			server->sendMessageError(user->getFd(), "472", " :is unknown mode char to me");
			return false;
		}
		else if (i == 0)
			continue;

		if (args[1][i] == 'i' )
		{
			this->inviteOnly(args, user, server, channelTarget);
		}
		else if (args[1][i] == 'l')
		{
			if (this->joinLimit(args, user, server, channelTarget, ac))
				ac++;
			else
				return false;
		}
		else if (args[1][i] == 't')
		{
			this->topicLimit(args, user, server, channelTarget);
		}
		else if (args[1][i] == 'k')
		{
			if (this->channelPassword(args, user, server, channelTarget, ac))
				ac++;
			else
				return false;
		}
		else if (args[1][i] == 'o')
		{
			if (this->channelOp(args, user, server, channelTarget, ac))
				ac++;
			else
				return false;
		}
		else
		{
			server->sendMessageError(user->getFd(), "472", " :is unknown mode char to me");
			return false;
		}
	}
    return true;
}
