/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserName.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/29 17:08:45 by gazzopar         ###   ########.fr       */
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
    
    for (int i = 0; args[i] != ' '; i++)
    {
        parameter.push_back(args[i]);
        break;
    }
    if (user->getNickname() == "")
        loginError(user->getFd(), "code", "nickname required");
    else if (this->_password != "" && user->_passIsSet == false)
        loginError(user->getFd(), "code", "password required");
    else if (isValidUsername(parameter) == 0)
        loginError(user->getFd(), "code", "username must contain only alphanumeric characters");
    else if (user->_passIsSet == true && this->_password != "") || (guser->_passIsSet == false && this->_password == ""))
    {
        sendMessage(user->getFd(), "username ok\r\n");
        user->setUserName(parameter);
    }
    return true;
}
