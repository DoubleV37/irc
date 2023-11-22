/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/22 11:06:33 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"

/**
 * NAME : PASS
 * USAGE : /pass <pass>
 */
Pass::Pass() : ACommand( "PASS", false )
{
}

Pass::~Pass()
{   
}

bool Pass::execute( std::vector<std::string> args, User* user, Server* server ) {
    
    static int tries = 0;
    
	if (args.size() == 0)
	{
        server->sendMessageError(user->getFd(), "461", "not enough parameters. Please retry.");
		return true;
	}
    if (server->isValidPass(args[0]) == 0)
    {
        server->sendMessageError(user->getFd(), "464", "password must contain only printable characters. Please retry.");
        return true;
    }
    if (server->getPassword() == "")
    {
        server->sendMessage(user->getFd(), "password ok : no require\r\n");
        user->setPassToggle(true);
    }
    if (server->getPassword() != "" && args[0] == server->getPassword())
    {
        server->sendMessage(user->getFd(), "password ok\r\n");
        user->setPassToggle(true);
    }
    else if (tries < 3)
    {
        server->sendMessageError(user->getFd(), "464", "password incorrect. Please retry.");
        tries++;
    }
    else 
    {
        tries = 0;
        server->loginError(user->getFd(), "464", "too many trys. Disconnecting...");
    }
    return true;
}
