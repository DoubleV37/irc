/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/20 11:47:31 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

/**
 * NAME : NICK
 * USAGE : /nick <nick>
 */
Nick::Nick() : ACommand( "NICK", false )
{
}

Nick::~Nick()
{
}

bool Nick::execute( std::vector<std::string> args, User* user, Server* server ) {
	if (args.size() == 0)
	{
        server->loginError(user->getFd(), "431", "nickname is empty");
		return true;
	}

    if (server->getPassword() != "" && user->passIsSet == false)
        server->loginError(user->getFd(), "464", "password required");
    else if ((user->passIsSet == true && server->getPassword() != "") || (user->passIsSet == false && server->getPassword() == ""))
    {
        if (args[0] != "" && args[0].size() <= MAX_NICK_LENGTH)
        {
            for (size_t i = 0 ; i < server->getUserList().size() ; i++)
            {
                if (args[0] == server->getUserList()[i]->getNickname())
                {
                    server->loginError(user->getFd(), "433", "nickname already taken");
                    break;
                }
                else
                {
                    user->setNickName(args[0]);
					server->sendMessage(user->getFd(), ": 001 " + user->getNickname() + " :Welcome to the awesome IRC Project " + user->getNickname() + "\r\n");
                    break;
                }
            }
        }
        else if (args[0].size() > MAX_NICK_LENGTH)
            server->loginError(user->getFd(), "432", "nickname is more than 12 characters");
        else if (args[0] == "")
            server->loginError(user->getFd(), "431", "nickname is empty");
    }
    return true;
}
