/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:22 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/02 11:15:24 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../User.hpp"
#include "../ACommand.hpp"

class Server;

class Join : public ACommand {

	public:
		Join();
		~Join();
		void sendJoinMessage( User* user, Channel* channel, Server* server );
		bool execute( std::vector<std::string> args, User* user, Channel* channel, Server* server );

};
