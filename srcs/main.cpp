/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviovi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/11/07 14:39:30 by vviovi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "ACommand.hpp"

#include <stdlib.h>
#include <csignal>
#include <bits/types/siginfo_t.h>

static Server serv;
User test;

static void	listen(int sig, siginfo_t *info, void *unused)
{
    (void)sig;
    (void)info;
    (void)unused;
    serv.exit();
    exit(0);
}

static void init_ctrl_c()
{
    struct sigaction sig;

    sig.sa_sigaction = listen;
	sig.sa_flags = SA_SIGINFO;
    sigemptyset(&sig.sa_mask);
    sigaction(SIGINT, &sig, NULL);
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr << "./ircserv [port] [password]" << std::endl;
		return (1);
	}
	int port = atoi(argv[1]);
	if (port < 1024 || port > 65535)
	{
		std::cerr << "Port must be between 1024 and 65535" << std::endl;
		return (1);
	}
    init_ctrl_c();
	try
	{
		serv = Server(port, argv[2]);
		serv.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
