FROM alpine:3.12.0

RUN apk update
RUN apk add influxdb --no-cache
RUN apk add supervisor --no-cache
RUN apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache

RUN mkdir -p /etc/telegraf
RUN mkdir -p /etc/influxdb

COPY ./srcs/telegraf.conf /etc/telegraf/telegraf.conf
COPY ./srcs/supervisord.conf /etc/supervisord.conf
# COPY ./srcs/influxdb.conf /etc/influxdb/influxdb.conf
COPY ./srcs/start.sh /tmp/

RUN chmod +x /tmp/start.sh

EXPOSE 8086 8088

ENTRYPOINT sh /tmp/start.sh