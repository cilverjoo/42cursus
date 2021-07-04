#include "utils.h"
#include "Config.hpp"

extern	std::vector<Server> g_servers;
extern	bool				g_state;

Config::Config()
{

}

Config::~Config()
{

}

/*!
 * @author	jinbkim
 * @param	sig 의미없음
 * @see		Config::init(), main.cpp
 * @brief	ctrl+c, 시그널 발생시 호출되는 함수
 */
void			Config::exit(int sig)
{
	(void)sig;

	std::cout << "\n" << "exiting...\n";
	g_state = false;  // 를 0으로 바꾸면 main문에서 계속 돌던 반복문을 벗어나 프로그램이 종료됨
}

/*!
 * @author	jinbkim sujlee
 * @param	rSet 서버가 읽을 파일 디스크립터는 set이되는 fd_set 구조체
 * 			만약 읽을 파일 디스크립터가 3, 4, 5, 6 4개면,
 * 			readSet.fds_bits[0] = 1111000(2) = 120
 * @param	wSet 0으로 초기화되는 fd_set 구조체
 * @param	readSet 0으로 초기화되는 fd_set 구조체
 * @param	writeSet 0으로 초기화되는 fd_set 구조체
 * @param	timeout 1초로 초기화되는 timeval 구조체(select 함수는 fd_set에 등록된 파일들에 데이터 변경이 있는지를 timeout시간 동안 기다림)
 * @see		main.cpp
 * @brief	시그널 함수 등록, 서버들 초기값 설정
 */
void			Config::init(fd_set *rSet, fd_set *wSet, fd_set *readSet, fd_set *writeSet, struct timeval *timeout)
{
	signal(SIGINT, exit);  // Config::exit() : ctrl+c 시그널 발생시 호출되는 함수
	// fd_set 구조체들 초기화
	FD_ZERO(rSet);
	FD_ZERO(wSet);
	FD_ZERO(readSet);
	FD_ZERO(writeSet);
	// timeout : 1초
	timeout->tv_sec = 1;
	timeout->tv_usec = 0;

	// 해당 서버의 fd_set 구조체들 초기화
	// 클라이언트에서 오는 연결요청을 받을 소켓을 생성, 주소할당, 연결요청가능 상태로 만듬
	// 서버 소켓 : SO_REUSEADDR 옵션을 1로 설정, non-blocking 모드
	// log 정보를 stdout에 출력
	for (std::vector<Server>::iterator it(g_servers.begin()); it != g_servers.end(); ++it)
		it->init(readSet, writeSet, rSet, wSet);
}

/*!
 * @author	jinbkim
 * @param	file 읽을 파일
 * @return	.conf 파일을 읽고 저장한 string 변수
 * @see		Config::parse()
 * @todo	4096을 매크로로 정의하면 좋을꺼 같음
 * @brief	.conf 파일을 읽고 string 변수에 저장
 */
std::string		Config::readFile(char *file)
{
	int 				fd;
	int					ret;
	char				buf[4096];
	std::string			parsed;

	fd = open(file, O_RDONLY);  // 읽기모드로 .conf 파일 읽기
	while ((ret = read(fd, buf, 4095)) > 0)  // 파일 전체 다읽기
	{
		buf[ret] = '\0';
		parsed += buf;  // 4095byte씩 끊어서 저장
	}
	close(fd);
	return (parsed);
}

/*!
 * @author	jinbkim, juhlee, sujlee
 * @param	file 파싱할 .conf 파일
 * @param	servers 파싱된 Server 객체가 저장된 Server 벡터
 * @see		main.cpp
 * @brief	.conf 파일을 파싱하여 servers에 저장
 */
