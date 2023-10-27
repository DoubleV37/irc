/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/27 17:03:18 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"

ACommand::ACommand( std::string const & name, std::string const & usage ) : _name(name), _usage(usage) {
    (void)name;
    (void)usage;
}

ACommand::~ACommand() {
    
}

bool ACommand::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)args;
    (void)user;
    (void)channel;
    (void)server;
    return true;
}

std::string const & ACommand::getName() const {

    return this->_name;
}

std::string const & ACommand::getUsage() const {

    return this->_usage;
}
