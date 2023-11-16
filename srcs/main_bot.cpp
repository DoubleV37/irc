#include "Bot.hpp"
#include <cstdlib>
#include <iostream>
#include <csignal>

static Bot bot;

static void	listen(int sig, siginfo_t *info, void *unused)
{
    (void)sig;
    (void)info;
    (void)unused;
    bot.close();
}

static void init_ctrl_c()
{
    struct sigaction sig;

    sig.sa_sigaction = listen;
	sig.sa_flags = SA_SIGINFO;
    sigemptyset(&sig.sa_mask);
    sigaction(SIGINT, &sig, NULL);
}

int	main(int ac, char **av)
{
	std::string name = "";
	if (ac < 3)
	{
		std::cout << "USAGE : ./bot <port> <password> [name]" << std::endl;
		exit(1);
	}
	init_ctrl_c();

	if (ac == 4)
	{
		name = av[3];
	}
	bot = Bot(atoi(av[1]), av[2], name);
	bot.run();
}
