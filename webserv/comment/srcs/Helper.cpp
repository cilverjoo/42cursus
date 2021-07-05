#include "utils.h"
#include "Helper.hpp"

/*!
 *  @author juhlee
 *  @see    Helper::decode64()
 *  @brief  char(8bit)로 표현 가능한 0~255 <=> Base64 변환할 때 사용하는 배열
 *  example>
 *  char 'T' = 84(ASCII code)
 *  B64index[84] = 19 (Base64 변환표에서 'T'의 값)
 */
static const int B64index[256] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,
0,  0,  0, 63,  0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

Helper::Helper()
{
	assignMIME();
}

Helper::~Helper()
{

}


/*!
 *	@author	sujlee
 *	@param	client 클라이언트 객체의 conf(= map<string, string>) 속성 사용
 *	@return	string
 *	@brief	Client 객체의 conf 속성 중, key 값이 "path"인 value의 파일확장자를 파싱.
 *	Handler::handleGet(), Handler::handleHead()에서 호출
 */
std::string		Helper::findType(Client &client)
{
	std::string 	extension;
	size_t			pos;

	if (client.conf["path"].find_last_of('.') != std::string::npos)	//path에 '.'문자가 있을 경우
	{
		pos = client.conf["path"].find('.');	//pos = path의 첫 번째 '.'문자 위치
		extension = client.conf["path"].substr(pos, client.conf["path"].find('.', pos + 1) - pos);	//extension = 첫 번째와 두 번째 '.' 사이의 값
		if (MIMETypes.find(extension) != MIMETypes.end())	//파싱한 확장자가 MIMETypes에 있을 경우
			return (MIMETypes[extension]);	//해당 확장자를 key로 가진 value를 return
		else
			return (MIMETypes[".bin"]);		//.bin의 value를 return
	}
	return ("");
}

/*!
 *	@author	sujlee
 *	@param	client 클라이언트 객체의 Response 구조체 사용
 *	@return	void
 *	@brief	Response 구조체의 status_code에 따라, 적절한 오류 페이지를 open().
 *	오류페이지의 path와 open() 결과는, 각각 Client의 path와 read_fd 속성에 할당.
 *	Handler::handleBadRequest(), Helper::getStatusCode()에서 호출
 */
void			Helper::getErrorPage(Client &client)
{
	std::string		path;

	path = client.conf["error"] + "/" + client.res.status_code.substr(0, 3) + ".html";	//
	client.conf["path"] = path;
	client.read_fd = open(path.c_str(), O_RDONLY);
}

/*!
 *	@author	sujlee
 *	@param	path	마지막 수정시간을 구하고 싶은 파일의 경로
 *	@return	string
 *	@brief	path 경로에 있는 파일의 마지막 수정시간으로써 현재 시간을 반환.
 *	Handler::handleGet(), Handler::handleHead()에서 호출
 */
std::string		Helper::getLastModified(std::string path)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	struct tm	*tm;
	struct stat	file_info;

	if (lstat(path.c_str(), &file_info) == -1)	//파일 호출 실패
		return ("");
	tm = localtime(&file_info.st_mtime);
	ret = strftime(buf, BUFFER_SIZE, "%a, %d %b %Y %T %Z", tm);	//포맷에 따라 현재시간을 buf에 할당
	buf[ret] = '\0';
	return (buf);	//현재시간 반환
}

/*!
 *	@author	sujlee
 *	@param	client 클라이언트 객체의 char *rBuf 사용
 *	@return	int
 *	@brief	rBuf의 첫 번째 문장을 파싱하여, 10진수 int 값으로 변환하여 반환.
 *	Handler::dechunkBody()에서 호출
 */
int				Helper::findLen(Client &client)
{
	std::string		to_convert;
	int				len;
	std::string		tmp;

	to_convert = client.rBuf;
	to_convert = to_convert.substr(0, to_convert.find("\r\n"));	//첫 번째 문장 파싱
	while (to_convert[0] == '\n')
		to_convert.erase(to_convert.begin());	//공백 라인 제거
	if (to_convert.size() == 0)
		len = 0;
	else
		len = fromHexa(to_convert.c_str());		//16진수 문자열 -> 10진수화
	len = fromHexa(to_convert.c_str());			//???
	tmp = client.rBuf;							//다음 문장으로 이동
	tmp = tmp.substr(tmp.find("\r\n") + 2);
	strcpy(client.rBuf, tmp.c_str());
	return (len);
}

