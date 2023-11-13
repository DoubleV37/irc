#include "Bot.hpp"
#include <cstdlib>
#include <iostream>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "USAGE : ./bot [port]" << std::endl;
		exit(1);
	}
	Bot bot(atoi(av[1]));
	bot.run();
}
