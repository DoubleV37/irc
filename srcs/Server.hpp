/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:37 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/20 13:35:23 by gazzopar         ###   ########.fr       */
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
        std::map<std::string, Channel*> _channels;
        std::map<std::string, ACommand*> _command;
        
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

    public:
        Server();
        Server( std::string ServerName );
        // Ajouter constructeur paramètres
        Server( const Server& obj );
        Server& operator=( const Server& obj );
        ~Server(); 

        User* getUserByUsername( std::string const & userName ) const;
        Channel* getChannelByName( std::string const & channel ) const;    
        void addChannel( Channel* channel );

};