/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:34 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/31 18:42:39 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ACommand.hpp"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

Server::Server() {

}

Server::Server(int port, std::string const & password) {
	this->_port = port; //verifier le port
	createSocketServer();
	for (int i = 0 ; i < MAX_CONNECTIONS ; i++)
		this->_all_connections[i] = -1;
	this->_nb_connections = 1;
	this->_all_connections[0] = this->_socket;
	this->_password = password;
}

Server::Server( const Server& obj ) {

	*this = obj;
}

Server& Server::operator=( const Server& obj ) {

	if (this == &obj )
		return *this;
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        this->_all_connections[i] = obj._all_connections[i];
    }
    this->_socket = obj._socket;
    this->_users = obj._users;
    this->_fd_to_read = obj._fd_to_read;
    this->_password = obj._password;
    this->_nb_connections = obj._nb_connections;
    this->_port = obj._port;
    this->_command = obj._command;
    this->_channels = obj._channels;

	return *this;
}

Server::~Server() {

}

int Server::createSocketServer()
{
	struct sockaddr_in addr;

	this->_socket = socket(AF_INET, SOCK_STREAM, 0); // ici on recupère le FD du socket
	if (this->_socket == -1)
		return (0); //erreur socket
	int opt = 1; // Verifier pourquoi 1
	setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	addr.sin_family = AF_INET; // IPV4
	addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
	addr.sin_port = htons(this->_port); // Port
	// fcntl(this->_socket, F_SETFL, O_NONBLOCK);
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
	unsigned int addrlen = sizeof(new_addr);

	if (FD_ISSET(this->_socket, &this->_fd_to_read))
	{
		/* accept the new connection */
		new_fd = accept(this->_socket, (struct sockaddr*)&new_addr, &addrlen);
		if (new_fd >= 0 && this->_nb_connections != MAX_CONNECTIONS) {
			std::cout << "Accepted a new connection with fd: " << new_fd << std::endl;
			for (int i = 0 ; i < MAX_CONNECTIONS ; i++) {
				if (this->_all_connections[i] < 0) {
					// fd du User qu on vient d'accepter
					this->_all_connections[i] = new_fd;
					User* user = new User(new_fd);
					_users.push_back(user);
					this->_nb_connections++;
					break;
				}
			}
		}
		else
		{
			sendMessageError(new_fd, "ERROR", "too many clients");
			return (0);
		}
	}
	return (1);
}

int	Server::recvMessage()
{
	std::vector<char> buffer(MAX_BUF_LENGTH);
	std::string	rcv_msg;
	int recv_val = 1;

	for (int i = 1 ; i < MAX_CONNECTIONS; i++) {
		if ((this->_all_connections[i] > 0) && (FD_ISSET(this->_all_connections[i], &this->_fd_to_read))) {
			while (rcv_msg[rcv_msg.size() - 2] != '\r' && rcv_msg[rcv_msg.size() - 1] != '\n')
			{
				recv_val = recv(this->_all_connections[i], &buffer[0] , buffer.size(), 0);
				if (recv_val > 0)
				{
					for (int i = 0; i < recv_val; i++)
						rcv_msg.push_back(buffer[i]);
				}
				else if (recv_val == 0)
				{
					std::cout << "Client " << this->_all_connections[i] << " disconnected" << std::endl;
					deleteUser(this->_all_connections[i]);
					break;
				}
				else
				{
					std::cerr << "ERROR" << std::endl;
					break;
				}
			}
			if (rcv_msg.size() > 0)
				dispatch(rcv_msg, this->_all_connections[i]);
			// Parsing / Dispatch
			// REMPLIR LE USER QUI EST DEJA STOCKE AVEC ADDUSER
			// Utiliser la fonction ADDUSER ou équivalent en trouvant le USER dans le vector
		}
	}
	return (1);
}

int	Server::sendMessage( int cli_fd, std::string const & message )
{
	send(cli_fd, message.c_str(), message.size(), 0);
	return (1);
}

int Server::sendMessageBetweenUsers(int start_fd, std::string target, std::string const & message)
{
	std::string msg = ":" + getUserByFd(start_fd)->getNickname() + " " + "PRIVMSG " + target + " :" + message + "\r\n";
	sendMessage(getUserByNickname(target)->getFd(), msg);
	return (1);
}

int	Server::sendMessageError( int cli_fd, std::string num_error, std::string const & message )
{
	std::string num_error_msg;
	std::string error_msg;

	num_error_msg = ": " + num_error + " " + getUserByFd(cli_fd)->getNickname() + "\r\n";
	error_msg = "ERROR :" + message + "\r\n";
	send(cli_fd, num_error_msg.c_str(), num_error_msg.size(), 0);
	send(cli_fd, error_msg.c_str(), error_msg.size(), 0);
	return (1);
}

