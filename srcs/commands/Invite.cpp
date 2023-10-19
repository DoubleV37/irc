/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:08 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 16:33:07 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"

Invite::Invite( std::string const & name, std::string const & usage ) : ACommand( name, usage) {
    
}

Invite::~Invite() {
    
}

bool Invite::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)args;
    (void)user;
    (void)channel;
    (void)server;
    return true;
}