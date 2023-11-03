/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doublev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:32 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/03 17:35:51 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "User.hpp"

class User;

class Channel {

    private:
        std::string _name;
        std::map<User*, int> _users;
        std::string _password;
		std::string _topic;
        bool _isPrivate;
        bool _hasLimit;
        bool _hasTopicProtection;
        int  _limit;


    public:
        Channel(std::string name);
		Channel(std::string name, std::string password);
        // Ajouter constructeur paramètres
        Channel( const Channel& obj );
        Channel& operator=( const Channel& obj );
        ~Channel();

        std::string const & getName();
        void addUser( User* user, int isAdmin );
        void removeUser( User* user );
        std::map<User*, int> getUsers();
        void setTopic( std::string topic );
		std::string getTopic();
        void setOp( User* user );
        void deOp( User* user );
        bool isOp( User* user );
        std::string getPassword();
        void setPassword(const std::string& password);
        bool isPrivate();
        void setPrivate(bool isPrivate);
        bool hasLimit();
        size_t getLimit();
        bool hasTopicProtection() const;
        void setTopicProtection(bool protection);
        void setLimit( int limit );
        bool isFull();
        bool sendInvite( std::string user );
        void broadcast( std::string message );
        bool containsUser( User* user );
		std::string getModes() const;
		std::string getUsersList();

};
