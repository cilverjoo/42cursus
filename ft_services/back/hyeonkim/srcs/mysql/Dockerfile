FROM alpine:3.12

RUN apk update
RUN apk add mariadb mariadb-client openrc
RUN apk add supervisor
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	chmod +x telegraf/telegraf && \
	cp telegraf/telegraf /usr/bin/ && \
	rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && \
	mkdir -p /etc/telegraf
# 생성된 컨테이너 안에서 지속적으로 실행해줘야하는 애들을 도커파일에 적으면 안되는 것 같다
# 7~17번 줄을 도커파일에 적었을 때와, setting.sh파일에 적어서 실행했을 때의 결과가 다르다.
# https://wiki.alpinelinux.org/wiki/Mysql 알파인 위키 참고
# RUN /usr/bin/mysql_install_db
# RUN /etc/init.d/mariadb setup
# RUN /etc/init.d/mariadb start 를 경로를 알아서 찾아서 실행해주는 명령어가 rc-service인가 보다.
# RUN openrc 
# # rc-service 명령을 실행하기 위해 openrc를 설치하고 실행해줘야 함
# RUN touch /run/openrc/softlevel
# # 위 파일을 만들어 줘야 rc-service mariacb " "가 실행이 된다.
# RUN mysql_install_db --user=root
# RUN rc-service mariadb setup
# # RUN rc-service mariadb start

# COPY /srcs/run.sh .
COPY /srcs/run.sh .
COPY /srcs/my.cnf /etc/mysql/my.cnf
COPY /srcs/setup.sh .
COPY /srcs/supervisord.conf  /etc/supervisord.conf
COPY /srcs/wordpress.sql .
COPY /srcs/telegraf.conf /etc/telegraf


# /lib/rc/sh/openrc-run.sh: line 279: can't create /sys/fs/cgroup/cpu/tasks: Read-only file system
# 위와 같은 오류를 방지하기 위해 볼륨 설정
VOLUME ["/sys/fs/cgroup"]

# EXPOSE 3306

CMD ["sh", "run.sh"]
#supervisor daemon을 사용하면 mysql pod restart가 거짓말처럼 사라진다.. 왜지?ㅠㅠ
#conf파일의 autorestart가 자동으로 재시작시켜주기 때문인가?
#프로세스와 pod가 어떤 차이가 있는지 알아봐야겠다.