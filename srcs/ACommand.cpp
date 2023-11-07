/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/07 14:09:07 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"
#include "Server.hpp"

ACommand::ACommand( std::string const & name, bool loginRequired ) : _name(name), _loginRequired(loginRequired)
{
}

ACommand::~ACommand()
{
}

bool ACommand::execute( std::vector<std::string> args, User* user, Server* server )
{
    (void)args;
    (void)user;
    (void)server;
    return true;
}

std::string const & ACommand::getName() const
{
    return this->_name;
}

bool ACommand::loginRequired() const
{
	return this->_loginRequired;
}

