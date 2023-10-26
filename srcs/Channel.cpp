/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:29 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/20 13:41:51 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() {
    
}

Channel::Channel( const Channel& obj ) {

    *this = obj;
}

Channel& Channel::operator=( const Channel& obj ) {
    
    if ( this != &obj )
    {
        return *this;
    }
    return *this;
}

Channel::~Channel() {
    
}

std::string const & Channel::getName() {
    
    return this->_name;
}

void Channel::addUser( User* user, int isAdmin ) {
    
    (void)user;
    (void)isAdmin;
}

void Channel::removeUser( User* user )
{
    (void)user;
}

void Channel::setOp(User* user ) {
    
    (void)user;
}

void Channel::deOp(User* user ) {

    (void)user;    
}

bool Channel::isOp(User* user ) {

    (void)user;
    return true;    
}

bool Channel::hasLimit() {
    
    return this->_hasLimit;
}

size_t  Channel::getLimit() {

   return this->_limit; 
}

void Channel::setLimit( int limit ) {
    
    this->_limit = limit;
}

bool Channel::sendInvite( std::string user ) {

    (void)user;
    return true;    
}

void Channel::broadcast( std::string message ) {
    
    (void)message;
}

std::string Channel::getPassword() {

    return this->_password;
}

bool Channel::isPrivate() {

    return this->_isPrivate;
}

void Channel::setTopic(std::string topic) {
    (void)topic;
}

bool Channel::containsUser(User *user)
{
    return this->_users.find(user) != this->_users.end();
}

std::map<User *, int> Channel::getUsers()
{
    return this->_users;
}

bool Channel::isFull()
{
    return this->hasLimit() && this->getUsers().size() == this->getLimit();
}
