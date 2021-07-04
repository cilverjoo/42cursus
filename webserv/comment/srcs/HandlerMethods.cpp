#include <stdlib.h>
#include "utils.h"
#include "Handler.hpp"

void	Handler::dispatcher(Client &client)
{
	typedef void	(Handler::*ptr)(Client &client);
	std::map<std::string, ptr> map;

	map["GET"] = &Handler::handleGet;
	map["HEAD"] = &Handler::handleHead;
	map["PUT"] = &Handler::handlePut;
	map["POST"] = &Handler::handlePost;
	map["CONNECT"] = &Handler::handleConnect;
	map["TRACE"] = &Handler::handleTrace;
	map["OPTIONS"] = &Handler::handleOptions;
	map["DELETE"] = &Handler::handleDelete;
	map["BAD"] = &Handler::handleBadRequest;

	(this->*map[client.req.method])(client);
}

void	Handler::handleGet(Client &client)
{
	struct stat	file_info;

	switch (client.status)
	{
		case Client::CODE:
			_helper.getStatusCode(client);
			fstat(client.read_fd, &file_info);
			if (S_ISDIR(file_info.st_mode) && client.conf["listing"] == "on")
				createListing(client);
			if (client.res.status_code == NOTFOUND)
				negotiate(client);
			if (((client.conf.find("CGI") != client.conf.end() && client.req.uri.find(client.conf["CGI"]) != std::string::npos)
			|| (client.conf.find("php") != client.conf.end() && client.req.uri.find(".php") != std::string::npos))
			&& client.res.status_code == OK)
			{
				execCGI(client);
				client.status = Client::CGI;
			}
			else
				client.status = Client::HEADERS;
			client.setFileToRead(true);
			break ;
		case Client::CGI:
			if (client.read_fd == -1)
			{
				parseCGIResult(client);
				client.status = Client::HEADERS;
			}
			break ;
		case Client::HEADERS:
			lstat(client.conf["path"].c_str(), &file_info);
			if (!S_ISDIR(file_info.st_mode))
				client.res.headers["Last-Modified"] = _helper.getLastModified(client.conf["path"]);
			if (client.res.headers["Content-Type"][0] == '\0')
				client.res.headers["Content-Type"] = _helper.findType(client);
			if (client.res.status_code == UNAUTHORIZED)
				client.res.headers["WWW-Authenticate"] = "Basic";
			else if (client.res.status_code == NOTALLOWED)
				client.res.headers["Allow"] = client.conf["methods"];
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			client.status = Client::BODY;
			break ;
		case Client::BODY:
			if (client.read_fd == -1)
			{
				client.res.headers["Content-Length"] = std::to_string(client.res.body.size());
				createResponse(client);
				client.status = Client::RESPONSE;
			}
			break;
	}
}

/*!
 * @author yonglee
 * @param client 클라이언트, conf config 벡터
 * @return void
 * @see HandlerMethods.cpp(dispatcher)
 * @brief handleGet에서 BODY와 CGI를 제외한 코드.
 * @brief HEAD method는 BODY없이 응답코드와 HEAD만 체크하기 때문이다.
 * @brief 웹서버 정보확인, 헬스체크, 버전확인, 최종 수정일자 확인등의 용도로 사용된다.
 */

void	Handler::handleHead(Client &client)
{
	struct stat	file_info;

	switch (client.status)
	{
		case Client::CODE:
			_helper.getStatusCode(client); // client.req.status_code에 CODE주어짐. 문제없으면 OK
			fstat(client.read_fd, &file_info);
			if (S_ISDIR(file_info.st_mode) && client.conf["listing"] == "on")
				createListing(client);
			else if (client.res.status_code == NOTFOUND) // 요청한 페이지가 없으면
				negotiate(client);
			fstat(client.read_fd, &file_info);
			if (client.res.status_code == OK)
			{
				client.res.headers["Last-Modified"] = _helper.getLastModified(client.conf["path"]); // 마지막 수정시간으로 현재시간 반환
				client.res.headers["Content-Type"] = _helper.findType(client);
			}
			else if (client.res.status_code == UNAUTHORIZED)
				client.res.headers["WWW-Authenticate"] = "Basic";
			else if (client.res.status_code == NOTALLOWED)
				client.res.headers["Allow"] = client.conf["methods"];
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			client.res.headers["Content-Length"] = std::to_string(file_info.st_size);
			createResponse(client);
			client.status = Client::RESPONSE;
			break ;
	}
}

