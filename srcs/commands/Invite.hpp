/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:05 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 16:37:43 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../User.hpp"
#include "../ACommand.hpp"

class Invite : public ACommand {
    
    Invite( std::string const & name, std::string const & usage );
    ~Invite();
    bool execute( std::vector<std::string> args, User* user, Channel* channel, Server* server );

};
