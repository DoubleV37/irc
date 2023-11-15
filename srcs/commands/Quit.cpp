#include "Quit.hpp"
#include "../Server.hpp"

/**
 * NAME : QUIT
 * USAGE : /quit
 */
Quit::Quit() : ACommand( "QUIT", true )
{
}

Quit::~Quit()
{
}

bool Quit::execute(std::vector<std::string> args, User *user, Server *server)
{
	(void)args;
	server->deleteUser(user->getFd());
	return true;
}
