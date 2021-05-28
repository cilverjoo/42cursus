## 목표
- Dockerfile을 만들어 nginx, phpmyadmin, wordpress를 localhost 상에서 사용해보자.

## nginx
- 80번 포트로 접속을 시도할 경우 443번 포트로 리다이렉트 해 줄 것.
- openssl을 설치해 key와 certificate를 적절한 위치에 넣어주고 nginx가 인식하게 할 것.

## phpmyadmin
- wordpress와 연동할 데이터베이스를 만들고, phpmyadmin 상에서 수정된 내용은 wordpress에서도 적용되게 할 것.

## wordpress
- wordpress에서 적용한 변경사항은 phpmyadmin에 저장되어 유지되게 할 것.

```
  docker build -t "ft_server_image" ./
  docker run -it --name "ft_server" -p80:80 -p443:443 "ft_server_image"
  
  //만들어진 컨테이너를 실행할 때
  docker exec -it "ft_server" /bin/bash
```
