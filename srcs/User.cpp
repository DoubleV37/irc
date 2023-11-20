/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/20 14:41:48 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "User.hpp"
#include <cstddef>

User::User()
{
    this->_fd = -1;
    this->_userName = "";
    this->_nickName = "";
    this->passIsSet = false;
	this->_todisconnect = false;
}

User::User( int fd )
{
    this->_fd = fd;
    this->_userName = "";
    this->_nickName = "";
    this->passIsSet = false;
	this->_todisconnect = false;
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
    this->passIsSet = obj.passIsSet;
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
    return this->_fd;
}

void User::setUserName( std::string const & userName ) {

    this->_userName = userName;
}

void User::setNickName( std::string const & nickName ) {

    this->_nickName = nickName;
}

void User::setPassToggle( bool status ) {

    this->passIsSet = status;
}

void User::setToDisconnect()
{
	this->_todisconnect = true;
}

bool User::getToDisconnect()
{
	return this->_todisconnect;
}

void User::addChannel( Channel* channel ) {

    this->_channels[channel->getName()] = channel;
}

void User::removeChannel( std::string const & name ) {

    if (this->_channels.find(name) != this->_channels.end())
        this->_channels.erase(name);
    return ;
}

std::map<std::string, Channel*> User::getChannels() {

    return this->_channels;
}

void User::send( std::string const & message ) {
	(void)message;
}

bool User::isLog() {

    return (this->_userName != "" && this->_nickName != "");
}

std::string &User::getBufferMsg()
{
	return this->_bufferMsg;
}

void User::appendBufferMsg(std::string const &msg)
{
	this->_bufferMsg += msg;
}