void			Config::parse(char *file, std::vector<Server> &servers)
{
	size_t					d;
	size_t					nb_line;  // .conf 파일의 몇번째 줄인지 알려줌
	std::string				context;
	std::string				buffer;  // .conf 파일을 읽어 buffer에 저장
	std::string				line;  // .conf 파일 한 줄
	Server					server;
	config					tmp;  // getContent 호출 이후 파싱된 map<string, map<string, string>>형태의 변수

	buffer = readFile(file);  // .conf 파일을 읽어 buffer에 저장
	nb_line = 0;
	if (buffer.empty())  // 읽은 파일이 비어있으면 예외처리
		throw(Config::InvalidConfigFileException(nb_line));
	while (!buffer.empty())
	{
		// line : buffer의 처음부터 첫 개행까지 저장됨
		// buffer는 처음부터 첫 개행까지 잘림
		ft::getline(buffer, line);
		nb_line++;  // .conf 파일의 몇번째 줄인지 알려줌

		while (ft::isspace(line[0]))  // line 앞부분에 공백이 있으면 지움
			line.erase(line.begin());
		if (!line.compare(0, 6, "server"))  // line의 앞이 server로 시작하면
		{
			while (ft::isspace(line[6]))  // server(line[0]~line[5])이후 부터 공백들 지움
				line.erase(6, 1);
			if (line[6] != '{')  // line[0]~line[6]이 server{ 가아니면
				throw(Config::InvalidConfigFileException(nb_line));
			if (!line.compare(0, 7, "server{"))  // 이미 앞에서 line[0]~line[6]이 server{ 가아니면 예외처리를 해주었기 때문이 이 조건문이 불필요해 보임
			{
				d = 7;
				while (ft::isspace(line[d]))  // server{부터 공백이면 지움
					line.erase(7, 1);
				if (line[d])  // line이 server{가 아니면
					throw(Config::InvalidConfigFileException(nb_line));
				/* getContent에 들어가기 전 인자의 상태
					buffer : 앞으로 더 파싱을 해야할것들
					context : 비어있는 string
					line : server{
					nb_line : .conf 파일의 몇번째 줄인지
					temp : 비어있는 string
				*/
				getContent(buffer, context, line, nb_line, tmp); // .conf 파일에서 server{} 블록 1개를 파싱하여, config 타입 변수 tmp에 저장함
				std::vector<Server>::iterator it(servers.begin());

				while (it != servers.end())  // 서버 벡터를 처음부터 탐색
				{
					/* 너무 햇갈려서 .conf 파일 출력해봄
						std::cout<<"##############################\n";
						std::vector<config>::iterator	it1;
						std::map<std::string, elmt>::iterator	it2;
						std::map<std::string, std::string>::iterator	it3;
						for(it1=it->_conf.begin(); it1!=it->_conf.end(); it1++)
						{
							std::cout<<"@@@@@@@@@@ SERVER @@@@@@@@@@\n";
							for(it2=it1->begin(); it2!=it1->end(); it2++)
							{
								std::cout<<"["<<it2->first<<"]\n";
								for(it3=it2->second.begin(); it3!=it2->second.end(); it3++)
									std::cout<<"key : "<<it3->first<<", value : "<<it3->second<<'\n';
							}
						}
					*/
					/* webserv.conf
						servers.size() : 4 (8080, 443, 80, 8081)
						8080 server의 conf.size() : 1
						443 server의 conf.size() : 1
						80 server의 conf.size() : 2
						8081 server의 conf.size() : 1
					*/
					// tmp : getContent에서 방금 파싱한 map<string, map<string, string>> 형태의 config 변수
					// tmp["server|"]["listen"] : getContent에서 방금 파싱한 config 변수의 listen 중인 포트번호
					// it->_conf.back()["server|"]["listen"] : 하나의 서버의 listen 중인 포트번호

					// it->_conf.back() : _conf는 이미 listen 하는 포트 번호로 나뉘었기 때문에 같은 서버의 _conf의 ["server|"]["listen"] 값은 같음
					// 그래서 back()은 의미가 없음
					// if (tmp["server|"]["listen"] == it->_conf[0]["server|"]["listen"]) 으로 하는게 덜 헷갈릴듯
					if (tmp["server|"]["listen"] == it->_conf.back()["server|"]["listen"])  // 이미 listen 중인 포트번호 이면
					{	// !!아래 if문은 it가 가리키고 있는 서버의 모든 _conf를 검사하도록 수정할 것
						std::vector<config>::iterator it2(it->_conf.begin());
						while (it2 != it->_conf.end())
						{
							if (tmp["server|"]["server_name"] == (*it2)["server|"]["server_name"])  // server_name 까지 같으면
								throw(Config::InvalidConfigFileException(nb_line));
							it2++;
						}
						it->_conf.push_back(tmp);  // _conf에 tmp추가 : listen하는 포트가 같다는건 -> 같은 Server
						break ;
					}
					++it;
				}
				if (it == servers.end())  // 새로운 포트를 listen 하려 할때
				{
					server._conf.push_back(tmp);  // _conf에 tmp추가 
					servers.push_back(server);  // 새로운 포트를 listen -> Server 개수 증가
				}
				server._conf.clear();
				tmp.clear();
				context.clear();
			}
			else
				throw(Config::InvalidConfigFileException(nb_line));
		}
		else if (line[0])
			throw(Config::InvalidConfigFileException(nb_line));
	}
}

