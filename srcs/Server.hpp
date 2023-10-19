/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:37 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 16:26:38 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include "User.hpp"
#include "Channel.hpp"
#include "ACommand.hpp"

class ACommand;

class Server {
    
    private:
        int _port;
        std::string _password;
        std::vector<User*> _users;
        std::vector<Channel*> _channels;
        std::map<std::string, ACommand*> _command;

    public:
        Server();
        Server( std::string ServerName );
        // Ajouter constructeur paramètres
        Server( const Server& obj );
        Server& operator=( const Server& obj );
        ~Server(); 
        
        void addUser( User* user );
        void addChannel( Channel* channel );
        std::vector<User*> getUsers();
        std::vector<Channel*> getChannels();
        User* getUserByUsername( std::string const & userName ) const;
        Channel* getChannelByName( std::string const & channel ) const;
        void deleteUser(User*);
        ACommand* getCommand( std::string const & command ) const;      

};