#include "Server.hpp"
#include "Config.hpp"
#include "Logger.hpp"

std::vector<Server>		g_servers;
Logger					g_logger(1, "console", LOW);
bool					g_state = true;

/*!
 * @author jinbkim
 * @param error 출력할 에러메시지
 * @return 1을 반환함으로써 메인문도 1을 반환하며 프로그램 종료
 * @see main.cpp
 * @brief 인자로 받은 에러메시지를 stderr에 출력
 */
int		ret_error(std::string error)
{
	std::cerr << error << std::endl;
	return (1);
}


int 	main(int ac, char **av)
{
	Config					config;
	Client					*client;

	fd_set					readSet;
	fd_set					writeSet;
	fd_set					rSet;
	fd_set					wSet;
	struct timeval			timeout;

	if (ac != 2)  // 인자가 한개가 아니면 에러처리
		return (ret_error("Usage: ./webserv config-file"));
	try
	{
		config.parse(av[1], g_servers);  // .conf 파일(av[1])을 파싱하여 g_servers에 저장
		config.init(&rSet, &wSet, &readSet, &writeSet, &timeout);  // 시그널 함수 등록, 서버들 초기값 설정
		// rSet : 서버가 읽을 파일 디스크립터가 set이 된 fd_set
		// wSet, readSet, writeSet : 0으로 초기화된 fd_set
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}

	while (g_state)
	{
		// readSet, writeSet은 select 함수 호출이후 변하기 때문에 계속 rSet과 wSet으로 초기화를 해주어야 함
		readSet = rSet;
		writeSet = wSet;

		// selct의 검사 대상이되는 파일 디스크립터 수 : config.getMaxFd(g_servers)+1 (0번~g_servers의 파일 디스크립터의 최대값)
		// readSet : 읽을 데이터가 있는지 검사하기 위한 fd_set
		// writeSet : 쓸 데이터가 있는지 검사하기 위한 fd_set
		// timeout : select 함수는 fd_set에 등록된 파일들에 데이터 변경이 있는지를 timeout시간 동안 기다림
		select(config.getMaxFd(g_servers) + 1, &readSet, &writeSet, NULL, &timeout);
		// select 호출 이후 : readSet 또는 writeSet에서 변화가 있는 fd만 set이 되있음

		for (std::vector<Server>::iterator s(g_servers.begin()); s != g_servers.end(); ++s)
		{
			if (FD_ISSET(s->getFd(), &readSet))  // 해당 서버의 서버 소켓이 데이터를 읽었다면
			{
				try
				{
					if (!g_state)
						break ;
					if (config.getOpenFd(g_servers) > MAX_FD)  // 모든 서버에 열려있는 fd 수가 MAX_FD 보다 크면
						s->refuseConnection();  // 클라이언트의 연결 요청을 대기하거나 거부
					else
						s->acceptConnection();  // 클라이언트의 연결 요청을 수락
				}
				catch (std::exception &e)
				{
					std::cerr << "Error: " << e.what() << std::endl;
				}
			}
			if (!s->_tmp_clients.empty())  // 대기중인 클라이언트가 있으면
			{
				// Server::refuseConnection()에서 FD_SET(fd, _wSet)으로 해줄 경우
				// while문을 돌고돌다보면 select 함수 호출이후 변한 writeSet에서 s->_tmp_clients.front()가 set이 당연히 되있음
				if (FD_ISSET(s->_tmp_clients.front(), &writeSet))  // 필요없는 조건문 인거 같아서 나중에 주석처리 예정
					s->send503(s->_tmp_clients.front());  // 접속 대기중인 클라이언트에 503 에러 출력
			}
			for (std::vector<Client*>::iterator c(s->_clients.begin()); c != s->_clients.end(); ++c)
			{
				client = *c;  // 해당 서버의 하나의 클라이언트
				if (FD_ISSET(client->fd, &readSet))  // 클라이언트가 서버로 데이터를 전달할 때
					if (!s->readRequest(c))  // 클라이언트가 보낸 request 메시지를 읽고 파싱. 다읽었다면 0을 반환하여 반복문 탈출.
						break ;
				if (FD_ISSET(client->fd, &writeSet))
					if (!s->writeResponse(c))
						break ;
				if (client->write_fd != -1)
					if (FD_ISSET(client->write_fd, &writeSet))
						client->writeFile();
				if (client->read_fd != -1)
					if (FD_ISSET(client->read_fd, &readSet))
						client->readFile(); // 에러메세지도 들어옴 getErrorPage()
			}
		}
	}
	g_servers.clear();
	return(0);
}