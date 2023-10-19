/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:10 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 16:33:03 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"

Kick::Kick( std::string const & name, std::string const & usage ) : ACommand( name, usage)  {
    
}

Kick::~Kick() {
    
}

bool Kick::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)args;
    (void)user;
    (void)channel;
    (void)server;
    return true;  
}