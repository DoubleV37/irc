/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/07 14:22:11 by ltuffery         ###   ########.fr       */
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
        server->loginError(user->getFd(), "code", "password nok");
    return true;
}
