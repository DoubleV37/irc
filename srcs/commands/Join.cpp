/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/30 15:45:44 by doublev          ###   ########.fr       */
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

void Join::sendJoinMessage( User* user, Channel* channel, Server* server )
{
	std::string message = ":" + user->getNickname() + " JOIN " + channel->getName() + "\r\n";
	std::map<User*, int> users = channel->getUsers();
	for (std::map<User*, int>::iterator it = users.begin(); it != users.end(); ++it)
		server->sendMessage(it->first->getFd(), message);
	if (channel->getTopic() != "")
		server->sendMessage(user->getFd(), ": 332 " + user->getNickname() + " " + channel->getName() + " :" + channel->getTopic() + "\r\n");
	else
		server->sendMessage(user->getFd(), ": 331 " + user->getNickname() + " " + channel->getName() + " :No topic is set\r\n");
	// server->sendMessage(user->getFd(), ": 353 " + user->getNickname() + " = " + channel->getName() + " :" + channel->getUsersList() + "\r\n");
	// server->sendMessage(user->getFd(), ": 366 " + user->getNickname() + " " + channel->getName() + " :End of /NAMES list.\r\n");
}

bool Join::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
    (void)channel;
	if (args.empty() || args.size() > 2)
        return false;

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
				return false;
			channels_name.push_back(channel_name);
			channel_name.clear();
		}
	}
	if ((channel_name[0] != '#' && channel_name[0] != '&') || channel_name.size() == 0 || channel_name.size() > 200 )
		return false;
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

	Channel *channeltarget;
	for (size_t i = 0; i < channels_name.size(); i++)
	{
		channeltarget = server->getChannelByName(channels_name[i]);
		if (channeltarget == NULL)
		{
			std::cout << "channeltarget == NULL" << std::endl;
			if (user->getChannels().size() >= 10)
			{
				server->sendMessageError(user->getFd(), "405", channels_name[i] + " :You have joined too many channels");
				continue;
			}
			if (channels_password.size() > 0 && channels_password.size() > i)
				channeltarget = new Channel(channels_name[i], channels_password[i]);
			else
				channeltarget = new Channel(channels_name[i]);
			channeltarget->addUser(user, 1);
			user->addChannel(channeltarget);
			server->addChannel(channeltarget);
			sendJoinMessage(user, channeltarget, server);
		}
		else
		{
			if (channeltarget->isFull())
			{
				server->sendMessageError(user->getFd(), "471", channels_name[i] + " :Cannot join channel, server full");
				continue;
			}
			if (channels_password.size() > 0 && channels_password.size() > i && channeltarget->getPassword() != channels_password[i])
			{
				server->sendMessageError(user->getFd(), "475", channels_name[i] + " :Cannot join channel, wrong password");
				continue;
			}
			if (channeltarget->isPrivate() && !channeltarget->sendInvite(user->getNickname()))
			{
				server->sendMessageError(user->getFd(), "473", channels_name[i] + " :Cannot join channel, invite only");
				continue;
			}
			if (channeltarget->containsUser(user))
			{
				server->sendMessageError(user->getFd(), "443", channels_name[i] + " :is already on channel");
				continue;
			}
			if (user->getChannels().size() >= 10)
			{
				server->sendMessageError(user->getFd(), "405", channels_name[i] + " :You have joined too many channels");
				continue;
			}
			channeltarget->addUser(user, 0);
			user->addChannel(channeltarget);
			sendJoinMessage(user, channeltarget, server);
		}
	}
	return true;
}
