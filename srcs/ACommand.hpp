/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:41 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/31 17:01:08 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "User.hpp"
#include "Channel.hpp"

class Server;

class ACommand {
    
    private:
        std::string _name;
        std::string _usage;
		bool		_opOnly;

    public:
        ACommand( std::string const & name, std::string const & usage, bool opOnly );
        virtual ~ACommand();

        virtual bool execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) = 0;
        std::string const & getName() const;
        std::string const & getUsage() const;
		bool opOnly() const;
             
};
