/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:34 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/21 18:34:12 by doublev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <unistd.h>

Server::Server() {

}

Server::Server(int port) {
	this->_port = port; //verifier le port
	createSocketServer();
	for (int i = 0 ; i < MAX_CONNECTIONS ; i++)
		this->_all_connections[i] = -1;
	this->_nb_connections = 1;
	this->_all_connections[0] = this->_socket;
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

int Server::createSocketServer()
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

int	Server::addNewConnections()
{
	int new_fd;
	struct sockaddr_in new_addr;
	socklen_t addrlen;

	if (FD_ISSET(this->_socket, &this->_fd_to_read))
	{
		/* accept the new connection */
		std::cout << "Returned fd is %d (server's fd)\n" << this->_socket << std::endl;
		new_fd = accept(this->_socket, (struct sockaddr*)&new_addr, &addrlen);
		if (new_fd >= 0 && this->_nb_connections != MAX_CONNECTIONS) {
			std::cout << "Accepted a new connection with fd: %d\n" << new_fd << std::endl;
			for (int i = 0 ; i < MAX_CONNECTIONS ; i++) {
				if (this->_all_connections[i] < 0) {
					this->_all_connections[i] = new_fd;
					this->_nb_connections++;
					break;
				}
			}
		}
		else
		{
			std::cerr << "ERROR" << std::endl;
			return (0);
		}
	}
	return (1);
}

int	Server::recvMessages()
{
	char	buf[BUFFER];

	for (int i = 1 ; i < MAX_CONNECTIONS; i++) {
		if ((this->_all_connections[i] > 0) && (FD_ISSET(this->_all_connections[i], &this->_fd_to_read))) {
			/* read incoming data */
			int recv_val = recv(this->_all_connections[i], buf, BUFFER, 0);
			if (recv_val == 0) {
				close(this->_all_connections[i]);
				this->_all_connections[i] = -1; /* Connection is now closed */
			}
			if (recv_val > 0) {
				std::cout << "cli nb : " << i << " msg : " << buf << std::endl;
			}
			if (recv_val == -1) {
				break;
			}
		}
	}
	return (1);
}

int	Server::sendMessages()
{
	return (1);
}

void Server::run()
{
	while (1)
	{
		FD_ZERO(&this->_fd_to_read);
		for (int i = 0 ; i < MAX_CONNECTIONS; i++) {
			if (this->_all_connections[i] >= 0) {
				FD_SET(this->_all_connections[i], &this->_fd_to_read);
			}
		}
		int nb_cli = select(FD_SETSIZE, &this->_fd_to_read, NULL, NULL, NULL);
		if (nb_cli >= 0)
		{
			addNewConnections();
			}
			if (nb_cli != 0)
			{
				recvMessages();
			}
		}
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