void Server::loginError( int cli_fd, std::string num_error, std::string message)
{
	sendMessageError(cli_fd, num_error, message);
	deleteUser(cli_fd);
}

int	Server::isValidUsername(std::string const & str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isalnum(str[i]))
			return (0);
	}
	return (1);
}

// void Server::login( std::string const & arg, int step, int cli_fd )
// {
// 	std::string parameter;
// 	switch(step) {

// 		default:
//         {
//             break ;
//         }
//         case 0:
// 		{
// 			//verif password
// 			std::cout << "password : " << arg << std::endl;
// 			if (this->_password != "" && arg == this->_password)
// 			{
// 				sendMessage(cli_fd, "password ok\r\n");
// 				getUserByFd(cli_fd)->setPassToggle(true);
// 			}
// 			else if (this->_password == "")
// 			{
// 				sendMessage(cli_fd, "password ok : no require\r\n");
// 				getUserByFd(cli_fd)->setPassToggle(true);
// 			}
// 			else
// 				loginError(cli_fd, "code", "password nok");
// 			break;
// 		}
//         case 1:
// 		{
// 			if (this->_password != "" && getUserByFd(cli_fd)->_passIsSet == false)
// 				loginError(cli_fd, "code", "password required");
// 			else if ((getUserByFd(cli_fd)->_passIsSet == true && this->_password != "") || (getUserByFd(cli_fd)->_passIsSet == false && this->_password == ""))
// 			{
// 				if (arg != "" && arg.size() <= MAX_NICK_LENGTH)
// 				{
// 					for (size_t i = 0 ; i < this->_users.size() ; i++)
// 					{
// 						if (arg == this->_users[i]->getNickname())
// 						{
// 							loginError(cli_fd, "433", "nickname already taken");
// 							break;
// 						}
// 						else
// 						{
// 							//autre vérifs de nickname valide ?
// 							sendMessage(cli_fd, "nickname ok\r\n");
// 							getUserByFd(cli_fd)->setNickName(arg);
// 							break;
// 						}
// 					}
// 				}
// 				else if (arg.size() > MAX_NICK_LENGTH)
// 					loginError(cli_fd, "432", "nickname is more than 12 characters");
// 				else if (arg == "")
// 					loginError(cli_fd, "431", "nickname is empty");
// 			}
// 			break;
// 		}
//         case 2:
// 		{
// 			for (int i = 0; arg[i] != ' '; i++)
// 			{
// 				parameter.push_back(arg[i]);
// 				break;
// 			}
// 			if (getUserByFd(cli_fd)->getNickname() == "")
// 				loginError(cli_fd, "code", "nickname required");
// 			else if (this->_password != "" && getUserByFd(cli_fd)->_passIsSet == false)
// 				loginError(cli_fd, "code", "password required");
// 			else if (isValidUsername(parameter) == 0)
// 				loginError(cli_fd, "code", "username must contain only alphanumeric characters");
// 			else if ((getUserByFd(cli_fd)->_passIsSet == true && this->_password != "") || (getUserByFd(cli_fd)->_passIsSet == false && this->_password == ""))
// 			{
// 				sendMessage(cli_fd, "username ok\r\n");
// 				getUserByFd(cli_fd)->setUserName(parameter);
// 			}
// 			break;
// 		}
// 	}
// }

