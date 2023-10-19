/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:29 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 15:00:40 by gazzopar         ###   ########.fr       */
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

void Channel::removeUser( User* user ) {
    
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

int  Channel::getLimit() {

   return this->_limit; 
}

void Channel::setLimit( int limit ) {
    
    this->_limit = limit;
}

bool Channel::sendInvite( std::string user ) {

    (void)user;
    return true;    
}