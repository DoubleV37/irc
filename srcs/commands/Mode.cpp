/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:15 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 16:33:00 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

Mode::Mode( std::string const & name, std::string const & usage ) : ACommand( name, usage)  {
    
}

Mode::~Mode() {
    
}

bool Mode::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {

    (void)args;
    (void)user;
    (void)channel;
    (void)server;
    return true; 
}