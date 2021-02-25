FROM alpine:latest

RUN apk update && \
    apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache

RUN mkdir -p /etc/telegraf

ENV TELEGRAF_CONFIG_PATH /etc/telegraf/telegraf.conf:$TELEGRAF_CONFIG_PATH

CMD ["/usr/bin/telegraf"]