/*!
 *	@author	juhlee
 *	@param	client 클라이언트 객체
 *	@return	void
 *  @todo 	strcpy를 통해 데이터 처리시 O(n)의 시간이 걸리므로 매우 비효율적. 포인터 방식으로 바꿀 것(?)
 *	@brief	클라이언트 객체의 read 버퍼 크기와 chunk 길이를 고려하여 request body의 내용을 채워주는 함수
 *	Handler::dechunkBody()에서 호출
 */
void			Helper::fillBody(Client &client)
{
	std::string		tmp;

	tmp = client.rBuf; // chunk_size\r\n(client.chunk.len) 다음 rBuf
	if (tmp.size() > client.chunk.len) // read 버퍼의 크기가 chunk 길이보다 길 때
	{
		client.req.body += tmp.substr(0, client.chunk.len); // read 버퍼의 내용을 chunk 길이만큼 request body에 붙여줌
		tmp = tmp.substr(client.chunk.len + 1);
		memset(client.rBuf, 0, BUFFER_SIZE + 1);
		strcpy(client.rBuf, tmp.c_str()); // request body에 붙인 이후 내용을 read 버퍼에 복사함
		client.chunk.len = 0;
		client.chunk.found = false;
	}
	else
	{
		client.req.body += tmp; // read 버퍼의 내용을 request body에 붙여줌
		client.chunk.len -= tmp.size(); // chunk 길이를 read 버퍼의 사이즈만큼 줄여줌
		memset(client.rBuf, 0, BUFFER_SIZE + 1);
	}
}

/*!
 *	@author	juhlee
 *	@param	nb 16진수 형식의 문자열
 *	@return	int type (파라미터 nb를 10진수 정수로 변환했을 때의 정수 값)
 *	@brief	16진수 형식의 문자열을 10진수 정수로 변환하는 함수
 *	Helper::findLen()에서 호출
 */
int				Helper::fromHexa(const char *nb)
{
	char	base[17] = "0123456789abcdef";
	char	base2[17] = "0123456789ABCDEF";
	int		result = 0;
	int		i;
	int		index;

	i = 0;
	while (nb[i])
	{
		int j = 0;
		while (base[j])
		{
			if (nb[i] == base[j]) // "0123456789abcdef" 중 일치하는 문자가 있을 경우
			{
				index = j;
				break ;
			}
			j++;
		}
		if (j == 16) // "0123456789abcdef" 중 일치하는 문자가 없었을 경우, 즉 대문자일 경우
		{
			j = 0;
			while (base2[j])
			{
				if (nb[i] == base2[j]) // "0123456789ABCDEF" 중 일치하는 문자가 있을 경우
				{
					index = j;
					break ;
				}
				j++;
			}
		}
		result += index * ft::getpower(16, (strlen(nb) - 1) - i);
		i++;
	}
	return (result);
}

/*!
 *  @author juhlee
 *  @param  data 클라이언트 객체의 request header의 'Authorization' 값
 *  @return string type (Base64 디코딩 결과 문자열)
 *  @brief  Base64로 인코딩된 클라이언트 객체의 request header의 'Authorization' 값을 문자열로 디코딩하는 함수
 *  인코딩 과정을 역으로 진행함
 *  :bulb: ref. https://devuna.tistory.com/41
 *  cf. 인코딩 과정
 *      (문자열 -> ASCII 2진수(8bit) -> 6bit로 쪼갠 후 자릿수 맞춰주기 위해 0으로 채움 -> Base64 index표에서 해당 문자 찾아 치환)
 *  Helper::getStatusCode()에서 호출
 */
std::string		Helper::decode64(const char *data)
{
	while (*data != ' ') // 첫번째 공백을 찾음
		data++;
	data++; // 첫번째 공백 이후에 디코딩할 'Authorization' 값이 나옴
	unsigned int len = strlen(data);
	unsigned char* p = (unsigned char*)data;
    int pad = len > 0 && (len % 4 || p[len - 1] == '='); // data의 길이가 4로 나누어 떨어지지 않거나 data의 마지막 문자가 '='일 때 패딩을 넣기 위함
    const size_t L = ((len + 3) / 4 - pad) * 4;
    std::string str(L / 4 * 3 + pad, '\0');
    for (size_t i = 0, j = 0; i < L; i += 4)
    {
        // Base64 치환 문자(6bit로 표현 가능) 4개를 비트 OR 연산
        int n = B64index[p[i]] << 18 | B64index[p[i + 1]] << 12 | B64index[p[i + 2]] << 6 | B64index[p[i + 3]];
        // 8bit로 변환
        str[j++] = n >> 16;
        str[j++] = n >> 8 & 0xFF;
        str[j++] = n & 0xFF;

        // example>
        // data = "TWFu"
        // Base64 index> T: 010011 W: 010110 F: 000101 u: 101110 // 6bit * 4 = 24bit
        // 8bit로 변환> 01001101 01100001 01101110  // 8bit * 3 = 24bit
        // ASCII> str[j] = M, str[j+1] = a, str[j+2] = n
    }
    if (pad) // 패딩 추가
    {
        int n = B64index[p[L]] << 18 | B64index[p[L + 1]] << 12;
        str[str.size() - 1] = n >> 16;

        if (len > L + 2 && p[L + 2] != '=')
        {
            n |= B64index[p[L + 2]] << 6;
            str.push_back(n >> 8 & 0xFF);
        }
    }
    if (str.back() == 0)
    	str.pop_back();
    return (str);
}

