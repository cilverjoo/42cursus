FROM 	alpine:3.12

RUN     apk update
RUN     apk add grafana --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache
RUN     apk add wget
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
        tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
        chmod +x telegraf/telegraf && \
        cp telegraf/telegraf /usr/bin/ && \
        rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && \
        mkdir -p /etc/telegraf

COPY    srcs/dashboards /var/lib/grafana/dashboards/
COPY    srcs/provisioning/dashboards/dashboards.yml /usr/share/grafana/conf/provisioning/dashboards/
COPY    srcs/provisioning/datasources/influxdb.yml /usr/share/grafana/conf/provisioning/datasources/
COPY    srcs/telegraf.conf /etc/telegraf
COPY    srcs/run.sh .

EXPOSE  3000

CMD     ["sh", "run.sh"]

