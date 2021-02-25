FROM alpine:3.12.0

RUN apk update
RUN apk add mysql mysql-client
RUN apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache

COPY ./srcs/my.cnf /etc/mysql/
COPY ./srcs/telegraf.conf /etc/
COPY ./srcs/start.sh /tmp/
COPY ./srcs/mysql_init /tmp/

EXPOSE 3306

ENTRYPOINT sh /tmp/start.sh