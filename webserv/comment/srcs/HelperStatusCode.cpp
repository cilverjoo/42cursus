#include "Helper.hpp"

/*!
 * @author yonglee
 * @param client 클라이언트, conf config 벡터
 * @return status가 OK이면 1, 그 외엔 0
 * @see HandlerMethods.cpp
 * @brief 각각의 Method에서 만날 수 있는 error를 체크한다.
 * @brief 문제가 없으면 client.req.status_code는 OK, 문제가 있으면 그에 따른 CODE가 주어진다.
 */

int			Helper::getStatusCode(Client &client)
{
	typedef int	(Helper::*ptr)(Client &client);
	std::map<std::string, ptr> 	map;
	std::string					credential;
	int							ret;
	map["GET"] = &Helper::GETStatus;
	map["HEAD"] = &Helper::GETStatus;
	map["PUT"] = &Helper::PUTStatus;
	map["POST"] = &Helper::POSTStatus;
	map["CONNECT"] = &Helper::CONNECTStatus;
	map["TRACE"] = &Helper::TRACEStatus;
	map["OPTIONS"] = &Helper::OPTIONSStatus;
	map["DELETE"] = &Helper::DELETEStatus;

	if (client.req.method != "CONNECT"
		&& client.req.method != "TRACE"
		&& client.req.method != "OPTIONS") // method가 CONNECT, TRACE, OPTIONS가 아니면. 즉, GET, HEAD, POST, PUT, DELETE, BAD 이면
	{
		client.res.version = "HTTP/1.1";
		client.res.status_code = OK;
		if (client.conf["methods"].find(client.req.method) == std::string::npos) //conf의 methods에 request.method가 없으면
			client.res.status_code = NOTALLOWED; // 405 허용되지 않는 http method 사용
		else if (client.conf.find("auth") != client.conf.end()) // conf에 "auth"가 있으면
		{
			client.res.status_code = UNAUTHORIZED; // 401 인증이 필요한 페이지. 아직 인증되지 않았음.
			if (client.req.headers.find("Authorization") != client.req.headers.end()) // request.headers에 Authorization이 있으면
			{
				credential = decode64(client.req.headers["Authorization"].c_str()); // 인코딩 된 값을 decoding하여 credential에 넣어줌
				if (credential == client.conf["auth"]) // 인증이 유효하면
					client.res.status_code = OK;
			}
		}
	}

	ret = (this->*map[client.req.method])(client); // method에 따라 Status를 받아옴. client.res.status_code가 ok로 유지되면 1, status가 변하면 0

	if (ret == 0)
		getErrorPage(client);
	return (ret);
}

/*!
 * @author yonglee
 * @param client 클라이언트, conf config 벡터
 * @return int
 * @see HelperStatusCode.cpp(getStatusCode)
 * @brief
 */

int			Helper::GETStatus(Client &client)
{
	struct stat		info;

	if (client.res.status_code == OK)
	{
		errno = 0;
		client.read_fd = open(client.conf["path"].c_str(), O_RDONLY);
		if (client.read_fd == -1 && errno == ENOENT) // 파일이나 디렉터리가 없으면
			client.res.status_code = NOTFOUND; // 404 요청한 페이지 없음
		else if (client.read_fd == -1) // 파일이 열리지 않으면
			client.res.status_code = INTERNALERROR; // 500 내부서버오류
		else // 파일이 열리면
		{
			fstat(client.read_fd, &info); // 열렸는지 확인
			if (!S_ISDIR(info.st_mode) // 디렉토리가 아니거나. 즉, 파일이거나
			|| (S_ISDIR(info.st_mode) && client.conf["listing"] == "on")) // 디렉토리면서 listing 키의 value값이 on으로
				return (1);
			else
				client.res.status_code = NOTFOUND; // 404 요청한 페이지 없음
		}
	}
	return (0);
}

