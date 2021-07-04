#include "utils.h"
#include "Handler.hpp"

Handler::Handler()
{

}

Handler::~Handler()
{

}

/*!
 * @author	yonglee, jinbkim
 * @param	client request한 클라이언트
 * @param	conf request 당한 서버의 _conf(config 벡터)
 * @see		server.cpp(readRequest)
 * @brief	rBuf로부터 method, uri, version을 받아온다.
 * @brief	request.headers에 Host 의 Hostname 혹은 IP를 받아온다
 * @brief	syntax가 맞는지 체크한다.
 * @brief 	getConf를 통해 Hostname과 server_name이 일치하는 conf를 찾아 client로 가져온다.
 * @brief 	root 경로가 이으면 이동한다.
 * @brief 	method 형태에 따라 status 변경한다.
 * 			request한 client 데이터들을 파싱하여 config벡터 conf에 저장함
 */
void			Handler::parseRequest(Client &client, std::vector<config> &conf)
{
	Request				request; // messages.hpp
	std::string			tmp;
	std::string			buffer;  // 클라이언트에서 read한 데이터 char * rBuf를 string buffer에 저장

	buffer = std::string(client.rBuf); // rBuf를 buffer에 넣어줌 (rBuf : 클라이언트에서 read한 데이터)
	if (buffer[0] == '\r') // 앞이 CR이면
		buffer.erase(buffer.begin());
	if (buffer[0] == '\n') // 개행이면
		buffer.erase(buffer.begin());
	ft::getline(buffer, request.method, ' '); // 첫번째 단어가 request.method로 들어감
	ft::getline(buffer, request.uri, ' '); // 두번째 단어가 request.uri에 들어감
	ft::getline(buffer, request.version); // 세번째 단어가 request.version에 들어감
	if (parseHeaders(buffer, request)) // buffer에서 key와 value를 request.headers[key] = value 형태로 넣는다.
		request.valid = checkSyntax(request); // method, uri, version, headers의 형식을 맞춘다.
	if (request.uri != "*" || request.method != "OPTIONS") // OPTIONS만 uri가 "*"일 수 있다. OPTIONS이면서 "*"인 경우만 getConf를 실행하지 않는다.
	
	/* getConf 함수들어가기 전 인자 상태
		client : request한 클라이언트
		request : 클라이언트가 보낸 request 메시지를 파싱한 것
		conf : request 당한 서버의 _conf(config 벡터)
	*/
		// 클라이언트가 보낸 request 메시지를 파싱한 request를 바탕으로 서버에게 request한 클라이언트의 client.conf에 값 채우기
		getConf(client, request, conf); // server_name과 Host가 일치하는 config를 찾고 uri에 해당하는 elmt를 찾아 client.conf에 넣어줌
	if (request.valid) // checksyntax를 넘어오면
	{
		if (client.conf["root"][0] != '\0') // 경로가 있으면
			chdir(client.conf["root"].c_str()); // 경로로 이동
		if (request.method == "POST" || request.method == "PUT") // POST나 PUT이면 -> 자원을 생성 혹은 수정하기 위해.
			client.status = Client::BODYPARSING; // BODY를 PARSING해야한다. POST 나 PUT인경우 요청메시지(rBuf)에 body부분이 들어가게 되어있음
		else
			client.status = Client::CODE; // CODE로 넘어간다.
	}
	else // valid하지 않으면
	{
		request.method = "BAD";
		client.status = Client::CODE; // CODE로 넘어간다.
	}
	client.req = request; // request 정보를 client로 옮긴다.
	tmp = client.rBuf;
	tmp = tmp.substr(tmp.find("\r\n\r\n") + 4); // 개행 다음부터 tmp에 옮긴다. 이부분은 요청메시지의 body부분이됨
	strcpy(client.rBuf, tmp.c_str()); // 개행 다음부터를 rBuf에 다시 넣는다. rBuf는 char* 형이어서 strcpy를 통해 잘라줘야한다. 이제 rBuf 내용은 body부분만 담게됨. 없으면 없는거고
}

/*!
 * @author	yonglee, sebaek
 * @param	buf req
 * @return	header의 key와 value를 잘 넣어줬으면 True, 문제가 있으면 False
 * @see		Handler.cpp
 * @brief	client.rBuf의 header부분과 Request가 들어와서 key와 value는 req.headers에, 검증은 req.valid에 적용된다.
 * @brief	header는 key:( )value\r\n 형태여야한다. key 뒤에 공백이 있으면 안된다. : 와 value 사이엔 공백 1개만 존재한다.
 */
