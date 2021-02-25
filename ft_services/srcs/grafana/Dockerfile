FROM alpine:3.12.0

RUN apk add grafana --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache && \
	apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache

COPY ./srcs/telegraf.conf /etc/
COPY ./srcs/grafana.db /usr/share/grafana/data/
COPY ./srcs/start.sh /tmp/

WORKDIR	/usr/share/grafana

EXPOSE 3000

CMD sh /tmp/start.sh