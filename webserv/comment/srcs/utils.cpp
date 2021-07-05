#include <string>
#include <iostream>
#include "Config.hpp"
#include "Server.hpp"

namespace ft
{

	bool	isspace(int c)
	{
		if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' ||
c == ' ')
			return (true);
		return (false);
	}

/*!
 * @author	jinbkim, hjung
 * @param	buffer 처음부터 첫번째 개행까지 잘림
 * @param	line buffer의 처음부터 첫번째 개행까지 저장됨
 * @see		Config.cpp, Handler.cpp, utils.cpp
 * @todo	쓸데없는 부분 주석처리 해둔거 나중에 지우기
 * @brief	buffer의 처음부터 개행까지 line에 저장되고 buffer는 처음부터 개행까지 잘림.
 * 			getline 함수가 이미 std에 있는데 새롭게 정의해서 쓴 이유는 github issue 참고하세요.
 */
	void	getline(std::string &buffer, std::string &line)
	{
		size_t					pos;

		pos = buffer.find("\n");  // buffer의 개행위치
		if (pos != std::string::npos)  // buffer에 개행이 있으면
		{
			//아래와 같이 인스턴스 명 없이 객체를 생성하는 것을 anonymous object 라고 합니다.
			//생성자가 호출되고 난 뒤 바로 소멸됩니다.
			line = std::string (buffer, 0, pos++);  // line : buffer의 처음부터 첫번째 개행까지
			buffer = buffer.substr(pos);  // buffer : 첫번째 개행 이후의 문자열이 buffer에 새롭게 저장됨.
		}
		else  //  buffer에 개행이 없으면
		{
			// if (buffer[buffer.size() - 1] == '\n')  // 개행이 없는 경우인데 마지막이 개행일때? (jinbkim)
			// 	buffer = buffer.substr(buffer.size());
			// else
			// {
				line = buffer;  // line에 buffer 그대로 넣기
				buffer = buffer.substr(buffer.size());  // buffer 비우기
			// }
		}
	}
/*!
 * @author	jinbkim, hjung
 * @param	buffer 처음부터 구분자인 첫번째 delim 까지 잘림
 * @param	line buffer의 처음부터 구분자인 첫번째 delim 까지 저장됨
 * @param	delim 함수의 구분자
 * @see		Config.cpp, Handler.cpp, utils.cpp
 * @todo	쓸데없는 부분 주석처리 해둔거 나중에 지우기
 * @brief	buffer의 처음부터 구분자인 첫번째 delim 까지 line에 저장되고 buffer는 처음부터 구분자인 첫번째 delim 까지 잘림.
 * 			getline 함수가 이미 std에 있는데 새롭게 정의해서 쓴 이유는 github issue 참고하세요.
 */
	void	getline(std::string &buffer, std::string &line, char delim)
	{
		size_t					pos;

		pos = buffer.find(delim);  // buffer의 첫번째 delim 위치
		if (pos != std::string::npos)  // buffer에 delim이 있으면
		{
			//아래와 같이 인스턴스 명 없이 객체를 생성하는 것을 anonymous object 라고 합니다.
			//생성자가 호출되고 난 뒤 바로 소멸됩니다.
			line = std::string (buffer, 0, pos++);  // line : buffer의 처음부터 첫번째 delim 까지
			buffer = buffer.substr(pos);  // buffer : 첫번째 delim 이후의 문자열이 buffer에 새롭게 저장됨.
		}
		else  //  buffer에 개행이 delim이 없으면
		{
			// if (buffer[buffer.size() - 1] == delim)  // delim이 없는 경우인데 마지막이 delim일때? (jinbkim)
				// buffer = buffer.substr(buffer.size());
			// else
			// {
				line = buffer;  // line에 buffer 그대로 넣기
				buffer = buffer.substr(buffer.size());  // buffer 비우기
			// }
		}
	}

	int		getpower(int nb, int power)
	{
		if (power < 0)
			return (0);
		if (power == 0)
			return (1);
		return (nb * getpower(nb, power - 1));
	}

/*!
 * @author jinbkim
 * @return 몇요일/몇일/몇월(영어)/몇년도 몇시:몇분:몇초 timezone
 * @see Client.cpp, HandlerMethods.cpp, Server.cpp
 * @brief 현재 시간 정보 반환
 */
	std::string		getDate()
	{
		struct timeval	time;
		struct tm		*tm;
		char			buf[BUFFER_SIZE + 1];
		int				ret;

		gettimeofday(&time, NULL);  // 1970-01-01 00:00:00 +0000 이후의 현재까지의 경과된 초와 micro 초 값이 time에 저장됨
		tm = localtime(&time.tv_sec);  // time.tv_sec를 기준으로 tm 구조체가 초기화됨
		// strftime : 시간을 원하는 형식으로 출력하기위해 사용
		// %a : 몇요일
		// %d : 몇일
		// %b : 몇월(영어)
		// %Y : 몇년도
		// %T : 몇시:몇분:몇초
		// %Z : timezone
		// buf : 몇요일/몇일/몇월(영어)/몇년도 몇시:몇분:몇초 timezone 이 저장됨
		ret = strftime(buf, BUFFER_SIZE, "%a, %d %b %Y %T %Z", tm);
		buf[ret] = '\0';
		return (buf);
	}

	void	freeAll(char **args, char **env)
	{
		free(args[0]);
		free(args[1]);
		free(args);
		int i = 0;
		while (env[i])
		{
			free(env[i]);
			++i;
		}
		free(env);
	}
}
