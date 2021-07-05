#include "utils.h"
#include "Server.hpp"

extern bool					g_state;

Server::Server() : _fd(-1), _maxFd(-1), _port(-1)
{
	memset(&_info, 0, sizeof(_info));
}

Server::~Server()
{
	Client		*client = NULL;

	if (_fd != -1)
	{
		for (std::vector<Client*>::iterator it(_clients.begin()); it != _clients.end(); ++it)
		{
			client = *it;
			*it = NULL;
			if (client)
				delete client;
		}
		while (!_tmp_clients.empty())
		{
			close(_tmp_clients.front());
			_tmp_clients.pop();
		}
		_clients.clear();
		close(_fd);
		FD_CLR(_fd, _rSet);
		g_logger.log("[" + std::to_string(_port) + "] " + "closed", LOW);
	}
}

/*!
 * @author	jinbkim
 * @return	한개서버의 파일 디스크립터의 최대값
 * @see		Config::getMaxFd()
 * @brief	한개서버의 파일 디스크립터의 최대값 구하기
 */
int		Server::getMaxFd()
{
	Client	*client;
	for (std::vector<Client*>::iterator it(_clients.begin()); it != _clients.end(); ++it)
	{
		client = *it;
		if (client->read_fd > _maxFd)
			_maxFd = client->read_fd;
		if (client->write_fd > _maxFd)
			_maxFd = client->write_fd;
	}
	return (_maxFd);
}

/*!
 * @author	jinbkim
 * @return	해당 서버의 서버 소켓
 * @see		main.cpp
 * @brief	해당 서버의 서버 소켓 구하기
 */
int		Server::getFd() const
{
	return (_fd);
}

/*!
 * @author	jinbkim
 * @return	해당서버에 연결된 클라이언트의 fd 수
 * @see		Config::getOpenFd()
 * @brief	해당서버에 연결된 클라이언트의 fd 수 구하기
 */
int		Server::getOpenFd()
{
	int 	nb = 0;
	Client	*client;

	//  client->read_fd, client->write_fd는 언제 어떻게 사용되는지 코드를 더 읽어봐야 알듯함
	for (std::vector<Client*>::iterator it(_clients.begin()); it != _clients.end(); ++it)
	{
		client = *it;
		nb += 1;  // socket 함수로 클라이언트를 생성할때 생기는 fd(+1)
		if (client->read_fd != -1)  // 클라이언트의 read_fd set 이면
			nb += 1;
		if (client->write_fd != -1) // 클라이언트의 write_fd set 이면
			nb += 1;
	}
	nb += _tmp_clients.size();  // 대기중인 클라이언트 수만큼 증가
	return (nb);
}

/*!
 * @author	jinbkim, juhlee, sujlee
 * @param 	readSet Server의 _readSet 속성에 할당될 fd_set 구조체
 * @param 	writeSet Server의 _writeSet 속성에 할당될 fd_set 구조체
 * @param	rSet Server의 _rSet 속성에 할당될 fd_set 구조체. 소켓 생성 이후, 해당 소켓은 rSet에 세팅됨.
 * @param 	wSet Server의 _wSet 속성에 할당될 fd_set 구조체
 * @see 	Config::init
 * @brief	해당 서버의 fd_set 구조체들 초기화
 * 			클라이언트에서 오는 연결요청을 받을 소켓을 생성, 주소할당, 연결요청가능 상태로 만듬
 * 			서버 소켓 : SO_REUSEADDR 옵션을 1로 설정, non-blocking 모드
 * 			log 정보를 stdout에 출력
 */
