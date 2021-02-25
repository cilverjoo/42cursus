FROM alpine:3.12.0

RUN apk update
RUN apk add influxdb --no-cache
RUN apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache
# RUN openrc && touch /run/openrc/softlevel && rc-update add telegraf

COPY ./srcs/telegraf.conf /etc/
COPY ./srcs/start.sh /tmp/

EXPOSE 8086

ENTRYPOINT sh /tmp/start.sh