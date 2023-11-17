/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:41 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/17 10:52:24 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <vector>

class Channel;

class User {

    private:
        std::string _userName;
        std::string _nickName;
		bool _todisconnect;
        std::map<std::string, Channel*> _channels;
		std::string _bufferMsg;
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
		void setToDisconnect();
		bool getToDisconnect();
        void addChannel( Channel* channel );
        void removeChannel( std::string const & name );
        std::map<std::string, Channel*> getChannels();
		std::string &getBufferMsg();
		void appendBufferMsg(std::string const &msg);
        int getFd() const;
        void send( std::string const & message );
        bool isLog();

        bool    passIsSet;

};