bool			Handler::parseHeaders(std::string &buf, Request &req)
{
	size_t		pos;
	std::string	line;
	std::string	key;
	std::string	value;

	while (!buf.empty())
	{
		ft::getline(buf, line); // 한 줄 받아옴
		if (line.size() < 1 || line[0] == '\n' || line[0] == '\r')
			break ;
		if (line.find(':') != std::string::npos) // :이 있으면
		{
			pos = line.find(':'); // line의 : 위치 찾기
			key = line.substr(0, pos); // key는 : 전까지
			if (line[pos + 1] == ' ') // : 다음이 ' '면
				value = line.substr(pos + 2); // ' ' 다음부터 value
			else
				value = line.substr(pos + 1); // 아니면 : 다음부터 value
			if (ft::isspace(value[0]) || ft::isspace(key[0]) || value.empty() || key.empty()) // value, key의 첫 글자가 space이면 안되고, 비어있으면 안된다.
			{
				req.valid = false;
				return (false);
			}
 			req.headers[key] = value; // header의 key 와 value map
 			req.headers[key].pop_back(); //remove '\r'. \n은 getline에서 제거
		}
		else // :가 없으면
		{
			req.valid = false; // error
			return (false);
		}
	}
	return (true);
}

/*!
 * @author yonglee
 * @param client
 * @return void
 * @see HandlerMethod(handlePost, handlePut), Server(readRequest)
 * @brief 따로 주어진 Content-Length 혹은 내용에 표기된 chunk_size만큼 client.req.body에 받아온다.
 * https://linuxism.ustd.ip.or.kr/783
 */

void			Handler::parseBody(Client &client)
{
	if (client.req.headers.find("Content-Length") != client.req.headers.end()) // client.req.headers에 "Content-Lenght"라는 key가 있으면
		getBody(client); // getBody 실행
	else if (client.req.headers["Transfer-Encoding"] == "chunked") // client.req.headers에 "Transfer-Encoding"의 value가 chunked이면. 즉, 분할전송방식을 채택한다면(sebaek)
		dechunkBody(client); // dechunkBody 실행. Chunked방식은 전체데이터를 나눠서 보내기 때문에 HTTP헤더엔 Content-Length헤더가 존재하지 않음.
	else // 길이를 구해올 수 없으면 error
	{
		client.req.method = "BAD";
		client.status = Client::CODE;
	}
	if (client.status == Client::CODE) // Bad request인경우 로그 찍어줌. 디버깅용
		g_logger.log("body size parsed from " + client.ip + ":" + std::to_string(client.port) + ": " + std::to_string(client.req.body.size()), MED);
}

/*!
 * @author yonglee
 * @param client
 * @return void
 * @see Handler.cpp(parseBody)
 * @brief Content-Length 만큼의 길이를 받은 다음 종료.
 */

void			Handler::getBody(Client &client)
{
	unsigned int	bytes;

	if (client.chunk.len == 0) // 길이가 0이면
		client.chunk.len = atoi(client.req.headers["Content-Length"].c_str()); // client.req.headers[Content-Length]의 value를 숫자로 치환.
	if (client.chunk.len < 0) // 0보다 작으면 BAD
	{
		client.req.method = "BAD";
		client.status = Client::CODE;
		return ;
	}
	bytes = strlen(client.rBuf); // rBuf 길이
	if (bytes >= client.chunk.len) // rBuf길이가 Content-Length보다 길면 읽을 만큼만 client.req.body에 받아옴
	{
		memset(client.rBuf + client.chunk.len, 0, BUFFER_SIZE - client.chunk.len); // client.chunk.len 뒤의 rBuf를 다 초기화
		client.req.body += client.rBuf; // rBuf를 넣어줌
		client.chunk.len = 0; // 초기화
		client.status = Client::CODE;
	}
	else // rBuf길이보다 읽어야 할 길이가 길면
	{
		client.chunk.len -= bytes; // client.chunk.len에서 rBuf의 길이만큼 뺌 = 못 읽는 문자열 길이 -> 이거 초기화를 왜 안 시킬까? 다음 getBody할 때 이 길이만큼 받아올 수 있도록 하기 위해.
		client.req.body += client.rBuf; // rBuf 전체를 client.req.body에 넣어줌
		memset(client.rBuf, 0, BUFFER_SIZE + 1); // 메모리 초기화
	}
}

