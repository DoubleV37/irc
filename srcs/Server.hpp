/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:37 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/31 16:59:49 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <iostream>
#include <vector>
// #include "ACommand.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "commands/Join.hpp"
// #include "commands/Kick.hpp"
// #include "commands/Message.hpp"
// #include "commands/Mode.hpp"
// #include "commands/Nick.hpp"
// #include "commands/Invite.hpp"
// #include "commands/UserName.hpp"
// #include "commands/Pass.hpp"
// #include "commands/Topic.hpp"
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
		void addCommand( ACommand* name );
		int isCommand( std::string const & name ) const;
		// SWITCH CASE POUR DISPATCH
		void login( std::string const & buffer, int step, int cli_fd );
		void dispatch( std::string const & recv_msg, int cli_fd );
		int createSocketServer();
		int	addNewConnections();
		int	recvMessage();

	public:
		Server();
		Server(int port, std::string const & password);
		// Ajouter constructeur paramètres
		Server( const Server& obj );
		Server& operator=( const Server& obj );
		~Server();

		User* getUserByNickname( std::string const & nickname ) const;
		User* getUserByFd( int fd ) const;
		std::string const & getPassword() const;
		int	sendMessage( int cli_fd, std::string const & message );
		int	sendMessageError( int cli_fd, std::string num_error, std::string const & message );
		int	sendMessageBetweenUsers(int start_fd, std::string target, std::string const & message);
		int	isValidUsername(std::string const & str);
		Channel* getChannelByName( std::string const & channel ) const;
		void loginError( int cli_fd, std::string num_error, std::string message );
		void addChannel( Channel* channel );
		void run();
        void exit();

};
