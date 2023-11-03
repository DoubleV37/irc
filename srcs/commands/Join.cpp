/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/03 15:19:18 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"
#include "../utils/CmdUtils.hpp"
#include <cstddef>
#include <string>
#include "../ACommand.hpp"

Join::Join() : ACommand( "JOIN", "/join <channel> [password]", false )
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

bool Join::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
    (void)channel;

	if (args.empty() || args.size() > 2)
	{
		server->sendMessageError(user->getFd(), "461", this->getUsage());
		return false;
	}
    if (!user->isLog())
	{
		server->sendMessageError(user->getFd(), "451", "You have not registered");
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
			if ((channel_name[0] != '#' && channel_name[0] != '&') || channel_name.size() == 0 || channel_name.size() > 200 )
			{
				server->sendMessageError(user->getFd(), "403", channel_name + " :No such channel");
				return false;
			}
			channels_name.push_back(channel_name);
			channel_name.clear();
		}
	}
	if ((channel_name[0] != '#' && channel_name[0] != '&') || channel_name.size() == 0 || channel_name.size() > 200 )
	{
		server->sendMessageError(user->getFd(), "403", channel_name + " :No such channel");
		return false;
	}
	else
		channels_name.push_back(channel_name);

	if (args.size() == 2)
	{
		std::string channel_password;
		for (size_t i = 0; i < args[1].size(); i++)
		{
			if (args[1][i] != ',')
				channel_password.push_back(args[1][i]);
			else if (args[1][i] == ',')
			{
				channels_password.push_back(channel_password);
				channel_password.clear();
			}
		}
		channels_password.push_back(channel_password);
	}

	Channel *channelTarget;
	for (size_t i = 0; i < channels_name.size(); i++)
	{
		channelTarget = server->getChannelByName(channels_name[i]);
		if (channelTarget == NULL)
		{
			if (user->getChannels().size() >= 10)
			{
				server->sendMessageError(user->getFd(), "405", channels_name[i] + " :You have joined too many channels");
				continue;
			}
			if (channels_password.size() > 0 && channels_password.size() > i)
				channelTarget = new Channel(channels_name[i], channels_password[i]);
			else
				channelTarget = new Channel(channels_name[i]);
			channelTarget->addUser(user, 1);
			user->addChannel(channelTarget);
			server->addChannel(channelTarget);
			sendJoinMessage(user, channelTarget, server);
		}
		else if (channelTarget->isFull())
		{
			server->sendMessageError(user->getFd(), "471", channels_name[i] + " :Cannot join channel, server full");
		}
		else if ((channels_password.size() > 0 && channels_password.size() - 1 >= i && channelTarget->getPassword() != channels_password[i]) || (channelTarget->getPassword() != "" && channels_password.size() <= i) )
		{
			server->sendMessageError(user->getFd(), "475", channels_name[i] + " :Cannot join channel, wrong password");
		}
		else if (channelTarget->isPrivate() && !channelTarget->sendInvite(user->getNickname()))
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
		else
		{
			channelTarget->addUser(user, 0);
			user->addChannel(channelTarget);
			sendJoinMessage(user, channelTarget, server);
		}
	}
	return true;
}