/*!
 * @author yonglee
 * @param client
 * @return void
 * @see Handler.cpp(parseBody)
 * @brief chunk된 내용에서 주어진 길이만큼 내용을 받아온다.
 * chunk_size+개행+내용+개행+chunk_size... 의 반복
 * chunk가 여러번 되어있으면 반복해서 넣어줘야하는데 이러한 부분이 없다.
 */

void			Handler::dechunkBody(Client &client)
{
	if (strstr(client.rBuf, "\r\n") && client.chunk.found == false) // rBuf에 \r\n이 있고 client.chunk.found가 false면
	{
		client.chunk.len = _helper.findLen(client); // chunk_size 문자열로 되어있는 것을 실제 숫자로 변환. client의 rBuf는 \r\n 다음으로 이동.
		if (client.chunk.len == 0) // 길이가 0이면 끝.
			client.chunk.done = true;
		else // 길이가 있으면 찾음을 알림
			client.chunk.found = true;
	}
	else if (client.chunk.found == true) // /r/n을 찾으면
		_helper.fillBody(client); // client.req.body에 내용을 채움 client.rBuf는 읽은 만큼 넘어감.
	if (client.chunk.done) // chunk 완료. client.chunk.len = 0
	{
		memset(client.rBuf, 0, BUFFER_SIZE + 1); // 초기화
		client.status = Client::CODE;
		client.chunk.found = false; // chunk가 끝났으므로 초기화
		client.chunk.done = false;
		return ;
	}
}

//TO COMPLETE
/*!
 * @author	sebaek, yonglee, jinbkim
 * @param	client request한 클라이언트
 * @param	req 클라이언트에서 읽은 데이터를 파싱한 것
 * @param	conf request 당한 서버의 _conf(config 벡터)
 * @return	client.conf에 키 밸류를 구성해줌. 주요 키값으로 "path"가 있고 특수한 경우 "savedpath"가 생성됨(되는듯..)
 * @see		Handler.cpp
 * @brief	std::vector<config> 의 요소들 중 req.headers["Host"]와 "server_name"이 일치하는 config를 찾고, 여기서 req.uri에 해당하는 elmt요소를 찾아 이를 client.conf에 넣어줌. 상황에 따라 client.conf["path"]의 내용을 수정함
 * 			클라이언트에서 읽은 데이터를 파싱한 req를 바탕으로 서버에게 request한 클라이언트의 client.conf에 값 채우기
 */
