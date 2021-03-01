FROM alpine:3.12.0

RUN apk update && \
    apk add openssl vsftpd --no-cache && \
	apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache && \
    mkdir -p /ftps/ekim && \
    adduser --home=/ftps/ekim -D ekim && \
    echo "ekim:password" | chpasswd && \
    openssl req -x509 -nodes -days 365 \
	-newkey rsa:2048 -subj  "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=ekim/CN=127.0.0.1" \
	-keyout /etc/ssl/private/vsftpd.key -out /etc/ssl/certs/vsftpd.crt

RUN mkdir -p /etc/vsftpd

COPY ./srcs/vsftpd.conf /etc/vsftpd/vsftpd.conf
COPY ./srcs/start.sh /tmp/
COPY ./srcs/telegraf.conf /etc/telegraf/

EXPOSE 21 50021

ENTRYPOINT sh /tmp/start.sh