/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/09 16:53:43 by ltuffery         ###   ########.fr       */
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
	if (args.size() == 0)
	{
        server->loginError(user->getFd(), "461", "not enough parameters");
		return true;
	}

    std::cout << "password : " << args[0] << std::endl;

    if (server->getPassword() != "" && args[0] == server->getPassword())
    {
        server->sendMessage(user->getFd(), "password ok\r\n");
        user->setPassToggle(true);
    }
    else if (server->getPassword() == "")
    {
        server->sendMessage(user->getFd(), "password ok : no require\r\n");
        user->setPassToggle(true);
    }
    else
        server->loginError(user->getFd(), "464", "password incorrect");
    return true;
}