/*!
 * @author sebaek
 * @param Client
 * @return void
 * @see HandlerMethods.cpp Server.cpp
 * @brief client.req.method 가 "POST"일때 실행되는 메소드. 새 리소스 생성 혹은 프로세스 처리 목적.
 */
void	Handler::handlePost(Client &client)
{
	switch (client.status)
	{
		case Client::BODYPARSING:
			parseBody(client);
			break ;
		case Client::CODE:
			_helper.getStatusCode(client); // Post에서는 getStautsCode의 결과 자체가 중요하기보다 CGI여부와 status_code값이 중요함
			if (((client.conf.find("CGI") != client.conf.end() && client.req.uri.find(client.conf["CGI"]) != std::string::npos)
			|| (client.conf.find("php") != client.conf.end() && client.req.uri.find(".php") != std::string::npos))
			&& client.res.status_code == OK) // CGI이면서 OK라는건 client.conf["exec"] 혹은 client.conf["path"]를 경로로하는 read_fd가 세팅되었다는뜻.
			{
				execCGI(client); // 요청된 프로세스 실행
				client.status = Client::CGI;
				client.setFileToRead(true);
			}
			else // CGI가 아닌경우
			{
				if (client.res.status_code == OK || client.res.status_code == CREATED) // 들어온 메시지대로 파일에 써질수(POST) 있도록
					client.setFileToWrite(true); // write셋을 하게됨. CREATED냐 OK냐는 다음 처리 HEADERS에서 중요하게 보게됨
				else // NOTALLOWED, UNAUTHORIZED, REQTOOLARGE 인경우
					client.setFileToRead(true); // 오류 페이지 읽을수 있도록함(GetErrorPage)
				client.status = Client::HEADERS;
			}
			break ;
		case Client::CGI:
			if (client.read_fd == -1)
			{
				parseCGIResult(client);
				client.status = Client::HEADERS;
			}
			break ;
		case Client::HEADERS:
			if (client.res.status_code == UNAUTHORIZED)
				client.res.headers["WWW-Authenticate"] = "Basic";
			else if (client.res.status_code == NOTALLOWED)
				client.res.headers["Allow"] = client.conf["methods"];
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			if (client.res.status_code == CREATED)
				client.res.body = "File created\n";
			else if (client.res.status_code == OK && !((client.conf.find("CGI") != client.conf.end() && client.req.uri.find(client.conf["CGI"]) != std::string::npos)
			|| (client.conf.find("php") != client.conf.end() && client.req.uri.find(".php") != std::string::npos)))
				client.res.body = "File modified\n";
			client.status = Client::BODY;
			break ;
		case Client::BODY:
			if (client.read_fd == -1 && client.write_fd == -1)
			{
				if (client.res.headers["Content-Length"][0] == '\0')
					client.res.headers["Content-Length"] = std::to_string(client.res.body.size());
				createResponse(client);
				client.status = Client::RESPONSE;
			}
			break ;
	}
}

/*!
 * @author sebaek
 * @param Client
 * @return void
 * @see HandlerMethods.cpp Server.cpp
 * @brief client.req.method 가 "PUT"일때 실행되는 메소드. "PUT"요청이 가능한지 확인하고 수행. 수행 결과에 따라 client.res.headers에 적절한 값 넣어줌
 */