/*!
 * @author	jinbkim
 * @return	모든 서버의 파일 디스크립터의 최대값
 * @see		Config::getMaxFd()
 * @brief	모든 서버의 파일 디스크립터의 최대값 구하기
 */
int				Config::getMaxFd(std::vector<Server> &servers)
{
	int		max = 0;
	int		fd;

	for (std::vector<Server>::iterator it(servers.begin()); it != servers.end(); ++it)
	{
		fd = it->getMaxFd();  // 한개서버의 파일 디스크립터의 최대값
		if (fd > max)
			max = fd;
	}
	return (max);
}

/*!
 * @author	jinbkim
 * @param	servers 열려있는 fd수를 셀 서버 벡터
 * @return	모든서버에 열려있는 fd수
 * @see		main.cpp
 * @brief	모든서버에 열려있는 fd수 구하기
 */
int				Config::getOpenFd(std::vector<Server> &servers)
{
	int		nb = 0;

	for (std::vector<Server>::iterator it(servers.begin()); it != servers.end(); ++it)
	{
		nb += 1;  // socket 함수로 서버를 생성할때 생기는 fd(+1)
		nb += it->getOpenFd();  // 해당 서버와 연결된 클라이언트의 열려있는 fd만큼 +
	}
	return (nb);
}

/*!
 * @author	jinbkim, juhlee, sujlee
 * @param	buffer 앞으로 더 파싱을 해야할것들
 * @param	context 지시어 블록
 * @param	prec 현재 라인이 어떤 지시어 블록에 포함되어 있는지 (server{ or location / ~~ {)
 * @param	nb_line .conf 파일의 몇번째 줄인지
 * @param	config .conf 파일이 파싱한뒤 저장되는 map<string, map<string, string>> 타입 변수
 * @see		Config::parse()
 * @brief	.conf 파일에서 server 1개를 파싱하여 config 타입 변수에 저장
 */
