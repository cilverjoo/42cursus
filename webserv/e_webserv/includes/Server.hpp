#ifndef Server_HPP
# define Server_HPP

#define PORT 9000

#include <queue>
#include <string>
#include <map>

#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/errno.h>

class Server
{
	friend class Config;
	typedef std::map<std::string, std::string> 	elmt;
	typedef std::map<std::string, elmt>			config;

	private:
		int						_fd;
		int						_maxFd;
		int						_port;
		struct sockaddr_in		_s_addr;
		fd_set					*_readSet;
		fd_set					*_writeSet;
		fd_set					*_rSet;
		fd_set					*_wSet;
		// Handler					_handler;
		std::vector<config>		_conf;

	public:
		Server();
		~Server();
		// Server(const Server& ref);
		// Server& operator=(const Server&ref);
		void init();
		void initialize_fdset();
		void connect();
		void refuseConnection();
		void acceptConnection();

	class		ServerException: public std::exception
	{
		private:
			std::string function;
			std::string error;

		public:
			ServerException(void);
			ServerException(std::string function, std::string error);
			virtual	~ServerException(void) throw();	
			virtual const char *what(void) const throw();
	};
};

#endif