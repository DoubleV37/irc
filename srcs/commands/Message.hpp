/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:59:15 by ltuffery          #+#    #+#             */
/*   Updated: 2023/11/07 14:01:12 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Channel.hpp"
#include "../Server.hpp"
#include "../User.hpp"
#include "../ACommand.hpp"

class Message : public ACommand
{

	public:
		Message();
		~Message();
    	bool	execute( std::vector<std::string> args, User* user, Server* server );
		void	sendBroadcastMessage(Server *server, Channel *channel, std::string message, User *origin_user);

};