void			Handler::getConf(Client &client, Request &req, std::vector<config> &conf)
{
	std::map<std::string, std::string> elmt;
	std::string		tmp;
	// std::string 	file;  // 사용하지 않아서 주석처리 해둠
	struct stat		info; // 파일관련 정보들을 담아주는 구조체
	config			to_parse; // <std::string, elmt>. 접속하려는 config(서버의 config 벡터 안에 있는 config 중 하나)

	// request가 valid하지 않다면 서버의 에러 페이지 경로를 담는 conf["error"] 키 밸류 생성해주고 return ;
	if (!req.valid)
	{
		client.conf["error"] = conf[0]["server|"]["error"];
		return ;
	}
	// config는 <string:elmt>형태의 맵. elmt는 <string:string>형태의 맵.
	// 따라서 (*it)["server|"]["server_name"] 은 config의 키값에 "server|"에 해당하는 elmt의 키값 "server_name"에 해당하는 밸류값임.
	// 반복문을 통해 config 벡터를 돌며 그 중 req.headers["Host"] 값과 위 elmt의 밸류값이 같은 config를 파싱해야하는것으로 지정, to_parse에 넣어줌.

	// 같은 포트를 listen 하는 경우 server_name으로 서버를 구분
	// Host를 명시해주면 그 서버로 접속
	// Host를 명시해주지 않으면 그냥 첫번째로 파싱한 서버로 접속
	std::vector<config>::iterator it(conf.begin());
	while (it != conf.end())
	{
		if (req.headers["Host"] == (*it)["server|"]["server_name"])  // Host를 명시해주면 그 서버로 접속
		{
			to_parse = *it;
			break ;
		}
		++it;
	}
	// 끝까지 돌아도 호스트와 같은 이름이 없을 수 있음. 그런경우 conf벡터의 첫번째 conf를 to_parse로 넣어줌...그래야하는 형태인가봄?
	if (it == conf.end())  // Host를 명시해주지 않으면 그냥 첫번째로 파싱한 서버로 접속
		to_parse = conf[0];
	// 사용하지 않아서 일단 주석처리 해둠
	// file = req.uri.substr(req.uri.find_last_of('/') + 1, req.uri.find('?')); // req.uri의 마지막 슬래쉬부터 ?까지의 문자열을 file에 넣어준다
	tmp = req.uri; // uri를통으로 넣어줌
	do // 아래 과정을 tmp가 비워지거나 elmt에 값을 넣게될때까지 반복
	{
		if (to_parse.find("server|location " + tmp + "|") != to_parse.end()) // to_parse에 "server|location " + uri통으로 넣은거 + "|" 이런문장의 key가 존재하면
		{
			elmt = to_parse["server|location " + tmp + "|"]; // 해당 부분의 밸류값, 즉 elmt를 넣어줌. config는 map<strinig,elmt> 였다는걸 기억해
			break ;
		}
		tmp = tmp.substr(0, tmp.find_last_of('/')); // uri통으로 넣어뒀던거에 마지막 /전까지 내용을 tmp에 다시 담아줌.
	} while (tmp != "");
	if (elmt.size() == 0) // tmp가 비워질때까지 찾지못해서 elmt에 값을 넣지 못한상황이라면
		// 어떻게 하면 이 조건문에 들어올까? (jinbkim)
		if (to_parse.find("server|location /|") != to_parse.end()) // tmp가 /인 경우를 보네...이런 처리는 왜 해주는걸까? 위에서 못잡아주니까 하는거같은데 왜 못잡지? (yonglee) 마지막 /를 지우고 찾기 때문에 /yonglee/였으면 tmp는 /yonglee -> ""가 되어서 /를 찾지 않기 때문
			elmt = to_parse["server|location /|"]; // 암튼 이런 경우면 elmt에 해당 키값 할당해줌
	/* elmt example
		location / {
	=>	index 		oldindex.html;
		methods 	GET;
		root 		/Users/jinbkim/code/42webserv_comment/www/content;
		php 		/usr/local/bin/php-cgi;

	=> elmt["index"] = oldindex.html
	} 
	*/

	// (4/16) jinbkim
	
	if (elmt.size() > 0) // elmt에 값이 들어있는 상태라면 비어있던 client.conf에 값이 채워짐
	{
		client.conf = elmt; // client.conf에 넣어주고 (client.conf는 <string:string>맵임. <string:elmt>와 헷갈리지 말라구..)
		client.conf["path"] = req.uri.substr(0, req.uri.find("?")); // req.uri의 0번째부터 ?전까지의 문자열을 client.conf["path"]에 넣어줌
		if (elmt.find("root") != elmt.end()) // 그런데 이때 elmt에 'root'키가 들어있다면
			client.conf["path"].replace(0, tmp.size(), elmt["root"]); // client.conf["path"]의 밸류값을 elmt['root']의 밸류값으로 바꿔줌
	}
	for (std::map<std::string, std::string>::iterator it(to_parse["server|"].begin()); it != to_parse["server|"].end(); ++it) // to_parse에서 "server|"를 키로 하는 elmt들을 돌며 다음을 수행
	{
		if (client.conf.find(it->first) == client.conf.end()) //it->first는 to_parse의 "server|"키에 해당하는 elmt밸류의 키값 스티링. 이를 client.conf.find로 찾는데 없으면
			client.conf[it->first] = it->second; // 키 밸류 만들어줌.
	}
	lstat(client.conf["path"].c_str(), &info); // lstat(파일의 절대경로 혹은 상대경로, &stat구조체) => 경로상의 파일의 정보를 얻어와 stat구조체에 값을 적어줌
	if (S_ISDIR(info.st_mode)) //S_ISDIR을 통해, 디렉토리 라면 if문으로 들어감("stat구조체.st_mode"는 파일이 디렉토리인가, 단순 파일인가, 케릭터디바이스인가를 리턴함)
	{
		// 언제 client.conf["listing"]이 on이 될까? (jinbkim)
		if (client.conf["index"][0] && client.conf["listing"] != "on") // "index"를 키로하는 밸류 스트링의 첫번째 문자(client.conf["index"][0])가 존재하고 "listing"을 키로하는 밸류 스트링이 "on"이 아닐경우
			client.conf["path"] += "/" + elmt["index"]; // 기존 client.conf["path"]의 내용에 / + elmt["index"] 의 스트링 추가
	}
	if (req.method == "GET")
		client.conf["savedpath"] = client.conf["path"]; // "path"의 밸류 스트링을 저장하는 "savedpath" 키 밸류 추가(혹은 갱신일수도있고..이건 elmt에 그게 있는지에 따를듯)
	g_logger.log("path requested from " + client.ip + ":" + std::to_string(client.port) + ": " + client.conf["path"], MED);
}

