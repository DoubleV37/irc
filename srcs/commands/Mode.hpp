/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:18 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 16:30:58 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../User.hpp"
#include "../ACommand.hpp"

class Mode : public ACommand {
    
    Mode( std::string const & name, std::string const & usage );
    ~Mode();
    bool execute( std::vector<std::string> args, User* user, Channel* channel, Server* server );

};