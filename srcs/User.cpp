/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 17:17:28 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"

User::User() {
    
}

User::User( std::string const & userName ) : _userName(userName) {
    
}

User::User( const User& obj ) {

    *this = obj;
}

User& User::operator=( const User& obj ) {
    
    if (this != &obj )
        return *this;
    return *this;
}

User::~User() {
    
}

std::string const & User::getUsername() const {
    
    return this->_userName;
}

std::string const & User::getNickname() const {
    
    return this->_nickName;
}

void User::setNickName( std::string const & nickName ) {
    
    this->_nickName = nickName;
}

void User::addChannel( Channel* channel ) {
    
    // Vérifier en amont si le channel existe déjà
    this->_channels[channel->getName()] = channel;
}

void User::removeChannel( std::string const & name ) {
    
    this->_channels.erase(name);    
}

std::map<std::string, Channel*> User::getChannels() {
    
    return this->_channels;
}