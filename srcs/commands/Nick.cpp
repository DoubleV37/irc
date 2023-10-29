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

Nick::Nick() : ACommand( "Nick", "/Nick <Nick>", false )
{
}

Nick::~Nick()
{   
}

bool Nick::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)channel;
    (void)server;

    if (this->_password != "" && user->_passIsSet == false)
        loginError(user->getFd(), "code", "password required");
    else if ((user->_passIsSet == true && this->_password != "") || (user->_passIsSet == false && this->_password == ""))
    {
        if (args != "" && args.size() <= MAX_NICK_LENGTH)
        {
            for (size_t i = 0 ; i < this->_users.size() ; i++)
            {
                if (args == this->_users[i]->getNickname())
                {
                    loginError(user->getFd(), "433", "nickname already taken");
                    break;
                }
                else
                {
                    //autre vérifs de nickname valide ?
                    sendMessage(user->getFd(), "nickname ok\r\n");
                    user->setNickName(args);
                    break;
                }
            }
        }
        else if (args.size() > MAX_NICK_LENGTH)
            loginError(user->getFd(), "432", "nickname is more than 12 characters");
        else if (args == "")
            loginError(user->getFd(), "431", "nickname is empty");
    }
    return true;
}
