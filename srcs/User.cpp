/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/27 22:24:47 by doublev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"

User::User()
{
    this->_userName = "";
    this->_nickName = "";
    this->_passIsSet = false;
    this->_fd = -1;
}

User::User( int fd )
{
    this->_fd = fd;
    this->_userName = "";
    this->_nickName = "";
    this->_passIsSet = false;
}

User::User( const User& obj ) {

    *this = obj;
}

User& User::operator=( const User& obj ) {

    if (this == &obj )
        return *this;

    this->_channels = obj._channels;
    this->_nickName = obj._nickName;
    this->_userName = obj._userName;
    this->_fd = obj._fd;
    this->_passIsSet = obj._passIsSet;
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

int User::getFd() const
{
//    return this->_fd;
    return 4;
}

void User::setUserName( std::string const & userName ) {

    this->_userName = userName;
}

void User::setNickName( std::string const & nickName ) {

    this->_nickName = nickName;
}

void User::setPassToggle( bool status ) {

    this->_passIsSet = status;
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

void User::send( std::string const & message ) {
	(void)message;
}