/*!
 * @author	jinbkim
 * @param	client 해당 Client객체의 Accept-Language의 value값을 사용
 * @param	map 해당 Client객체의 Accept-Language의 value값을 ',' 또는 ';'를 기준으로 쪼개어 map에 저장
 * @see		Handler::negotiate()
 * @brief	client의 Accept-Language value를 쪼개어 map에 저장
 * ;q= (q-인자 가중치) weight라고 불리는 상대적 품질 값을 사용해 표현되는 선호도에 따라 대체되는 값.
 * ex) Accept-Language: fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5
 */
void			Helper::parseAcceptLanguage(Client &client, std::multimap<std::string, std::string> &map)
{
	std::string							language;  // client의 Accept-Language의 value값이 ',' 또는 ';' 으로 쪼개어서 저장됨
	std::string							to_parse;  // client의 Accept-Language의 value값이 저장됨
	std::string							q;

	to_parse = client.req.headers["Accept-Language"];
	int i = 0;
	while (to_parse[i] != '\0')
	{
		language.clear();
		q.clear();
		// client의 Accept-Language 의 value값을 ',' 또는 ';'로 구분하고 쪼개어 language에 복사
		while (to_parse[i] && to_parse[i] != ',' && to_parse[i] != ';')
		{
			language += to_parse[i];
			++i;
		}

		// q값 세팅
		if (to_parse[i] == ',' || to_parse[i] == '\0') // 인자 가중치를 안 주면 1
			q = "1";
		else if (to_parse[i] == ';') // 인자 가중치가 있으면 q에 넣어줌.
		{
			i += 3; // ';q=' 넘어감
			while (to_parse[i] && to_parse[i] != ',')
			{
				q += to_parse[i];
				++i;
			}
		}

		if (to_parse[i])
			++i;
		// client의 Accept-Language의 value값을 통해얻은 q와 language를 인자로받은 map에 삽입
		std::pair<std::string, std::string>	pair(q, language); // multiset으로 같은 q를 가질 수 있다.
		map.insert(pair);
	}
}

/*!
 * @author	jinbkim
 * @param	client 해당 Client객체의 Accept-Charset의 value값을 사용
 * @param	map 해당 Client객체의 Accept-Charset의 value값을 ',' 또는 ';'를 기준으로 쪼개어 map에 저장
 * @see		Handler::negotiate()
 * @brief	client의 Accept-Charset value를 쪼개어 map에 저장
 */
void			Helper::parseAcceptCharset(Client &client, std::multimap<std::string, std::string> &map)
{
	std::string							charset;  // client의 Accept-Charset의 value값이 ',' 또는 ';' 으로 쪼개어서 저장됨
	std::string							to_parse;  // client의 Accept-Charset 의 value값이 저장됨
	std::string							q;

	to_parse = client.req.headers["Accept-Charset"];
	int i = 0;
	while (to_parse[i] != '\0')
	{
		charset.clear();
		q.clear();

		// client의 Accept-Charset 의 value값을 ',' 또는 ';'로 구분하고 쪼개어 charset에 복사
		while (to_parse[i] && to_parse[i] != ',' && to_parse[i] != ';')
		{
			charset += to_parse[i];
			++i;
		}

		// q값 세팅
		if (to_parse[i] == ',' || to_parse[i] == '\0')
			q = "1";
		else if (to_parse[i] == ';')
		{
			i += 3;
			while (to_parse[i] && to_parse[i] != ',')
			{
				q += to_parse[i];
				++i;
			}
		}

		if (to_parse[i])
			++i;

		// client의 Accept-Charset 의 value값을 통해얻은 q와 charset를 인자로받은 map에 삽입
		std::pair<std::string, std::string>	pair(q, charset);
		map.insert(pair);
	}
}