void			Config::getContent(std::string &buffer, std::string &context, std::string prec, size_t &nb_line, config &config)
{
	std::string			line;  // .conf 파일의 한줄
	std::string			key;
	std::string			value;
	size_t				pos;
	size_t				tmp;

	// server{ => server 또는 location / ~~ { => location / ~~
	prec.pop_back();  // prec의 마지막 문자 제거 : ;

	// while (isspace(prec.back()))
	// 이게 더 괜찮아 보임
	// cpp 11
	while (prec.back() == ' ' || prec.back() == '\t')
		prec.pop_back();  // prec 뒤에있는 공백 제거
	context += prec + "|";  // context : server|location / ~~|
	// while (ft::isspace(line[0]))  // line은 이미 비어있는 상태임. 왜 이짓거리를 할까? (jinbkim)
	// 	line.erase(line.begin());
	while (line != "}" && !buffer.empty())
	{
		// line : buffer의 처음부터 첫 개행까지 저장됨
		// buffer는 처음부터 첫 개행까지 잘림
		ft::getline(buffer, line);
		nb_line++;  // // .conf 파일의 몇번째 줄인지 알려줌
		while (ft::isspace(line[0]))  // line 앞부분에 공백이 있으면 지움
			line.erase(line.begin());
		if (line[0] != '}')
		{
			pos = 0;
			/*
				server       {              
			=>	listen 	8080;
				error 	/Users/jinbkim/code/42webserv_comment/www/errorPages;
				location / {
					index 		oldindex.html;
					methods 	GET;
					root 		/Users/jinbkim/code/42webserv_comment/www/content;
					php 		/usr/local/bin/php-cgi;
				}
			
			=> key:listen, value:8080
			*/
			while (line[pos] && line[pos] != ';' && line[pos] != '{')
			{
				while (line[pos] && !ft::isspace(line[pos]))
					key += line[pos++];
				while (ft::isspace(line[pos]))
					pos++;
				while (line[pos] && line[pos] != ';' && line[pos] != '{')
					value += line[pos++];
			}
			tmp = 0;
			if (line[pos] != ';' && line[pos] != '{')
				throw(Config::InvalidConfigFileException(nb_line));
			else
				tmp++; // tmp 는 항상 1인데 굳이 이렇게 표현해야하나? (jinbkim)
			while (ft::isspace(line[pos + tmp]))  // line의 ';'나 '{' 의 뒤에 공백이 있으면 일단 넘어가기
				tmp++;
			if (line[pos + tmp])  // ';' or '{' or 공백 이후 '\0' 아닐 때 예외 처리
				throw(Config::InvalidConfigFileException(nb_line));
			/* 예시
				1. location / {
				2. index 	oldindex.html;
				3. methods 	GET;
				4. root 	/Users/jinbkim/code/42webserv_comment/www/content;
				5. php 		/usr/local/bin/php-cgi;
				}
			}
			*/
			else if (line[pos] == '{')  // 1
				/* getContent에 들어가는 인자의 상태
					buffer : 앞으로 더 파싱을 해야할것들
					context : server|
					line : location / ~~{
					nb_line : line이 .conf 파일의 몇번째 줄인지
					config : .conf 파일이 파싱한뒤 저장되는 map<string, map<string, string>>
				*/
				getContent(buffer, context, line, nb_line, config);
			else  // 2, 3, 4, 5
			{
				// context : server| or server|location / ~~|
				/* 
					server {
				=>	listen 	8080;
					error 	PWD/www/errorPages;
					location / {
						index 		oldindex.html;
						methods 	GET;
						root 		PWD/www/content;
						php 		/usr/local/bin/php-cgi;
					}

				=>	config(server|, listen, 8080)
				*/
				std::pair<std::string, std::string>	tmp(key, value);
				config[context].insert(tmp);
				key.clear();
				value.clear();
			}
		}
		else if (line[0] == '}' && !buffer.empty())
		{
			pos = 0;
			// line : }뒤에 공백만 있어도 에러가 발생하는 문제가 있음
			// while(line[1] && ft::isspace(line[1])) 으로 고칠 예정
			while (ft::isspace(line[++pos]))
				line.erase(line.begin()+1);
			// if (line[1]) 으로 고칠 예정
			if (line[pos])
				throw(Config::InvalidConfigFileException(nb_line));
	
			// context : server| => server => '\0' 또는 server|location / ~~| => server|location / ~~ => server|
			context.pop_back();
			context = context.substr(0, context.find_last_of('|') + 1);
		}
	}
	if (line[0] != '}')
		throw(Config::InvalidConfigFileException(nb_line));
}

Config::InvalidConfigFileException::InvalidConfigFileException(void) {this->line = 0;}

Config::InvalidConfigFileException::InvalidConfigFileException(size_t d) {
	this->line = d;
	this->error = "line " + std::to_string(this->line) + ": Invalid Config File";
}

Config::InvalidConfigFileException::~InvalidConfigFileException(void) throw() {}

size_t						Config::InvalidConfigFileException::getLine(void) const
{
	return (this->line);
}

const char					*Config::InvalidConfigFileException::what(void) const throw()
{
	if (this->line)
		return (error.c_str());
	return ("Invalid Config File");
}
