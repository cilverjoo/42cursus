#include "./includes/Server.hpp"
#include "./includes/Config.hpp"
#include <iostream>

std::vector<Server>		g_servers;

int main(int argc, char** argv)
{
	Server server;
	Config config;
	fd_set readSet;
	fd_set writeSet;
	fd_set rSet;
	fd_set wSet;

	if (argc != 2)
		return (0);

	try 
	{
		signal(SIGINT, exit);
		config.parse(argv[1], g_servers);
		for (std::vector<Server>::iterator it(g_servers.begin()); it != g_servers.end(); ++it)
		{
			it->initialize_fdset();
			it->init();
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return (0);
}