/*!
 * @author yonglee
 * @param client
 * @return void
 * @see HandlerMethod(handleGet, handleHead)
 * @brief Acccept-Language, Accept-Charset을 정리하고 우선순위부터 경로를 입력해 열린 파일대로 client.res.headers["Content-Location"], client.conf["path"]에 경로를 넣어준다.
 * https://blockdmask.tistory.com/88
 * multiset : 하나의 key로 여러 value를 가질 수 있다. 기본 오름차순 정렬이다. mul.equal_range(key)로 key의 원소들의 범위를 반환한다.
 * multiset을 사용하는 이유는 language는 같은 가중치를 갖는 여러 언어를 할당하기 위해.
 * charset은
 * https://www.zerocho.com/category/HTTP/post/5b3ba2d0b3dabd001b53b9db
 * Charset은 문자 인코딩(UTF-8 등)을 명시하는 부분이고, Language는 원하는 언어
 * https://word.tistory.com/14
 * reverse_iterator는 마지막 원소부터 첫번째 원소 이전가까지를 나타낸다.
 */

void			Handler::negotiate(Client &client)
{
	std::multimap<std::string, std::string> 	languageMap;
	std::multimap<std::string, std::string> 	charsetMap;
	int				fd = -1;
	std::string		path;
	std::string		ext;

	if (client.req.headers.find("Accept-Language") != client.req.headers.end())
		_helper.parseAcceptLanguage(client, languageMap); // <q(인자가중치), language>를 languageMap에 넣음.
	if (client.req.headers.find("Accept-Charset") != client.req.headers.end())
		_helper.parseAcceptCharset(client, charsetMap); // <q(인자가중치), charset>를 charsetMat에 넣음.
	if (!languageMap.empty()) // language가 있으면
	{
		for (std::multimap<std::string, std::string>::reverse_iterator it(languageMap.rbegin()); it != languageMap.rend(); ++it) // q = 1부터 시작. 1부터 우선순위 적용 fd가 한번 찾아졌으면 멈춰야 하는 것 아닐까?
		{
			if (!charsetMap.empty()) // charset이 있으면
			{
				for (std::multimap<std::string, std::string>::reverse_iterator it2(charsetMap.rbegin()); it2 != charsetMap.rend(); ++it2) // q = 1부터 시작. 1부터 우선순위 적용
				{
					ext = it->second + "." + it2->second; // language.charset
					path = client.conf["savedpath"] + "." + ext; // "client.conf["savedpath"]".language.charset
					fd = open(path.c_str(), O_RDONLY);
					if (fd != -1) // 파일을 못 읽으면
					{
						client.res.headers["Content-Language"] = it->second; // language
						break ;
					}
					ext = it2->second + "." + it->second; // charset.language
					path = client.conf["savedpath"] + "." + ext; // "client.conf["savedpath"]".charset.language
					fd = open(path.c_str(), O_RDONLY);
					if (fd != -1) // 파일을 못 읽으면
					{
						client.res.headers["Content-Language"] = it->second; // language
						break ;
					}
				}
			}
			else // charset이 없으면
			{
				ext = it->second; // language
				path = client.conf["savedpath"] + "." + ext; // "client.conf["savedpath"]".language
				fd = open(path.c_str(), O_RDONLY);
				if (fd != -1) // 파일을 못 읽으면
				{
					client.res.headers["Content-Language"] = it->second; // language
					break ;
				}
			}
		}
	}
	else if (languageMap.empty()) // language가 비어있으면
	{
		if (!charsetMap.empty()) // charset이 있으면
		{
			for (std::multimap<std::string, std::string>::reverse_iterator it2(charsetMap.rbegin()); it2 != charsetMap.rend(); ++it2) // q = 1부터 시작. 1부터 우선순위 적용
			{
				ext = it2->second; // charset
				path = client.conf["savedpath"] + "." + it2->second; // "client.conf["savedpath"]".charset
				fd = open(path.c_str(), O_RDONLY);
				if (fd != -1) // 파일을 못 읽으면
					break ;
			}
		}
	}
	if (fd != -1) // 파일을 열었으면
	{
		client.conf["path"] = path; // path를 넣어줌
		client.res.headers["Content-Location"] = client.req.uri + "." + ext; // client.req.uri(경로).ext
		if (client.read_fd != -1) // 기존에 열려있는 게 있으면
			close(client.read_fd); //닫음
		client.read_fd = fd; // 새로 열린 fd를 부여
		client.res.status_code = OK; //response.status_code OK
	}
}