/*!
 * @author	jinbkim
 * @param	client key=value 형태이 문자열 배열로 가공될 Client객체
 * @return	key=value 형태인 문자열 배열
 * @see 	Handler::execCGI()
 * @brief	입력으로 받은 Client 객체를 바탕으로 가공하여 key=value 형태인 문자열 배열로 만듬
 */
char			**Helper::setEnv(Client &client)
{
	char											**env;  // 세팅된 envMap이 가공되어 저장될 문자열 배열
	std::map<std::string, std::string> 				envMap;  // 함수의 인자인 client의 정보를 바탕으로 세팅될 맵
	size_t											pos;

	// 함수의 인자인 client의 정보를 바탕으로 envMap 세팅
	envMap["GATEWAY_INTERFACE"] = "CGI/1.1";
	envMap["SERVER_PROTOCOL"] = "HTTP/1.1";
	envMap["SERVER_SOFTWARE"] = "webserv";
	envMap["REQUEST_URI"] = client.req.uri;
	envMap["REQUEST_METHOD"] = client.req.method;
	envMap["REMOTE_ADDR"] = client.ip;
	envMap["PATH_INFO"] = client.req.uri;
	envMap["PATH_TRANSLATED"] = client.conf["path"];
	envMap["CONTENT_LENGTH"] = std::to_string(client.req.body.size());

	if (client.req.uri.find('?') != std::string::npos)
		envMap["QUERY_STRING"] = client.req.uri.substr(client.req.uri.find('?') + 1);
	else
		envMap["QUERY_STRING"];
	if (client.req.headers.find("Content-Type") != client.req.headers.end())
		envMap["CONTENT_TYPE"] = client.req.headers["Content-Type"];
	if (client.conf.find("exec") != client.conf.end())
		envMap["SCRIPT_NAME"] = client.conf["exec"];
	else
		envMap["SCRIPT_NAME"] = client.conf["path"];
	if (client.conf["listen"].find(":") != std::string::npos)
	{
		envMap["SERVER_NAME"] = client.conf["listen"].substr(0, client.conf["listen"].find(":"));
		envMap["SERVER_PORT"] = client.conf["listen"].substr(client.conf["listen"].find(":") + 1);
	}
	else
		envMap["SERVER_PORT"] = client.conf["listen"];
	if (client.req.headers.find("Authorization") != client.req.headers.end())
	{
		pos = client.req.headers["Authorization"].find(" ");
		envMap["AUTH_TYPE"] = client.req.headers["Authorization"].substr(0, pos);
		envMap["REMOTE_USER"] = client.req.headers["Authorization"].substr(pos + 1);
		envMap["REMOTE_IDENT"] = client.req.headers["Authorization"].substr(pos + 1);
	}
	if (client.conf.find("php") != client.conf.end() && client.req.uri.find(".php") != std::string::npos)
		envMap["REDIRECT_STATUS"] = "200";

	std::map<std::string, std::string>::iterator b = client.req.headers.begin();
	while (b != client.req.headers.end())
	{
		envMap["HTTP_" + b->first] = b->second;
		++b;
	}

	env = (char **)malloc(sizeof(char *) * (envMap.size() + 1));  // 세팅된 envMap 크기만큼 env 동적할당
	std::map<std::string, std::string>::iterator it = envMap.begin();
	int i = 0;
	while (it != envMap.end())
	{
		env[i] = strdup((it->first + "=" + it->second).c_str());  // env에 envMap의 key값 + "=" + value값을 복사해서 한줄씩 넣기
		++i;
		++it;
	}
	env[i] = NULL;
	return (env);
}

/*!
 * @author	jinbkim
 * @see		Helper 객체의 생성자
 * @brief
 * std::map<std::string, std::string> MIMETypes;
 * MIMETypes 세팅
 */
void			Helper::assignMIME()
{
	MIMETypes[".txt"] = "text/plain";
	MIMETypes[".bin"] = "application/octet-stream";
	MIMETypes[".jpeg"] = "image/jpeg";
	MIMETypes[".jpg"] = "image/jpeg";
	MIMETypes[".html"] = "text/html";
	MIMETypes[".htm"] = "text/html";
	MIMETypes[".png"] = "image/png";
	MIMETypes[".bmp"] = "image/bmp";
	MIMETypes[".pdf"] = "application/pdf";
	MIMETypes[".tar"] = "application/x-tar";
	MIMETypes[".json"] = "application/json";
	MIMETypes[".css"] = "text/css";
	MIMETypes[".js"] = "application/javascript";
	MIMETypes[".mp3"] = "audio/mpeg";
	MIMETypes[".avi"] = "video/x-msvideo";
}