void Server::dispatch( std::string const & recv_msg, int cli_fd )
{
	std::vector<std::string> split_msg;
	std::string arg;
	std::string info[3] = {"PASS", "NICK", "USER"};

	if (recv_msg == "CAP LS 302\r\n")
		return ;
	std::cout << "recv_msg : " << recv_msg << std::endl;
	for (size_t i = 0; i < recv_msg.size(); i++)
	{
		if (recv_msg[i] == '\r' && (recv_msg.size() > (i + 1) && recv_msg[i + 1] == '\n'))
		{
			if (arg != "CAP LS 302")
				split_msg.push_back(arg);
			arg.clear();
			i++;
		}
		else if (recv_msg[i] == '\n')
		{
			split_msg.push_back(arg);
			arg.clear();
		}
		else
			arg.push_back(recv_msg[i]);
	}
		
	for (size_t i = 0; i < split_msg.size(); i++)
	{
		ACommand* command;
		std::string	cmd;
		std::vector<std::string> split_msg_tmp;

		for (size_t j = 0; j < split_msg[i].size(); j++)
		{
			if (split_msg[i][j] == ' ')
				break;
			cmd.push_back(split_msg[i][j]);
		}
		if (getCommand(cmd) != NULL)
		{
			command = getCommand(cmd);
			std::cout << "YOUHOU: " << command->getName() << std::endl;
			std::string tmp;
			for (size_t j = cmd.size() + 1 ; j < split_msg[i].size(); j++)
			{
				if (split_msg[i][j] == ' ')
				{
					split_msg_tmp.push_back(tmp);
					tmp.clear();
				}
				else
					tmp.push_back(split_msg[i][j]);
			}
			if (tmp[0] == ':')
				tmp.erase(0, 1);
			split_msg_tmp.push_back(tmp);
			command->execute(split_msg_tmp, getUserByFd(cli_fd), NULL, this);
		}
		else
		{
			sendMessageError(cli_fd, "421", "invalid command");
			break ;
		}
	}
}
// 		// switch (isCommand(cmd))
// 		// {
// 		// 	default:
// 		// 	{
// 		// 		std::cout << "Commande inconnue : " << split_msg[0] << std::endl;
// 		// 		sendMessageError(cli_fd, "421", "invalid command");
// 		// 		break ;
// 		// 	}
// 		// 	case 0:
// 		// 	{
// 		// 		login(split_msg[i].substr(cmd.size() + 1), 0, cli_fd);
// 		// 		break;
// 		// 	}
// 		// 	case 1:
// 		// 	{
// 		// 		login(split_msg[i].substr(cmd.size() + 1), 1, cli_fd);
// 		// 		break;
// 		// 	}
// 		// 	case 2:
// 		// 	{
// 		// 		login(split_msg[i].substr(cmd.size() + 1), 2, cli_fd);
// 		// 		break;
// 		// 	}
// 			case 3:
// 			{
// 				ACommand* command = new Message();
// 				std::vector<std::string> split_msg_tmp;
// 				std::string tmp;
// 				for (size_t j = cmd.size() + 1 ; j < split_msg[i].size(); j++)
// 				{
// 					if (split_msg[i][j] == ' ')
// 					{
// 						split_msg_tmp.push_back(tmp);
// 						tmp.clear();
// 					}
// 					else
// 						tmp.push_back(split_msg[i][j]);
// 				}
// 				if (tmp[0] == ':')
// 					tmp.erase(0, 1);
// 				split_msg_tmp.push_back(tmp);
// 				command->execute(split_msg_tmp, getUserByFd(cli_fd), NULL, this);
// 				break;
// 			}
// 		}
// 	}
// }

ACommand* Server::getCommand( std::string const & name ) const {
	
	std::cout << "cmd name : " << name << std::endl;
	if (_command.find(name) != _command.end())
		return (_command.find(name)->second);
	std::cout << "NULL" << std::endl;
	return (NULL);
}

int Server::isCommand( std::string const & name ) const  {

	if (_command.find(name) != _command.end())
		return (1);
	return (0);
}

void Server::addCommand(ACommand* command ) {

	_command[command->getName()] = command;
}

void Server::run()
{
		
	addCommand(new Pass());
	addCommand(new Nick());
	addCommand(new UserName());
	addCommand(new Join());
	addCommand(new Topic());
	addCommand(new Message());
	addCommand(new Mode());
	addCommand(new Invite());
	addCommand(new Kick());

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
				recvMessage();
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

User* Server::getUserByNickname( std::string const & nickname ) const {

	for ( size_t i = 0 ; i < this->_users.size() ; i++ )
	{
		if ( this->_users[i]->getNickname() == nickname )
			return this->_users[i];
	}
	return NULL;
}

User* Server::getUserByFd( int fd ) const {

	for ( size_t i = 0 ; i < this->_users.size() ; i++ )
	{
		if ( this->_users[i]->getFd() == fd )
		{
			User* userName = this->_users[i];
			return userName;
		}
	}
	return NULL;
}

Channel* Server::getChannelByName( std::string const & channel ) const {

	if (this->_channels.find(channel) != this->_channels.end())
		return this->_channels.find(channel)->second;
	return NULL;
}

std::string const & Server::getPassword() const {

	return this->_password;
}

void Server::deleteUser(User* user) {

	for (size_t i = 0; i < this->_users.size(); i++)
	{
		if (this->_users[i] == user)
		{
			this->_users.erase(this->_users.begin() + i);
			break;
		}
	}
}

void Server::deleteUser(int cli_fd) {

	delete getUserByFd(cli_fd);
	//le supprimer de tous les channels
	close(cli_fd);
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		if (this->_all_connections[i] == cli_fd)
		{
			this->_all_connections[i] = -1;
			this->_nb_connections--;
			break;
		}
	}
}

std::vector<User*> Server::getUserList() const {

	return this->_users;
}

void Server::exit()
{
    // TODO: Clean _users, _channels, _command
    std::cout << "Good Bye" << std::endl;
}
