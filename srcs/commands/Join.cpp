/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 17:22:23 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

Join::Join( std::string const & name, std::string const & usage ) : ACommand( name, usage)  {
    
}

Join::~Join() {
    
}

bool Join::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    
    (void)args;
    (void)user;
    (void)channel;
    (void)server;
    return true;
}