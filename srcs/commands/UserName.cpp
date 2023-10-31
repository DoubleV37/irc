/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserName.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/31 17:00:18 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserName.hpp"

UserName::UserName() : ACommand( "UserName", "/UserName <UserName>", false )
{
    
}

UserName::~UserName()
{ 
    
}

bool UserName::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    
    std::string parameter;
    
    (void)channel;
    (void)server;
    
    parameter = args[0];

    if (user->getNickname() == "")
        server->loginError(user->getFd(), "code", "nickname required");
    else if (server->getPassword() != "" && user->_passIsSet == false)
        server->loginError(user->getFd(), "code", "password required");
    else if (server->isValidUsername(parameter) == 0)
        server->loginError(user->getFd(), "code", "username must contain only alphanumeric characters");
    else if ((user->_passIsSet == true && server->getPassword() != "") || (user->_passIsSet == false && server->getPassword() == ""))
    {
        server->sendMessage(user->getFd(), "username ok\r\n");
        user->setUserName(parameter);
    }
    return true;
}
