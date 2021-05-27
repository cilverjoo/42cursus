## 쿠버네티스 활용하기
- 쿠버네티스를 활용하여 nginx, wordpress, phpmyadmin, ftps, grafana, mysql, influxdb를 관리해주는 파드를 만들고 각 파드들의 상태가 Running이 유지되도록 설정할 것.
- nginx 파드 따로, phpmyadmin와 wordpress 파드 내 nginx 설치를 별도로 실행하여 nginx 파드에서 phpmyadmin으로의 접근은 리다이렉트로, wordpress로의 접근은 포트를 통해서 진행되도록 할 것.
- influxdb, mysql의 데이터는 파드를 죽였다가 다시 생성해 보아도 유지되어야 한다.

#
<img width="787" alt="스크린샷 2021-05-27 오후 5 32 53" src="https://user-images.githubusercontent.com/64128985/119793977-0b031500-bf12-11eb-819e-ecce3e7feff3.png">


## metallb
별개의 컨테이너가 돌아가고 있는 파드 끼리의 통신을 가능하게 하려면 metallb가 필요하다.
metallb는 쿠버네티스에서 기본적으로 지원하는 기능이므로 metallb addon만 켜 주면 된다.
부가적인 설정은 metallb.yaml 파일을 적용하면 되는데, 하나의 ip 기반하여 포트를 바꿔가며 통신해야하는 본 서브젝트의 요구사항대로 구현하기 위해 annotation부분에 ip-share를 허용해주는 옵션을 달아주면 된다. 

## nginx, wordpress, phpmyadmin, mysql
wordpress의 데이터가 담겨있는 mysql 을 구동하고 wordpress와 phpmyadmin을 연결시켜야 한다.
먼저 mysql을 설치하고 phpmyadmin을 mysql 서버에 연동시킨 다음에 wordpress을 실행한다.
여기서 중요했던 점은, yaml 파일로 설정해 둔 service의 이름을 wordpress 설정 파일 내의 host로 넣어줘야 찾아서 연결해준다는 것이다.
wordpress를 실행하면 연동된 데이터베이스에 필요한 테이블들을 형성하는데, 과제에 맞게 몇 가지 내용만 수정한 다음 wordpress.db파일로 만들어서 빼 줬다.

참고
* https://wiki.alpinelinux.org/wiki/Nginx
* https://wiki.alpinelinux.org/wiki/Wordpress
* https://wiki.alpinelinux.org/wiki/PhpMyAdmin

## ftp

 ```
  mkdir -p /ftps/ekim                          //ekim 사용자의 home directory 생성
  adduser --home=/ftps/ekim -D ekim            // 유저 추가
  echo "ekim:password" | chpasswd              // 비밀번호 수정

  apk install vsftpd                           // alpine linux에 vsftpd 설치
 /usr/sbin/vsftpd /etc/vsftpd/vsftpd.conf      // userlist에 ekim이 추가된 conf파일을 인자로 넘겨준다.
 curl ftp://EXTERNAL-IP:21 --ssl -k --user ekim -T filename  //파일을 다음과 같이 보내주면 끝!
 ```

## grafana, influxdb, telegraf
각 파드들의 역할은 다음과 같다.
* telegraf는 파드들에서 넘어오는 cpu, memory 등 각종 데이터를 수집한다.
* influxdb는 시계열 데이터를 위한 DB이다.
* grafana는 시계열 데이터를 시각화해주는 웹 서비스이다.

따라서 telegraf로 수집한 각 파드들의 정보를 influxdb에 보내서 grafana로 선택한 데이터만 시각화해서 보여주면 된다.
각 파드마다 설치된 telegraf를 이용하여 telegraf.conf에서 input으로 모을 데이터의 종류를 지정하고, output으로 어떤 데이터베이스에 보낼 것이고 그 주소는 무엇인지 지정해준다.
telegraf의 갑작스러운 종료를 방지해주기 위해서 supervisor를 설치하여 만약 telegraf에 문제가 생길 시에 다시 시작하도록 지정해준다.

