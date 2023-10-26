/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/26 13:19:56 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "ACommand.hpp"

#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		// vérifiert le port
		std::cerr << "./ircserv [port] [password]" << std::endl;
		return (1);
	}
	if (argc == 2)
	{
		Server serv(atoi(argv[1]), "");
		serv.run();
	}
	else
	{
		Server serv(atoi(argv[1]), argv[2]);
		serv.run();
	}
	return (0);
}
