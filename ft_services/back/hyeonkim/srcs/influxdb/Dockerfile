FROM alpine:3.12

RUN apk update
RUN apk add influxdb --no-cache
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
    tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
    chmod +x telegraf/telegraf && \
    cp telegraf/telegraf /usr/bin/ && \
    rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && \
    mkdir -p /etc/telegraf

COPY    /srcs/telegraf.conf /etc/telegraf/
COPY    /srcs/run.sh /

EXPOSE 8086

CMD ["sh", "run.sh"]