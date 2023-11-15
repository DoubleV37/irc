/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuffery <ltuffery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:05:00 by ltuffery          #+#    #+#             */
/*   Updated: 2023/11/15 15:06:38 by ltuffery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../ACommand.hpp"

class Quit : public ACommand {

	public:
		Quit();
		~Quit();
    	bool	execute( std::vector<std::string> args, User* user, Server* server );

};
