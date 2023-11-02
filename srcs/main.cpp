/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:39 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/31 18:40:24 by gazzopar         ###   ########.fr       */
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
		// vérifiert le port
		std::cerr << "./ircserv [port] [password]" << std::endl;
		return (1);
	}
    init_ctrl_c();
    serv = Server(atoi(argv[1]), argv[2]);
	serv.run();
	return (0);
}
