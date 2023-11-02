/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/31 16:36:17 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"
#include "Server.hpp"

ACommand::ACommand( std::string const & name, std::string const & usage, bool opOnly ) : _name(name), _usage(usage), _opOnly(opOnly)
{
}

ACommand::~ACommand()
{    
}

bool ACommand::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server )
{
    (void)args;
    (void)user;
    (void)channel;
    (void)server;
    return true;
}

std::string const & ACommand::getName() const
{
    return this->_name;
}

std::string const & ACommand::getUsage() const
{
    return this->_usage;
}

bool ACommand::opOnly() const
{
    return this->_opOnly;
}
