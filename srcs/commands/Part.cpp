/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/02 10:58:33 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

Part::Part() : ACommand( "PART", "<canal>{,< canal >} [<reason>]", false )
{

}

Part::~Part()
{

}

bool Part::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    std::string channelName;
    (void)channel;

	if (args.empty() || args.size() > 2)
	{
		server->sendMessageError(user->getFd(), "461", this->getUsage());
		return false;
	}
    for (size_t i = 0; i < args[0].size(); i++)
	{
        if (args[0][i] != ',')
                channelName = args[0];
        else if (args[0][i] == ',')
        {
            if ((channelName[0] != '#' && channelName[0] != '&') || channelName.size() == 0 || channelName.size() > 200 )
            {
                server->sendMessageError(user->getFd(), "403", channelName + " :No such channel");
                return false;
            }
            leaveChannel(user, server, channelName);
            channelName.clear();
        }
    }
    if ((channelName[0] != '#' && channelName[0] != '&') || channelName.size() == 0 || channelName.size() > 200 )
    {
        server->sendMessageError(user->getFd(), "403", channelName + " :No such channel");
        return false;
    }
    else
    {
        leaveChannel(user, server, channelName);
    }
    return true;
}

void Part::leaveChannel( User* user, Server* server, std::string channelName )
{
    Channel* channelTarget = server->getChannelByName(channelName);

    if (channelTarget == NULL)
    {
        server->sendMessageError(user->getFd(), "403", channelName + " :No such channel");
        return ;
    }

    std::map<User*, int> usersMap = server->getChannelByName(channelName)->getUsers();

    if (channelTarget->containsUser(user) == false)
    {
        server->sendMessageError(user->getFd(), "442", channelName + " :You're not on that channel");
        return ;
    }
    server->sendMessageChannel(channelTarget, ":" + user->getNickname() + " PART " + channelName + "\r\n");
    user->removeChannel(channelName);
    if (usersMap.size() == 1)
	{
        server->deleteChannel(channelName);
		return ;
	}
    else if (channelTarget->isOp(user) == true)
    {
        for (std::map<User*, int>::iterator it = usersMap.begin(); it != usersMap.end(); it++)
        {
            if (it->first != user && !channelTarget->isOp(it->first))
                channelTarget->setOp(it->first);
        }
    }
    channelTarget->removeUser(user);
    channelTarget = NULL;
}
