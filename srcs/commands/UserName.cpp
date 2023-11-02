/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserName.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/02 14:47:13 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserName.hpp"

UserName::UserName() : ACommand( "USER", "/UserName <UserName>", false )
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
        server->loginError(user->getFd(), "431", "nickname required");
    else if (server->getPassword() != "" && user->passIsSet == false)
        server->loginError(user->getFd(), "464", "password required");
    else if (server->isValidUsername(parameter) == 0)
        server->loginError(user->getFd(), "432", "username must contain only alphanumeric characters");
    else if (parameter.size() > MAX_USER_LENGTH)
        server->loginError(user->getFd(), "432", "username is more than 12 characters");
    else if (parameter == "")
        server->loginError(user->getFd(), "461", "username is empty");
    else if ((user->passIsSet == true && server->getPassword() != "") || (user->passIsSet == false && server->getPassword() == ""))
    {
        server->sendMessage(user->getFd(), "username ok\r\n");
        user->setUserName(parameter);
    }
    return true;
}
