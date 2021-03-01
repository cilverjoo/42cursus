FROM alpine:3.12.0

RUN apk update
RUN apk add mariadb mariadb-client supervisor openrc
RUN apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache
RUN mkdir -p /run/openrc && touch /run/openrc/softlevel

COPY ./srcs/my.cnf /etc/mysql/
COPY ./srcs/telegraf.conf /etc/telegraf/
COPY ./srcs/supervisord.conf /etc/
COPY ./srcs/start.sh .
COPY ./srcs/run.sh .

EXPOSE 3306

ENTRYPOINT sh start.sh