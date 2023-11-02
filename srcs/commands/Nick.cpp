/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/21 17:47:36 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

Nick::Nick() : ACommand( "NICK", "/Nick <Nick>", false )
{
}

Nick::~Nick()
{   
}

bool Nick::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)channel;

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
                    //autre vérifs de nickname valide ?
                    server->sendMessage(user->getFd(), "nickname ok\r\n");
                    user->setNickName(args[0]);
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