void	Handler::handlePut(Client &client)
{
	std::string		path;
	std::string		body;

	switch (client.status)
	{
		case Client::BODYPARSING:
			parseBody(client); // 따로 주어진 Content-Length 혹은 내용에 표기된 chunk_size만큼 client.req.body에 받아온다
			break ;
		case Client::CODE:
			if (_helper.getStatusCode(client)) // client.req.method가 실행 가능한지 각 경우에 따라 가능여부 파악해주고 실행해주는 함수. 지금의 경우 client.req.method 는 "PUT"이 될거고. HelperStatusCode.cpp참고
				client.setFileToWrite(true); // PUT이 가능하면 client의 write_fd를 fd_set인 wSet에 추가해줌
			else
				client.setFileToRead(true); // PUT이 가능하지 않다면 client의 read_fd를 fd_set인 rSet에 추가해줌. 이때 read_fd는 errorpage
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			if (client.res.status_code == CREATED || client.res.status_code == NOCONTENT) // status_code는 HelperStatusCode.cpp의 PUTStatus() 함수에서 값이 결정됨. PUT성공한경우 다음 실행
			{
				client.res.headers["Location"] = client.req.uri;
				if (client.res.status_code == CREATED)
					client.res.body = "Ressource created\n";
			}
			if (client.res.status_code == NOTALLOWED) // PUT결과 NOTALLOWED라면 다음 실행
				client.res.headers["Allow"] = client.conf["methods"]; // Allow하는 요청만 받겠다는걸 표시해주기위해 ["Allow"]에 client.conf["methods"] 적어줌. 참고: https://www.zerocho.com/category/HTTP/post/5b4c4e3efc5052001b4f519b
			else if (client.res.status_code == UNAUTHORIZED) // PUT결과 UNAUTHORIZED라면 다음 실행
				client.res.headers["WWW-Authenticate"] = "Basic"; // 401 UNAUTHORIZED는 클라이언트가 해당 리소스에 대한 유효한 인증 자격 증명이 없기 때문에 요청이 적용되지 않았음을 나타내는 응답코드. 이 상태는 WWW-Authenticate헤더와 함께 전송되며 올바르게 인증하는 방법에 대한 정보를 포함하고있음. Basic이 올바른 인증방법인가봄. 참고: https://developer.mozilla.org/ko/docs/Web/HTTP/Status/401
			client.status = Client::BODY;
			break ;
		case Client::BODY:
			if (client.write_fd == -1 && client.read_fd == -1) // 쓸거 다썼고 읽을것도 다 읽었다면
			{
				client.res.headers["Content-Length"] = std::to_string(client.res.body.size()); //Content-Length 헤더는 요청과 응답 메시지의 본문 크기를 바이트 단위로 표시해줌.
				createResponse(client); // client.res.version, client.res.status_code, client.res.header, client.res.body를 참조하여 필요한 양식대로 문자열을 구성해 client.response에 넣어주고 다써서 필요없어진 client.res를 clear해줌
				client.status = Client::RESPONSE; // BODY다음은 RESPONSE처리로 넘어가나봐
			}
			break ;
	}
}

/*!
 * @author sebaek
 * @param Client
 * @return void
 * @see HandlerMethods.cpp Server.cpp
 * @brief client.req.method 가 "CONNECT"일때(동적으로 터널모드를 교환, 프락시 기능 요청시 사용. 우린 이 기능 구현 안하는듯) 실행되는 메소드. 항상 NOTIMPLEMENTED로 501 에러 페이지 오픈해줌. 요청을 수행할수 있는 기능을 서버가 지원하지 않는다는것을 의미
 * 요청자에게 서버에서 기능이 지원될때 다시 확인해 볼 수 있도록 Retry-After헤더를 전송해줄 수도 있다는데 이건 구현하지 않은듯함
 */
void	Handler::handleConnect(Client &client)
{
	switch (client.status)
	{
		case Client::CODE:
			_helper.getStatusCode(client);// client.res.status_code = NOTIMPLEMENTED. 하고 501 에러 페이지를 read_fd에 open해줌. 참고: https://developer.mozilla.org/ko/docs/Web/HTTP/Status/501
			client.setFileToRead(true); // 에러페이지를 fd_set인 rSet에 등록해주고 다음 실행
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			client.status = Client::BODY;
			break ;
		case Client::BODY:
			if (client.read_fd == -1)
			{
				client.res.headers["Content-Length"] = std::to_string(client.res.body.size());
				createResponse(client);
				client.status = Client::RESPONSE;
			}
			break ;
	}
}

/*!
 * @author sebaek
 * @param Client
 * @return void
 * @see HandlerMethods.cpp Server.cpp
 * @brief client.req.method 가 "TRACE"일때(서버에 루프백 메시지 호출하기 위한 테스트용으로 사용하는 메소드) 실행되는 함수
 */
void	Handler::handleTrace(Client &client)
{
	switch (client.status)
	{
		case Client::CODE:
			_helper.getStatusCode(client); // TRACE가 Allow된 기능이면 client.res.status_code 에 OK넣어주고 아니라면 NOTALLOWED넣어주고 에러페이지를 read_fd에 오픈해줌
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			if (client.res.status_code == OK)
			{
				client.res.headers["Content-Type"] = "message/http"; // Content-Type헤더에 message/http 적고 밑에 바디 구성
				client.res.body = client.req.method + " " + client.req.uri + " " + client.req.version + "\r\n"; // TRACE 경로 버전
				for (std::map<std::string, std::string>::iterator it(client.req.headers.begin());
					it != client.req.headers.end(); ++it)
				{
					client.res.body += it->first + ": " + it->second + "\r\n"; // 헤더의 내용들 바디에 넣어줌
				}
			}
			else
				client.setFileToRead(true); // 에러페이지의 fd가저장된 read_fd를 fd_set인 rSet에 등록해줌
			client.status = Client::BODY;
			break ;
		case Client::BODY:
			if (client.read_fd == -1)
			{
				client.res.headers["Content-Length"] = std::to_string(client.res.body.size());
				createResponse(client);
				client.status = Client::RESPONSE;
			}
			break ;
	}
}

