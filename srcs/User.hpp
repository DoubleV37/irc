/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:41 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 14:46:15 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

class Channel;

class User {
    
    private:
        std::string _userName;
        std::string _nickName;
        std::vector<Channel*> _channels;

    public:
        User();
        User( std::string const & userName );
        // Ajouter constructeur paramètres
        User( const User& obj );
        User& operator=( const User& obj );
        ~User();

        std::string const & getUsername() const;
        std::string const & getNickname() const;
        void setNickName( std::string const & nickName );
        void addChannel( Channel* channel );
        void removeChannel( Channel* channel );
        std::vector<Channel*> getChannels();
             
};