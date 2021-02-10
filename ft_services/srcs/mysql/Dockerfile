FROM alpine:latest

RUN apk update && \
    apk add mysql mysql-client mariadb mariadb-client

RUN mkdir -p /run/mysqld

COPY ./srcs/my.cnf /etc/mysql/
COPY ./srcs/start.sh /tmp/

EXPOSE 3306

ENTRYPOINT sh /tmp/start.sh