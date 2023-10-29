/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:41 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/26 15:35:31 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>

class Channel;

class User {
    
    private:
        std::string _userName;
        std::string _nickName;
        int _fd;
        std::map<std::string, Channel*> _channels;

    public:
        User();
        User( int fd );
        // Ajouter constructeur paramètres
        User( const User& obj );
        User& operator=( const User& obj );
        ~User();

        std::string const & getUsername() const;
        std::string const & getNickname() const;
        void setUserName( std::string const & userName );
        void setNickName( std::string const & nickName );
        void setPassToggle( bool status );
        void addChannel( Channel* channel );
        void removeChannel( std::string const & name );
        std::map<std::string, Channel*> getChannels();
        int getFd();
        void send( std::string const & message );

        bool    _passIsSet;
             
};