/*!
 * @author sebaek
 * @param client
 * @return client.res.body에 html형식으로 감싸진 문자열로 채워줌
 * @see HandlerMethod.cpp
 * @brief Client.conf["path"]의 값을 참조하여 해당 경로의 디렉토리안에 있는 파일들을 html태그로 감싸서 client.res.body에 저장해주는 역할을 한다.
 */

//TO COMPLETE

void			Handler::createListing(Client &client)
{
	DIR				*dir;
	struct dirent	*cur;

	close(client.read_fd);
	client.read_fd = -1;
	dir = opendir(client.conf["path"].c_str());
	client.res.body = "<html>\n<body>\n";
	client.res.body += "<h1>Directory listing</h1>\n";
	while ((cur = readdir(dir)) != NULL)
	{
		if (cur->d_name[0] != '.')
		{
			client.res.body += "<a href=\"" + client.req.uri;
			if (client.req.uri != "/")
				client.res.body += "/";
			client.res.body += cur->d_name;
			client.res.body += "\">";
			client.res.body += cur->d_name;
			client.res.body += "</a><br>\n";
		}
	}
	closedir(dir);
	client.res.body += "</body>\n</html>\n";
}

//TO COMPLETE
/*!
 * @author	yonglee, sebaek
 * @param	req
 * @return	문제 없으면 true, 문제 있으면 false
 * @see		Handler.cpp
 * @brief	Request의 method, uri, version, headers를 체크한다.
 * @brief	method는 8개 중에 한개여야한다.
 * @brief	OPTION을 제외한 method는 uri가 /로 시작해야한다.
 * @brief	version은 "HTTP/1.1\r" 혹은 "HTTP/1.1"이어야한다.
 * @brief	headers의 key는 "Host"여야한다.
 */
bool			Handler::checkSyntax(const Request &req)
{

	if (req.method.size() == 0 || req.uri.size() == 0
		|| req.version.size() == 0)
		return (false);
	if (req.method != "GET" && req.method != "POST"
		&& req.method != "HEAD" && req.method != "PUT"
		&& req.method != "CONNECT" && req.method != "TRACE"
		&& req.method != "OPTIONS" && req.method != "DELETE")
		return (false);
	if (req.method != "OPTIONS" && req.uri[0] != '/') //OPTIONS can have * as uri option OPTIONS 만 / 가 uri로 안 와도 된다. 나머지는 모두 /부터 시작해야한다.
		return (false);
	if (req.version != "HTTP/1.1\r" && req.version != "HTTP/1.1") // version 규약
		return (false);
	if (req.headers.find("Host") == req.headers.end()) // headers에 Host가 없으면
		return (false);
	return (true);
}

/*!
 * @author jakang
 * @param Client
 * @return void
 * @see Handler::handlePost, Handler::handleGet
 * @todo
 * @brief CGI 처리, 외부 프로그램을 execve로 실행, 결과값은 파일로 저장되므로 별도로 읽는 작업 필요. (389줄 근처)
 */
