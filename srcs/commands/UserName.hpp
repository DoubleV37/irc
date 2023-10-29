/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic copy.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:22 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/29 16:43:38 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../User.hpp"
#include "../ACommand.hpp"

class UserName : public ACommand {
    
	public:
		UserName();
		~UserName();
		bool execute( std::vector<std::string> args, User* user, Channel* channel, Server* server );
    
};
