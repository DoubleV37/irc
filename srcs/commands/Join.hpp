/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:22 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/17 15:52:40 by ltuffery         ###   ########.fr       */
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

	private:
		void	sendJoinMessage( User* user, Channel* channel, Server* server );
		bool	isValidChannelName(std::string channel_name, Server* server, User* user);
		void	channelCreate(std::string channel_name, Server* server, User* user, std::vector<std::string> &channels_password);

	public:
		Join();
		~Join();
		bool	execute( std::vector<std::string> args, User* user, Server* server );

};
