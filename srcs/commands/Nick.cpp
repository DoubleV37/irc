/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/22 19:04:38 by ltuffery         ###   ########.fr       */
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
        server->sendMessageError(user->getFd(), "431", "nickname is empty");
	else if (args.size() > 1)
		server->sendMessageError(user->getFd(), "461", "too many parameters");
    else if (server->getPassword() != "" && user->passIsSet == false)
        server->sendMessageError(user->getFd(), "464", "password required, Please use command PASS.");
    else if ((user->passIsSet == true && server->getPassword() != "") || (user->passIsSet == false && server->getPassword() == ""))
    {
        if (server->isValidUsername(args[0]) == 0) 
        {
            server->sendMessageError(user->getFd(), "432", "nickname must contain only alphanumeric characters");
            return true;
        }
        if (args[0].size() > MAX_NICK_LENGTH) 
        {
            server->sendMessageError(user->getFd(), "432", "nickname is more than 12 characters");
            return true;
        }
        if (args[0] != "" && args[0].size() <= MAX_NICK_LENGTH)
        {
            for (size_t i = 0 ; i < server->getUserList().size() ; i++)
            {
                if (args[0] == server->getUserList()[i]->getNickname())
                {
                    server->sendMessageError(user->getFd(), "433", "nickname already taken");
                    return true;
                }
            }
        }
        user->setNickName(args[0]);
        server->sendMessage(user->getFd(), ": 001 " + user->getNickname() + " :Welcome to the awesome IRC Project\r\n");
    }
    return true;
}
