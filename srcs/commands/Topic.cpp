/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:20 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 16:32:54 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

Topic::Topic( std::string const & name, std::string const & usage ) : ACommand( name, usage)  {
    
}

Topic::~Topic() {
    
}

bool Topic::execute( std::vector<std::string> args, User* user, Channel* channel, Server* server ) {
    
    (void)args;
    (void)user;
    (void)channel;
    (void)server;
    return true;
}