/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 13:54:03 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command( std::string const & name, std::string const & usage ) : _name(name), _usage(usage) {

    (void)name;
    (void)usage;
 
}

Command::~Command() {
    
}

bool Command::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)args;
    (void)user;
    (void)channel;
    (void)server;
    return true;
}

std::string const & Command::getName() const {

    return this->_name;
}

std::string const & Command::getUsage() const {

    return this->_usage;
}
