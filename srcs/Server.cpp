/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:34 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/21 12:34:12 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {

}

Server::Server(int port) {
	this->_port = port;
	create_socket_server();
	for (int i = 0 ; i < MAX_CONNECTIONS ; i++)
		this->all_connections[i] = -1;
	this->nb_connections = 1;
	this->all_connections[0] = this->_socket;
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

int Server::create_socket_server()
{
	struct sockaddr_in addr;

	this->_socket = socket(AF_INET, SOCK_STREAM, 0); // ici on recupère le FD du socket
	if (this->_socket == -1)
		return (0);//erreur socket
	int opt = 1; // Verifier pourquoi 1
	setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	addr.sin_family = AF_INET; // IPV4
	addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
	addr.sin_port = htons(this->_port); // Port
	if (bind(this->_socket, (struct sockaddr *)&addr, sizeof(addr)) != 0)
		return (0);
	if (listen(this->_socket, MAX_CONNECTIONS))
		return (0);
	return (1);
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
