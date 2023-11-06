/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:29 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/06 11:06:02 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name) : _name(name) {
    this->_hasLimit = false;
	this->_limit = 0;
	this->_isPrivate = false;
	this->_hasTopicProtection = false;
	this->_topic = "";
	this->_password = "";
}

Channel::Channel(std::string name, std::string password) : _name(name) {
    this->_hasLimit = false;
	this->_limit = 0;
	this->_isPrivate = false;
	this->_hasTopicProtection = false;
	this->_topic = "";
	this->_password = password;
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

	this->_users[user] = isAdmin;
}

void Channel::removeUser( User* user )
{
    if (this->_users.find(user) != this->_users.end())
		this->_users.erase(user);
}

void Channel::setOp(User* user ) {

    if (this->_users.find(user) != this->_users.end())
		this->_users[user] = 1;
}

void Channel::deOp(User* user ) {

    if (this->_users.find(user) != this->_users.end())
		this->_users[user] = 0;
}

bool Channel::isOp(User* user ) {

    if (this->_users.find(user) != this->_users.end())
		return this->_users[user] == 1;
    return false;
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
	this->_topic = topic;
}

std::string Channel::getTopic() {
	return this->_topic;
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

void Channel::setPrivate(bool isPrivate)
{
    this->_isPrivate = isPrivate;
}

bool Channel::hasTopicProtection() const
{
    return this->_hasTopicProtection;
}

void Channel::setTopicProtection(bool protection)
{
    this->_hasTopicProtection = protection;
}

void Channel::setPassword(const std::string& password)
{
    this->_password = password;
}

std::string Channel::getUsersList()
{
	std::string usersList;
	std::map<User*, int>::iterator it = this->_users.begin();
	while (it != this->_users.end())
	{
		if (it->second == 1)
			usersList += "@";
		else
			usersList += "+";
		usersList += it->first->getNickname();
		++it;
		if (it != this->_users.end())
			usersList += " ";
	}
	return usersList;
}

int	Channel::getUsersOpCount()
{
	int count = 0;
	std::map<User*, int>::iterator it = this->_users.begin();
	for (; it != this->_users.end(); ++it)
	{
		if (it->second == 1)
			count++;
	}
	return (count);
}
