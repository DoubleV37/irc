/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/17 12:07:49 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"
#include "../utils/CmdUtils.hpp"
#include <cstddef>
#include <string>
#include "../ACommand.hpp"

/**
 * NAME : JOIN
 * USAGE : /join <channel>,{1,} [password]{0,}
 */
Join::Join() : ACommand( "JOIN", true )
{
}

Join::~Join()
{
}

void Join::sendJoinMessage( User* user, Channel* channel, Server* server )
{
	std::string message = ":" + user->getNickname() + " JOIN " + channel->getName() + "\r\n";
	server->sendMessageChannel(channel, message);
	if (channel->getTopic() != "")
		server->sendMessage(user->getFd(), ": 332 " + user->getNickname() + " " + channel->getName() + " :" + channel->getTopic() + "\r\n");
	else
		server->sendMessage(user->getFd(), ": 331 " + user->getNickname() + " " + channel->getName() + " :No topic is set\r\n");
}

bool	Join::isValidChannelName(std::string channel_name, Server* server, User* user)
{
	if ((channel_name.size() <= 1 || channel_name.size() > 200) || (channel_name[0] != '#' && channel_name[0] != '&'))
	{
		server->sendMessageError(user->getFd(), "403", channel_name + " :No such channel");
		return false;
	}
	return true;
}

void	Join::channelCreate(std::string channel_name, Server* server, User* user, std::vector<std::string> &channels_password)
{
	Channel *channelTarget;
	if (user->getChannels().size() >= 10)
	{
		server->sendMessageError(user->getFd(), "405", channel_name + " :You have joined too many channels");
		return ;
	}
	if (channels_password.size() > 0)
		channelTarget = new Channel(channel_name, channels_password[0]);
	else
		channelTarget = new Channel(channel_name);
	channelTarget->addUser(user, 1);
	user->addChannel(channelTarget);
	server->addChannel(channelTarget);
	sendJoinMessage(user, channelTarget, server);
}

bool Join::execute( std::vector<std::string> args, User* user, Server* server )
{
	if (args.empty() || args.size() > 2)
	{
		server->sendMessageError(user->getFd(), "461", "/join <channel>,{1,} [password],{0,}");
		return false;
	}

	std::vector<std::string> channels_name;
	std::vector<std::string> channels_password;
	std::string channel_name;

	for (size_t i = 0; i < args[0].size(); i++)
	{
		if (args[0][i] != ',')
			channel_name.push_back(args[0][i]);
		else if (args[0][i] == ',')
		{
			if (!isValidChannelName(channel_name, server, user))
				return false;
			channels_name.push_back(channel_name);
			channel_name.clear();
		}
	}
	if (!isValidChannelName(channel_name, server, user))
		return false;
	else
		channels_name.push_back(channel_name);
	if (args.size() == 2)
		channels_password = server->split(args[1], ',');

	Channel *channelTarget;
	for (size_t i = 0; i < channels_name.size(); i++)
	{
		channelTarget = server->getChannelByName(channels_name[i]);
		if (channelTarget == NULL)
		{
			channelCreate(channels_name[i], server, user, channels_password);
		}
		else if (channelTarget->isFull())
		{
			server->sendMessageError(user->getFd(), "471", channels_name[i] + " :Cannot join channel, server full");
		}
		else if ((channels_password.size() > 0 && channels_password.size() - 1 >= i && channelTarget->getPassword() != channels_password[i]) || (channelTarget->getPassword() != "" && channels_password.size() <= i) )
		{
			server->sendMessageError(user->getFd(), "475", channels_name[i] + " :Cannot join channel, wrong password");
		}
		else if (channelTarget->isPrivate() && !channelTarget->isInvited(user->getNickname()))
		{
			server->sendMessageError(user->getFd(), "473", channels_name[i] + " :Cannot join channel, invite only");
		}
		else if (channelTarget->containsUser(user))
		{
			server->sendMessageError(user->getFd(), "443", channels_name[i] + " :is already on channel");
		}
		else if (user->getChannels().size() >= 10)
		{
			server->sendMessageError(user->getFd(), "405", channels_name[i] + " :You have joined too many channels");
		}
		else if ((channels_password.size() > i && channelTarget->getPassword() == channels_password[i]) || (channels_password.size() == 0 && channelTarget->getPassword() == ""))
		{
			channelTarget->addUser(user, 0);
			user->addChannel(channelTarget);
			sendJoinMessage(user, channelTarget, server);
		}
		else
		{
			server->sendMessageError(user->getFd(), "475", channels_name[i] + " :Cannot join channel, wrong password");
		}
	}
	return true;
}
