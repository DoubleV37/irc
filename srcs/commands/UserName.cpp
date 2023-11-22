/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserName.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/22 18:48:19 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserName.hpp"

/**
 * NAME : USER
 * USAGE : /user <username>
 */
UserName::UserName() : ACommand( "USER", false )
{
}

UserName::~UserName()
{ 
}

bool UserName::execute( std::vector<std::string> args, User* user, Server* server ) {
    
    (void)server;

	std::string parameter;

	if (args.size() == 0)
	{
        server->sendMessageError(user->getFd(), "461", "Not enough parameters");
		return true;
	}

    parameter = args[0];

    if (user->getNickname() == "")
        server->sendMessageError(user->getFd(), "431", "nickname required");
    else if (server->getPassword() != "" && user->passIsSet == false)
        server->sendMessageError(user->getFd(), "464", "password required");
    else if (server->isValidUsername(parameter) == 0)
        server->sendMessageError(user->getFd(), "432", "username must contain only alphanumeric characters");
    else if (parameter.size() > MAX_USER_LENGTH)
        server->sendMessageError(user->getFd(), "432", "username is more than 12 characters");
    else if ((user->passIsSet == true && server->getPassword() != "") || (user->passIsSet == false && server->getPassword() == ""))
    {
        server->sendMessage(user->getFd(), "username ok\r\n");
        user->setUserName(parameter);
    }
    return true;
}