void	Server::init(fd_set *readSet, fd_set *writeSet, fd_set *rSet, fd_set *wSet)
{
	int				yes = 1;
	std::string		to_parse;  // 연결 요청이 가능한 포트번호
	std::string		host;  // client IP

	// Server의 fd_set 구조체들을 0으로 초기화된 fd_set 구조체로 초기화
	_readSet = readSet;
	_writeSet = writeSet;
	_wSet = wSet;
	_rSet = rSet;

	// config 벡터인 _conf은 이미 listen하는 포트번호로 나뉘었기 때문에 한 서버의 _conf의 ["server|"]["listen"]값은 모두 동일
	to_parse = _conf[0]["server|"]["listen"];  // 연결 요청이 가능한 포트번호
	errno = 0;	//errno 0은 정해진 에러 메시지가 없음
	// PF_INET : IPv4 인터넷 프로토콜 체계
	// SOCK_STREAM : TCP 전송방식
	if ((_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		throw(ServerException("socket()", std::string(strerror(errno))));
	// time wait상태에서도 포트번호를 할당할수 있도록 SO_REUSEADDR 옵션을 1로 설정
	// Q. 근데 이거 안하면 무슨 문제가 생기는지는 정확하게는 잘 모르겠음
	/* A.
    ** server가 먼저 close()할 경우 해당 소켓을 커널에서 놓아주지 않기 때문에
    ** time wait 상태에서도 포트 번호를 재사용(할당)할 수 있도록 SO_REUSEADDR을 설정해주는 것(강의 #12)
    ** ref. https://m.blog.naver.com/PostView.nhn?blogId=cache798&logNo=130080237440&proxyReferer=https:%2F%2Fwww.google.com%2F
    */
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		throw(ServerException("setsockopt()", std::string(strerror(errno))));
    if (to_parse.find(":") != std::string::npos)  // ex) listen 127.0.0.1:8080;
    {
    	host = to_parse.substr(0, to_parse.find(":"));  // client IP
    	if ((_port = atoi(to_parse.substr(to_parse.find(":") + 1).c_str())) < 0)  // client port
			throw(ServerException("Wrong port", std::to_string(_port)));
		_info.sin_addr.s_addr = inet_addr(host.c_str());  // inet_addr : 문자열 주소를 32비트 정수로 변환
		_info.sin_port = htons(_port);  // htons : short형 호스트 바이트 순서를 네트워크 바이트 순서로 변환
    }
    else  // ex) listen 8080;
    {
		_info.sin_addr.s_addr = INADDR_ANY;  // INADDR_ANY : 0으로 define된 값으로, 사용가능한 LAN 카드의 IP주소를 사용하라는 의미
		if ((_port = atoi(to_parse.c_str())) < 0)  // client port
			throw(ServerException("Wrong port", std::to_string(_port)));
		_info.sin_port = htons(_port);  // htonl : long형 호스트 바이트 순서를 네트워크 바이트 순서로 변환
    }
	_info.sin_family = AF_INET;  // IPv4 인터넷 프로토콜에 적용하는 주소체계
	if (bind(_fd, (struct sockaddr *)&_info, sizeof(_info)) == -1) // bind 함수호출로 _fd에 IP 주소, 포트를 할당
		throw(ServerException("bind()", std::string(strerror(errno))));
    if (listen(_fd, 256) == -1)  // listen 함수호출로 클라이언트 접속 요청을 기다림
		throw(ServerException("listen()", std::string(strerror(errno))));
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)  // _fd를 non-blocking 모드로 바꿈
		throw(ServerException("fcntl()", std::string(strerror(errno))));
	FD_SET(_fd, _rSet);  // 서버 소켓 _fd를 fd_set 구조체 _rSet에 추가
    _maxFd = _fd; // fd의 가장 큰값 갱신
    g_logger.log("[" + std::to_string(_port) + "] " + "listening...", LOW);  // log 정보를 stdout에 출력
}

/*!
 * @author	jinbkim
 * @see		main.cpp
 * @brief	클라이언트의 연결요청을 대기하거나 거부
 * 			거부 : accept 하자마자 close
 * 			대기 : 클라이언트 fd를 _tmp_clients 대기열에 추가 -> 나중에 503 에러처리
 */
void	Server::refuseConnection()
{
	int 				fd = -1;
	struct sockaddr_in	info;
	socklen_t			len;

	errno = 0;
	len = sizeof(struct sockaddr);
	if ((fd = accept(_fd, (struct sockaddr *)&info, &len)) == -1)  // accept 함수호출로 클라이언트의 연결요청을 수락
		throw(ServerException("accept()", std::string(strerror(errno))));
	if (_tmp_clients.size() < 10)  // 대기중인 클라이언트가 10개 미만면
	{
		_tmp_clients.push(fd);  // 해당 클라이언트를 서버의 대기열(큐)에 넣기
		FD_SET(fd, _wSet);  // fd_set 구조체 _wSet에 해당 클라이언트 추가 => 클라이언트에 503 에러를 출력하기 위해
	}
	else
		close(fd);
}

/*!
 * @author	jinbkim
 * @see		main.cpp
 * @brief	클라이언트의 연결요청을 수락
 */
void	Server::acceptConnection()
{
	int 				fd = -1;
	struct sockaddr_in	info;
	socklen_t			len;
	Client				*newOne = NULL;

	memset(&info, 0, sizeof(struct sockaddr));
	errno = 0;
	len = sizeof(struct sockaddr);
	if ((fd = accept(_fd, (struct sockaddr *)&info, &len)) == -1)  // accept 함수호출로 클라이언트의 연결요청을 수락
		throw(ServerException("accept()", std::string(strerror(errno))));
	if (fd > _maxFd)
		_maxFd = fd;  // 파일 디스크립터의 최대값 갱신
	newOne = new Client(fd, _rSet, _wSet, info);  // 새로운 클라이언트 생성 및 초기화, rSet, _wSet에 클라이언트 소켓의 fd 추가
	_clients.push_back(newOne);  // 서버의 클라이언트 벡터에 새로운 클라이언트 추가
	g_logger.log("[" + std::to_string(_port) + "] " + "connected clients: " + std::to_string(_clients.size()), LOW); // 연결 요청한 클라이언트 log 정보를 stdout에 출력
}

/*!
 * @author	jinbkim
 * @see		main.cpp
 * @return	클라이언트가 보낸 request 메시지를 다 읽었으면 0, 아니면 1 반환
 * @brief	클라이언트가 보낸 request 메시지를 읽고 파싱
 */
int		Server::readRequest(std::vector<Client*>::iterator it)
{
	int 		bytes;
	int			ret;
	Client		*client = NULL;
	std::string	log;

	client = *it;
	bytes = strlen(client->rBuf);  // rBuf에 대해 잘 모르겠지만, 아마도 read한후 출력하지 못한 것들이 저장된 버퍼 겠지? (jinbkim). rBuf는 클라이언트가 서버에게 요청하는 요청메시지의 내용에 해당됨.(sebaek)
	// rBuf 에 들어갈 클라이언트의 요청 메시지 예시
	/*
	GET /members/100 HTTP/1.1
	Host: localhost:8080
	*/
	/*
	POST /members HTTP/1.1
	Content-Type: application/json

	{
		"username": "sebaek",
		"age": 26
	}
	*/
	ret = read(client->fd, client->rBuf + bytes, BUFFER_SIZE - bytes);  // 클라이언트가 보낸 request 메시지 읽기
	bytes += ret;
	if (ret > 0)
	{
		client->rBuf[bytes] = '\0';
		if (strstr(client->rBuf, "\r\n\r\n") != NULL  // 헤더의 끝은 항상 "\r\n\r\n"로 끝나는건 알겠으나 이게 왜 필요한지는 모르겠음 (jinbkim)
			&& client->status != Client::BODYPARSING)  // 메서드가 PUT 또는 POST가 아닐때
		{
			log = "REQUEST:\n";
			log += client->rBuf;
			g_logger.log(log, HIGH);  // HIGH 가 무슨의미? (jinbkim)
			client->last_date = ft::getDate();  // 몇요일/몇일/몇월(영어)/몇년도 몇시:몇분:몇초 timezone
			_handler.parseRequest(*client, _conf);  // request한 client 데이터들을 파싱하여 config벡터 _conf에 저장함
			client->setWriteState(true);  // 클라이언트가 데이터를 보낼 준비가 됨
		}
		if (client->status == Client::BODYPARSING) // client.req.method 가 PUT 이나 POST인 경우 요청 메시지에 body부분이 들어가게됨
			_handler.parseBody(*client); // client.req.body에 내용 저장
		return (1);
	}
	else // 다 읽은 경우
	{
		*it = NULL;
		_clients.erase(it);
		if (client)
			delete client;
		g_logger.log("[" + std::to_string(_port) + "] " + "connected clients: " + std::to_string(_clients.size()), LOW);
		return (0);
	}
}

int		Server::writeResponse(std::vector<Client*>::iterator it)
{
	unsigned long	bytes;
	std::string		tmp;
	std::string		log;
	Client			*client = NULL;

	client = *it;
	switch (client->status)
	{
		case Client::RESPONSE:
			log = "RESPONSE:\n";
			log += client->response.substr(0, 128);
			g_logger.log(log, HIGH);
			bytes = write(client->fd, client->response.c_str(), client->response.size());
			if (bytes < client->response.size())
				client->response = client->response.substr(bytes);
			else
			{
				client->response.clear();
				client->setToStandBy();
			}
			client->last_date = ft::getDate();
			break ;
		case Client::STANDBY:
			if (getTimeDiff(client->last_date) >= TIMEOUT)
				client->status = Client::DONE;
			break ;
		case Client::DONE:
			delete client;
			_clients.erase(it);
			g_logger.log("[" + std::to_string(_port) + "] " + "connected clients: " + std::to_string(_clients.size()), LOW);
			return (0);
		default:
			_handler.dispatcher(*client);
	}
	return (1);
}

/*!
 * @author	jinbkim
 * @param	fd 접속 대기중인 클라이언트 파일 디스크립터
 * @see		main.cpp
 * @brief	접속 대기중인 클라이언트에 503 에러 출력
 */
void	Server::send503(int fd)
{
	Response		response;
	std::string		str;
	int				ret = 0;

	// 503 Service Unavailable : 서버쪽 문제로 인하여 서비스가 현재 불가능한 상태를 의미
	// reponse 객체에 대해 전반적으로 잘모르겠음
	response.version = "HTTP/1.1";
	response.status_code = UNAVAILABLE;
	response.headers["Retry-After"] = RETRY;
	response.headers["Date"] = ft::getDate();
	response.headers["Server"] = "webserv";
	response.body = UNAVAILABLE;
	response.headers["Content-Length"] = std::to_string(response.body.size());
	std::map<std::string, std::string>::const_iterator b = response.headers.begin();
	str = response.version + " " + response.status_code + "\r\n";
	// str에 response.headers 정보들을 추가
	while (b != response.headers.end())
	{
		if (b->second != "")
			str += b->first + ": " + b->second + "\r\n";
		++b;
	}
	str += "\r\n";
	str += response.body;
	ret = write(fd, str.c_str(), str.size());  // 접속하려는 클라이언트에 503 에러 출력
	if (ret >= -1)  // write의 반환값은 항상 -1 이상인데 이걸 왜해놓은걸까? (jinbkim)
	{
		close(fd);
		FD_CLR(fd, _wSet);
		_tmp_clients.pop();  // 대기중인 맨앞 클라이언트 제거
	}
	g_logger.log("[" + std::to_string(_port) + "] " + "connection refused, sent 503", LOW);  // stdout에 503에러 log 전달
}


int		Server::getTimeDiff(std::string start)
{
	struct tm		start_tm;
	struct tm		*now_tm;
	struct timeval	time;
	int				result;

	strptime(start.c_str(), "%a, %d %b %Y %T", &start_tm);
	gettimeofday(&time, NULL);
	now_tm = localtime(&time.tv_sec);
	result = (now_tm->tm_hour - start_tm.tm_hour) * 3600;
	result += (now_tm->tm_min - start_tm.tm_min) * 60;
	result += (now_tm->tm_sec - start_tm.tm_sec);
	return (result);
}
