/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:37 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/26 15:43:48 by gazzopar         ###   ########.fr       */
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
#define MAX_BUF_LENGTH 4096
#define MAX_NICK_LENGTH 12

class ACommand;

class Server {

	private:
		int	_port;
		int	_socket;
		int	_all_connections[MAX_CONNECTIONS];
		int	_nb_connections;
		fd_set	_fd_to_read;

		std::string	_password;
		std::vector<User*>	_users;
		std::map<std::string, Channel*>		_channels;
		std::map<std::string, ACommand*>	_command;

		void addUser( User* user );
		std::vector<User*> getUsers();
		std::map<std::string, Channel*> getChannels();
		void deleteUser(User*);
		void deleteUser(int cli_fd);
		void deleteChannel(Channel*);
		ACommand* getCommand( std::string const & command ) const;
		void addCommand( std::string const & name, ACommand* command );
		int isCommand( std::string const & name );
		// SWITCH CASE POUR DISPATCH
		void login( std::string const & buffer, int step, int cli_fd );
		void dispatch( std::string const & recv_msg, int cli_fd );
		int createSocketServer();
		int	addNewConnections();
		int	recvMessage();
		int	sendMessage( int cli_fd, std::string const & message );
		void loginError( int cli_fd, std::string message );
		int	isValidUsername(std::string const & str);

	public:
		Server();
		Server(int port, std::string const & password);
		// Ajouter constructeur paramètres
		Server( const Server& obj );
		Server& operator=( const Server& obj );
		~Server();

		User* getUserByUsername( std::string const & userName ) const;
		User* getUserByFd( int fd ) const;
		Channel* getChannelByName( std::string const & channel ) const;
		void addChannel( Channel* channel );
		void run();

};
