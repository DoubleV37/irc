/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:32 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/20 13:41:06 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>

class User;

class Channel {
    
    private:
        std::string _name;
        std::map<User*, int> _users;
        std::string _password;
        bool _isPrivate;
        bool _hasLimit;
        int  _limit;
        

    public:
        Channel();
        // Ajouter constructeur paramètres
        Channel( const Channel& obj );
        Channel& operator=( const Channel& obj );
        ~Channel();

        std::string const & getName();
        void addUser( User* user, int isAdmin );
        void removeUser( User* user );
        std::map<User*, int> getUsers();
        void setTopic( std::string topic );
        void setOp( User* user );
        void deOp( User* user );
        bool isOp( User* user );
        std::string getPassword();
        bool isPrivate();
        bool hasLimit();
        size_t getLimit();
        void setLimit( int limit );
        bool sendInvite( std::string user );
        void broadcast( std::string message );
        bool containsUser( User* user );

};