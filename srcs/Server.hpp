/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:37 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/21 13:30:16 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include "User.hpp"
#include "Channel.hpp"
#include "ACommand.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>

#define BUFFER 5000
#define MAX_CONNECTIONS 10

class ACommand;

class Server {

	private:
		int	_port;
		int	_socket;
		int	all_connections[MAX_CONNECTIONS];
		int	nb_connections;
		fd_set	fd_to_read;

		std::string	_password;
		std::vector<User*>	_users;
		std::map<std::string, Channel*>		_channels;
		std::map<std::string, ACommand*>	_command;

		void addUser( User* user );
		std::vector<User*> getUsers();
		std::map<std::string, Channel*> getChannels();
		void deleteUser(User*);
		void deleteChannel(Channel*);
		ACommand* getCommand( std::string const & command ) const;
		void addCommand( std::string const & name, ACommand* command );
		bool isCommand( std::string const & name );
		void run();
		// SWITCH CASE POUR DISPATCH
		void dispatch( std::string const & buffer);
		int create_socket_server();
		int	add_new_connections();
		int	recv_messages();
		int	send_messages();

	public:
		Server();
		Server(int port);
		// Ajouter constructeur paramètres
		Server( const Server& obj );
		Server& operator=( const Server& obj );
		~Server();

		User* getUserByUsername( std::string const & userName ) const;
		Channel* getChannelByName( std::string const & channel ) const;
		void addChannel( Channel* channel );

};