int			Helper::POSTStatus(Client &client)
{
	int				fd;
	struct stat		info;
	// client.res.status_code 가 OK라는 건 getStatusCode()에서 NOTALLOWED나 UNAUTHORIZED에 빠지지 않았다는것
	// max_body가 conf에 정해져있고 그 값 보다 현재 들어온 요청의 body사이즈가 더 크다면 REQTOOLARGE로 상태 코드 입력
	if (client.res.status_code == OK && client.conf.find("max_body") != client.conf.end()
	&& client.req.body.size() > (unsigned long)atoi(client.conf["max_body"].c_str()))
		client.res.status_code = REQTOOLARGE;
	if (client.res.status_code == OK)
	{
		if (client.conf.find("CGI") != client.conf.end()
		&& client.req.uri.find(client.conf["CGI"]) != std::string::npos)
		{
			if (client.conf["exec"][0]) // ["exec"] 의 [0]은 뭐지..?(sebaek)
				client.read_fd = open(client.conf["exec"].c_str(), O_RDONLY); // PWD/cgi_tester
			else
				client.read_fd = open(client.conf["path"].c_str(), O_RDONLY); // config파일에 root가 있으면 PWD/www/content 없으면 요청한 uri의 location
			fstat(client.read_fd, &info);
			if (client.read_fd == -1 || S_ISDIR(info.st_mode))
				client.res.status_code = INTERNALERROR;
			else
				return (1);
		}
		else
		{
			errno = 0;
			fd = open(client.conf["path"].c_str(), O_RDONLY); // config파일에 root가 있으면 PWD/www/content 없으면 요청한 uri의 location
			if (fd == -1 && errno == ENOENT) // open()에서 O_CREAT 옵션을 안줬기때문에 경로에 파일이 없으면 errno가 2로 세팅되고 -1리턴됨
				client.res.status_code = CREATED; // 생성되지 않았을텐데? CREATED를 넣네? 왜냐면 있든 없든 이따 create할건데 지금 체크해야하는건 새로 만들어지는건지 아님 기존거에 append되는건지이기 때문
			else if (fd != -1)
				client.res.status_code = OK; // 오픈 성공해서 fd값 얻어왔으면 OK. 즉 이미 존재함
			close(fd); // 방금 연 파일 닫아주고
			client.write_fd = open(client.conf["path"].c_str(), O_WRONLY | O_APPEND | O_CREAT, 0666); // 이번엔 O_APPEND| O_CREAT플래그를 넣어서 이미 있으면 있는대로 연장해서 내용 써지고 없으면 만들어줄수있도록 open함
			if (client.write_fd == -1)
				client.res.status_code = INTERNALERROR; // 위 open이 실패하는건 예상치못한 내부적인 오류임. INTERNALERROR넣어줌
			else
				return (1);
		}
	}
	return (0); // status_code가 NOTALLOWED, UNAUTHORIZED, REQTOOLARGE인경우 0 리턴
}

int			Helper::PUTStatus(Client &client)
{
	int 		fd;
	struct stat	info;
	int			save_err;


	if (client.res.status_code == OK && client.conf.find("max_body") != client.conf.end()
	&& client.req.body.size() > (unsigned long)atoi(client.conf["max_body"].c_str()))
		client.res.status_code = REQTOOLARGE;
	else if (client.res.status_code == OK)
	{
		errno = 0;
		fd = open(client.conf["path"].c_str(), O_RDONLY);
		save_err = errno;
		fstat(fd, &info);
		if (S_ISDIR(info.st_mode)) // 디렉터리 파일인지
			client.res.status_code = NOTFOUND; // 디렉터리 파일이 아니면 return (0)
		else
		{
			if (fd == -1 && save_err == ENOENT) // 안 열리고 파일 또는 디렉터리가 없는 경우. 이 경우 앞에서 디렉터리인지 아닌지 확인했으므로 파일이 없는 경우이다.
				client.res.status_code = CREATED; // 파일 생성
			else if (fd == -1) // 호출시 서버 내부적 오류, 예상치 못한 에러 총칭
			{
				client.res.status_code = INTERNALERROR;
				return (0);
			}
			else // 열린 경우
			{
				client.res.status_code = NOCONTENT;
				if (close(fd) == -1) // 제대로 안 닫혔을 경우
				{
					client.res.status_code = INTERNALERROR;
					return (0);
				}
			}
			client.write_fd = open(client.conf["path"].c_str(), O_WRONLY | O_CREAT, 0666); // CREATED
			if (client.write_fd == -1) // 안 만들어졌을 경우
			{
				client.res.status_code = INTERNALERROR;
				return (0);
			}
			return (1); // 만들어졌을 경우
		}
	}
	return (0);
}

int			Helper::CONNECTStatus(Client &client)
{
	client.res.version = "HTTP/1.1";
	client.res.status_code = NOTIMPLEMENTED;
	return (0);
}

int			Helper::TRACEStatus(Client &client)
{
	client.res.version = "HTTP/1.1";
	if (client.conf["methods"].find(client.req.method) == std::string::npos)
	{
		client.res.status_code = NOTALLOWED;
		return (0);
	}
	else
	{
		client.res.status_code = OK;
		return (1);
	}
}

int			Helper::OPTIONSStatus(Client &client)
{
	client.res.version = "HTTP/1.1";
	client.res.status_code = NOCONTENT;
	return (1);
}

int			Helper::DELETEStatus(Client &client)
{
	int 		fd;
	struct stat	info;
	int			save_err;

	if (client.res.status_code == OK)
	{
		errno = 0;
		fd = open(client.conf["path"].c_str(), O_RDONLY);
		save_err = errno;
		fstat(fd, &info);
		if ((fd == -1 && save_err == ENOENT) || S_ISDIR(info.st_mode))
			client.res.status_code = NOTFOUND;
		else if (fd == -1)
			client.res.status_code = INTERNALERROR;
		else
			return (1);
	}
	return (0);
}
