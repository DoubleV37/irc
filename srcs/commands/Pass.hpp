/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:53:22 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/21 17:46:03 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../User.hpp"
#include "../ACommand.hpp"

class Pass : public ACommand {
    
	public:
		Pass();
		~Pass();
		bool execute( std::vector<std::string> args, User* user, Channel* channel, Server* server );
    
};