void			Handler::execCGI(Client &client)
{
	char			**args = NULL;
	char			**env = NULL;
	std::string		path;
	int				ret;
	int				tubes[2];

	// path 값 설정
	if (client.conf["php"][0] && client.conf["path"].find(".php") != std::string::npos)
		path = client.conf["php"]; // conf에 php가 채워져있으면,
	else if (client.conf["exec"][0])
		path = client.conf["exec"]; // conf에 exec가 채워져있으면,
	else
		path = client.conf["path"]; // php 또는 exec 둘다 채워져있지 않으면,
	close(client.read_fd);
	client.read_fd = -1;
	// execve에 넘기기 위한 args 생성
	args = (char **)(malloc(sizeof(char *) * 3));
	args[0] = strdup(path.c_str()); // c_str은 string을 char *로 변경
	args[1] = strdup(client.conf["path"].c_str());
	args[2] = NULL;
	// execve에 넘길 env 생성 (key, value 형태 char **)
	env = _helper.setEnv(client);
	client.tmp_fd = open(TMP_PATH, O_WRONLY | O_CREAT, 0666);
	pipe(tubes);
	g_logger.log("executing CGI for " + client.ip + ":" + std::to_string(client.port), MED);
	if ((client.cgi_pid = fork()) == 0)
	{
		close(tubes[1]);
		dup2(tubes[0], 0);
		dup2(client.tmp_fd, 1);
		errno = 0;
		ret = execve(path.c_str(), args, env);
		if (ret == -1)
		{
			std::cerr << "Error with CGI: " << strerror(errno) << std::endl;
			exit(1);
		}
	}
	else
	{
		close(tubes[0]);
		client.write_fd = tubes[1];
		client.read_fd = open(TMP_PATH, O_RDONLY);
		client.setFileToWrite(true); // true이면 FD_SET으로 write_fd를 set
	}
	ft::freeAll(args, env); // args랑 env 모두 초기화
}

/*!
 * @author jakang
 * @param Client
 * @return void
 * @see Handler::handlePost, Handler::handleGet
 * @todo
 * @brief
 */
void		Handler::parseCGIResult(Client &client)
{
	size_t			pos;
	std::string		headers;
	std::string		key;
	std::string		value;

	// \r\n\r\n이 없으면 그냥 종료
	if (client.res.body.find("\r\n\r\n") == std::string::npos)
		return ;
	// 헤더 자르고, Status 부분 찾기
	headers = client.res.body.substr(0, client.res.body.find("\r\n\r\n") + 1);
	pos = headers.find("Status");
	if (pos != std::string::npos)
	{
		client.res.status_code.clear();
		pos += 8;
		// \r 만날때까지 pos += 8하면서 status_code에 집어넣음
		while (headers[pos] != '\r')
		{
			client.res.status_code += headers[pos];
			pos++;
		}
	}
	// key, value 나누기
	pos = 0;
	while (headers[pos])
	{
		while (headers[pos] && headers[pos] != ':')
		{
			key += headers[pos];
			++pos;
		}
		++pos;
		while (headers[pos] && headers[pos] != '\r')
		{
			value += headers[pos];
			++pos;
		}
		client.res.headers[key] = value;
		key.clear();
		value.clear();
		if (headers[pos] == '\r')
			pos++;
		if (headers[pos] == '\n')
			pos++;
	}
	// \r\n\r\n + 4부터 body
	pos = client.res.body.find("\r\n\r\n") + 4;
	client.res.body = client.res.body.substr(pos);
	// content length 부분을 body의 사이즈로 채우기
	client.res.headers["Content-Length"] = std::to_string(client.res.body.size());
}

/*!
 * @author sebaek
 * @param client
 * @return client.response에 필요한 양식대로 구성된 문자열을 넣어줌
 * @see HandlerMethod.cpp
 * @brief client.res.version, client.res.status_code, client.res.header, client.res.body를 참조하여 필요한 양식대로 문자열을 구성해 client.response에 넣어주고 다써서 필요없어진 client.res를 clear해줌.
 */

//TO COMPLETE
void		Handler::createResponse(Client &client)
{
	std::map<std::string, std::string>::const_iterator b;

	client.response = client.res.version + " " + client.res.status_code + "\r\n";
	b = client.res.headers.begin();
	while (b != client.res.headers.end())
	{
		if (b->second != "")
			client.response += b->first + ": " + b->second + "\r\n";
		++b;
	}
	client.response += "\r\n";
	client.response += client.res.body;
	client.res.clear();
}
