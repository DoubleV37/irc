/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:41 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/02 13:57:42 by gazzopar         ###   ########.fr       */
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
        std::map<std::string, Channel*> _channels;
//        bool    _usingHexChat;
        int _fd;

    public:
        User();
        User( int fd );
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
        int getFd() const;
        void send( std::string const & message );

        bool    passIsSet;
             
};