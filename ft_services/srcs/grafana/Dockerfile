FROM alpine:3.12.0

RUN apk add grafana --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache
RUN apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache

COPY ./srcs/start.sh /tmp/
COPY ./srcs/dashboards /var/lib/grafana/dashboards/
COPY ./srcs/provisioning/dashboards/dashboard.yaml /usr/share/grafana/conf/provisioning/dashboards/
COPY ./srcs/provisioning/datasources/influxDB.yaml /usr/share/grafana/conf/provisioning/datasources/
COPY ./srcs/grafana.ini /etc/grafana/grafana.ini

WORKDIR	/usr/share/grafana

EXPOSE 3000

CMD sh /tmp/start.sh