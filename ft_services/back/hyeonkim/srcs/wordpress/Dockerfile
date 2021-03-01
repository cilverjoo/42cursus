FROM    alpine:3.12

RUN     apk update
RUN     apk add nginx
RUN     apk add php7 php7-fpm php7-opcache php7-gd php7-mysqli php7-zlib php7-curl php7-mbstring php7-json php7-session
RUN     apk add wget
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
        tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
        chmod +x telegraf/telegraf && \
        cp telegraf/telegraf /usr/bin/ && \
        rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && \
        mkdir -p /etc/telegraf

COPY    /srcs/nginx.conf    /etc/nginx/nginx.conf
COPY    /srcs/wp-config.php  .
COPY    /srcs/telegraf.conf /etc/telegraf/

COPY    /srcs/run.sh    .

RUN     mkdir /run/nginx

CMD     ["sh", "run.sh"]