/*!
 * @author sebaek
 * @param Client
 * @return void
 * @see HandlerMethods.cpp Server.cpp
 * @brief client.req.method 가 "OPTIONS"일때(웹서버에서 지원되는 메소드의 종류를 확인할때) 사용되는 함수.
 */
void	Handler::handleOptions(Client &client)
{
	switch (client.status)
	{
		case Client::CODE:
			_helper.getStatusCode(client); // status_code에 NOCONTENT 넣어줌. HelperStatusCode.cpp에 OPTIONSStatus 참고
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			if (client.req.uri != "*")
				client.res.headers["Allow"] = client.conf["methods"];
			createResponse(client);
			client.status = Client::RESPONSE;
			break ;
	}
}

/*!
 * @author sebaek
 * @param Client
 * @return void
 * @see HandlerMethods.cpp Server.cpp
 * @brief client.req.method 가 "DELETE"일때(요청된 자원을 삭제할 것을 요청함) 실행되는 함수.
 */
void	Handler::handleDelete(Client &client)
{
	switch (client.status)
	{
		case Client::CODE:
			std::cout << "here\n";
			if (!_helper.getStatusCode(client)) // 여는데 실패하거나 존재하지 않는 파일인지 여부 client.res.status에 넣고, 존재하지 않거나 여는데 실패하면 에러페이지를 read_fd에 오픈해줌
				client.setFileToRead(true);
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			if (client.res.status_code == OK) // OK면 삭제
			{
				unlink(client.conf["path"].c_str());
				client.res.body = "File deleted\n";
			}
			else if (client.res.status_code == NOTALLOWED) // dispatcher단계에서 걸려서 deletestatus까지 가지못한경우에 해당
				client.res.headers["Allow"] = client.conf["methods"];
			else if (client.res.status_code == UNAUTHORIZED)
				client.res.headers["WWW-Authenticate"] = "Basic";
			client.status = Client::BODY;
			break ;
		case Client::BODY:
			if (client.read_fd == -1)
			{
				client.res.headers["Content-Length"] = std::to_string(client.res.body.size());
				createResponse(client);
				client.status = Client::RESPONSE;
			}
			break ;
	}
}

/*!
 * @author sebaek
 * @param Client
 * @return client.status에 따라 client.res.headers에 내용 넣어줌
 * @see HandlerMethods.cpp Server.cpp
 * @brief client.status가 CODE인 경우 에러페이지의 경로를 client.conf["path"]에 넣어주고 client.read_fd에 open한뒤 rSet에 등록해줌. BODY인경우 client.response에 적절한 양식에 따라 문자열 구성해줌
 */
void	Handler::handleBadRequest(Client &client)
{
	struct stat		file_info; // 파일 정보 담는 구조체

	switch (client.status)
	{
		case Client::CODE:
			client.res.version = "HTTP/1.1";
			client.res.status_code = BADREQUEST; // "400 Bad request" 를 status code에 넣어주고
			_helper.getErrorPage(client); // 400에 해당하는 에러 html페이지를 읽어 client.conf["path"]에 담고 이를 client.read_fd에 open()해줌
			fstat(client.read_fd, &file_info); // client.read_fd, 즉, 에러페이지의 파일정보를 file_info에 담아줌. 그런데 이 file_info를 뒤에 사용하질 않는데 왜 있는거지?
			client.setFileToRead(true); // client의 fd_set인 rSet에 read_fd 등록
			client.res.headers["Date"] = ft::getDate();
			client.res.headers["Server"] = "webserv";
			client.status = Client::BODY; // CODE 처리가 끝나면 BODY처리로 넘어가는 형식인가봄
			break ;
		case Client::BODY:
			if (client.read_fd == -1)
			{
				client.res.headers["Content-Length"] = std::to_string(client.res.body.size()); // Content-Length 헤더는 요청과 응답 메시지의 본문 크기를 바이트 단위로 표시해줌.
				createResponse(client); // client.res.version, client.res.status_code, client.res.header, client.res.body를 참조하여 필요한 양식대로 문자열을 구성해 client.response에 넣어주고 다써서 필요없어진 client.res를 clear해줌
				client.status = Client::RESPONSE; // BODY처리하면 다음은 RESPONSE 처리해줘야하나봐
			}
			break ;
	}
}
