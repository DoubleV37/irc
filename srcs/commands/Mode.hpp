/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:18 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/17 13:12:16 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../User.hpp"
#include "../ACommand.hpp"

class Mode : public ACommand {
    
	public:
		Mode();
		~Mode();
		bool execute( std::vector<std::string> args, User* user, Server* server );
		bool channelOp(std::vector<std::string> &args, User* user, Server* server, Channel *channelTarget, size_t &ac);
		bool channelPassword(std::vector<std::string> &args, User* user, Server* server, Channel *channelTarget, size_t &ac);
		void topicLimit(std::vector<std::string> &args, User* user, Server* server, Channel *channelTarget);
		bool joinLimit(std::vector<std::string> &args, User* user, Server* server, Channel *channelTarget, size_t &ac);
		void inviteOnly(std::vector<std::string> &args, User* user, Server* server, Channel *channelTarget);

};
