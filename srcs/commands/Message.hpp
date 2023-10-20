/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:59:15 by ltuffery          #+#    #+#             */
/*   Updated: 2023/10/20 11:00:43 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../ACommand.hpp"

class Message : public ACommand
{

	public:
		Message();
		~Message();
    	bool execute( std::vector<std::string> args, User* user, Channel* channel, Server* server );

};
