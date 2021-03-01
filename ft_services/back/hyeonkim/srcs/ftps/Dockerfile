FROM    alpine:3.12

RUN     apk update
RUN     apk add openssl vsftpd --no-cache
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
        tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
        chmod +x telegraf/telegraf && \
        cp telegraf/telegraf /usr/bin/ && \
        rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && \
        mkdir -p /etc/telegraf

COPY    srcs/telegraf.conf /etc/telegraf
COPY    srcs/openssl.conf /etc/ssl/private/
COPY    srcs/vsftpd.conf /etc/vsftpd/vsftpd.conf
COPY    srcs/run.sh /

EXPOSE 20 21 31111 31112
CMD ["sh", "run.sh"]