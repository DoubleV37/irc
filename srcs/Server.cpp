/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:34 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/20 13:37:15 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {
    
}

Server::Server( const Server& obj ) {

    *this = obj;
}

Server& Server::operator=( const Server& obj ) {
    
    if (this != &obj )
        return *this;
    return *this;    
}

Server::~Server() {
    
}

void Server::addUser( User* user ) {

    (void)user;
}

void Server::addChannel( Channel* channel ) {

    (void)channel;   
}

std::vector<User*> Server::getUsers() {

    return this->_users;
}

std::map<std::string, Channel*> Server::getChannels() {

    return this->_channels;
}

User* Server::getUserByUsername( std::string const & userName ) const {

    (void)userName;
    return NULL;     
}

Channel* Server::getChannelByName( std::string const & channel ) const {

    (void)channel;    
    return NULL;   
}

void Server::deleteUser(User* user) {

    (void)user;
}

ACommand* Server::getCommand( std::string const & command ) const  {

    (void)command;
    return NULL;
}

void Server::addCommand( std::string const & name, ACommand* command ) {
    
    (void)name;
    (void)command;
}