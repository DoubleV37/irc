/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:13 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/20 11:02:18 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../User.hpp"
#include "../ACommand.hpp"

class Kick : public ACommand {

	public:
		Kick( std::string const & name, std::string const & usage );
		~Kick();
		bool execute( std::vector<std::string> args, User* user, Channel* channel, Server* server );

};
